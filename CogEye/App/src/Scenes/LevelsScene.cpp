#include "LevelsScene.h"

#include <UI/UIButton.h>
#include <Core/SceneManager.h>

#include "MainMenuScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Level3Scene.h"
#include "Level4Scene.h"
#include "Level5Scene.h"

LevelsScene::LevelsScene() :
	Scene(true, true),
	m_UI(),
	m_Fonts()
{
	Soul::UIButton* back = PARTITION(Soul::UIButton, "Back", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(MainMenuScene) });
		});

	Soul::UIButton* level1 = PARTITION(Soul::UIButton, "Level 1", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level1Scene) });
		});

	Soul::UIButton* level2 = PARTITION(Soul::UIButton, "Level 2", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level2Scene) });
		});

	Soul::UIButton* level3 = PARTITION(Soul::UIButton, "Level 3", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level3Scene) });
		});

	Soul::UIButton* level4 = PARTITION(Soul::UIButton, "Level 4", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level4Scene) });
		});

	Soul::UIButton* level5 = PARTITION(Soul::UIButton, "Level 5", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, PARTITION(Level5Scene) });
		});

	level1->setPosition(35, 100);
	level2->setPosition(35, 150);
	level3->setPosition(35, 200);
	level4->setPosition(35, 250);
	level5->setPosition(35, 300);
	back->setPosition(35, 660);

	level1->AddConnection(Soul::UIComponent::Up, back);
	level1->AddConnection(Soul::UIComponent::Down, level2);
	level2->AddConnection(Soul::UIComponent::Up, level1);
	level2->AddConnection(Soul::UIComponent::Down, level3);
	level3->AddConnection(Soul::UIComponent::Up, level2);
	level3->AddConnection(Soul::UIComponent::Down, level4);
	level4->AddConnection(Soul::UIComponent::Down, level3);
	level4->AddConnection(Soul::UIComponent::Down, level5);
	level5->AddConnection(Soul::UIComponent::Down, level4);
	level5->AddConnection(Soul::UIComponent::Down, back);
	back->AddConnection(Soul::UIComponent::Up, level5);
	back->AddConnection(Soul::UIComponent::Down, level1);

	m_UI.AddUIComponent(level1);
	m_UI.AddUIComponent(level2);
	m_UI.AddUIComponent(level3);
	m_UI.AddUIComponent(level4);
	m_UI.AddUIComponent(level5);
	m_UI.AddUIComponent(back);
}

void LevelsScene::Update(f32 dt)
{
	m_UI.Update(dt);
}

void LevelsScene::Draw(sf::RenderStates states) const
{
	m_UI.Draw(states);
}