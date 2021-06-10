
#include<iostream>
#include "Texture.h"
#include <string>
#include <fstream>
using namespace std;

SDL_Renderer* Texture::Renderer = NULL;

Texture::Texture() {
	Tex = NULL;
	width = 0;
	height = 0;
}


void Texture::LoadImage(string path) {
	
	empty();

	if (Texture::Renderer == NULL) {
		return;
	}
	
	SDL_Surface* surface = SDL_LoadBMP(path.c_str()); // BMP Image is loaded

	if (surface == NULL) {
		cout << "Unable to load Image" << endl;
	}
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 3, 3, 3));

		Tex = SDL_CreateTextureFromSurface(Texture::Renderer, surface);

		if (Tex == NULL)
			cout << "Texture couldn't be created" << endl;

		else
		{	// Take surface dimensions
			width = surface->w;
			height = surface->h;
		}
	}

	SDL_FreeSurface(surface);
}
void Texture::LoadText(TTF_Font* FONT, SDL_Color colour, string sentance) {
	empty();
	if (Renderer == NULL) {
		return;
	}
	SDL_Surface* surface = TTF_RenderText_Solid(FONT, sentance.c_str(), colour); // Text is loaded

	if (surface == NULL) {
		cout << "Unable to load Image" << endl;
	}
	else
	{
		Tex = SDL_CreateTextureFromSurface(Renderer, surface);

		if (Tex == NULL)
			cout << "Texture couldn't be created" << endl;

		else
		{	// Take surface dimensions
			width = surface->w;
			height = surface->h;
		}
	}

	SDL_FreeSurface(surface);
}

int Texture::GHeight(){
	return height;
}

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip RFlip) {


	if (Renderer == NULL) {
		return;
	}

	//centre->x = x +10;
	//centre->y = y + 10;

	SDL_Rect RenderVals = { x,y, GHeight(), GWidth() };
	if (clip != NULL) {
		RenderVals.w = clip->w;
		RenderVals.h = clip->h;

	}
	SDL_RenderCopyEx(Renderer, Tex,  clip, &RenderVals, angle, centre, RFlip);
}



int Texture::GWidth() {
	return width;
}
void Texture::empty() {
	if (Tex == NULL) {
		SDL_DestroyTexture(Tex);
		height = 0;
		width = 0;
	}
}