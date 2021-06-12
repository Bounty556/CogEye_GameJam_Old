#pragma once

#include <Defines.h>
#include <UI/UIContainer.h>

#include <SFML/Graphics.hpp>

#include "Cog.h"

class CogQueue
{
public:
	CogQueue(u32 smallCogs, u32 medCogs, u32 largeCogs);

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
};