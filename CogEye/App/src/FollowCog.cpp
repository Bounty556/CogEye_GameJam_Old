#include "FollowCog.h"

#include <Rendering/Renderer.h>

FollowCog::FollowCog(Soul::TextureManager& textures, Cog::Size size, f32 radius) :
	m_Size(size),
	m_Connections(),
	m_Sprite(),
	m_Radius(radius),
	m_Textures(textures)
{
	sf::Vector2u spriteSize;

	switch (size)
	{
	case Cog::Size::Small:
	{
		m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/SmallCog1.png"));
		spriteSize = textures.RequestTexture("res/Sprites/SmallCog1.png")->getSize();
	} break;

	case Cog::Size::Medium:
	{
		m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/MediumCog1.png"));
		spriteSize = textures.RequestTexture("res/Sprites/MediumCog1.png")->getSize();
	} break;

	case Cog::Size::Large:
	{
		m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/LargeCog1.png"));
		spriteSize = textures.RequestTexture("res/Sprites/LargeCog1.png")->getSize();
	} break;
	}

	m_Sprite.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);

	f32 diameter = radius * 2;
	f32 newScale = diameter / (f32)spriteSize.x;
	m_Sprite.setScale(newScale, newScale);
	m_Sprite.setColor(sf::Color(255, 255, 120));
}

void FollowCog::Update(f32 dt)
{
	// TODO: Get mousepos
}

void FollowCog::Draw(sf::RenderStates states) const
{
	states.transform *= getTransform();
	Soul::Renderer::Render(m_Sprite, states);
}

Cog&& FollowCog::MakeCog()
{
	// TODO:
	return std::move(Cog(m_Textures, Cog::Direction::None, Cog::Size::Small, 1.0f, 1.0f));
}