//
// Created by Abomy on 7/05/2017.
//

#ifndef SE3D_WEBREQUEST_H
#define SE3D_WEBREQUEST_H

#include <string>

namespace se {
    class WebRequest {
    public:
        WebRequest(){};
        static void fetchHighscores();
        static void addHighscores(int id, std::string map_seed, int time);
    };

}

#endif //SE3D_WEBREQUEST_H
