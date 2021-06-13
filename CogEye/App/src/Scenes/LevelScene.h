#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <Resources/TextureManager.h>
#include <Resources/FontManager.h>
#include <Resources/SoundManager.h>
#include <Structures/Vector.h>
#include <Core/Listener.h>

#include <SFML/Audio.hpp>

#include "../Cog.h"
#include "../FollowCog.h"
#include "../CogRider.h"
#include "../Block.h"
#include "../CogQueue.h"
#include "../Goal.h"

class LevelScene : public Soul::Scene
{
public:
	LevelScene(u32 small, u32 med, u32 large, u32 goalNeeded, f32 goalX, f32 goalY, f32 goalWidth, f32 goalHeight);

	virtual ~LevelScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;
	virtual void ResetScene() = 0;
	virtual void NextLevel() = 0;

protected:
	Soul::TextureManager m_Textures;
	Soul::FontManager m_Fonts;
	Soul::SoundManager m_Sounds;
	FollowCog m_FollowCog;
	Soul::Vector<CogRider*> m_CogRiders;
	Soul::Vector<Cog*> m_Cogs;
	Soul::Vector<Block*> m_Blocks;
	Soul::Listener m_Listener;
	CogQueue m_CogQueue;
	Goal m_Goal;
	sf::Sprite m_Background;
	sf::Sound m_CogSound;
	sf::Sound m_MeltSound;
};
