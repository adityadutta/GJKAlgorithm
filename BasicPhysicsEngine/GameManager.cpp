#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "ScenePhysics.h"

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this onCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::onCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (ptr == nullptr) {
		onDestroy();
		return false;
	}
	if (ptr->onCreate() == false) {
		onDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		onDestroy();
		return false;
	}

	currentScene = new ScenePhysics(ptr->GetSDL_Window());
	if (currentScene == nullptr) {
		onDestroy();
		return false;
	}
	
	if (currentScene->onCreate() == false) {
		onDestroy();
		return false;
	}


	return true;
}

/// Here's the whole game
void GameManager::Run() {

	SDL_Event event;

	timer->Start();

	while (isRunning) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				}	
			}
		}
		currentScene->handleEvents(event);
		
		timer->UpdateFrameTicks();
		currentScene->update(timer->GetDeltaTime());
		currentScene->render();
		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec

	}
}

GameManager::~GameManager() {}

void GameManager::onDestroy() {
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}