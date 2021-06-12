#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>
#include <UI/UIContainer.h>
#include <UI/UILabel.h>
#include <Resources/FontManager.h>
#include <Resources/TextureManager.h>
#include <Core/Listener.h>

#include <SFML/Graphics.hpp>

#include "Cog.h"

class CogQueue
{
public:
	CogQueue(Soul::FontManager& font, Soul::TextureManager& textures, u32 smallCogs, u32 medCogs, u32 largeCogs);

	CogQueue(const CogQueue&) = delete;
	CogQueue(CogQueue&& other) noexcept;

	CogQueue& operator=(const CogQueue&) = delete;
	CogQueue& operator=(CogQueue&& other) noexcept;

	void Update(f32 dt);
	void Draw(sf::RenderStates states) const;

	bool CanPlace(Cog::Size cogSize);

private:
	u32 m_CogsLeft[3];
	Soul::UIContainer m_UI;
	Soul::UILabel* m_CogText[3];
	Soul::Listener m_Listener;
};