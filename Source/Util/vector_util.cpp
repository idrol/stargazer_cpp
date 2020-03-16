#include <iostream>
#include "vector_util.h"

void vector_util::printVector(std::vector <std::string> vec) {
    for(int i=0; i<vec.size();i++) {
        std::cout << vec[i] << std::endl;
    }
}

void vector_util::printVector(std::vector<GLfloat> vec) {
    for(int i=0; i<vec.size();i++) {
        std::cout << vec[i] << std::endl;
    }
}
