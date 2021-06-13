#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <Resources/FontManager.h>

#include <UI/UIContainer.h>

#include <SFML/Graphics/RectangleShape.hpp>

class PauseScene : public Soul::Scene
{
public:
	PauseScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	sf::RectangleShape m_MenuBG;
	Soul::FontManager m_Fonts;
	Soul::UIContainer m_UI;
};
