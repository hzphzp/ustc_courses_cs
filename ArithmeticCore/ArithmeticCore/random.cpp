#include"core.h"
#include <cstdlib> 
#include <time.h> 
#include <iostream>
using namespace std;
static unsigned seed = (unsigned) time(NULL);
int core::random(int low, int high)
{
	int i;
	srand(seed);
	i = (rand() % (high - low + 1)) + low;
	seed = (seed + 199) % RAND_MAX;
	return i;
}
double core::random(double low, double high)
{
	int i = random((int)low*(int)low, (int)high*(int)high);
	return sqrt(i);
}