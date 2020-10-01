#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include "Scene.h"

class Window;
class Timer;
class UI;
class GameManager {
private:
	Window *ptr;
	Timer *timer;
	bool isRunning;
	Scene *currentScene;


public:
	GameManager();
	~GameManager();
	bool onCreate();
	void onDestroy();

	void Run();
};
#endif


