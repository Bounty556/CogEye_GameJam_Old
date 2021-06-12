#include "CogQueue.h"

#include <UI/UISprite.h>

CogQueue::CogQueue(Soul::FontManager& fonts, Soul::TextureManager& textures, u32 smallCogs, u32 medCogs, u32 largeCogs) :
	m_UI(),
	m_Listener()
{
	m_CogsLeft[0] = smallCogs;
	m_CogsLeft[1] = medCogs;
	m_CogsLeft[2] = largeCogs;
	m_CogText[0] = PARTITION(Soul::UILabel, Soul::String::IntToString(smallCogs).GetCString(), *fonts.RequestFont("res/Fonts/m5x7.ttf"));
	m_CogText[1] = PARTITION(Soul::UILabel, Soul::String::IntToString(medCogs).GetCString(), *fonts.RequestFont("res/Fonts/m5x7.ttf"));
	m_CogText[2] = PARTITION(Soul::UILabel, Soul::String::IntToString(largeCogs).GetCString(), *fonts.RequestFont("res/Fonts/m5x7.ttf"));

	Soul::UISprite* small = PARTITION(Soul::UISprite, *textures.RequestTexture("res/Sprites/SmallCog1.png"), 64, 64);
	Soul::UISprite* medium = PARTITION(Soul::UISprite, *textures.RequestTexture("res/Sprites/MediumCog1.png"), 64, 64);
	Soul::UISprite* large = PARTITION(Soul::UISprite, *textures.RequestTexture("res/Sprites/LargeCog1.png"), 64, 64);

	m_CogText[0]->setPosition(50, 25);
	small->setPosition(75, 25);
	m_CogText[1]->setPosition(150, 25);
	medium->setPosition(175, 25);
	m_CogText[2]->setPosition(250, 25);
	large->setPosition(275, 25);
	m_UI.AddUIComponent(m_CogText[0]);
	m_UI.AddUIComponent(m_CogText[1]);
	m_UI.AddUIComponent(m_CogText[2]);
	m_UI.AddUIComponent(small);
	m_UI.AddUIComponent(medium);
	m_UI.AddUIComponent(large);

	m_Listener.Subscribe("PlacedCog",
		[&](void* data)
		{
			u32 size = *(Cog::Size*)data;
			m_CogsLeft[size]--;
			m_CogText[size]->SetText(Soul::String::IntToString(m_CogsLeft[size]).GetCString());
			Soul::MemoryManager::FreeMemory((Cog::Size*)data);
		});
}

CogQueue::CogQueue(CogQueue&& other) noexcept :
	m_UI(std::move(other.m_UI))
{
	for (u32 i = 0; i < 3; i++)
	{
		m_CogsLeft[i] = other.m_CogsLeft[i];
		m_CogText[i] = other.m_CogText[i];
		other.m_CogText[i] = nullptr;
	}
}

CogQueue& CogQueue::operator=(CogQueue&& other) noexcept
{
	m_UI = std::move(other.m_UI);
	for (u32 i = 0; i < 3; i++)
	{
		m_CogsLeft[i] = other.m_CogsLeft[i];
		m_CogText[i] = other.m_CogText[i];
		other.m_CogText[i] = nullptr;
	}

	return *this;
}

void CogQueue::Update(f32 dt)
{
	m_UI.Update(dt);
}

void CogQueue::Draw(sf::RenderStates states) const
{
	m_UI.Draw(states);
}

bool CogQueue::CanPlace(Cog::Size cogSize)
{
	return m_CogsLeft[(u32)cogSize] > 0;
}