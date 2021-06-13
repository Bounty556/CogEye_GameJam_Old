#include "Level1Scene.h"

#include <Core/SceneManager.h>

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

	m_Listener.Subscribe("LevelComplete",
		[&](void* data)
		{
			LOG_DEBUG("Level complete!");
		});
}

void Level1Scene::Draw(sf::RenderStates states) const
{
	m_TutorialText.Draw(states);
	LevelScene::Draw(states);
}

void Level1Scene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}