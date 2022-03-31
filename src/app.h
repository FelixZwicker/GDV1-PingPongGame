#pragma once
#include "game.h"


class CApplication : public IApplication {
public:
	CApplication();
	virtual ~CApplication();

private:
	BHandle ballTexture;
	BHandle ballMesh;

	BHandle leftPaddleTexture;
	BHandle leftPaddleMesh;

    BHandle rightPaddleTexture;
    BHandle rightPaddleMesh;

    BHandle blockTexture;
    BHandle blockMesh;

    EKey key;
    CGame* game;

private:
    virtual bool InternOnStartup();
    virtual bool InternOnShutdown();
    virtual bool InternOnCreateTextures();
    virtual bool InternOnReleaseTextures();
    virtual bool InternOnCreateMeshes();
    virtual bool InternOnReleaseMeshes();
    virtual bool InternOnResize(int _width, int _height);
    virtual bool InternOnKeyEvent(unsigned int _key, bool _isKeyDown, bool _isAltDown);
    virtual bool InternOnUpdate();
    virtual bool InternOnFrame();
};
