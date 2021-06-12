#include "TestLevelScene.h"

#include <IO/InputManager.h>	

TestLevelScene::TestLevelScene() :
	m_Textures(),
	m_FollowCog(m_Textures, Cog::Size::Medium, 50),
	m_CogRider(m_Textures, 50, 100, CogRider::Green),
	m_Cogs(),
	m_Listener()
{
	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 150, 0.1f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 150, 0.1f);
	cog->setPosition(100, 500);
	cog2->setPosition(1000, 500);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);

	m_Listener.Subscribe("MeltCog",
		[&](void* data)
		{
			m_Cogs.Remove((Cog*)data);
			Soul::MemoryManager::FreeMemory((Cog*)data);
		});
}

TestLevelScene::~TestLevelScene()
{
	for (u32 i = 0; i < m_Cogs.Count(); i++)
		Soul::MemoryManager::FreeMemory(m_Cogs[i]);
}

void TestLevelScene::Update(f32 dt)
{
	for (u32 i = 0; i < m_Cogs.Count(); i++)
		m_Cogs[i]->Update(dt);
	m_FollowCog.Update(dt);
	m_FollowCog.CheckCollisions(m_Cogs);

	m_CogRider.Update(dt);
	m_CogRider.CheckCollisions(m_Cogs);

	if (Soul::InputManager::GetControlState(-1, "Click").state == Soul::Controller::Pressed)
	{
		Cog* newCog = m_FollowCog.MakeCog();
		if (newCog)
			m_Cogs.Push(newCog);
	}
}

void TestLevelScene::Draw(sf::RenderStates states) const
{
	for (u32 i = 0; i < m_Cogs.Count(); i++)
		m_Cogs[i]->Draw(states);
	m_FollowCog.Draw(states);
	m_CogRider.Draw(states);
}