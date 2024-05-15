#include <iostream>
#include <vector>
#include <functional>
std::vector<double> secant(std::function<double(double)> f, 
	std::function<double(double)> df, std::function<double(double)> d2f, 
	double p0, double p1, double delta, double eps, double max1) {

	double p2, err, relerr, y;
	int k;

	for (k = 1; k < max1; k++) {
		p2 = p1 - df(p1) * (p1 - p0) / (df(p1) - df(p0));
		err = abs(p2 - p1);
		relerr = 2 * err / (abs(p2) + delta);
		p0 = p1;
		p1 = p2;
		y = df(p1);
		if ((err < delta) || (relerr < delta) || (abs(y) < eps)) {
			if (d2f(p1) > 0) {
				y = f(p1);
				break;
			}
		}
	}
	
	std::vector<double> res = { p1, err, double(k), y };
	
	return res;
}
