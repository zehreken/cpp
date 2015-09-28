// author: Guchan Alkan
// date: 2015.09.29

#include <iostream>

int main()
{
	int prev = 0;
	int next = 1;
	int sumOfEvens = 0;

	while (next + prev < 100)
	{
		next = next + prev;
		prev = next - prev;

		if (next % 2 == 0)
		{
			sumOfEvens += next;
		}
	}
	
	std::cout << sumOfEvens << std::endl;
}