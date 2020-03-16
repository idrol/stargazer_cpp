//
// Created by Idrol on 29-09-2017.
//

#include "string_util.h"

std::vector<std::string> string_util::stringSplit(std::string str, std::string delimeter) {
    size_t pos = 0;
    std::vector<std::string> data;
    std::string token;
    while ((pos = str.find(delimeter)) != std::string::npos) {
        token = str.substr(0, pos);
        data.push_back(token);
        str.erase(0, pos + delimeter.length());
    }
    data.push_back(str);
    return data;
}