#pragma once

#include <Defines.h>
#include <Resources/TextureManager.h>
#include <Resources/FontManager.h>
#include <UI/UILabel.h>

#include <SFML/Graphics.hpp>

#include "CogRider.h"

class Goal : sf::Transformable
{
public:
	Goal(u32 required, Soul::FontManager& fonts, f32 x, f32 y, f32 width, f32 height);

	void Draw(sf::RenderStates states) const;

	void CheckCollisions(const Soul::Vector<CogRider*>& cogRiders);

private:
	sf::RectangleShape m_Rect;
	Soul::UILabel m_Label;
	u32 m_Required;
	u32 m_Reached;
};