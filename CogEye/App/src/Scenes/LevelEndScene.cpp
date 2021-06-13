#include "LevelEndScene.h"

#include <Core/SceneManager.h>
#include <Rendering/Renderer.h>

#define END_TEXT "Thank you for playing Cog Eye!\nUnfortunately this is all I had time for during the Game Jam.\nAlthough it was short, I would be ever so grateful if you could rate this\ngame on Itch.io and let me know what you thought."

LevelEndScene::LevelEndScene() :
	LevelScene(99, 99, 99, 5, 10000, 10000, 200, 150),
	m_TutorialText(END_TEXT, *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"))
{
	m_TutorialText.setPosition(200, 550);

	CogRider* cogRider = PARTITION(CogRider, m_Textures, 200, 251, CogRider::None);
	CogRider* cogRider2 = PARTITION(CogRider, m_Textures, 400, 401, CogRider::Red);
	CogRider* cogRider3 = PARTITION(CogRider, m_Textures, 600, 251, CogRider::Green);
	CogRider* cogRider4 = PARTITION(CogRider, m_Textures, 800, 401, CogRider::Blue);
	CogRider* cogRider5 = PARTITION(CogRider, m_Textures, 1000, 251, CogRider::Yellow);
	m_CogRiders.Push(cogRider);
	m_CogRiders.Push(cogRider2);
	m_CogRiders.Push(cogRider3);
	m_CogRiders.Push(cogRider4);
	m_CogRiders.Push(cogRider5);

	Cog* cog = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Medium, 50, 0.2f);
	Cog* cog2 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Medium, 50, 0.2f);
	Cog* cog3 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Medium, 50, 0.2f);
	Cog* cog4 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Medium, 50, 0.2f);
	Cog* cog5 = PARTITION(Cog, m_Textures, Cog::Direction::Clockwise, Cog::Size::Medium, 50, 0.2f);
	cog->setPosition(200, 250);
	cog2->setPosition(400, 400);
	cog3->setPosition(600, 250);
	cog4->setPosition(800, 400);
	cog5->setPosition(1000, 250);
	m_Cogs.Push(cog);
	m_Cogs.Push(cog2);
	m_Cogs.Push(cog3);
	m_Cogs.Push(cog4);
	m_Cogs.Push(cog5);
}

void LevelEndScene::NextLevel()
{
	// TODO: Next level
}

void LevelEndScene::ResetScene()
{
	Soul::SceneManager::ResetScene(this, nullptr);
}

void LevelEndScene::Draw(sf::RenderStates states) const
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
