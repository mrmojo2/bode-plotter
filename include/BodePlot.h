#ifndef BODE_H
#define BODE_H

#include "Vector.h"

#include <vector>

class BodePlot{
public:
	BodePlot();
	
	void drawSemiLog();
	double bodeMagnitude(double w);
	double bodePhase(double w);
	
	bool showPoints = false;
	bool showMagPlot = true;
	bool showPhasePlot = false;
	std::vector<Vector> magPoints;
	std::vector<Vector> phasePoints;

};

#endif
