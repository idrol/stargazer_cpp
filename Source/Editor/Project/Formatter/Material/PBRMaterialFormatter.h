#pragma once

#include "MaterialFormatter.h"

class PBRMaterialFormatter: public MaterialFormatter {
public:
    nlohmann::json serialize(Material *material) override;
    void deserialize(nlohmann::json materialData, Mesh *mesh) override;
};


