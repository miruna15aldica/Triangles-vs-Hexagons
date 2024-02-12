#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateDiamond(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center - glm::vec3(length/2, 0, 0), color),
        VertexFormat(center + glm::vec3(0, length, 0), color),
        VertexFormat(center + glm::vec3(length / 2, 0, 0), color),
        VertexFormat(center - glm::vec3(0, length, 0), color)
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    diamond->InitFromData(vertices, indices);
    return diamond;
}


Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {

        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateHeart(std::string name, glm::vec3 baseCorner, float height, glm::vec3 color)
{
    glm::vec3 corner = baseCorner;
    float high = height;
    float low = 2 * height / 3;
    float len = height;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(len / 2, low, 0), color),
        VertexFormat(corner + glm::vec3(len / 4, high, 0), color),
        VertexFormat(corner + glm::vec3(0, low, 0), color),
        VertexFormat(corner + glm::vec3(-len / 4, high, 0), color),
        VertexFormat(corner + glm::vec3(-len / 2, low, 0), color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                            0, 2, 3,
                                            0, 3, 4,
                                            0, 4, 5
    };

    triangle->SetDrawMode(GL_TRIANGLES);

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateStar(
    const std::string& name, glm::vec3 baseCorner,
    float length,
    glm::vec3 color)
{


    std::vector<VertexFormat> vertices =
    {
        VertexFormat(baseCorner + glm::vec3(1.05 * length, 0.65 * length, 0), color),
        VertexFormat(baseCorner + glm::vec3(1.8 * length, 0.2 * length, 0), color), 
        VertexFormat(baseCorner + glm::vec3(1.42 * length, 0.82 * length, 0), color),
        VertexFormat(baseCorner + glm::vec3(2 * length, 1.25 * length, 0), color), 
        VertexFormat(baseCorner + glm::vec3(1.2 * length, 1.25 * length, 0), color), 
        VertexFormat(baseCorner + glm::vec3(1 * length,2 * length, 0), color), 
        VertexFormat(baseCorner + glm::vec3(0.82 * length, 1.255 * length, 0), color), 
        VertexFormat(baseCorner + glm::vec3(0, 1.25 * length, 0), color), 
        VertexFormat(baseCorner + glm::vec3(0.65 * length, 0.8 * length, 0), color), 
        VertexFormat(baseCorner + glm::vec3(0.2 * length, 0.2 * length, 0), color) 

    };

    std::vector<unsigned int> indices = { 5, 6, 4, 6, 7, 8, 6, 8, 4, 4, 8, 2, 4, 2, 3, 8, 9, 0, 8, 0, 2, 0, 1, 2 };

    Mesh* star = new Mesh(name);

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateHexagon(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < 6; ++i) {
        float x = center.x + radius * cos(glm::radians(60.0f * i));
        float y = center.y + radius * sin(glm::radians(60.0f * i));
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0.3f), color));
    }

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < vertices.size(); ++i)
        indices.push_back(i);

    for (unsigned int i = 1; i < vertices.size() - 1; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    hexagon->SetDrawMode(GL_TRIANGLES);
    hexagon->InitFromData(vertices, indices);

    return hexagon;
}

Mesh* object2D::CreateStar1(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0.83f * length, 0.65f * length, 0), color),
        VertexFormat(corner + glm::vec3(length * 0.32f, length * 0.32f, 0), color),
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length * 0.32f, length, 0), color),
        VertexFormat(corner + glm::vec3(length * 0.51f, length * 0.51f, 0), color),
        VertexFormat(corner + glm::vec3(length * 0.16f, length * 0.51, 0), color),
        VertexFormat(corner + glm::vec3(length * 0.32f, length, 0), color),
        VertexFormat(corner + glm::vec3(0.65f * length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length * 0.32f, length * 0.32f, 0), color),
        VertexFormat(corner + glm::vec3(-length * 0.16f, 0.65f * length, 0), color)
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 5, 6, 7, 8, 9, 0, 1, 2, 3, 4 };

    if (!fill) {
        star->SetDrawMode(GL_LINE_STRIP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);

    }

    star->InitFromData(vertices, indices);
    return star;
}


Mesh* object2D::CreateFlower(
    const std::string& name,
    glm::vec3 center,
    float radiusOuter,
    float radiusInner,
    glm::vec3 color)
{
    Mesh* star = new Mesh(name);
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    vertices.push_back(VertexFormat(center, color));

    for (int i = 0; i < 5; ++i) {
        float outerX = center.x + radiusOuter * cos(glm::radians(72.0f * i + 18));
        float outerY = center.y + radiusOuter * sin(glm::radians(72.0f * i + 18));
        vertices.push_back(VertexFormat(glm::vec3(outerX, outerY, 0), color));
        float innerX = center.x + radiusInner * cos(glm::radians(72.0f * i + 36.0f + 18));
        float innerY = center.y + radiusInner * sin(glm::radians(72.0f * i + 36.0f + 18));
        vertices.push_back(VertexFormat(glm::vec3(innerX, innerY, 0), color));
        indices.push_back(0);
        indices.push_back(i * 2 + 1);
        indices.push_back(i * 2 + 2);
    }

    star->SetDrawMode(GL_TRIANGLES);
    star->InitFromData(vertices, indices);
    return star;
}







