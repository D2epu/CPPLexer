#include <iostream>

using namespace std;

int main()
{
	float x = 100;
	float y = 0;
	float z = 101;
	float m;

	while (y + 1 != z)
	{
		m = (y + z) / 2;

		if (m*m <= x)
			y = m;
		else
			z = m;
	}

	cout << y;

	return 0;
}
