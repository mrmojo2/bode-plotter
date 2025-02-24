#include "Application.h"
#include "Graphics.h"
#include "Vector.h"

#include <SDL2/SDL.h>
#include <iostream>

#define PI 3.14159

void Application::setup(){
	isRunning = Graphics::initializeWindow();
	Graphics::initializeColorBuffer();
	plot = BodePlot();
	
	
	double w_min = 0.1;
	double w_max = 1000;
	int N = 200;
	double ratio = pow(w_max/w_min, 1.0/(N-1));
	for(int j=0;j<N;j++){
		double w = w_min * pow(ratio, j);
		double mag = plot.bodeMagnitude(w);
		double phase = plot.bodePhase(w);
		Vector p1(w,-mag);
		Vector p2(w,-phase);
		p1.toSemiLogPixelMag();
		p2.toSemiLogPixelPhase();
		plot.magPoints.push_back(p1);
		plot.phasePoints.push_back(p2);
	}

}

void Application::input(){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;

			if(event.key.keysym.sym == SDLK_r)
				plot.showPoints = !plot.showPoints;
			if(event.key.keysym.sym == SDLK_m){
				plot.showMagPlot = !plot.showMagPlot;
			}
			if(event.key.keysym.sym == SDLK_p){
				plot.showPhasePlot = !plot.showPhasePlot;
			}
			break;
	}
}

void Application::update(){
}

void Application::render(){
	Graphics::clearScreen(0xffffffff);		// clear screen in each "frame" 

	// draw here
	plot.drawSemiLog();

if(plot.showMagPlot){
	for(int index = 0 ;index < plot.magPoints.size()-2; index+=2){
		Vector P0 = plot.magPoints[index];
		Vector P1 = plot.magPoints[index+1];
		Vector P2 = plot.magPoints[index+2];
		
		if(plot.showPoints)	
			Graphics::drawCircle(P0.x,P0.y,2,0xffff0000);	

		Vector prevB = P0;
		for(float t=0;t<=1;t+=0.01){
			Vector B = P0*(1-t)*(1-t) + P1*2*t*(1-t) + P2*t*t;
			Graphics::drawLine(prevB.x,prevB.y,B.x,B.y,0xffff0000);
			prevB = B;
		}


	}
}
if(plot.showPhasePlot){
	for(int index = 0 ;index < plot.phasePoints.size()-2; index+=2){
		Vector P0 = plot.phasePoints[index];
		Vector P1 = plot.phasePoints[index+1];
		Vector P2 = plot.phasePoints[index+2];
		
		if(plot.showPoints)	
			Graphics::drawCircle(P0.x,P0.y,2,0xff0000ff);	

		Vector prevB = P0;
		for(float t=0;t<=1;t+=0.01){
			Vector B = P0*(1-t)*(1-t) + P1*2*t*(1-t) + P2*t*t;
			Graphics::drawLine(prevB.x,prevB.y,B.x,B.y,0xff0000ff);
			prevB = B;
		}


	}
}
	
	Graphics::renderColorBuffer();			//render to screen
}

Application::~Application(){

	//free used memory
	SDL_DestroyRenderer(Graphics::renderer);
	SDL_DestroyWindow(Graphics::window);
	SDL_DestroyTexture(Graphics::color_buffer_texture);
	delete [] Graphics::color_buffer;
	SDL_Quit();
}
