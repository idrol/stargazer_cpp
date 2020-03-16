#pragma once

#include <json.hpp>

class Mesh;
class Model;

class MeshFormatter {
public:
    static nlohmann::json serialize(Mesh *mesh);
    static void deserialize(nlohmann::json meshData, Model *model);
};


