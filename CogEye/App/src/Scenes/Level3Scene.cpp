#include "Level3Scene.h"

#include <Core/SceneManager.h>
#include <Rendering/Renderer.h>

#include "Level4Scene.h"

#define TUTORIAL_TEXT3 "If a Cog Rider touches a wood block,\nit will be knocked off."

Level3Scene::Level3Scene() :
	LevelScene(0, 2, 2, 1, 1000, 300, 200, 150),
	m_TutorialText(TUTORIAL_TEXT3, *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"))
{
	m_TutorialText.setPosition(100, 400);

	CogRider* cogRider = PARTITION(CogRider, m_Textures, 250, 249, CogRider::None);
	m_CogRiders.Push(cogRider);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	cog->setPosition(250, 225);
	cog2->setPosition(650, 575);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);

	Block* block = PARTITION(Block, m_Textures, Block::Wood, 610, 50, 50, 250);
	m_Blocks.Push(block);
}

void Level3Scene::NextLevel()
{
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level4Scene) });
}

void Level3Scene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}

void Level3Scene::Draw(sf::RenderStates states) const
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
