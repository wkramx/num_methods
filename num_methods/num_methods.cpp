#include <iomanip>
#include <math.h>
#include <iostream>
#include <vector>
#include <functional>
#include "golden.h"
#include "secant.h"
#include "quadmin.h"
#include "newton.h"

double f(double x) { // Change the function
    return pow(x, 2) - sin(x);
	//return 0.01 * pow(x, 4) - 0.01 * x;
	//return pow(x, 2) * sin(x);
}

double df(double x) { // Change the derivative of the function
	return 2 * x - cos(x);
	//return 0.01 * 4 * pow(x, 3) - 0.01;
}

double d2f(double x) { // Change the second derivative of the function
	return 2 + sin(x);
	//return 0.01 * 12 * pow(x, 2);
}

void main(void) {
	std::cout << "Choose one of three methods:" << std::endl
		<< "1 - Golden Ratio Method" << std::endl
		<< "2 - Secant Method" << std::endl
		<< "3 - Quadratic Approximation" << std::endl 
		<< "4 - Newton Method" << std::endl << std::endl << "Method #";

	double a = -10; // Left edge of the interval 
	double b = 10; // Right edge of the interval
	double delta = 1e-7; // Permissible deviation for x
	double eps = 1e-7; // Permissible deviation for y

	double p0 = 0; // First initial approximation
	double p1 = 1; // Second initial approximation
	int max1 = 1000; // Maximum number of iterations

	int method;
	std::cin >> method;

	switch (method) {
		case 1: {
			auto res_golden = golden(f, a, b, delta, eps);
			std::cout << "Golden Ratio Method" << std::endl << "x: " << std::setprecision(7) << res_golden[0] << ", y: "
				<< res_golden[1] << ", iter: " << res_golden[2] << std::endl << std::endl;
			break;
		}
		case 2: {
			auto res_secant = secant(f, df, d2f, p0, p1, delta, eps, max1);
			std::cout << "Secant Method" << std::endl << "x: " << std::setprecision(7) << res_secant[0] << ", y: "
				<< res_secant[3] << ", iter: " << res_secant[2] << std::endl << std::endl;
			break;
		}
		case 3: {
			auto res_quadmin = quadmin(f, a, b, delta, eps);
			std::cout << "Quadratic Approximation" << std::endl << "x: " << std::setprecision(7) << res_quadmin[0] << ", y: "
				<< res_quadmin[1] << ", iter: " << res_quadmin[4] << std::endl;
			break;
		}
		case 4: {
			auto res_newton = newton(f, df, d2f, p0, delta, eps, max1);
			std::cout << "Newton Method" << std::endl << "x: " << std::setprecision(7) << res_newton[0] << ", y: "
				<< res_newton[3] << ", iter: " << res_newton[2] << std::endl;
			break;
		}
		default:
			std::cout << "Invalid method chosen. Please select a correct method number." << std::endl;
			break;
	}
}