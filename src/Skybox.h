//
// Created by Abomy on 4/29/2017.
//

#ifndef SE3D_SKYBOX_H
#define SE3D_SKYBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Program.h"
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <fstream>
#include "Renderable.h"
#include "BlenderOBJ.h"
#include "OBJManager.h"
#include "tools.h"
#include "Camera.h"


namespace se {



    struct SkyboxConfig {

    public:
        std::string VertexShader, FragmentShader, Directory;

        SkyboxConfig() {
            Sides->resize(6);
        }

        void Process(std::string key, std::string value) {
            if (key == "VertexShader")
                VertexShader = value;
            else if (key == "FragmentShader")
                FragmentShader = value;
            else if (key == "Ext")
                Ext = value;
            else if (key == "Front")
                Sides[0] = value;
            else if (key == "Back")
                Sides[1] = value;
            else if (key == "Top")
                Sides[2] = value;
            else if (key == "Bottom")
                Sides[3] = value;
            else if (key == "Left")
                Sides[4] = value;
            else if (key == "Right")
                Sides[5] = value;
        }

        std::string GetSide(int i) {
            return (Directory + Sides[i] + "." + Ext);
        }

    private:
        std::string Sides[6], Ext;

    };

    class Skybox {
    public:
        Skybox(std::string dir) { loadSkybox(dir); };

        void update()
        {
            _obj.rotateY(-0.00001f);
        }

    private:


        void loadSkybox(std::string dir) {

           // delete &_obj;
            float f = g_Camera.getClippingPlane() / 2;

            _obj = BlenderOBJ(se::OBJManager::requestOBJ("cube"));
            _obj.setType(SKYBOX);
            _obj.setPosition(glm::vec3(0,0,0));
            _obj.setScale(glm::vec3(f, f, f));
            _obj.initialise();


            //Setting the directory for assets
            config.Directory = tools::getWorkingDirectory() + "/content/images/skybox/" + dir + "/";

            if (openConfig(config.Directory)) {

                _obj.getProgram()->loadShaders(config.VertexShader, config.FragmentShader);

                createCubeMap(_obj.getTexture());

                //update();
            } else
                std::cerr << "Could not load skybox: " << dir << std::endl;
        }


        bool openConfig(std::string dir){
            std::ifstream configFile;
            configFile.open((dir + "skybox.ini").c_str());

            if (configFile.is_open()) {

                std::string line;
                while (getline(configFile, line)) {
                    if (line.size() > 0) {
                        int eIndex = line.find('=');
                        if (eIndex > 0) {
                            std::string key, value;
                            key = line.substr(0, eIndex);
                            value = line.substr(eIndex + 1);

                            //stripping line endings for MAC support
                            if (!value.empty() && value[value.size() - 1] == '\r')
                                value.erase(value.size() - 1);

                            config.Process(key, value);
                        }
                    }
                }
                configFile.close();
                return true;
            } else
                return false;
        }


        void createCubeMap(GLuint *tex_cube) {
            // generate a cube-map texture to hold all the sides
            glActiveTexture(GL_TEXTURE0);
            glGenTextures(1, tex_cube);

            // load each image and copy into a side of the cube-map texture

            /*GL_TEXTURE_CUBE_MAP_POSITIVE_X	Right
              GL_TEXTURE_CUBE_MAP_NEGATIVE_X	Left
              GL_TEXTURE_CUBE_MAP_POSITIVE_Y	Top
              GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	Bottom
              GL_TEXTURE_CUBE_MAP_POSITIVE_Z	Back
              GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	Front
            */
            loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, config.GetSide(0).c_str());
            loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, config.GetSide(1).c_str());
            loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, config.GetSide(2).c_str());
            loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, config.GetSide(3).c_str());
            loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, config.GetSide(4).c_str());
            loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, config.GetSide(5).c_str());

            // format cube map texture
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        bool loadSide(GLuint texture, GLenum side_target, const char *file_name) {

            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

            int x, y, n;
            int force_channels = 4;

            sf::Image *img_data = new sf::Image();
            if (!img_data->loadFromFile(file_name)) {
                std::fprintf(stderr, "Could not load '%s'.", file_name);
                return false;
            }

            x = img_data->getSize().x;
            y = img_data->getSize().y;
            // non-power-of-2 dimensions check
            if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
                fprintf(stderr,
                        "WARNING: image %s is not power-of-2 dimensions\n",
                        file_name);
            }

            // copy image data into 'target' side of cube map
            glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data->getPixelsPtr());
            return true;
        }

        SkyboxConfig config;

        se::BlenderOBJ _obj;



    };

}
#endif //SE3D_SKYBOX_H

