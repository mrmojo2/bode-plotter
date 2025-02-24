#include "Graphics.h"

#include <iostream>
#include <cmath>

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;
uint32_t* Graphics::color_buffer = nullptr;
SDL_Texture* Graphics::color_buffer_texture = nullptr;
int Graphics::window_width = 1024;
int Graphics::window_height = 600;

bool Graphics::initializeWindow(){
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0 ){
		std::cerr<<"Failed to initialize SDL Error: "<<SDL_GetError()<<std::endl;
		return false;
	}

	//create the window
	window = SDL_CreateWindow(
		"SDL Setup",
		SDL_WINDOWPOS_CENTERED+500,		
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS		
	);
	if(!window){
		std::cerr<<"SDL Error: "<<SDL_GetError()<<std::endl;
		return false;
	}
	//std::cout << "SDL Window Created" << std::endl;

	//create renderer
	renderer = SDL_CreateRenderer(
        	window,
        	-1, // use default output/display device
        	0   // no special flags
    	);

	if (!renderer){
		std::cerr<<"SDL Error: "<<SDL_GetError() << std::endl;
		return false;
	}
	//std::cout << "SDL Renderer Created" << std::endl;
	
	return true;
}

void Graphics::initializeColorBuffer(){
	color_buffer = new uint32_t[window_width * window_height];

	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
}

	
void Graphics::clearScreen(uint32_t color){
	for(int y=0; y<window_height;y++){
		for(int x=0; x< window_width; x++){
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void Graphics::renderColorBuffer(){
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int) (window_width * sizeof(uint32_t))		
	);

	SDL_RenderCopy(
		renderer,
		color_buffer_texture,
		NULL,
		NULL
	);

	SDL_RenderPresent(renderer);
}



void Graphics::drawPixel(int x, int y, uint32_t color){
	if(x >= window_width || x <= 0 || y >= window_height || y < 0) return;//out of bound check
	color_buffer[(window_width * y)+x] = color;
}

void Graphics::drawCircle(int h, int k, int r, uint32_t color){
	int p = 1-r;
	int x=0,y=r;

	while(x<=y){
		drawPixel(h + x, k + y, color);
		drawPixel(h - x, k + y, color);
		drawPixel(h + x, k - y, color);
		drawPixel(h - x, k - y, color);
		drawPixel(h + y, k + x, color);
		drawPixel(h - y, k + x, color);
		drawPixel(h + y, k - x, color);
		drawPixel(h - y, k - x, color);


		if(p < 0){
			p+=2*x+3;
		}else{
			p+=2*(x-y)+5;
			y--;	
		}
		x++;
	}
}


void Graphics::drawLine(int x0,int y0, int x1, int y1, uint32_t color){
	int dx = abs(x1-x0);
	int dy = abs(y1-y0);
	int sx = (x0 < x1) ? 1 : -1;	
	int sy = (y0 < y1) ? 1 : -1;

	int err = dx - dy;

	while(true){
		drawPixel(x0,y0,color);
		if(x0==x1 && y0==y1) break;
		int e2 = 2*err;
		
		if(e2 > -dy){
			err-=dy;
			x0+=sx;
		}
		if(e2<dx){
			err += dx;
			y0 += sy;
		}	
	}
}

void Graphics::drawEllipse(int xc, int yc, int a, int b, uint32_t color) {
    int x = 0;
    int y = b;

    int a2 = a * a;  // a^2
    int b2 = b * b;  // b^2
    int twoA2 = 2 * a2;
    int twoB2 = 2 * b2;

    // Region 1: Slope is less than 1
    int p1 = b2 - (a2 * b) + (a2 / 4);
    int dx = 0;  // Change in x
    int dy = twoA2 * y;  // Change in y

    while (dx < dy) {  // Until slope becomes >= 1
        drawPixel(xc + x, yc + y, color);
        drawPixel(xc - x, yc + y, color);
        drawPixel(xc + x, yc - y, color);
        drawPixel(xc - x, yc - y, color);

        x++;
        dx += twoB2;

        if (p1 < 0) {
            p1 += dx + b2;
        } else {
            y--;
            dy -= twoA2;
            p1 += dx - dy + b2;
        }
    }

    // Region 2: Slope is greater than or equal to 1
    int p2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;

    while (y >= 0) {
        drawPixel(xc + x, yc + y, color);
        drawPixel(xc - x, yc + y, color);
        drawPixel(xc + x, yc - y, color);
        drawPixel(xc - x, yc - y, color);

        y--;
        dy -= twoA2;

        if (p2 > 0) {
            p2 += a2 - dy;
        } else {
            x++;
            dx += twoB2;
            p2 += dx - dy + a2;
        }
    }
}

