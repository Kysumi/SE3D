//
// Created by Abomy on 7/05/2017.
//

#include "WebRequest.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

namespace se {

    void WebRequest::fetchHighscores()
    {
        sf::Http http;
        http.setHost("http://149.56.98.94",7265);

        sf::Http::Request request("/se3d/api/gamerino/highscores", sf::Http::Request::Get);

        sf::Http::Response response = http.sendRequest(request);

        std::cout  << response.getBody() << std::endl;

        auto j3 = json::parse(response.getBody());

        std::cerr  << j3[0]["map_seed"] << std::endl;

    }

    void WebRequest::addHighscores(int id, std::string map_seed, int time) {

        sf::Http http;
        http.setHost("http://149.56.98.94",7265);

        sf::Http::Request request("/se3d/api/gamerino/highscores/add", sf::Http::Request::Post);
        // fill the request...

        std::ostringstream stream;
        stream << "player_id=" << id << "&map_seed=" << map_seed << "&time="<< time;
        request.setBody(stream.str());

        sf::Http::Response response = http.sendRequest(request);

        std::cout << "body: " << response.getBody() << std::endl;

    }


}