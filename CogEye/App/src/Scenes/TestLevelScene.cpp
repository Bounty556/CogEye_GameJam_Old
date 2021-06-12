#include "TestLevelScene.h"

TestLevelScene::TestLevelScene() :
	m_Textures(),
	m_Cog(m_Textures, Cog::Direction::None, Cog::Size::Medium, 50, 0.1f)
{
	m_Cog.setPosition(500, 500);
}

void TestLevelScene::Update(f32 dt)
{
	m_Cog.Update(dt);
}

void TestLevelScene::Draw(sf::RenderStates states) const
{
	m_Cog.Draw(states);
}