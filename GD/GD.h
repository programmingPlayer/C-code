#include<iostream>
#include<vector>

#define ERROR 0.001
//定义想求最大值的函数

struct MaxVal{
	float y;
	std::vector<float> x;
};

float model(std::vector<float> vec);

class GradDes{
public:
	GradDes(float step, std::vector<float> init_pos);
	float function(std::vector<float> x);//定义想求极大值的函数
	MaxVal startIteration();
private:
	float step;
	std::vector<float> last_pos;
	int element;
};