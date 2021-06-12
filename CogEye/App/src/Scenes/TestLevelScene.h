#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <Resources/TextureManager.h>
#include <Structures/Vector.h>
#include <Core/Listener.h>

#include "../Cog.h"
#include "../FollowCog.h"
#include "../CogRider.h"

class TestLevelScene : public Soul::Scene
{
public:
	TestLevelScene();

	~TestLevelScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	Soul::TextureManager m_Textures;
	FollowCog m_FollowCog;
	CogRider m_CogRider;
	Soul::Vector<Cog*> m_Cogs;
	Soul::Listener m_Listener;
};
