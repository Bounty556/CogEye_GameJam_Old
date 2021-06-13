#pragma once

#include <Core/Scene.h>
#include <UI/UIContainer.h>
#include <Resources/FontManager.h>

class LevelFinishScene : public Soul::Scene
{
public:
	LevelFinishScene();

	void Update(f32 dt) override;
	void Draw(sf::RenderStates states) const override;

private:
	Soul::UIContainer m_Container;
	Soul::FontManager m_Fonts;
};