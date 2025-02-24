#include "BodePlot.h"
#include "Graphics.h"

#include <cmath>


BodePlot::BodePlot(){}

void BodePlot::drawSemiLog(){
	int slogstep = Graphics::window_width/4;
	for(int i=0; i<Graphics::window_width;i+=slogstep){
		//draw minor gridlines
		for(int j=0;j<10;j++){
			int x = i+log10(j+1)*slogstep;
			Graphics::drawLine(x,0,x,Graphics::window_height,0xffd3d3d3);
		}
		//draw major gridlines
		Graphics::drawLine(i,0,i,Graphics::window_height,0x00000000);
	}
	for(int i=0; i<Graphics::window_height;i+=Graphics::window_height/4){
		Graphics::drawLine(0,i,Graphics::window_width,i,0x00000000);
	}
}

double BodePlot::bodeMagnitude(double w){
#if 0
	/////////////////////////////////////////////////////////////////////////////////////
	//		G(s) = 25/(s^2+2s+25)
	////////////////////////////////////////////////////////////////////////////////////
	double numerator = 25.0;
       	double wn = 5.0;
	double zita = 0.2;

	double denominator = sqrt(pow(wn*wn - w*w,2) + pow(2*zita*wn*w,2));

	return 20*log10(numerator/denominator);
#endif
#if 0
	///////////////////////////////////////////////////////////////////////////////////
	//		G(s) = s/(s+10)
	//////////////////////////////////////////////////////////////////////////////////
	double k = 1;
	double wc = 10;
	return 20*log10(k*w/sqrt(w*w+wc*wc));
#endif
#if 0 
	///////////////////////////////////////////////////////////////////////////////////
	//		G(s) = 10s/(s^2+10s+10000)
	//////////////////////////////////////////////////////////////////////////////////
	double w0 = 100;
	double Q = 5;	
	double numerator = (w0/Q)*w;
	double denominator = sqrt(pow(w*w-w0*w0,2)+pow((w0/Q)*w,2));
	return 20*log10(numerator/denominator);

#endif
#if 1
	///////////////////////////////////////////////////////////////////////////////////
	//		G(s) = 4(s^2+s+25)/(s^3+100s^s)
	//////////////////////////////////////////////////////////////////////////////////
	double numerator = 4 * sqrt(pow(-w*w+25,2)+w*w);
	double denominator = sqrt(pow(w,6)+10000*pow(w,4));
	return 20*log10(numerator/denominator);

#endif
}
double BodePlot::bodePhase(double w){
#if 0
	/////////////////////////////////////////////////////////////////////////////////////
	//		G(s) = 25/(s^2+2s+25)
	////////////////////////////////////////////////////////////////////////////////////
	return (-atan2(2,25-w*w))*180/M_PI;
#endif
#if 0
	///////////////////////////////////////////////////////////////////////////////////
	//		G(s) = s/(s+10)
	//////////////////////////////////////////////////////////////////////////////////
	return (90 -  (atan2(w,10))*180/M_PI);
#endif
#if 0
	///////////////////////////////////////////////////////////////////////////////////
	//		G(s) = 10s/(s^2+10s+10000)
	//////////////////////////////////////////////////////////////////////////////////
	return atan2(10000-w*w,10*w) * 180/M_PI;

#endif
#if 1
	///////////////////////////////////////////////////////////////////////////////////
	//		G(s) = 4(s^2+s+25)/(s^3+100s^s)
	//////////////////////////////////////////////////////////////////////////////////
	return ((atan2(w,(-w*w+25)) - atan2(w,100) )* 180/M_PI)-90; 
#endif
}
