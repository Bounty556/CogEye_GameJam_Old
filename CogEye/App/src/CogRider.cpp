#include "CogRider.h"

#include <Math/Constants.h>
#include <Math/Vectors.h>
#include <Rendering/Renderer.h>
#include <Core/MessageBus.h>

#include "RiderHat.h"

CogRider::CogRider(Soul::TextureManager& textures, f32 x, f32 y, Affiliation affiliation) :
	m_Sprite(*textures.RequestTexture("res/Sprites/CogRider.png")),
	m_Affiliation(affiliation),
	m_AttachedCog(nullptr),
	m_AttachedAngle(0.0f),
	m_OldCog(nullptr),
	m_InBlock(nullptr),
	m_Listener(),
	m_Hats(),
	m_IsCollidingWithRider(false)
{
	m_Sprite.setOrigin(64, 32);
	setScale(0.25f, 0.25f);
	setPosition(x, y);

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

	// Make sure we detach from a cog if it melts
	m_Listener.Subscribe("MeltCog",
		[&](void* data)
		{
			if (m_AttachedCog == (Cog*)data)
			{
				m_AttachedCog = nullptr;
				m_OldCog = nullptr;
			}
		});
}

CogRider::CogRider(CogRider&& other) noexcept :
	m_Sprite(std::move(other.m_Sprite)),
	m_Affiliation(other.m_Affiliation),
	m_AttachedCog(other.m_AttachedCog),
	m_AttachedAngle(other.m_AttachedAngle),
	m_OldCog(other.m_OldCog),
	m_InBlock(other.m_InBlock),
	m_Listener(std::move(other.m_Listener)),
	m_Hats(std::move(other.m_Hats)),
	m_IsCollidingWithRider(other.m_IsCollidingWithRider)
{
}

CogRider::~CogRider()
{
	for (u32 i = 0; i < m_Hats.Count(); i++)
		Soul::MemoryManager::FreeMemory(m_Hats[i]);
}

CogRider& CogRider::operator=(CogRider&& other) noexcept
{
	m_Sprite = std::move(other.m_Sprite);
	m_Affiliation = other.m_Affiliation;
	m_AttachedCog = other.m_AttachedCog;
	m_AttachedAngle = other.m_AttachedAngle;
	m_OldCog = other.m_OldCog;
	m_InBlock = other.m_InBlock;
	m_Listener = std::move(other.m_Listener);
	m_Hats = std::move(other.m_Hats);
	m_IsCollidingWithRider = other.m_IsCollidingWithRider;

	return *this;
}

void CogRider::Update(f32 dt)
{
	m_IsCollidingWithRider = false;

	if (m_AttachedCog)
	{
		// Ride along cog circumference
		if (m_Affiliation & Affiliation::Red)
			m_AttachedAngle += m_AttachedCog->GetRotSpeed() * (i32)m_AttachedCog->GetDirection() * dt;
		else
			m_AttachedAngle -= m_AttachedCog->GetRotSpeed() * (i32)m_AttachedCog->GetDirection() * dt;
		m_AttachedAngle = FLOAT_MOD(m_AttachedAngle, 360.0f);
		if (m_AttachedAngle < -180.0f) // The Sin and Cos functions are inaccurate at values at or above 2Pi
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
	for (u32 i = 0; i < m_Hats.Count(); ++i)
		m_Hats[i]->Draw(states);
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

				MeltOldCog();

				break;
			}
		}
		else if (m_OldCog == allCogs[i])
		{
			f32 distance = Soul::Math::Distance(getPosition(), allCogs[i]->getPosition());
			if (distance > allCogs[i]->GetRadius() + 16)
				m_OldCog = nullptr; // We disconnected, now we can reconnect
		}
	}
}

void CogRider::CheckCollisions(Soul::Vector<Block*>& allBlocks)
{
	for (u32 i = 0; i < allBlocks.Count(); ++i)
	{
		sf::Vector2f blockPos = allBlocks[i]->getPosition();
		sf::Vector2i blockSize = allBlocks[i]->GetSize();
		if (getPosition().x - blockPos.x >= 0 &&
			getPosition().x - blockPos.x <= (f32)blockSize.x &&
			getPosition().y - blockPos.y >= 0 &&
			getPosition().y - blockPos.y <= (f32)blockSize.y)
		{
			if (allBlocks[i]->GetBlockType() == Block::Lava)
				Soul::MessageBus::QueueMessage("MeltRider", this);
			else if (m_InBlock == nullptr)
			{
				// Fall off cog
				m_InBlock = allBlocks[i];
				m_OldCog = m_AttachedCog;
				m_AttachedCog = nullptr;

				MeltOldCog();
			}
			return;
		}
	}

	m_InBlock = nullptr;
}

void CogRider::CheckCollisions(Soul::Vector<CogRider*>& allCogRiders)
{
	bool foundUs = false;
	for (u32 i = 0; i < allCogRiders.Count(); ++i)
	{
		if (allCogRiders[i] == this)
		{
			foundUs = true;
			continue;
		}

		if (foundUs)
		{
			if (Soul::Math::Distance(getPosition(), allCogRiders[i]->getPosition()) < 32 &&
				!allCogRiders[i]->IsCollidingWithRider())
			{
				RiderPair* pair = PARTITION(RiderPair);
				pair->riderA = this;
				pair->riderB = allCogRiders[i];
				Soul::MessageBus::QueueMessage("RiderCollision", pair);
				m_IsCollidingWithRider = true;
				pair->riderB->SetCollidingWithRider();
			}
		}
	}
}

void CogRider::AddHat(Soul::TextureManager& textures, Affiliation affiliation)
{
	u32 diffAffil = (m_Affiliation ^ affiliation) & ~m_Affiliation;
	u32 affilMask = 1;
	
	while (diffAffil && affilMask < 16)
	{
		u32 masked = diffAffil & affilMask;

		if (masked)
		{
			// Add any powers we're missing
			m_Affiliation = (Affiliation)(masked + m_Affiliation);
			RiderHat* hat = PARTITION(RiderHat, textures, (Affiliation)masked);
			hat->setPosition(0.0f, 54.0f + m_Hats.Count() * 48.0f);
			m_Hats.Push(hat);
		}

		affilMask = affilMask << 1;
	}
}

CogRider::Affiliation CogRider::GetAffiliation() const
{
	return m_Affiliation;
}

bool CogRider::IsCollidingWithRider() const
{
	return m_IsCollidingWithRider;
}

void CogRider::SetCollidingWithRider()
{
	m_IsCollidingWithRider = true;
}

void CogRider::MeltOldCog()
{
	if (m_Affiliation & Affiliation::Green && m_OldCog)
	{
		Soul::MessageBus::QueueMessage("MeltCog", (void*)m_OldCog); // Destroy cog
		m_OldCog = nullptr;
	}
}