#include "CogQueue.h"

CogQueue::CogQueue(u32 smallCogs, u32 medCogs, u32 largeCogs) :
	m_UI()
{
	m_CogsLeft[0] = smallCogs;
	m_CogsLeft[1] = medCogs;
	m_CogsLeft[2] = largeCogs;
}

CogQueue::CogQueue(CogQueue&& other) noexcept :
	m_UI(std::move(other.m_UI))
{
	m_CogsLeft[0] = other.m_CogsLeft[0];
	m_CogsLeft[1] = other.m_CogsLeft[1];
	m_CogsLeft[2] = other.m_CogsLeft[2];
}

CogQueue& CogQueue::operator=(CogQueue&& other) noexcept
{
	m_UI = std::move(other.m_UI);
	m_CogsLeft[0] = other.m_CogsLeft[0];
	m_CogsLeft[1] = other.m_CogsLeft[1];
	m_CogsLeft[2] = other.m_CogsLeft[2];

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