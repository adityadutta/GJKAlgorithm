#ifndef SCENEPHYSICS_H
#define SCENEPHYSICS_H

#include "Matrix.h"
#include"Vector.h"
#include "Scene.h"
#include"UILabel.h"
#include<SDL_ttf.h>
#include<vector>

class Body;
using namespace MATH;
class ScenePhysics : public Scene {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	Matrix4 projectionMatrix;

	Body* body1;
	Body* body2;

	std::vector<Body*> bodies;

	float elapsedTime;
	bool isRunning;

	TTF_Font* font;
	UILabel* collided;

public:
	ScenePhysics(SDL_Window* sdlWindow);
	bool onCreate();
	void onDestroy();
	void update(const float time);
	void render();
	void handleEvents(const SDL_Event &_event);
	void AddBody(Body* body);
};

#endif

