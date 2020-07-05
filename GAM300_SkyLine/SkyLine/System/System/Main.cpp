#include "Engine.hpp"

#include <SDL_main.h>



int main(int /*argc*/, char** /*argv*/)
{
			Engine*game = Engine::instance();
			game->GameLoop();
/*	std::cout << "test" << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Delay(1000);
	
	SDL_Quit();*/
	return 0;
}
//int main(void)
//{
//	
//				Engine::instance(false);
//	return 0;
//}