#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Core/String.h>

#include "Scenes/MainMenuScene.h"

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		MainMenuScene* mainScene = PARTITION(MainMenuScene);

		Soul::SetScene(mainScene);
	}

	Soul::ShutdownEngine();
	return 0;
}