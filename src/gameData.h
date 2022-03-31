#pragma once
#include "block.h"

const float BORDER_TOP = 5.0f;
const float BORDER_BOTTOM = -5.0f;
const float BORDER_RIGHT = 8.0f;
const float BORDER_LEFT = -8.0f;

struct SObjectList {
	float position[3];
};

const unsigned int NUM_OF_BLOCKS = 34;
static SObjectList BORDER_BLOCKS[] = {
	//Top
	{-8.0f,5.0f,0.0f},
	{-7.0f,5.0f,0.0f},
	{-6.0f,5.0f,0.0f},
	{-5.0f,5.0f,0.0f},
	{-4.0f,5.0f,0.0f},
	{-3.0f,5.0f,0.0f},
	{-2.0f,5.0f,0.0f},
	{-1.0f,5.0f,0.0f},
	{0.0f,5.0f,0.0f},
	{1.0f,5.0f,0.0f},
	{2.0f,5.0f,0.0f},
	{3.0f,5.0f,0.0f},
	{4.0f,5.0f,0.0f},
	{5.0f,5.0f,0.0f},
	{6.0f,5.0f,0.0f},
	{7.0f,5.0f,0.0f},
	{8.0f,5.0f,0.0f},
	//Bottom
	{-8.0f,-5.0f,0.0f},
	{-7.0f,-5.0f,0.0f},
	{-6.0f,-5.0f,0.0f},
	{-5.0f,-5.0f,0.0f},
	{-4.0f,-5.0f,0.0f},
	{-3.0f,-5.0f,0.0f},
	{-2.0f,-5.0f,0.0f},
	{-1.0f,-5.0f,0.0f},
	{0.0f,-5.0f,0.0f},
	{1.0f,-5.0f,0.0f},
	{2.0f,-5.0f,0.0f},
	{3.0f,-5.0f,0.0f},
	{4.0f,-5.0f,0.0f},
	{5.0f,-5.0f,0.0f},
	{6.0f,-5.0f,0.0f},
	{7.0f,-5.0f,0.0f},
	{8.0f,-5.0f,0.0f},
};

const unsigned int NUM_OF_PADDLES = 2;
static SObjectList PADDELS[] = {
	{-7.0f,0.0f,0.0f},
	{7.0f,0.0f,0.0f},
};

static SObjectList MENU[] = {
	{0.0f,0.0f,0.0f},
};

static SObjectList SCORE[] = {
	{-8.0f, 4.0f, 0.0f},
	{8.0f, 4.0f, 0.0f},
};