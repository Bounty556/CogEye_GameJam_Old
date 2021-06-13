#include "Level1Scene.h"

#include <Core/SceneManager.h>
#include <Rendering/Renderer.h>

#include "Level2Scene.h"

#define TUTORIAL_TEXT "Welcome to Cog Eye!\nYour goal is to get enough Cog Riders (that little white rectangle on the left)\ninto the goal on the right to meet the quota listed just above it.\nTo do this, you'll need to connect some cogs to that big cog on the left.\nIn the top left you'll see how many cogs of each size you have available to you.\nPress 'E' to select your desired size, then Left click to place it.\nRestart - 'R'\nSpeed Up - 'Space'"

Level1Scene::Level1Scene() :
	LevelScene(2, 2, 2, 1, 1000, 300, 200, 150),
	m_TutorialText(TUTORIAL_TEXT, *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"))
{
	m_TutorialText.setPosition(400, 20);

	CogRider* cogRider = PARTITION(CogRider, m_Textures, 250, 250, CogRider::None);
	m_CogRiders.Push(cogRider);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	cog->setPosition(250, 400);
	m_Cogs.Push(cog);
}

void Level1Scene::NextLevel()
{
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
	Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level2Scene) });
}

void Level1Scene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}

void Level1Scene::Draw(sf::RenderStates states) const
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
