#include "TestLevelScene.h"

#include <Core/SceneManager.h>

TestLevelScene::TestLevelScene() :
	LevelScene(5, 5, 5, 3, 1000, 300, 200, 150)
{
	CogRider* cogRider = PARTITION(CogRider, m_Textures, 50, 100, CogRider::Green);
	CogRider* cogRider2 = PARTITION(CogRider, m_Textures, 50, -200, CogRider::Yellow);
	CogRider* cogRider3 = PARTITION(CogRider, m_Textures, 50, -300, CogRider::Red);
	CogRider* cogRider4 = PARTITION(CogRider, m_Textures, 50, 100, CogRider::Blue);
	m_CogRiders.Push(cogRider);
	m_CogRiders.Push(cogRider2);
	m_CogRiders.Push(cogRider3);
	m_CogRiders.Push(cogRider4);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Large, 125, 0.1f);
	cog->setPosition(150, 200);
	cog2->setPosition(200, 500);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);

	Block* block = PARTITION(Block, m_Textures, Block::Wood, 175.0f, 200.0f, 150, 50);
	m_Blocks.Push(block);
}

void TestLevelScene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}

void TestLevelScene::NextLevel()
{

}