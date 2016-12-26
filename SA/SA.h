#ifndef _SA_H
#define _SA_H

#include<vector>
#include<cmath>

struct FinStatus{
	std::vector<float> x;
	float y;
};

struct Range{
	float MIN_X;
	float MAX_X;
};

class SimAnneal{
public:
	SimAnneal(float temp, float minTemp, float tempRate, float step, std::vector<float> &initX, std::vector<Range> &xRange);
	float function(std::vector<float> x);
	std::vector<float> disturb(std::vector<float> x);
    FinStatus annealStart();
	int metropolis(std::vector<float> nextX, std::vector<float> x);
private:
	std::vector<float> preX;
	std::vector<float> bestX;
	std::vector<float> x;
	std::vector<Range> xRange;
	float minTemp;
	float temp;
	float tempRate;
	float step;
};

#endif