#include "Level1Scene.h"

#include <Core/SceneManager.h>

Level1Scene::Level1Scene() :
	LevelScene(2, 2, 2, 1, 1000, 300, 200, 150)
{
	CogRider* cogRider = PARTITION(CogRider, m_Textures, 250, 250, CogRider::None);
	m_CogRiders.Push(cogRider);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	cog->setPosition(250, 400);
	m_Cogs.Push(cog);
}

void Level1Scene::Draw(sf::RenderStates states) const
{
	LevelScene::Draw(states);
}

void Level1Scene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}