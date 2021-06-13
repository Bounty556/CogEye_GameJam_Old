#pragma once

#include <Defines.h>
#include <UI/UILabel.h>

#include "LevelScene.h"

class Level5Scene : public LevelScene
{
public:
	Level5Scene();

	virtual void ResetScene() override;
	virtual void Draw(sf::RenderStates states) const override;
	virtual void NextLevel() override;

private:
	Soul::UILabel m_TutorialText;
};