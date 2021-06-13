#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Core/String.h>

#include "Scenes/MainMenuScene.h"
#include "Scenes/TestLevelScene.h"

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Cog Eye"))
	{
		MainMenuScene* testScene = PARTITION(MainMenuScene);

		Soul::SetScene(testScene);
	}

	Soul::ShutdownEngine();
	return 0;
}