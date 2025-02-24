#ifndef APPLICATION_H
#define APPLICATION_H

#include "BodePlot.h"

class Application{
public:
	bool isRunning;
	
	void setup();
	void input();
	void update();
	void render();

	Application()=default;
	~Application();


	BodePlot plot;
};


#endif
