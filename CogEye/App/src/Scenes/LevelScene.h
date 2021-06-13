#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <Resources/TextureManager.h>
#include <Structures/Vector.h>
#include <Core/Listener.h>

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

protected:
	Soul::TextureManager m_Textures;
	Soul::FontManager m_Fonts;
	FollowCog m_FollowCog;
	Soul::Vector<CogRider*> m_CogRiders;
	Soul::Vector<Cog*> m_Cogs;
	Soul::Vector<Block*> m_Blocks;
	Soul::Listener m_Listener;
	CogQueue m_CogQueue;
	Goal m_Goal;
};
