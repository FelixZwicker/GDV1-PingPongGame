#include "mesh.h"

float normals[][3] = {
    { 0.0f, 0.0f, -1.0f },
    { 0.0f, 0.0f, -1.0f },
    { 0.0f, 0.0f, -1.0f },
    { 0.0f, 0.0f, -1.0f },
};

BHandle CreateMesh(int numberOfVertices, float* vertices, int numberOfIndices, int* indices, float* texCoords, BHandle texture) {
    SMeshInfo MeshInfo;

    MeshInfo.m_NumberOfVertices = numberOfVertices;
    MeshInfo.m_NumberOfIndices = numberOfIndices;
    MeshInfo.m_pVertices = vertices;
    MeshInfo.m_pIndices = indices;
    MeshInfo.m_pTexCoords = texCoords;
    MeshInfo.m_pTexture = texture;
    MeshInfo.m_pNormals = &normals[0][0];
    MeshInfo.m_pColors = nullptr;

    BHandle mesh = nullptr;
    CreateMesh(MeshInfo, &mesh);

    return mesh;
}