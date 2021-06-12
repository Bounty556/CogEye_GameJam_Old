#pragma once

#include <Defines.h>
#include <Structures/Vector.h>
#include <Resources/TextureManager.h>

#include <SFML/Graphics.hpp>

#include "Cog.h"

class FollowCog : public sf::Transformable
{
public:
	FollowCog(Soul::TextureManager& textures, Cog::Size size);

	void Update(f32 dt);
	void Draw(sf::RenderStates states) const;

	void NextSize();
	void CheckCollisions(Soul::Vector<Cog*>& allCogs);
	Cog* MakeCog();

	Cog::Size GetSize() const;

private:
	void ResetSprite();

private:
	Cog::Size m_Size;
	Soul::Vector<Cog*> m_Connections;
	sf::Sprite m_Sprite;
	f32 m_Radius;
	Soul::TextureManager& m_Textures;
};