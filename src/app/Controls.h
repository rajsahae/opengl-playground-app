#pragma once

#include "glm/glm.hpp"

namespace controls
{
    struct VP {
        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
    };

    VP computeMatricesFromInputs(float deltaTime);
}
