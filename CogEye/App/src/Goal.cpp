#include "Goal.h"

#include <Core/MessageBus.h>
#include <Rendering/Renderer.h>

Goal::Goal(u32 required, Soul::FontManager& fonts, f32 x, f32 y, f32 width, f32 height) :
	m_Rect(sf::Vector2f(width, height)),
	m_Label("", *fonts.RequestFont("res/Fonts/m5x7.ttf")),
	m_Required(required),
	m_Reached(0)
{
	m_Rect.setFillColor(sf::Color(60, 210, 60, 75));
	m_Rect.setOutlineThickness(-5.0f);
	m_Rect.setOutlineColor(sf::Color(35, 210, 35, 75));

	Soul::String labelText = "0/";
	labelText += Soul::String::IntToString(required);
	m_Label.SetText(labelText.GetCString());

	setPosition(x, y);

	m_Label.setPosition(0, -35);
}

void Goal::Draw(sf::RenderStates states) const
{
	states.transform *= getTransform();
	Soul::Renderer::Render(m_Rect, states);
	m_Label.Draw(states);
}

void Goal::CheckCollisions(const Soul::Vector<CogRider*>& cogRiders)
{
	for (u32 i = 0; i < cogRiders.Count(); i++)
	{
		sf::Vector2f riderPos = cogRiders[i]->getPosition();
		sf::Vector2f blockSize = m_Rect.getSize();
		if (riderPos.x - getPosition().x >= 0 &&
			riderPos.x - getPosition().x <= (f32)blockSize.x &&
			riderPos.y - getPosition().y >= 0 &&
			riderPos.y - getPosition().y <= (f32)blockSize.y)
		{
			// Cog rider hit goal
			m_Reached += cogRiders[i]->GetValue();

			Soul::String labelText = "";
			labelText += Soul::String::IntToString(m_Reached);
			labelText += '/';
			labelText += Soul::String::IntToString(m_Required);
			m_Label.SetText(labelText.GetCString());

			Soul::MessageBus::QueueMessage("GoalReached", cogRiders[i]);

			if (m_Reached >= m_Required)
				Soul::MessageBus::QueueMessage("LevelComplete", nullptr);
		}
	}
}