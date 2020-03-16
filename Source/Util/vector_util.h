#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>

class vector_util {
public:
    static void printVector(std::vector<std::string> vec);
    static void printVector(std::vector<GLfloat> vec);
};
