#pragma once

#include <Defines.h>
#include <Structures/Vector.h>
#include <Resources/TextureManager.h>

#include <SFML/Graphics.hpp>

class Cog : public sf::Transformable
{
public:
	enum Direction
	{
		CounterClockwise = -1,
		None = 0,
		Clockwise = 1
	};

	enum Size
	{
		Small,
		Medium,
		Large
	};

public:
	Cog(Soul::TextureManager& textures, Direction direction, Size size, f32 radius, f32 rotSpeed);

	Cog(const Cog&) = delete;
	Cog(Cog&& other) noexcept;

	~Cog();

	Cog& operator=(const Cog&) = delete;
	Cog& operator=(Cog&& other) noexcept;

	void Update(f32 dt);
	void Draw(sf::RenderStates states) const;

	void AddConnection(Cog* connection);
	void RemoveConnection(Cog* connection);

	Direction GetDirection() const;
	f32 GetRadius() const;
	f32 GetRotSpeed() const;

private:
	Direction m_Direction;
	Size m_Size;
	Soul::Vector<Cog*> m_Connections;
	sf::Sprite m_Sprite;
	f32 m_Radius;
	f32 m_RotSpeed;
};