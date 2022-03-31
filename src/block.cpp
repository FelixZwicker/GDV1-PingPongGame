#include "block.h"
#include "mesh.h"

SBlock::SBlock(){}

SBlock::SBlock(BHandle* blockMesh, float position[3]) {
    this->mesh = blockMesh;
    this->position[0] = position[0];
    this->position[1] = position[1];
    this->position[2] = position[2];

    this->updateWorldMatrix();
}

BHandle CreateBlockMesh(BHandle texture, float width, float height, float depth) {
    float x = width / 2.0f; // half width  length
    float y = height / 2.0f; // half height length
    float z = depth / 2.0f; // half depth  length

    float vertices[][3] = {
        // front
        { -x, y,-z},
        { -x,-y,-z},
        {  x,-y,-z},
        {  x, y,-z},
        // back
        { -x,-y, z},
        { -x, y, z},
        {  x, y, z},
        {  x,-y, z},
        // top
        { -x, y, z},
        { -x, y,-z},
        {  x, y,-z},
        {  x, y, z},
        // bottom
        { -x,-y,-z},
        { -x,-y, z},
        {  x,-y, z},
        {  x,-y,-z},
        // right
        {  x, y,-z},
        {  x,-y,-z},
        {  x,-y, z},
        {  x, y, z},
        // left
        { -x, y, z},
        { -x,-y, z},
        { -x,-y,-z},
        { -x, y,-z}
    };

    float s_U[] =
    {
        0.0f,
        1.0f,
    };

    float s_V[] =
    {
        0.0f,
        1.0f,
    };

    float texCoords[][2] =
    {
        { s_U[0], s_V[0], },
        { s_U[0], s_V[1], },
        { s_U[1], s_V[1], },
        { s_U[1], s_V[0], },

        { s_U[0], s_V[0], },
        { s_U[0], s_V[1], },
        { s_U[1], s_V[1], },
        { s_U[1], s_V[0], },

        { s_U[0], s_V[0], },
        { s_U[0], s_V[1], },
        { s_U[1], s_V[1], },
        { s_U[1], s_V[0], },

        { s_U[0], s_V[0], },
        { s_U[0], s_V[1], },
        { s_U[1], s_V[1], },
        { s_U[1], s_V[0], },

        { s_U[0], s_V[0], },
        { s_U[0], s_V[1], },
        { s_U[1], s_V[1], },
        { s_U[1], s_V[0], },

        { s_U[0], s_V[0], },
        { s_U[0], s_V[1], },
        { s_U[1], s_V[1], },
        { s_U[1], s_V[0], },
    };

    int indices[][3] =
    {
        {  0,  1,  2, },
        {  0,  2,  3, },

        {  4,  5,  6, },
        {  4,  6,  7, },

        {  8,  9, 10, },
        {  8, 10, 11, },

        { 12, 13, 14, },
        { 12, 14, 15, },

        { 16, 17, 18, },
        { 16, 18, 19, },

        { 20, 21, 22, },
        { 20, 22, 23, },
    };

    return CreateMesh(24, &vertices[0][0], 12, &indices[0][0], &texCoords[0][0], texture);
}
