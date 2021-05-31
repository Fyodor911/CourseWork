#include <ctime>

struct TimeFeature {
	TimeFeature(double start, double finish, int size);

	void print();

	int size;
	double time;
};
