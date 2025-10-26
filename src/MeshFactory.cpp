#define _USE_MATH_DEFINES
#include "MeshFactory.h"
#include <cmath>
#include <glm/gtc/constants.hpp>

static void AddTriangle(std::vector<float>& vertices, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
    glm::vec3 verts[3] = { v0, v1, v2 };
    for (int i = 0; i < 3; i++) {
        vertices.push_back(verts[i].x);
        vertices.push_back(verts[i].y);
        vertices.push_back(verts[i].z);
    }
}

std::shared_ptr<Mesh> MeshFactory::CreateCube(float size) {
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

std::shared_ptr<Mesh> MeshFactory::CreateQuad(float size) {
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

std::shared_ptr<Mesh> MeshFactory::CreateSphere(int segments, int rings, float radius) {
    std::vector<float> vertices;
    for (int y = 0; y <= rings; ++y) {
        float v = (float)y / rings;
        float phi = v * glm::pi<float>();
        for (int x = 0; x <= segments; ++x) {
            float u = (float)x / segments;
            float theta = u * glm::two_pi<float>();

            float xPos = std::cos(theta) * std::sin(phi) * radius;
            float yPos = std::cos(phi) * radius;
            float zPos = std::sin(theta) * std::sin(phi) * radius;

            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);
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

            AddTriangle(finaVerts, v0, v1, v2);
            AddTriangle(finaVerts, v2, v1, v3);
        }
    }

    return std::make_shared<Mesh>(finaVerts);
}

std::shared_ptr<Mesh> MeshFactory::CreateCylinder(float radius, float height, int segments)  {
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
        AddTriangle(vertices, p0, p1, p2);
        // triangle 2
        AddTriangle(vertices, p2, p3, p0);
    }

    // top circle
    glm::vec3 topCenter(0, halfHeight, 0);
    for (int i = 0; i < segments; i++) {
        float theta = i * angleStep;
        float nextTheta = (i + 1) * angleStep;

        glm::vec3 p0(radius * cos(theta), halfHeight, radius * sin(theta));
        glm::vec3 p1(radius * cos(nextTheta), halfHeight, radius * sin(nextTheta));

        AddTriangle(vertices, topCenter, p0, p1);
    }

    // bottom circle
    glm::vec3 bottomCenter(0, -halfHeight, 0);
    for (int i = 0; i < segments; i++) {
        float theta = i * angleStep;
        float nextTheta = (i + 1) * angleStep;

        glm::vec3 p0(radius * cos(nextTheta), -halfHeight, radius * sin(nextTheta));
        glm::vec3 p1(radius * cos(theta), -halfHeight, radius * sin(theta));

        AddTriangle(vertices, bottomCenter, p0, p1);
    }

    return std::make_shared<Mesh>(vertices);
}

std::shared_ptr<Mesh> MeshFactory::CreateCapsule(int segments, int rings, float radius, float height) {
    std::vector<float> vertices;

    if (height < 2.0f * radius)
        height = 2.0f * radius;

    float halfCylHeight = (height / 2.0f) - radius;

    auto addTri = [&](glm::vec3 v) {
        vertices.push_back(v.x);
        vertices.push_back(v.y);
        vertices.push_back(v.z);
        };

    std::vector<glm::vec3> points;

    // ===== Cylinder =====
    for (int y = 0; y <= 1; ++y) {
        float ypos = (y == 0 ? -halfCylHeight : halfCylHeight);
        for (int x = 0; x <= segments; ++x) {
            float theta = (float)x / segments * glm::two_pi<float>();
            float xPos = std::cos(theta) * radius;
            float zPos = std::sin(theta) * radius;
            points.emplace_back(xPos, ypos, zPos);
        }
    }

    // Triangulate cylinder
    for (int x = 0; x < segments; ++x) {
        int i0 = x;
        int i1 = x + segments + 1;
        int i2 = i0 + 1;
        int i3 = i1 + 1;

        addTri(points[i0]);
        addTri(points[i1]);
        addTri(points[i2]);

        addTri(points[i2]);
        addTri(points[i1]);
        addTri(points[i3]);
    }

    // ===== Top hemisphere =====
    for (int y = 0; y < rings / 2; ++y) {
        float v0 = (float)y / (rings / 2);
        float v1 = (float)(y + 1) / (rings / 2);
        float phi0 = v0 * glm::half_pi<float>();
        float phi1 = v1 * glm::half_pi<float>();

        for (int x = 0; x < segments; ++x) {
            float u0 = (float)x / segments;
            float u1 = (float)(x + 1) / segments;
            float theta0 = u0 * glm::two_pi<float>();
            float theta1 = u1 * glm::two_pi<float>();

            glm::vec3 v00 = { std::cos(theta0) * std::sin(phi0) * radius, std::cos(phi0) * radius + halfCylHeight, std::sin(theta0) * std::sin(phi0) * radius };
            glm::vec3 v10 = { std::cos(theta1) * std::sin(phi0) * radius, std::cos(phi0) * radius + halfCylHeight, std::sin(theta1) * std::sin(phi0) * radius };
            glm::vec3 v01 = { std::cos(theta0) * std::sin(phi1) * radius, std::cos(phi1) * radius + halfCylHeight, std::sin(theta0) * std::sin(phi1) * radius };
            glm::vec3 v11 = { std::cos(theta1) * std::sin(phi1) * radius, std::cos(phi1) * radius + halfCylHeight, std::sin(theta1) * std::sin(phi1) * radius };

            addTri(v00); addTri(v01); addTri(v10);
            addTri(v10); addTri(v01); addTri(v11);
        }
    }

    // ===== Bottom hemisphere =====
    for (int y = 0; y < rings / 2; ++y) {
        float v0 = (float)y / (rings / 2);
        float v1 = (float)(y + 1) / (rings / 2);
        float phi0 = v0 * glm::half_pi<float>();
        float phi1 = v1 * glm::half_pi<float>();

        for (int x = 0; x < segments; ++x) {
            float u0 = (float)x / segments;
            float u1 = (float)(x + 1) / segments;
            float theta0 = u0 * glm::two_pi<float>();
            float theta1 = u1 * glm::two_pi<float>();

            glm::vec3 v00 = { std::cos(theta0) * std::sin(phi0) * radius, -std::cos(phi0) * radius - halfCylHeight, std::sin(theta0) * std::sin(phi0) * radius };
            glm::vec3 v10 = { std::cos(theta1) * std::sin(phi0) * radius, -std::cos(phi0) * radius - halfCylHeight, std::sin(theta1) * std::sin(phi0) * radius };
            glm::vec3 v01 = { std::cos(theta0) * std::sin(phi1) * radius, -std::cos(phi1) * radius - halfCylHeight, std::sin(theta0) * std::sin(phi1) * radius };
            glm::vec3 v11 = { std::cos(theta1) * std::sin(phi1) * radius, -std::cos(phi1) * radius - halfCylHeight, std::sin(theta1) * std::sin(phi1) * radius };

            addTri(v00); addTri(v10); addTri(v01);
            addTri(v10); addTri(v11); addTri(v01);
        }
    }

    return std::make_shared<Mesh>(vertices);
}

