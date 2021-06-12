#pragma once

#include <Defines.h>
#include <Resources/TextureManager.h>

#include <SFML/Graphics.hpp>

class Block : public sf::Transformable
{
public:
	enum BlockType
	{
		Wood,
		Lava
	};

public:
	Block(Soul::TextureManager& textures, BlockType blockType, f32 x, f32 y, i32 width, i32 height);

	Block(const Block&) = delete;
	Block(Block&& other) noexcept;

	Block& operator=(const Block&) = delete;
	Block& operator=(Block&& other) noexcept;

	void Draw(sf::RenderStates states) const;
	const sf::Vector2i& GetSize() const;
	BlockType GetBlockType() const;

private:
	sf::Sprite m_Sprite;
	sf::Vector2i m_Size;
	BlockType m_BlockType;
};