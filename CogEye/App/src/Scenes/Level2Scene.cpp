#include "Level2Scene.h"

#include <Core/SceneManager.h>
#include <Rendering/Renderer.h>

#define TUTORIAL_TEXT "You can't place a cog that connects\ntwo cogs rotating in opposite directions."

Level2Scene::Level2Scene() :
	LevelScene(1, 1, 2, 1, 1000, 300, 200, 150),
	m_TutorialText(TUTORIAL_TEXT, *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"))
{
	m_TutorialText.setPosition(550, 600);

	CogRider* cogRider = PARTITION(CogRider, m_Textures, 250, 250, CogRider::None);
	m_CogRiders.Push(cogRider);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Medium, 75, 0.5f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Medium, 75, 0.5f);
	Cog* cog3 = PARTITION(Cog, m_Textures, Cog::Direction::CounterClockwise, Cog::Size::Medium, 75, 0.5f);
	cog->setPosition(250, 400);
	cog2->setPosition(550, 400);
	cog3->setPosition(750, 400);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);
	m_Cogs.Push(cog3);
}

void Level2Scene::NextLevel()
{
	// TODO: Next level
}

void Level2Scene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}

void Level2Scene::Draw(sf::RenderStates states) const
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
