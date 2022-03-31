#include "ball.h"
#include "math.h"
#include "mesh.h"
#include <cmath>

const float SPEED = 0.15f;
const float INCREASESPEED = 0.00015f;
const int INCREASEAFTER = 5;
const float DIRECTION[] = { -1.0f, 0.0f, 0.0f };
const float POSITION[] = { 0.0f, 0.0f, 0.0f };

const float BALLRADIUS = 0.3f;
const float PADDLEHEIGHT = 1.5f;

SBall::SBall(){}

SBall::SBall(BHandle* ballMesh) {
    this->mesh = ballMesh;
    this->position[0] = POSITION[0];
    this->position[1] = POSITION[1];
    this->position[2] = POSITION[2];

    this->speed = SPEED;
    this->direction[0] = DIRECTION[0];
    this->direction[1] = DIRECTION[1];
    this->direction[2] = DIRECTION[2];

    this->hits = 0;

    GetNormalizedVector(this->direction, this->direction);

    this->updateWorldMatrix();
}

bool SBall::handleCollision(float topBoarder, float bottomBoarder) {
    if (topBoarder < this->position[1] + 0.5f + BALLRADIUS) {       //0.5f == half edge length of boarder blocks
        this->changeDirection(ECollisionAt::TOP);
        return true;
    }
    if (bottomBoarder > this->position[1] - 0.5f - BALLRADIUS) {
        this->changeDirection(ECollisionAt::BOTTOM);
        return true;
    }
}

const float WEIGHT_OF_PADDLE_ANGLE = 0.8f;

bool SBall::handleCollision(SPaddle& paddle) {
    float xDiff = this->position[0] - paddle.position[0]; // XDiff = 0 == same x 
    float yDiff = this->position[1] - paddle.position[1]; // YDiff = 0 == same y             
    float yOffset = BALLRADIUS + PADDLEHEIGHT / 2;                    
    float yDirection = yDiff / yOffset;

    if (paddle.position[0] < 0 && xDiff <= 0 && std::fabs(yDiff) < yOffset) {
        this->changeDirection(ECollisionAt::LEFT);
        hits++;

        this->direction[1] += WEIGHT_OF_PADDLE_ANGLE * (yDirection - this->direction[1]);
        GetNormalizedVector(this->direction, this->direction);
        return true;
    }
    else if (paddle.position[0] > 0 && xDiff >= 0 && std::fabs(yDiff) < yOffset) {
        this->changeDirection(ECollisionAt::RIGHT);
        hits++;

        this->direction[1] += WEIGHT_OF_PADDLE_ANGLE * (yDirection - this->direction[1]);
        GetNormalizedVector(this->direction, this->direction);
        return true;
    }

    return false;
}

bool SBall::hitCheckpoint(int hits) {
    switch (hits % INCREASEAFTER) {
    case 0:
        return true;

    default:
        return false;
    }
}

bool SBall::isOutLeft(float boarder) {
    return boarder > this->position[0];
}

bool SBall::isOutRight(float boarder) {
    return boarder < this->position[0];
}

void SBall::move() {
    if (hitCheckpoint(this->hits)) {
        this->speed += INCREASESPEED;       //increases speed every 5 hits
    }
    this->position[0] += this->speed * this->direction[0];
    this->position[1] += this->speed * this->direction[1];
    this->position[2] += this->speed * this->direction[2];

    this->updateWorldMatrix();
}

void SBall::changeDirection(ECollisionAt collisionAt) {
    switch (collisionAt) {
    case ECollisionAt::TOP:
        if (this->direction[1] > 0) {
            this->direction[1] *= -1.0f;    //inverts direction
        }
        break;
    case ECollisionAt::BOTTOM:
        if (this->direction[1] < 0) {
            this->direction[1] *= -1.0f;
        }
        break;
    case ECollisionAt::LEFT:
        if (this->direction[0] < 0) {
            this->direction[0] *= -1.0f;
        }
        break;
    case ECollisionAt::RIGHT:
        if (this->direction[0] > 0) {
            this->direction[0] *= -1.0f;
        }
        break;
    }
}

BHandle CreateBallMesh(BHandle texture, float radius)
{
    static const float s_Pi = 3.1415926535897932384626433832795f;
    static const int   s_Delta = 10;
    static const int   s_NumberOfVerticalVertices = 180 / s_Delta + 1;
    static const int   s_NumberOfHorizontalVertices = 360 / s_Delta + 1;
    static const int   s_NumberOfVertices = s_NumberOfVerticalVertices * s_NumberOfHorizontalVertices;
    static const int   s_NumberOfIndices = s_NumberOfVertices * 2 * 3;

    int   IndexOfVertex;
    int   IndexOfIndex;

    float RadiusOfSphere;
    float CenterOfSphere[3];
    float RadiusOfHorizontalCircle;
    float CenterOfHorizontalCircle[3];
    float FirstVertexOfHorizontalCircle[3];
    float Distance[3];

    int   Indices[s_NumberOfIndices];
    float Vertices[s_NumberOfVertices * 3];
    float TexCoords[s_NumberOfVertices * 2];

    RadiusOfSphere = radius;

    CenterOfSphere[0] = 0.0f;
    CenterOfSphere[1] = 0.0f;
    CenterOfSphere[2] = 0.0f;

    IndexOfVertex = 0;

    for (float Alpha = 90.0f; Alpha <= 270; Alpha += s_Delta)
    {
        FirstVertexOfHorizontalCircle[0] = CenterOfSphere[0] + RadiusOfSphere * cos(s_Pi * Alpha / 180.0f);
        FirstVertexOfHorizontalCircle[1] = CenterOfSphere[1] + RadiusOfSphere * sin(s_Pi * Alpha / 180.0f);
        FirstVertexOfHorizontalCircle[2] = CenterOfSphere[2];

        CenterOfHorizontalCircle[0] = CenterOfSphere[0];
        CenterOfHorizontalCircle[1] = FirstVertexOfHorizontalCircle[1];
        CenterOfHorizontalCircle[2] = CenterOfSphere[2];

        Distance[0] = FirstVertexOfHorizontalCircle[0] - CenterOfHorizontalCircle[0];
        Distance[1] = FirstVertexOfHorizontalCircle[1] - CenterOfHorizontalCircle[1];
        Distance[2] = FirstVertexOfHorizontalCircle[2] - CenterOfHorizontalCircle[2];

        RadiusOfHorizontalCircle = sqrtf(Distance[0] * Distance[0] + Distance[1] * Distance[1] + Distance[2] * Distance[2]);

        for (float Gamma = 0.0f; Gamma <= 360; Gamma += s_Delta)
        {
            Vertices[IndexOfVertex * 3 + 0] = CenterOfHorizontalCircle[0] + RadiusOfHorizontalCircle * cos(s_Pi * Gamma / 180.0f);
            Vertices[IndexOfVertex * 3 + 1] = CenterOfHorizontalCircle[1];
            Vertices[IndexOfVertex * 3 + 2] = CenterOfHorizontalCircle[2] + RadiusOfHorizontalCircle * sin(s_Pi * Gamma / 180.0f);

            TexCoords[IndexOfVertex * 2 + 0] = Gamma / 360.0f;
            TexCoords[IndexOfVertex * 2 + 1] = (Alpha - 90.0f) / 180.0f;

            ++IndexOfVertex;
        }
    }

    IndexOfIndex = 0;

    for (int IndexOfCircle = 0; IndexOfCircle < s_NumberOfVerticalVertices; ++IndexOfCircle)
    {
        int FirstIndexOfCircle = IndexOfCircle * s_NumberOfHorizontalVertices;

        for (int IndexOfTriangle = 0; IndexOfTriangle < s_NumberOfHorizontalVertices; ++IndexOfTriangle)
        {
            int UpperLeft = FirstIndexOfCircle + 0 + IndexOfTriangle;
            int UpperRight = FirstIndexOfCircle + 0 + IndexOfTriangle + 1;
            int LowerLeft = FirstIndexOfCircle + s_NumberOfHorizontalVertices + IndexOfTriangle;
            int LowerRight = FirstIndexOfCircle + s_NumberOfHorizontalVertices + IndexOfTriangle + 1;

            Indices[IndexOfIndex + 0] = LowerLeft;
            Indices[IndexOfIndex + 1] = LowerRight;
            Indices[IndexOfIndex + 2] = UpperRight;

            Indices[IndexOfIndex + 3] = LowerLeft;
            Indices[IndexOfIndex + 4] = UpperRight;
            Indices[IndexOfIndex + 5] = UpperLeft;

            IndexOfIndex += 6;
        }
    }

    return CreateMesh(s_NumberOfVertices, Vertices, s_NumberOfIndices, Indices, TexCoords, texture);
}