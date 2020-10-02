#include "../../../Engine/Core/CoreEngine.h"
#include "../../../Game/Game1.h"

int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("GAME258 Engine", 900, 700)) {
		std::cout << "Engine failed to be created" << std::endl;
		return 0;
	}

	CoreEngine::GetInstance()->Run();
	
	return 0;
}