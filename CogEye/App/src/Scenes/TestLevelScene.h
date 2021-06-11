#pragma once

#include <Defines.h>
#include <Core/Scene.h>

class TestLevelScene : public Soul::Scene
{
public:
	TestLevelScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;
};
