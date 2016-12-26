#include "SA.h"
#include<cstdlib>
#include<ctime>
#include<iostream>


/*Function:return a floating number from zero to one*/
float randZ2O(){
	return rand()*1.0 / RAND_MAX;
}

/*****************************************************************************************************************************
Function:init the simulated annealing
Parameter:
temp:the initial temperature;
minTemp:the iteration will not stop until decreasing to minTemp;
tempRate:rate of decay of temperature;
step:max step size 
initX:the initial position
range:the range of x
*****************************************************************************************************************************/
SimAnneal::SimAnneal(float temp, float minTemp, float tempRate, float step, std::vector<float> &initX, std::vector<Range> &xRange){
	this->temp = temp;
	this->minTemp = minTemp;
	this->tempRate = tempRate;
	this->preX = initX;
	this->bestX = initX;
	this->x = initX;
	this->xRange = xRange;
	this->step = step;
}

/*Function:the function we want to get maximum*/
float SimAnneal::function(std::vector<float> x){
	return exp(-x[0] * x[0] - x[1] * x[1]);
}

/*****************************************************************************************************************************
Function:disturb the position
Paramenter:
x:present position
*****************************************************************************************************************************/
std::vector<float> SimAnneal::disturb(std::vector<float> x){
	std::vector<float> tempX = x;
	float p;
	float delta;
	for (auto i = 0; i < tempX.size(); ++i){
		do{
			delta = step * randZ2O();
			p = randZ2O();
			if (p > 0.5) delta *= -1;
			tempX[i] += delta;
		} while (tempX[i] < xRange[i].MIN_X || tempX[i] > xRange[i].MAX_X);
	}
	return tempX;
}

int SimAnneal::metropolis(std::vector<float> nextX, std::vector<float> x){
	float p = exp((function(nextX) - function(x)) / temp);
	if (randZ2O() < p) return 1;
	else return 0;
}

FinStatus SimAnneal::annealStart(){
	std::vector<float> tempX;
	srand(time(0));
	int iter_num = 0;
	while (temp > minTemp){
		++iter_num;
		tempX = disturb(x);
		if (function(tempX) > function(bestX)){
			preX = bestX;
			bestX = tempX;
			std::cout << "目前最优解:x = " << bestX[0] << " " << bestX[1] << "函数输出:y = " << function(bestX) << std::endl;
		}
		if (function(tempX) > function(x)){
			x = tempX;
		}
		else{
			if (metropolis(tempX, x)){
				x = tempX;
			}
		}
		temp *= tempRate;
	}
	FinStatus fin_status;
	fin_status.x = bestX;
	fin_status.y = function(bestX);
	std::cout << std::endl << "最终得到的最优解为:x = " << bestX[0] << " " << bestX[1] << " " << "y = " << fin_status.y << std::endl;
	return fin_status;
}