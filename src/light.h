#pragma once

struct SLight {
    float position[3] = { 0.0f, 0.0f, -4.0f };
    float ambient[4] = { 0.8f, 0.8f, 0.8f, 0.8f };
    float diffuse[4] = { 0.6f,0.6f,0.6f,1.0f };
    float specular[4] = { 0.9f, 0.9f, 0.9f,1.0f };
};