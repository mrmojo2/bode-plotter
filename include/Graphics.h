#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <SDL2/SDL.h>

class Graphics{
public:

	//sdl objects
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_Texture* color_buffer_texture;
	static uint32_t* color_buffer;
	
	//window dimentions
	static int window_width;
	static int window_height;
	
	//sdl stuffs
	static bool initializeWindow();
	static void initializeColorBuffer();
	static void clearScreen(uint32_t );
	static void renderColorBuffer();
	
	//drawing stuffs
	static void drawPixel(int x, int y, uint32_t color);
	static void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
	static void drawCircle(int h, int k, int r,uint32_t color);
	static void drawEllipse(int xc,int yc,int a, int b, uint32_t color);

};

#endif
