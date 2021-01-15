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
	SDL_Rect position;
public:
	Sprite () : texture(nullptr) {}
	~Sprite() { if (texture != nullptr) SDL_DestroyTexture(texture); }

	void loadTexture(const string path, SDL_Renderer *rend);
	const SDL_Texture* getTexture() const { return texture; }
	const SDL_Rect getPosition() const { return position; }
	void setPosition(const int x, const int y);
	void setDimension(const int w, const int h);
	bool checkCursirHit(const int mouse_x, const int mouse_y) const;
};

// метод загрузки изображения
// обрабатываем ошибки при загрузке изображения из файла
// и при создании текстуры из поверхности
void Sprite::loadTexture(const string path, SDL_Renderer *rend)
{
	SDL_Surface *tmp = nullptr;
	
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	texture = nullptr;

	tmp = IMG_Load(path.c_str());	// загружаем изображение в виде поверхности
	if (tmp == nullptr)
		throw "Can't load image";
	
	texture = SDL_CreateTextureFromSurface(rend, tmp);	// создаем текстуру из полученной поверхности
	if (texture == nullptr)
		throw "Can't create texture";

	SDL_FreeSurface(tmp);
}

// устанавливаем позицию левого верхнего угла текстуры на экране
void Sprite::setPosition(const int x, const int y)
{
	position.x = x;
	position.y = y;
}

// устанавливаем высоту и ширину текстуры
void Sprite::setDimension(const int w, const int h)
{
	position.w = w;
	position.h = h;
}

// проверяем, подает ли курсор в данную текстуру
bool Sprite::checkCursirHit(const int mouse_x, const int mouse_y) const
{
	if (mouse_x > position.x && mouse_x < (position.x + position.w) &&
		mouse_y > position.y && mouse_y < (position.y + position.h))
		return true;
	else
		return false;
}