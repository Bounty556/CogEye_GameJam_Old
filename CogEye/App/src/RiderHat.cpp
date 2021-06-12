#include "RiderHat.h"

#include <Rendering/Renderer.h>

RiderHat::RiderHat(Soul::TextureManager& textures, CogRider::Affiliation affiliation) :
	m_Sprite(*textures.RequestTexture("res/Sprites/CogRider.png"))
{
	m_Sprite.setOrigin(64, 32);
	setScale(0.75f, 0.75f);
	switch (affiliation)
	{
		case CogRider::Red:
		{
			m_Sprite.setColor(sf::Color(255, 75, 75));
		} break;

		case CogRider::Blue:
		{
			m_Sprite.setColor(sf::Color(50, 50, 200));
		} break;

		case CogRider::Green:
		{
			m_Sprite.setColor(sf::Color(50, 200, 50));
		} break;

		case CogRider::Yellow:
		{
			m_Sprite.setColor(sf::Color(255, 255, 0));
		} break;
	}
}

void RiderHat::Draw(sf::RenderStates states) const
{
	states.transform *= getTransform();
	Soul::Renderer::Render(m_Sprite, states);
}