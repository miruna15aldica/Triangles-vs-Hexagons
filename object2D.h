#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = true);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill = true);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = true);
    Mesh* CreateHeart(std::string name, glm::vec3 baseCorner, float height, glm::vec3 color);
    Mesh* CreateStar(const std::string& name, glm::vec3 baseCorner, float length, glm::vec3 color);
    Mesh* CreateHexagon(std::string name, glm::vec3 center, float radius, glm::vec3 color);
    Mesh* CreateStar1(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateFlower(const std::string& name, glm::vec3 center, float radiusOuter, float radiusInner, glm::vec3 color);
}
