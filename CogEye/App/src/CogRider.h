#pragma once

#include <Defines.h>
#include <Resources/TextureManager.h>
#include <Structures/Vector.h>

#include <SFML/Graphics.hpp>

#include "Cog.h"
#include "Block.h"

class CogRider : public sf::Transformable
{
public:
	enum Affiliation
	{
		None = 0,
		Red = 1,
		Blue = 2,
		Green = 4,
		Yellow = 8
	};

public:
	CogRider(Soul::TextureManager& textures, f32 x, f32 y, Affiliation affiliation);

	CogRider(const CogRider&) = delete;
	CogRider(CogRider&& other) noexcept;

	CogRider& operator=(const CogRider&) = delete;
	CogRider& operator=(CogRider&& other) noexcept;

	void Update(f32 dt);
	void Draw(sf::RenderStates states) const;

	void CheckCollisions(Soul::Vector<Cog*>& allCogs);
	void CheckCollisions(Soul::Vector<Block*>& allBlocks);

private:
	sf::Sprite m_Sprite;
	Affiliation m_Affiliation;
	Cog* m_AttachedCog;
	f32 m_AttachedAngle;
	Cog* m_OldCog;
	Block* m_InBlock;
};