#include "GD.h"

int main(){
	std::vector<float> initX = { -1.0, -1.0}; 
	GradDes gd(0.001, initX);
	gd.startIteration();
	
	getchar();
	return 0;
}