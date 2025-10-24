#define _USE_MATH_DEFINES
#include "MeshFactory.h"
#include <cmath>
#include <glm/gtc/constants.hpp>

std::shared_ptr<Mesh> MeshFactory::CreateCube() {
	std::vector<float> vertices = {
        // Front face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        // Back face
        -0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,

        // Left face
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,

        // Right face
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,

        // Top face
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f
	};

    return std::make_shared<Mesh>(vertices);
}

std::shared_ptr<Mesh> MeshFactory::CreateQuad() {
    std::vector<float> vertices = {
        -0.5f, 0.0f, -0.5f,
         0.5f, 0.0f, -0.5f,
         0.5f, 0.0f,  0.5f,
        -0.5f, 0.0f, -0.5f,
         0.5f, 0.0f,  0.5f,
        -0.5f, 0.0f,  0.5f
    };

    return std::make_shared<Mesh>(vertices);
}

std::shared_ptr<Mesh> MeshFactory::CreateSphere(int segments, int rings) {
    std::vector<float> vertices;
    for (int y = 0; y <= rings; ++y) {
        float v = (float)y / rings;
        float phi = v * glm::pi<float>();
        for (int x = 0; x <= segments; ++x) {
            float u = (float)x / segments;
            float theta = u * glm::two_pi<float>();

            float xPos = std::cos(theta) * std::sin(phi);
            float yPos = std::cos(phi);
            float zPos = std::sin(theta) * std::sin(phi);

            vertices.push_back(xPos * 0.5f);
            vertices.push_back(yPos * 0.5f);
            vertices.push_back(zPos * 0.5f);
        }
    }

    // ring into triangle
    std::vector<float> finaVerts;
    for (int y = 0; y < rings; ++y) {
        for (int x = 0; x < segments; ++x) {
            int i0 = y * (segments + 1) + x;
            int i1 = i0 + segments + 1;

            glm::vec3 v0(vertices[i0 * 3 + 0], vertices[i0 * 3 + 1], vertices[i0 * 3 + 2]);
            glm::vec3 v1(vertices[i1 * 3 + 0], vertices[i1 * 3 + 1], vertices[i1 * 3 + 2]);
            glm::vec3 v2(vertices[(i0 + 1) * 3 + 0], vertices[(i0 + 1) * 3 + 1], vertices[(i0 + 1) * 3 + 2]);
            glm::vec3 v3(vertices[(i1 + 1) * 3 + 0], vertices[(i1 + 1) * 3 + 1], vertices[(i1 + 1) * 3 + 2]);

            auto addTri = [&](glm::vec3 v) {
                finaVerts.push_back(v.x);
                finaVerts.push_back(v.y);
                finaVerts.push_back(v.z);
            };

            addTri(v0); addTri(v1); addTri(v2);
            addTri(v2); addTri(v1); addTri(v3);
        }
    }

    return std::make_shared<Mesh>(finaVerts);
}

std::shared_ptr<Mesh> MeshFactory::CreateCylinder(float radius, float height, int segments) {
    std::vector<float> vertices;

    float halfHeight = height * 0.5f;
    float angleStep = 2.0f * M_PI / segments;

    // side quads
    for (int i = 0; i < segments; i++) {
        float theta = i * angleStep;
        float nextTheta = (i + 1) * angleStep;

        glm::vec3 p0(radius * cos(theta), -halfHeight, radius * sin(theta));
        glm::vec3 p1(radius * cos(nextTheta), -halfHeight, radius * sin(nextTheta));
        glm::vec3 p2(radius * cos(nextTheta), halfHeight, radius * sin(nextTheta));
        glm::vec3 p3(radius * cos(theta), halfHeight, radius * sin(theta));

        // triangle 1
        vertices.insert(vertices.end(), { p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z });
        // triangle 2
        vertices.insert(vertices.end(), { p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p0.x, p0.y, p0.z });
    }

    // top circle
    glm::vec3 topCenter(0, halfHeight, 0);
    for (int i = 0; i < segments; i++) {
        float theta = i * angleStep;
        float nextTheta = (i + 1) * angleStep;

        glm::vec3 p0(radius * cos(theta), halfHeight, radius * sin(theta));
        glm::vec3 p1(radius * cos(nextTheta), halfHeight, radius * sin(nextTheta));

        vertices.insert(vertices.end(), { topCenter.x, topCenter.y, topCenter.z,
                                         p0.x, p0.y, p0.z,
                                         p1.x, p1.y, p1.z });
    }

    // bottom circle
    glm::vec3 bottomCenter(0, -halfHeight, 0);
    for (int i = 0; i < segments; i++) {
        float theta = i * angleStep;
        float nextTheta = (i + 1) * angleStep;

        glm::vec3 p0(radius * cos(nextTheta), -halfHeight, radius * sin(nextTheta));
        glm::vec3 p1(radius * cos(theta), -halfHeight, radius * sin(theta));

        vertices.insert(vertices.end(), { bottomCenter.x, bottomCenter.y, bottomCenter.z,
                                         p0.x, p0.y, p0.z,
                                         p1.x, p1.y, p1.z });
    }

    return std::make_shared<Mesh>(vertices);
}
