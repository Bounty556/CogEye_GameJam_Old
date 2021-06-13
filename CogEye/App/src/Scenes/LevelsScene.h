#pragma once

#include <Core/Scene.h>
#include <UI/UIContainer.h>
#include <Resources/FontManager.h>

class LevelsScene : public Soul::Scene
{
public:
	LevelsScene();

	void Update(f32 dt) override;
	void Draw(sf::RenderStates states) const override;

private:
	Soul::UIContainer m_UI;
	Soul::FontManager m_Fonts;
};