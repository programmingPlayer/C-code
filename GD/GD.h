#include<iostream>
#include<vector>

#define ERROR 0.001
//�����������ֵ�ĺ���

struct MaxVal{
	float y;
	std::vector<float> x;
};

float model(std::vector<float> vec);

class GradDes{
public:
	GradDes(float step, std::vector<float> init_pos);
	float function(std::vector<float> x);//�������󼫴�ֵ�ĺ���
	MaxVal startIteration();
private:
	float step;
	std::vector<float> last_pos;
	int element;
};