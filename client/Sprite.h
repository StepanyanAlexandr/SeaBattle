#pragma once

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#define _CANT_LOAD_IMAGE_		(-1)
#define _CANT_CREATE_TEXTURE_	(-2)

// класс используемый для загрузки и хранения текстуры
class Sprite
{
private:
	SDL_Texture *texture;
	SDL_Rect *position;
public:
	Sprite() : texture(nullptr) { position = new SDL_Rect; }
	~Sprite() { if (texture != nullptr) SDL_DestroyTexture(texture); }

	void loadTexture(const string path, SDL_Renderer *rend);
	SDL_Texture* getTexture() const { return texture; }
	SDL_Rect* getRect() const { return position; }
	void setPosition(const int x, const int y);
	void setDimension(const int w, const int h);
	bool checkCursorHit(const int mouse_x, const int mouse_y) const;
};