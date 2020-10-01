#include "ScenePhysics.h"
#include"MMath.h"
#include"Collider.h"
#include<iostream>

using namespace A3Engine;
ScenePhysics::ScenePhysics(SDL_Window* sdlWindow_) {

	isRunning = false;
	window = sdlWindow_;

	elapsedTime = 0.0f;
}

bool ScenePhysics::onCreate() {
	TTF_Init();

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	renderer = SDL_CreateRenderer(window, -1, 0);

	float aspectRatio = (float)w / (float)h;
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-5.0f, 9.0f, -5.0f * aspectRatio, 9.0f * aspectRatio, 0.0f, 1.0f);

	font = TTF_OpenFont("Fonts/BebasNeue-Regular.ttf", 30);
	if (font == nullptr) {
		onDestroy();
		return false;
	}

	SDL_Color color = { 255, 255, 255 };

	//timer init
	collided = new UILabel(" ", Vec3(-26.0f, -21.25f, 0.0f), color, 26);

	body1 = new Body(2.0f, 4.0f);
	body2 = new Body(1.0f, 2.0f);

	//Assignments Coords
	// 0,0 0,4 4 0
	// 1.5,2 1.5,4 1.4,2
	//collided
	body1->addVertex(Vec3(0.0f, 0.0f, 1.0f));
	body1->addVertex(Vec3(0.0f, 4.0f, 1.0f));
	body1->addVertex(Vec3(4.0f, 0.0f, 1.0f));


	body2->addVertex(Vec3(4.5f, 4.0f, 1.0f));
	body2->addVertex(Vec3(5.5f, 8.0f, 1.0f));
	body2->addVertex(Vec3(9.0f, 6.0f, 1.0f));


	body1->linearVelocity += Vec3(0.0f, 1.0f, 0.0f);
	body2->linearVelocity += Vec3(-1.0f, 0.0f, 0.0f);

	AddBody(body1);
	AddBody(body2);

	for (auto body : bodies) {
		if (body == nullptr) {
			onDestroy();
			return false;
		}
	}

	return true;
}

void ScenePhysics::onDestroy() {

	for (auto body : bodies) {
		if (body) {
			delete body;
			body = nullptr;
		}
	}

	TTF_CloseFont(font);

	TTF_Quit();

	SDL_DestroyRenderer(renderer);
}

void ScenePhysics::update(const float time) {
		Collider::HandleCollision(*body1, *body2);

		if (Collider::Collided(*body1, *body2)) {
			collided->text = "Triangles Collided";
			std::cout << "Triangles Collided" << std::endl;
		}
		else {
			collided->text = "Not Colliding";
		}

		body1->UpdateOrientation(time);
		body2->UpdateOrientation(time);

		body1->update(time);
		body2->update(time);
}

void ScenePhysics::render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	//Clear the screen.
	SDL_RenderClear(renderer);

	//Draw blue horizontal line
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, 0, 720 / 2, 1280, 720 / 2);
	//Draw blue vertical line
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, 1280 / 2, 0, 1280 / 2, 720);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, collided->text.c_str(), collided->color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 500, 200, texW, texH };

	SDL_RenderCopy(renderer, texture, NULL, &dstrect);


	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);

	for (auto body : bodies) {
		for (int i = 0; i < body->vertices.size(); i++) {
			Vec3 screenCoords1 = projectionMatrix * body->vertices[i];
			Vec3 screenCoords2;
			if (i + 1 < body->vertices.size()) {
				screenCoords2 = projectionMatrix * body->vertices[i + 1];
			}
			else {
				screenCoords2 = projectionMatrix * body->vertices[0];
			}

			//Drawing the lines we want.
			SDL_RenderDrawLine(renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
		}
	}

	//Update the Renderer.
	SDL_RenderPresent(renderer);
}

void ScenePhysics::handleEvents(const SDL_Event &_event) {

	if (_event.type == SDL_KEYDOWN)
	{
		switch (_event.key.keysym.sym)
		{
		case SDLK_a:
			for (int i = 0; i < this->body2->vertices.size(); i++) {
				body2->vertices[i] += VECTOR3_LEFT * 5.0f * 0.016f;
			}
			break;
		case SDLK_d:
			for (int i = 0; i < this->body2->vertices.size(); i++) {
				body2->vertices[i] += VECTOR3_RIGHT * 5.0f * 0.016f;
			}
			break;
		case SDLK_w:
			for (int i = 0; i < this->body2->vertices.size(); i++) {
				body2->vertices[i] += VECTOR3_UP * 5.0f * 0.016f;
			}
			break;
		case SDLK_s:
			for (int i = 0; i < this->body2->vertices.size(); i++) {
				body2->vertices[i] += VECTOR3_DOWN * 5.0f * 0.016f;
			}
			break;
		case SDLK_q:
			for (int i = 0; i < body2->vertices.size(); i++) {
				float x = body2->vertices[i].x * cos(30 * DEGREES_TO_RADIANS) - body2->vertices[i].y * sin(30 * DEGREES_TO_RADIANS);
				float y = body2->vertices[i].x * sin(30 * DEGREES_TO_RADIANS) + body2->vertices[i].y * cos(30 * DEGREES_TO_RADIANS);
				body2->vertices[i].y = y;
				body2->vertices[i].x = x;
				//body2->vertices[i] = MMath::translate(body2->position) * body2->vertices[i];
				//body2->vertices[i] = MMath::translate(VECTOR3_ZERO) * body2->vertices[i];			
			}
			break;
		case SDLK_1:
			body1->linearVelocity += Vec3(0.0f, 1.0f, 0.0f);
			body2->linearVelocity += Vec3(-5.0f, 0.0f, 0.0f);
			break;
		default:
			break;
		}
	}
}

void ScenePhysics::AddBody(Body* body)
{
	bodies.push_back(body);
}