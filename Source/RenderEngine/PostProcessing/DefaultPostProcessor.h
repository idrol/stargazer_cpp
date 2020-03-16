#pragma once

#include "PostProcessor.h"

class DefaultPostProcessor: public PostProcessor {
public:
    void doPostProcessing(GLuint texture) override;
};


