#include "Controls.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp" // glm::perspective
#include "glm/ext/matrix_transform.hpp" // glm::lookAt

namespace controls
{
    VP computeMatricesFromInputs(float deltaTime)
    {
        GLFWwindow* window = glfwGetCurrentContext();
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // position
        static glm::vec3 position = glm::vec3( 0, 0, 5 );
        // horizontal angle : toward -Z
        static float horizontalAngle = 3.14f;
        // vertical angle : 0, look at the horizon
        static float verticalAngle = 0.0f;
        // Initial Field of View
        static float initialFoV = 45.0f;

        static float speed = 3.0f; // 3 units / second
        static float mouseSpeed = 0.005f;

        // Get mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Hide the cursor
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Reset mouse position for next frame
        // glfwSetCursorPos(window, width/2, height/2);

        // Compute new orientation
        // horizontalAngle += mouseSpeed * deltaTime * float(width/2 - xpos );
        // verticalAngle   += mouseSpeed * deltaTime * float(height/2 - ypos );

        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
        );

        // Right vector
        glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
        );

        // Up vector : perpendicular to both direction and right
        glm::vec3 up = glm::cross( right, direction );

        // Move forward
        if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
            position += direction * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
            position -= direction * deltaTime * speed;
        }
        // Strafe right
        if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
            position += right * deltaTime * speed;
        }
        // Strafe left
        if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
            position -= right * deltaTime * speed;
        }

        // TODO: Get this working
        float FoV = initialFoV; // - 5 * glfwGetMouseWheel();

        // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 proj = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

        // Camera matrix
        glm::mat4 view = glm::lookAt(
            position,           // Camera is here
            position+direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
        );

        return VP { proj, view };
    }
}
