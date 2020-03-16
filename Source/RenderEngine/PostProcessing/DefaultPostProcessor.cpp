#include "DefaultPostProcessor.h"

void DefaultPostProcessor::doPostProcessing(GLuint texture) {
    start();
    finalizeRender(texture);
    end();
}