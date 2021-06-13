#include "Level4Scene.h"

#include <Core/SceneManager.h>
#include <Rendering/Renderer.h>

#include "Level5Scene.h"

#define TUTORIAL_TEXT4 "Watchout for the lava!"

Level4Scene::Level4Scene() :
	LevelScene(1, 0, 3, 1, 1000, 300, 200, 150),
	m_TutorialText(TUTORIAL_TEXT4, *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"))
{
	m_TutorialText.setPosition(700, 200);

	CogRider* cogRider = PARTITION(CogRider, m_Textures, 200, 328, CogRider::None);
	m_CogRiders.Push(cogRider);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::CounterClockwise, Cog::Size::Large, 125, 0.1f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::CounterClockwise, Cog::Size::Large, 125, 0.1f);
	Cog* cog3 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	cog->setPosition(200, 325);
	cog2->setPosition(450, 575);
	cog3->setPosition(750, 350);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);
	m_Cogs.Push(cog3);

	Block* block = PARTITION(Block, m_Textures, Block::Lava, 430, 150, 50, 350);
	m_Blocks.Push(block);
}

void Level4Scene::NextLevel()
{
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level5Scene) });
}

void Level4Scene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}

void Level4Scene::Draw(sf::RenderStates states) const
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
