#include "SA.h"

using namespace std;

int main(){
	vector<float> x = { -3, -5 };
	Range temp;
	temp.MIN_X = -10;
	temp.MAX_X = 10;
	vector<Range> range = { temp, temp };
	SimAnneal sa(100,0.001,0.98,1.5,x,range);
	FinStatus fin = sa.annealStart();
	getchar();
	return 0;
}