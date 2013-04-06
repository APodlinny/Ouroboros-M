#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>
#include <time.h>
#include <thread>

#include "Algorithm.h"

int main()
{
	Ouroboros::OuroborosAlgo algo("d:/s27.bench", "d:/s27.flt", 5);
	algo.Run();
	
	return 0;
}