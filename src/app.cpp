#include "app.h"

#include "camera.h"
#include "light.h"


CApplication::CApplication()
    : ballTexture(nullptr)
    , ballMesh(nullptr)
    , leftPaddleTexture(nullptr)
    , leftPaddleMesh(nullptr)
    , rightPaddleTexture(nullptr)
    , rightPaddleMesh(nullptr)
    , blockTexture(nullptr)
    , blockMesh(nullptr)
    , key(EKey::NONE)
    , game(nullptr)
{
}

CApplication::~CApplication()
{
}

bool CApplication::InternOnStartup() {
    this->game = new CGame(&this->ballMesh, &this->leftPaddleMesh, &this->rightPaddleMesh, &this->blockMesh);

    return true;
}

bool CApplication::InternOnShutdown() {
    this->game->~CGame();

	return true;
}

bool CApplication::InternOnCreateTextures() {
    CreateTexture("..\\data\\images\\neon_marmor.jpg", &ballTexture);
	CreateTexture("..\\data\\images\\blue.jpg", &leftPaddleTexture);
    CreateTexture("..\\data\\images\\red.png", &rightPaddleTexture);
    CreateTexture("..\\data\\images\\boarders.jpg", &blockTexture);

	return true;
}

bool CApplication::InternOnReleaseTextures() {
    ReleaseTexture(ballTexture);
	ReleaseTexture(leftPaddleTexture);
    ReleaseTexture(rightPaddleTexture);
    ReleaseTexture(blockTexture);

    game->createMenu->~CMenu();             //in case the player closes the game on his own

	return true;
}

bool CApplication::InternOnCreateMeshes() {
    this->ballMesh = CreateBallMesh(ballTexture, 0.3f);
    this->leftPaddleMesh = CreateBlockMesh(leftPaddleTexture, 0.3f, 1.5f, 1.0f);
    this->rightPaddleMesh = CreateBlockMesh(rightPaddleTexture, 0.3f, 1.5f, 1.0f);
    this->blockMesh = CreateBlockMesh(blockTexture, 1.0f, 1.0f, 1.0f);

    return true;
}

bool CApplication::InternOnReleaseMeshes() {
    ReleaseMesh(ballMesh);
    ReleaseMesh(leftPaddleMesh);
    ReleaseMesh(rightPaddleMesh);
    ReleaseMesh(blockMesh);

    //in case the player closes the game on his own
    game->removeLeftScore();
    game->removeRightScore();
    if (game->showesMenu) {
        game->removeMenu();
    }

    return true;
}

bool CApplication::InternOnResize(int _width, int _height) {
    SCamera camera;
    SLight light;

    float viewMatrix[16];
    GetViewMatrix(camera.position, camera.target, camera.up, viewMatrix);
    SetViewMatrix(viewMatrix);

    float projectionMatrix[16];
    float aspectRatio = (float)_width / (float)_height;
    GetProjectionMatrix(camera.aperture, aspectRatio, camera.nearClip, camera.farClip, projectionMatrix);
    SetProjectionMatrix(projectionMatrix);

    SetLightPosition(light.position);
    SetLightColor(light.ambient, light.diffuse, light.specular, 127);

    return true;
}

bool CApplication::InternOnKeyEvent(unsigned int _key, bool _isKeyDown, bool _isAltDown) {
    switch (_key) {
        case KEY_SPACE:
            if (!_isKeyDown) {
                this->key = EKey::SPACE;
                return true;
            }
            break;

        case KEY_UP:
            this->key = EKey::UP;
            break;

        case KEY_DOWN:
            this->key = EKey::DOWN;
            break;

        case KEY_W:
            this->key = EKey::W;
            break;

        case KEY_S:
            this->key = EKey::S;
            break;

        case KEY_ONE:
            this->key = EKey::ONE;
            break;

        case KEY_TWO:
            this->key = EKey::TWO;
            break;

        default:
            this->key = EKey::NONE;
    }

    if (!_isKeyDown) {
        this->key = EKey::NONE;
    }

    return true;
}

bool CApplication::InternOnUpdate() {
    this->game->update(this->key);

    if (this->key == EKey::SPACE) {
        this->key = EKey::NONE;
    }

    return true;
}

bool CApplication::InternOnFrame() {
    std::vector<SObject*>* objects = this->game->getObjects();

    for (auto object : *objects) {
        SetWorldMatrix(object->worldMatrix);
        DrawMesh(*object->mesh);
    }

    return true;
}