#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <UI/UIContainer.h>
#include <Resources/FontManager.h>

class MainMenuScene : public Soul::Scene
{
public:
	MainMenuScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	Soul::UIContainer m_UI;
	Soul::FontManager m_Fonts;
};
