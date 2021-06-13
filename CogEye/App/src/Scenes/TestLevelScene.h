#pragma once

#include <Defines.h>

#include "LevelScene.h"

class TestLevelScene : public LevelScene
{
public:
	TestLevelScene();

	virtual void ResetScene() override;
};