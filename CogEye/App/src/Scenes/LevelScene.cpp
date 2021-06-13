#include "LevelScene.h"

#include <IO/InputManager.h>
#include <Core/MessageBus.h>
#include <Core/SceneManager.h>

#include "PauseScene.h"

LevelScene::LevelScene(u32 small, u32 med, u32 large, u32 goalNeeded, f32 goalX, f32 goalY, f32 goalWidth, f32 goalHeight) :
	Scene(true, true),
	m_Textures(),
	m_Fonts(),
	m_FollowCog(m_Textures, Cog::Size::Small),
	m_CogRiders(),
	m_Cogs(),
	m_Blocks(),
	m_Listener(),
	m_CogQueue(m_Fonts, m_Textures, small, med, large),
	m_Goal(goalNeeded, m_Fonts, goalX, goalY, goalWidth, goalHeight)
{
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

	m_Listener.Subscribe("GoalReached",
		[&](void* data)
		{
			((CogRider*)data)->MeltCog();
			m_CogRiders.Remove((CogRider*)data);
			Soul::MemoryManager::FreeMemory((CogRider*)data);
		});

	m_Listener.Subscribe("LevelComplete",
		[&](void* data)
		{
			LOG_DEBUG("Level complete!");
		});
}

LevelScene::~LevelScene()
{
	for (u32 i = 0; i < m_CogRiders.Count(); i++)
		Soul::MemoryManager::FreeMemory(m_CogRiders[i]);
	for (u32 i = 0; i < m_Cogs.Count(); i++)
		Soul::MemoryManager::FreeMemory(m_Cogs[i]);
	for (u32 i = 0; i < m_Blocks.Count(); i++)
		Soul::MemoryManager::FreeMemory(m_Blocks[i]);
}

void LevelScene::Update(f32 dt)
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

	m_Goal.CheckCollisions(m_CogRiders);

	// E to change selected part
	if (Soul::InputManager::GetControlState(-1, "ChangePart").state == Soul::Controller::Pressed)
		m_FollowCog.NextSize();
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
	if (Soul::InputManager::GetControlState(-1, "Restart").state == Soul::Controller::Pressed)
		ResetScene();
	if (Soul::InputManager::GetControlState(-1, "Pause").state == Soul::Controller::Pressed)
		Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(PauseScene) });
}

void LevelScene::Draw(sf::RenderStates states) const
{
	for (u32 i = 0; i < m_Blocks.Count(); i++)
		m_Blocks[i]->Draw(states);

	m_Goal.Draw(states);

	for (u32 i = 0; i < m_Cogs.Count(); i++)
		m_Cogs[i]->Draw(states);

	m_FollowCog.Draw(states);

	for (u32 i = 0; i < m_CogRiders.Count(); i++)
		m_CogRiders[i]->Draw(states);

	m_CogQueue.Draw(states);
}