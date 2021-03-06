#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main (int argc, char * argv [])
{
	ifstream input (argv[1]);
	int i = 0, n = -1, p = 1;
	input >> n;
	while (!input.eof() && !input.fail() && !input.bad() && input.good())
	{
		cout << left << setw (10) << n;
		if (++i == 8)
		{
			cout << endl;
			i = 0;
		}
		p *= n;
		input >> n;
	}
	if (i)
		cout << endl;
	cout << "The product of the numbers is " << p << endl;
	return 0;
}
