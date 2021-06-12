#include "FollowCog.h"

#include <Rendering/Renderer.h>
#include <Math/Constants.h>
#include <Math/Functions.h>
#include <Math/Vectors.h>

FollowCog::FollowCog(Soul::TextureManager& textures, Cog::Size size, f32 radius) :
	m_Size(size),
	m_Connections(),
	m_Sprite(),
	m_Radius(radius),
	m_Textures(textures),
	m_LastGoodPos(0.0f, 0.0f)
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
	m_Sprite.setColor(sf::Color(255, 255, 255, 120));
}

void FollowCog::Update(f32 dt)
{
	setPosition((sf::Vector2f)sf::Mouse::getPosition(Soul::Renderer::GetWindow()));
}

void FollowCog::Draw(sf::RenderStates states) const
{
	states.transform *= getTransform();
	Soul::Renderer::Render(m_Sprite, states);
}

void FollowCog::CheckCollisions(Soul::Vector<Cog*>& allCogs)
{
	m_Connections.Clear();
	for (u32 i = 0; i < allCogs.Count(); ++i)
	{
		Cog* cog = allCogs[i];
		f32 minDistance = Soul::Math::Max(0.0f, m_Radius + cog->GetRadius());
		if (Soul::Math::Distance(cog->getPosition(), getPosition()) < minDistance)
			m_Connections.Push(cog);
	}
}

Cog* FollowCog::MakeCog()
{
	if (m_Connections.Count() > 0)
	{
		// If all colliding cogs have the same direction
		Cog::Direction direction = m_Connections[0]->GetDirection();

		f32 leeway = 30.0f;

		for (u32 i = 0; i < m_Connections.Count(); ++i)
		{
			f32 distance = Soul::Math::Distance(m_Connections[i]->getPosition(), getPosition());
			f32 error = Soul::Math::Abs(distance - (m_Radius + m_Connections[i]->GetRadius()));

			if (error > leeway)
				return nullptr;

			if (m_Connections[i]->GetDirection() != direction)
				return nullptr;
		}

		f32 newCircumference = 2.0f * PI * m_Radius;
		f32 otherCircumference = 2.0f * PI * m_Connections[0]->GetRadius();
		f32 ratio = otherCircumference / newCircumference;
		f32 newSpeed = m_Connections[0]->GetRotSpeed() * ratio;

		Cog* newCog = PARTITION(Cog, m_Textures, (Cog::Direction)-direction, m_Size, m_Radius, newSpeed);
		newCog->setPosition(getPosition());
		return newCog;
	}
	else
		return nullptr;
}