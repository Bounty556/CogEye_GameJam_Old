#include "CreditsScene.h"

#include <UI/UIButton.h>
#include <UI/UILabel.h>
#include <Core/SceneManager.h>

#include "MainMenuScene.h"

#define CREDITS "Fonts - Daniel Linsson\nArt Assets - Bluce, Luke.RUSTLTD, Alex Tepetidis\nAudio Assets - Alexander Nakarada, Michel Baradari, timgormly\n\nThis game was submitted to the 2021 GMTK Game Jam.\nThanks to Mark Brown for putting together this wonderful event.\n\nPress 'Enter' to return."

CreditsScene::CreditsScene() :
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

	back->setPosition(35, 660);

	Soul::UILabel* credits = PARTITION(Soul::UILabel, CREDITS, *m_Fonts.RequestFont("res/Fonts/m5x7.ttf"));
	credits->setPosition(100, 250);

	m_UI.AddUIComponent(back);
	m_UI.AddUIComponent(credits);
}

void CreditsScene::Update(f32 dt)
{
	m_UI.Update(dt);
}

void CreditsScene::Draw(sf::RenderStates states) const
{
	m_UI.Draw(states);
}