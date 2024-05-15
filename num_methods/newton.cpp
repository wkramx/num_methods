#include <iostream>
#include <vector>
#include <functional>
std::vector<double> newton(std::function<double(double)> f,
  std::function<double(double)> df, std::function<double(double)> d2f,
  double p0, double delta, double eps, double max1) {

  double p1, err, relerr, y;
  int k;

  for (k = 1; k < max1; k++) {
    p1 = p0 - df(p0) / d2f(p0);
    err = abs(p1 - p0);
    relerr = 2 * err / (abs(p1) + delta);
    p0 = p1;
    y = df(p0);
    if ((err < delta) || (relerr < delta) || (abs(y) < eps)) {
      if (d2f(p0) > 0) {
        y = f(p0);
        break;
      }
    }
  }

  std::vector<double> res = { p0, err, double(k), y };

  return res;
}