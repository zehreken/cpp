// author: Guchan Alkan
// date: 2015.09.29

#include <iostream>

int main()
{
	int sum = 0;

	for (int i = 0; i < 1000; ++i)
	{
		if (i % 5 == 0)
			sum += i;
		else if (i % 3 == 0)
			sum += i;
	}
	
	std::cout << sum << std::endl;
}