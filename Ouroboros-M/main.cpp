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
	Ouroboros::OuroborosAlgo algo("d:/s298.bench", "d:/s298.flt", 10);
	algo.Run();
	
	return 0;
}