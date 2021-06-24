#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Texture
{
public:
	// Texture Dimentions
	int width;
	int height;
	static SDL_Renderer* Renderer;
	SDL_Texture* Tex;  // The actual loaded texture

	
	Texture();
	// Loading Image and text
	void LoadImageFromPath(std::string path);
	void LoadText(TTF_Font* FONT, SDL_Color colour, std::string sentance);
	// Window Render
	void Render(int x, int y, double angle , SDL_RendererFlip RFlip, SDL_Rect* clip = NULL , SDL_Point* centre = NULL);

	void empty(); // emptys all the assets
	//Get Height and Width
	int GWidth();
	int GHeight();

};
