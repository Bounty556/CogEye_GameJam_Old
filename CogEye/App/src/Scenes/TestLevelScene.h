#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <Resources/TextureManager.h>

#include "../Cog.h"

class TestLevelScene : public Soul::Scene
{
public:
	TestLevelScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	Soul::TextureManager m_Textures;
	Cog m_Cog;
};
