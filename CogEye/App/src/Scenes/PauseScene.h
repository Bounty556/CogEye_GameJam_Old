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

	PauseScene(const PauseScene&) = delete;
	PauseScene(PauseScene&& other) noexcept;

	PauseScene& operator=(const PauseScene&) = delete;
	PauseScene& operator=(PauseScene&& other) noexcept;

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	sf::RectangleShape m_MenuBG;
	Soul::FontManager m_Fonts;
	Soul::UIContainer m_UI;
};
