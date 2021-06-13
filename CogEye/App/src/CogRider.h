#pragma once

#include <Defines.h>
#include <Core/Listener.h>
#include <Resources/TextureManager.h>
#include <Structures/Vector.h>

#include <SFML/Graphics.hpp>

#include "Cog.h"
#include "Block.h"

class RiderHat;

class CogRider : public sf::Transformable
{
public:
	enum Affiliation
	{
		None = 1,
		Red = 2,
		Blue = 4,
		Green = 8,
		Yellow = 16
	};

	/*
	For sending collision information through the MessageBus
	*/
	struct RiderPair
	{
		CogRider* riderA;
		CogRider* riderB;
	};

public:
	CogRider(Soul::TextureManager& textures, f32 x, f32 y, Affiliation affiliation);

	CogRider(const CogRider&) = delete;
	CogRider(CogRider&& other) noexcept;

	~CogRider();

	CogRider& operator=(const CogRider&) = delete;
	CogRider& operator=(CogRider&& other) noexcept;

	void Update(f32 dt);
	void Draw(sf::RenderStates states) const;

	void CheckCollisions(Soul::Vector<Cog*>& allCogs);
	void CheckCollisions(Soul::Vector<Block*>& allBlocks);
	void CheckCollisions(Soul::Vector<CogRider*>& allCogRiders);

	void AddHat(Soul::TextureManager& textures, Affiliation affiliation);

	void MeltCog();
	void MeltOldCog();

	Affiliation GetAffiliation() const;
	u32 GetValue() const;
	
private:
	bool IsCollidingWithRider() const;
	void SetCollidingWithRider();

private:
	sf::Sprite m_Sprite;
	Affiliation m_Affiliation;
	Cog* m_AttachedCog;
	f32 m_AttachedAngle;
	Cog* m_OldCog;
	Block* m_InBlock;
	Soul::Listener m_Listener;
	Soul::Vector<RiderHat*> m_Hats;
	bool m_IsCollidingWithRider;
	u32 m_Value;
};