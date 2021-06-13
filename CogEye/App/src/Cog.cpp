#include "Cog.h"

#include <Rendering/Renderer.h>

#include <SFML/System/Vector2.hpp>

Cog::Cog(Soul::TextureManager& textures, Direction direction, Size size, f32 radius, f32 rotSpeed) :
	m_Direction(direction),
	m_Size(size),
	m_Connections(),
	m_Sprite(),
	m_Radius(radius),
	m_RotSpeed(rotSpeed)
{
	sf::Vector2u spriteSize;

	switch (size)
	{
		case Size::Small:
		{
			m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/SmallCog1.png"));
			spriteSize = textures.RequestTexture("res/Sprites/SmallCog1.png")->getSize();
		} break;

		case Size::Medium:
		{
			m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/MediumCog1.png"));
			spriteSize = textures.RequestTexture("res/Sprites/MediumCog1.png")->getSize();
		} break;

		case Size::Large:
		{
			m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/LargeCog1.png"));
			spriteSize = textures.RequestTexture("res/Sprites/LargeCog1.png")->getSize();
		} break;
	}

	m_Sprite.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);

	f32 diameter = radius * 2;
	f32 newScale = diameter / (f32)spriteSize.x;
	m_Sprite.setScale(newScale, newScale);
}

Cog::Cog(Cog&& other) noexcept :
	m_Direction(other.m_Direction),
	m_Size(other.m_Size),
	m_Connections(std::move(other.m_Connections)),
	m_Sprite(std::move(other.m_Sprite)),
	m_Radius(other.m_Radius),
	m_RotSpeed(other.m_RotSpeed)
{
}

Cog::~Cog()
{
	for (u32 i = 0; i < m_Connections.Count(); ++i)
		m_Connections[i]->RemoveConnection(this);
}

Cog& Cog::operator=(Cog&& other) noexcept
{
	m_Direction = other.m_Direction;
	m_Size = other.m_Size;
	m_Connections = std::move(other.m_Connections);
	m_Sprite = std::move(other.m_Sprite);
	m_Radius = other.m_Radius;
	m_RotSpeed = other.m_RotSpeed;

	return *this;
}

void Cog::Update(f32 dt)
{
	m_Sprite.rotate(m_RotSpeed * (i32)m_Direction * dt);
}

void Cog::Draw(sf::RenderStates states) const
{
	states.transform *= getTransform();
	Soul::Renderer::Render(m_Sprite, states);
}

void Cog::AddConnection(Cog* connection)
{
	m_Connections.Push(connection);
}

void Cog::RemoveConnection(Cog* connection)
{
	m_Connections.Remove(connection);
}

Cog::Direction Cog::GetDirection() const
{
	return m_Direction;
}

f32 Cog::GetRadius() const
{
	return m_Radius;
}

f32 Cog::GetRotSpeed() const
{
	return m_RotSpeed;
}

const Soul::Vector<Cog*>& Cog::GetConnections() const
{
	return m_Connections;
}