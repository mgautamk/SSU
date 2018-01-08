/* Program to compute ECC Integer Point-Pairs */
#include <iostream>
#include <cmath> // pow
using std::cout;
using std::cin;
using std::endl;
using std::string;

int  main(){

	int x, y, A, B, C;
	float X, Y;

	cout << \
	"\n\e[1m" << "y^2 = x^(\e[1;31mA\e[1;30m) - \e[1;31mB\e[1;30mx + \e[1;31mC\e[0m\n";
	cout << "\e[1m" << "Input (\e[1;31mA\e[1;30m): " << "\e[0m"; cin >> A;
	cout << "\e[1m" << "Input (\e[1;31mB\e[1;30m): " << "\e[0m"; cin >> B;
	cout << "\e[1m" << "Input (\e[1;31mC\e[1;30m): " << "\e[0m"; cin >> C;


	// Linux escape codes for yellow highlighting
	cout << "\n\e[1;103m" << "y^2 = x^(" << A << ") - " << B << "x + " << C << "\e[0m\n\n";

	int threshold = 1000, count = 0;
	for (int i = -threshold; i < threshold; i++){
		x = i;
		for (int j = -threshold; j < threshold; j++){
			y = j;
			Y = pow(y, 2); // y is usually squared
			X = pow(x, A) - B*x + C; // the equation (might have to change)

			if ( Y == X ){
				cout << "(x, y) = " << "\e[1;103m" << "(" \
					<< x << ", " << y << ")" << "\e[0m\n";
				cout << Y << " = " << X;
				cout << "\033[1;32m" << " √" << "\033[0m\n\n";
				count++;
			}
		}
	}

	cout << "\033[1m" << "Results found: " << "\033[1;31m" << count << "\033[0m";
	cout << endl;
	return  0;
}
