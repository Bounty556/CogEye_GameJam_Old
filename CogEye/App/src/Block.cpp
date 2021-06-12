#include "Block.h"

#include <Rendering/Renderer.h>

Block::Block(Soul::TextureManager& textures, BlockType blockType, f32 x, f32 y, i32 width, i32 height) :
	m_Sprite(),
	m_Size(width, height),
	m_BlockType(blockType)
{
	switch (blockType)
	{
		case BlockType::Wood:
		{
			m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/Wood.png", true));
		} break;

		case BlockType::Lava:
		{
			// TODO:
			m_Sprite.setTexture(*textures.RequestTexture("res/Sprites/Lava.png", true));
		} break;
	}

	m_Sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	setPosition(x, y);
}

Block::Block(Block&& other) noexcept :
	m_Sprite(std::move(other.m_Sprite)),
	m_Size(other.m_Size),
	m_BlockType(other.m_BlockType)
{
}

Block& Block::operator=(Block&& other) noexcept
{
	m_Sprite = std::move(other.m_Sprite);
	m_Size = other.m_Size;
	m_BlockType = other.m_BlockType;

	return *this;
}

void Block::Draw(sf::RenderStates states) const
{
	states.transform *= getTransform();
	Soul::Renderer::Render(m_Sprite, states);
}

const sf::Vector2i& Block::GetSize() const
{
	return m_Size;
}

Block::BlockType Block::GetBlockType() const
{
	return m_BlockType;
}