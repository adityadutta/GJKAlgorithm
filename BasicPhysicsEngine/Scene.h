#ifndef SCENE_H
#define SCENE_H
#include<memory>
#include<SDL.h>

class UIManager;
class Scene {
public:
	virtual bool onCreate() = 0;								//creates the scene elements
	virtual void onDestroy() = 0;								//cleaner method to destroy and free memory
	virtual void update(const float time) = 0;					//updates the scene with the given timeStep
	virtual void render() = 0;									//renders the scene elements and the UI
	virtual void handleEvents(const SDL_Event &_event) = 0;		//handles key and mouse inputs in the scene
};

#endif
