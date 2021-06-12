#include "TestLevelScene.h"

#include <IO/InputManager.h>
#include <Core/MessageBus.h>

TestLevelScene::TestLevelScene() :
	m_Textures(),
	m_Fonts(),
	m_FollowCog(m_Textures, Cog::Size::Medium),
	m_CogRiders(),
	m_Cogs(),
	m_Blocks(),
	m_Listener(),
	m_CogQueue(m_Fonts, m_Textures, 5, 5, 5)
{
	CogRider* cogRider = PARTITION(CogRider, m_Textures, 50, 100, CogRider::Green);
	CogRider* cogRider2 = PARTITION(CogRider, m_Textures, 50, -200, CogRider::Yellow);
	CogRider* cogRider3 = PARTITION(CogRider, m_Textures, 50, -300, CogRider::Red);
	CogRider* cogRider4 = PARTITION(CogRider, m_Textures, 50, 100, CogRider::Blue);
	CogRider* cogRider5 = PARTITION(CogRider, m_Textures, 50, 100, CogRider::Blue);
	m_CogRiders.Push(cogRider);
	m_CogRiders.Push(cogRider2);
	m_CogRiders.Push(cogRider3);
	m_CogRiders.Push(cogRider4);
	m_CogRiders.Push(cogRider5);

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

	m_Listener.Subscribe("MeltRider",
		[&](void* data)
		{
			m_CogRiders.Remove((CogRider*)data);
			Soul::MemoryManager::FreeMemory((CogRider*)data);
		});

	m_Listener.Subscribe("RiderCollision",
		[&](void* data)
		{
			CogRider::RiderPair* pair = (CogRider::RiderPair*)data;
			pair->riderA->AddHat(m_Textures, pair->riderB->GetAffiliation());

			m_CogRiders.Remove(pair->riderB);
			Soul::MemoryManager::FreeMemory(pair->riderB);
			Soul::MemoryManager::FreeMemory(pair);
		});
}

TestLevelScene::~TestLevelScene()
{
	for (u32 i = 0; i < m_CogRiders.Count(); i++)
		Soul::MemoryManager::FreeMemory(m_CogRiders[i]);
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

	for (u32 i = 0; i < m_CogRiders.Count(); i++)
	{
		m_CogRiders[i]->Update(dt);
		m_CogRiders[i]->CheckCollisions(m_Cogs);
		m_CogRiders[i]->CheckCollisions(m_Blocks);
		m_CogRiders[i]->CheckCollisions(m_CogRiders);
	}

	// E to change selected part
	if (Soul::InputManager::GetControlState(-1, "ChangePart").state == Soul::Controller::Pressed)
		m_FollowCog.NextSize();
	// click, check for selected part and place if can

	if (Soul::InputManager::GetControlState(-1, "Click").state == Soul::Controller::Pressed &&
		m_CogQueue.CanPlace(m_FollowCog.GetSize()))
	{
		Cog* newCog = m_FollowCog.MakeCog();
		if (newCog)
		{
			m_Cogs.Push(newCog);
			Cog::Size* size = PARTITION(Cog::Size);
			*size = m_FollowCog.GetSize();
			Soul::MessageBus::QueueMessage("PlacedCog", size);
		}
	}
}

void TestLevelScene::Draw(sf::RenderStates states) const
{
	for (u32 i = 0; i < m_Blocks.Count(); i++)
		m_Blocks[i]->Draw(states);
	for (u32 i = 0; i < m_Cogs.Count(); i++)
		m_Cogs[i]->Draw(states);
	m_FollowCog.Draw(states);
	for (u32 i = 0; i < m_CogRiders.Count(); i++)
		m_CogRiders[i]->Draw(states);

	m_CogQueue.Draw(states);
}