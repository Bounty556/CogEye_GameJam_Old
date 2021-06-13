#pragma once

#include <Defines.h>
#include <UI/UILabel.h>

#include "LevelScene.h"

class Level1Scene : public LevelScene
{
public:
	Level1Scene();

	virtual void ResetScene() override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	Soul::UILabel m_TutorialText;
};