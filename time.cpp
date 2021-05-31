#include "time.h"
#include <iostream>

using namespace std;

TimeFeature::TimeFeature(double start, double finish, int size)
: size(size)
, time((finish - start) / CLOCKS_PER_SEC)
{ }

void TimeFeature::print()
{
	cout << "Размер: " << size << ", Время: " << time << endl;
}
