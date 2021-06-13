#include "PauseScene.h"

#include <Core/SceneManager.h>
#include <IO/InputManager.h>
#include <UI/UIButton.h>
#include <Rendering/Renderer.h>

#include "MainMenuScene.h"

PauseScene::PauseScene() :
	Scene(false, true),
	m_MenuBG(sf::Vector2f(1280, 720)),
	m_Fonts(),
	m_UI()
{
	Soul::UIButton* resume = PARTITION(Soul::UIButton, "Resume", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Pop, nullptr });
		});
	Soul::UIButton* mainMenu = PARTITION(Soul::UIButton, "Main Menu", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
			MainMenuScene* mainMenu = PARTITION(MainMenuScene);
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Push, mainMenu });
		});
	Soul::UIButton* quit = PARTITION(Soul::UIButton, "Quit", *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"),
		[]()
		{
			Soul::SceneManager::PushCommand({ Soul::SceneManager::Clear, nullptr });
		});

	resume->setPosition(35, 300);
	mainMenu->setPosition(35, 350);
	quit->setPosition(35, 400);

	resume->AddConnection(Soul::UIComponent::Up, quit);
	resume->AddConnection(Soul::UIComponent::Down, mainMenu);
	mainMenu->AddConnection(Soul::UIComponent::Up, resume);
	mainMenu->AddConnection(Soul::UIComponent::Down, quit);
	quit->AddConnection(Soul::UIComponent::Up, mainMenu);
	quit->AddConnection(Soul::UIComponent::Down, resume);

	m_UI.AddUIComponent(resume);
	m_UI.AddUIComponent(mainMenu);
	m_UI.AddUIComponent(quit);

	m_MenuBG.setFillColor(sf::Color(0, 0, 0, 125));
}

PauseScene::PauseScene(PauseScene&& other) noexcept :
	m_MenuBG(std::move(other.m_MenuBG)),
	m_Fonts(std::move(other.m_Fonts)),
	m_UI(std::move(other.m_UI))
{
}

PauseScene& PauseScene::operator=(PauseScene&& other) noexcept
{
	m_MenuBG = std::move(other.m_MenuBG);
	m_Fonts = std::move(other.m_Fonts);
	m_UI = std::move(other.m_UI);

	return *this;
}

void PauseScene::Update(f32 dt)
{
	if (Soul::InputManager::GetControlState(-1, "Pause").state == Soul::Controller::Pressed)
		Soul::SceneManager::PushCommand({ Soul::SceneManager::Pop, nullptr });
	else
		m_UI.Update(dt);
}

void PauseScene::Draw(sf::RenderStates states) const
{
	Soul::Renderer::Render(m_MenuBG, states);
	m_UI.Draw(states);
}