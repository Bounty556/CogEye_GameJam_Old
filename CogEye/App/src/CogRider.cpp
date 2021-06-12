#include "CogRider.h"

#include <Math/Constants.h>
#include <Math/Vectors.h>
#include <Rendering/Renderer.h>
#include <Core/MessageBus.h>

CogRider::CogRider(Soul::TextureManager& textures, f32 x, f32 y, Affiliation affiliation) :
	m_Sprite(*textures.RequestTexture("res/Sprites/CogRider.png")),
	m_Affiliation(affiliation),
	m_AttachedCog(nullptr),
	m_AttachedAngle(0.0f),
	m_OldCog(nullptr)
{
	m_Sprite.setOrigin(64, 32);
	setScale(0.25f, 0.25f);
	setPosition(x, y);

	// TODO: set color based on affiliation
	switch (affiliation)
	{
		case Red:
		{
			m_Sprite.setColor(sf::Color(255, 75, 75));
		} break;

		case Blue:
		{
			m_Sprite.setColor(sf::Color(50, 50, 200));
		} break;

		case Green:
		{
			m_Sprite.setColor(sf::Color(50, 200, 50));
		} break;

		case Yellow:
		{
			m_Sprite.setColor(sf::Color(255, 255, 0));
		} break;
	}
}

CogRider::CogRider(CogRider&& other) noexcept :
	m_Sprite(std::move(other.m_Sprite)),
	m_Affiliation(other.m_Affiliation),
	m_AttachedCog(other.m_AttachedCog),
	m_AttachedAngle(other.m_AttachedAngle),
	m_OldCog(other.m_OldCog)
{
}

CogRider& CogRider::operator=(CogRider&& other) noexcept
{
	m_Sprite = std::move(other.m_Sprite);
	m_Affiliation = other.m_Affiliation;
	m_AttachedCog = other.m_AttachedCog;
	m_AttachedAngle = other.m_AttachedAngle;
	m_OldCog = other.m_OldCog;

	return *this;
}

void CogRider::Update(f32 dt)
{
	if (m_AttachedCog)
	{
		// Ride along cog circumference
		if (m_Affiliation & Affiliation::Red)
			m_AttachedAngle += m_AttachedCog->GetRotSpeed() * (i32)m_AttachedCog->GetDirection() * dt;
		else
			m_AttachedAngle -= m_AttachedCog->GetRotSpeed() * (i32)m_AttachedCog->GetDirection() * dt;
		m_AttachedAngle = FLOAT_MOD(m_AttachedAngle, 360.0f);
		if (m_AttachedAngle < -180.0f)
			m_AttachedAngle += 360.0f;

		sf::Vector2f direction = Soul::Math::AngleToVector(m_AttachedAngle);
		setPosition(m_AttachedCog->getPosition() + direction * m_AttachedCog->GetRadius());
		setRotation(-FLOAT_MOD(m_AttachedAngle + 90.0f, 360.0f));
	}
	else
	{
		// Fall at a constant speed
		const f32 GRAVITY = 0.98f;
		move(0.0f, GRAVITY * dt);
	}
}

void CogRider::Draw(sf::RenderStates states) const
{
	states.transform *= getTransform();
	Soul::Renderer::Render(m_Sprite, states);
}

void CogRider::CheckCollisions(Soul::Vector<Cog*>& allCogs)
{
	for (u32 i = 0; i < allCogs.Count(); i++)
	{
		if (m_AttachedCog != allCogs[i] && m_OldCog != allCogs[i])
		{
			f32 distance = Soul::Math::Distance(getPosition(), allCogs[i]->getPosition());
			if (distance <= allCogs[i]->GetRadius() + 16)
			{
				// Attach cog
				m_OldCog = m_AttachedCog;
				m_AttachedCog = allCogs[i];
				m_AttachedAngle = Soul::Math::VectorToAngle(getPosition() - allCogs[i]->getPosition());
				break;
			}
		}
		else if (m_OldCog == allCogs[i])
		{
			f32 distance = Soul::Math::Distance(getPosition(), allCogs[i]->getPosition());
			if (distance > allCogs[i]->GetRadius() + 16)
			{
				if (m_Affiliation & Affiliation::Green)
					Soul::MessageBus::QueueMessage("MeltCog", (void*)m_OldCog); // Destroy cog

				m_OldCog = nullptr; // We disconnected, now we can reconnect
			}
		}
	}
}