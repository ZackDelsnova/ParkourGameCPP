#include "Object.h"

static const float cubeVertices[] = {
    -0.5f,-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.5f,0.5f,-0.5f,
    0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,0.5f, 0.5f,-0.5f,0.5f, 0.5f,0.5f,0.5f,
    0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f,
    -0.5f,0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,
    0.5f,0.5f,0.5f,0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,
    -0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,-0.5f,
    -0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,
    0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,-0.5f
};

Object::Object() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Object::Draw(const Shader& shader) const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Object::Destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
