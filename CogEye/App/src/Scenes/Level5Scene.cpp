#include "Level5Scene.h"

#include <Core/SceneManager.h>
#include <Rendering/Renderer.h>

#include "LevelEndScene.h"

#define TUTORIAL_TEXT5 "The red Cog Rider moves backwards!\nYou can connect two Cog Riders by\ntouching them to combine their powers."

Level5Scene::Level5Scene() :
	LevelScene(0, 2, 2, 2, 1000, 300, 200, 150),
	m_TutorialText(TUTORIAL_TEXT5, *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"))
{
	m_TutorialText.setPosition(700, 200);

	CogRider* cogRider = PARTITION(CogRider, m_Textures, 100, 150, CogRider::None);
	CogRider* cogRider2 = PARTITION(CogRider, m_Textures, 200, 601, CogRider::Red);
	m_CogRiders.Push(cogRider);
	m_CogRiders.Push(cogRider2);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	Cog* cog3 = PARTITION(Cog, m_Textures, Cog::Direction::CounterClockwise, Cog::Size::Large, 125, 0.1f);
	cog->setPosition(200, 250);
	cog2->setPosition(200, 600);
	cog3->setPosition(600, 350);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);
	m_Cogs.Push(cog3);

	Block* block = PARTITION(Block, m_Textures, Block::Lava, 600, 450, 50, 250);
	m_Blocks.Push(block);
}

void Level5Scene::NextLevel()
{
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(LevelEndScene) });
}

void Level5Scene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}

void Level5Scene::Draw(sf::RenderStates states) const
{
	Soul::Renderer::Render(m_Background, states);
	m_TutorialText.Draw(states);

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
