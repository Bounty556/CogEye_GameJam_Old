#pragma once

#include <Defines.h>
#include <Resources/TextureManager.h>

#include <SFML/Graphics.hpp>

#include "CogRider.h"

class RiderHat : public sf::Transformable
{
public:
	RiderHat(Soul::TextureManager& textures, CogRider::Affiliation affiliation);

	void Draw(sf::RenderStates states) const;

private:
	sf::Sprite m_Sprite;
};