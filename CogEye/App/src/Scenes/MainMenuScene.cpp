#include "MainMenuScene.h"

#include <Memory/MemoryManager.h>
#include <UI/UIButton.h>
#include <Core/SceneManager.h>

#include <functional>

MainMenuScene::MainMenuScene() :
	m_UI(),
	m_Fonts()
{
	Soul::UIButton* startButton = PARTITION(Soul::UIButton, "Play", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"), []() { /**/ });
	Soul::UIButton* levelsButton = PARTITION(Soul::UIButton, "Levels", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"), []() { /**/ });
	Soul::UIButton* creditsButton = PARTITION(Soul::UIButton, "Credits", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"), []() { /**/ });
	Soul::UIButton* quitButton = PARTITION(Soul::UIButton, "Quit", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
		});

	startButton->AddConnection(Soul::UIButton::Up, quitButton);
	startButton->AddConnection(Soul::UIButton::Down, levelsButton);
	levelsButton->AddConnection(Soul::UIButton::Up, startButton);
	levelsButton->AddConnection(Soul::UIButton::Down, creditsButton);
	creditsButton->AddConnection(Soul::UIButton::Up, levelsButton);
	creditsButton->AddConnection(Soul::UIButton::Down, quitButton);
	quitButton->AddConnection(Soul::UIButton::Up, creditsButton);
	quitButton->AddConnection(Soul::UIButton::Down, startButton);

	startButton->setPosition(35, 300);
	levelsButton->setPosition(35, 350);
	creditsButton->setPosition(35, 400);
	quitButton->setPosition(35, 450);

	m_UI.AddUIComponent(startButton);
	m_UI.AddUIComponent(levelsButton);
	m_UI.AddUIComponent(creditsButton);
	m_UI.AddUIComponent(quitButton);
}

void MainMenuScene::Update(f32 dt)
{
	m_UI.Update(dt);
}

void MainMenuScene::Draw(sf::RenderStates states) const
{
	m_UI.Draw(states);
}
