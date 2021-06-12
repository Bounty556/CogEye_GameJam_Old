#include "TestLevelScene.h"

#include <IO/InputManager.h>	

TestLevelScene::TestLevelScene() :
	m_Textures(),
	m_FollowCog(m_Textures, Cog::Size::Medium, 50),
	m_CogRider(m_Textures, 50, 100, CogRider::Green),
	m_Cogs(),
	m_Blocks(),
	m_Listener()
{
	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	cog->setPosition(150, 200);
	cog2->setPosition(200, 500);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);

	Block* block = PARTITION(Block, m_Textures, Block::Wood, 175.0f, 200.0f, 150, 50);
	m_Blocks.Push(block);

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
	for (u32 i = 0; i < m_Blocks.Count(); i++)
		Soul::MemoryManager::FreeMemory(m_Blocks[i]);
}

void TestLevelScene::Update(f32 dt)
{
	for (u32 i = 0; i < m_Cogs.Count(); i++)
		m_Cogs[i]->Update(dt);
	m_FollowCog.Update(dt);
	m_FollowCog.CheckCollisions(m_Cogs);

	m_CogRider.Update(dt);
	m_CogRider.CheckCollisions(m_Cogs);
	m_CogRider.CheckCollisions(m_Blocks);

	if (Soul::InputManager::GetControlState(-1, "Click").state == Soul::Controller::Pressed)
	{
		Cog* newCog = m_FollowCog.MakeCog();
		if (newCog)
			m_Cogs.Push(newCog);
	}
}

void TestLevelScene::Draw(sf::RenderStates states) const
{
	for (u32 i = 0; i < m_Blocks.Count(); i++)
		m_Blocks[i]->Draw(states);
	for (u32 i = 0; i < m_Cogs.Count(); i++)
		m_Cogs[i]->Draw(states);
	m_FollowCog.Draw(states);
	m_CogRider.Draw(states);
}