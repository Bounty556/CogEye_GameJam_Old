#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Core/String.h>

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
	}

	Soul::ShutdownEngine();
	return 0;
}