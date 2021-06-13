#include "LevelFinishScene.h"

#include <Core/MessageBus.h>
#include <UI/UIButton.h>

LevelFinishScene::LevelFinishScene() :
	Scene(true, true),
	m_Container(),
	m_Fonts()
{
	Soul::UIButton* nextLevel = PARTITION(Soul::UIButton, "Press 'Enter' to Continue", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::MessageBus::QueueMessage("NextLevel", nullptr);
		});

	nextLevel->setPosition(500, 650);
	m_Container.AddUIComponent(nextLevel);
}

void LevelFinishScene::Update(f32 dt)
{
	m_Container.Update(dt);
}

void LevelFinishScene::Draw(sf::RenderStates states) const
{
	m_Container.Draw(states);
}