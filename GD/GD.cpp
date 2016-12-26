#include "GD.h"
#include<cmath>

using namespace std;

vector<float> operator+(const vector<float>& v1, const vector<float>& v2) {
	// 假设 v1.size() == v2.size()
	vector<float> r;

	r.reserve(v1.size());
	for (auto i = 0; i < v1.size(); ++i) {
		r.push_back(v1[i] + v2[i]);
	}
	return r;
}

vector<float> operator/(const vector<float>& v1, const float& v2){
	vector<float> r;

	r.reserve(v1.size());
	for (auto i = 0; i < v1.size(); ++i){
		r.push_back(v1[i] / v2);
	}
	return r;
}

vector<float> operator*(const vector<float>& v1, const float& v2){
	vector<float> r;

	r.reserve(v1.size());
	for (auto i = 0; i < v1.size(); ++i){
		r.push_back(v1[i] * v2);
	}
	return r;
}

float model(vector<float> vec){
	float sum = 0;
	for(auto i = 0; i < vec.size(); ++ i){
		sum += vec[i]*vec[i];
	}
	return sqrt(sum);
}

GradDes::GradDes(float step, std::vector<float> init_pos){
	this->step = step;
	this->last_pos = init_pos;
	this->element = init_pos.size();
}

float GradDes::function(std::vector<float> x){
    //定义想求极值的函数
	return exp(-x[0] * x[0] - x[1] * x[1]);
}

MaxVal GradDes::startIteration(){
	std::vector<float> train_x;
	float temp_grad;
	float sum_grad = 0;
	float last_sum = 0;
	float lastY = 0;
	int iter_num = 0;
	MaxVal finXY;
	while (iter_num < 500){
		std::vector<float> grad;
		++iter_num;
		train_x = last_pos;
		cout << endl;
		cout << "第" << iter_num << "次迭代:";
		for (int i = 0; i < element; ++i){
			train_x[i] += step;
			temp_grad = (function(train_x) - function(last_pos)) / (train_x[i] - last_pos[i]);
			cout << temp_grad << " ";
			if (temp_grad > 0) grad.push_back(temp_grad);
			else if (temp_grad < 0){
				train_x[i] -= 2 * step;
				grad.push_back((function(train_x) - function(last_pos)) / (train_x[i] - last_pos[i]));
			}
			else{
				train_x[i] -= step;
				grad.push_back(0);
			}
		}
		sum_grad = model(grad);
		grad = grad / sum_grad * sqrt(step);
		last_pos = last_pos + grad;
		cout << "函数输出为:" << function(last_pos) << endl;
		if (abs(function(last_pos) - lastY) < ERROR && iter_num != 1) break;
		lastY = function(last_pos);
	}
	finXY.x = last_pos;
	finXY.y = function(last_pos);
	return finXY;
}