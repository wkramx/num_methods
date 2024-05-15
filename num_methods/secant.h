#pragma once
std::vector<double> secant(std::function<double(double)> f,
	std::function<double(double)> df, std::function<double(double)> d2f,
	double p0, double p1, double delta, double eps, double max1);