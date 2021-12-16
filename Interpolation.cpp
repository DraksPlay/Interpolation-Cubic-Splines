

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <malloc.h>

using namespace std;


double f(double x) {
	double y;
	if (x == 0) { return 0; }
	y = sin(pow(x, 4)) / (x * x);
	return y;
}


void func(double* xi, double* yi, int n, double a, double b) {
	FILE* p;
	p = fopen("DATA.txt", "w");
	double h = (b - a) / n;
	for (int i=0; i<=n; i++)
	{
		xi[i] = a + i * h;
		yi[i] = f(xi[i]);
		fprintf(p, "%f %f\n", xi[i], yi[i]);
		cout << xi[i] << " " << yi[i] << endl;
	}
	fclose(p);
}


void Slopes(double* xi, double* yi, double* m, int n) {
	double a = xi[0];
	double b = xi[n];
	double h = (b-a)/n;
	m[0] = (4 * yi[1] - yi[2] - 3 * yi[0]) / (2 * h);
	m[n] = (3 * yi[n] + yi[n - 2] - 4 * yi[n - 1]) / (2 * h);
	for (int i = 1; i < n; i++)
	{
		m[i] = (yi[i + 1] - yi[i - 1]) / (2 * h);
	}
}


double Spline(double* xi, double* yi, double* m, double x0, int n) {
	double s;
	double h = xi[1] - xi[0];
	for (int i = 0; i < n; i++) {
		if (xi[i] <= x0 && xi[i + 1] >= x0) {
			s = (xi[i + 1] - x0) * (xi[i + 1] - x0) * (2 * (x0 - xi[i]) + h) / (h * h * h) * yi[i] + (x0 - xi[i]) * (x0 - xi[i]) * (2 * (xi[i + 1] - x0) + h) / (h * h * h) * yi[i + 1] + (xi[i + 1] - x0) * (((xi[i + 1] - x0) * (x0 - xi[i])) / (h * h) * m[i]) + ((x0 - xi[i]) * (x0 - xi[i]) * (x0 - xi[i + 1]) / (h * h) * m[i + 1]);
			return s;
		}
	}

}


void main()
{
	int n = 9;
	double a = 0;
	double b = 1.6;
	double s;

	double* xi = new double[n+1];
	double* yi = new double[n+1];
	double* m = new double[n+1];

	func(xi, yi, n, a, b);


	Slopes(xi, yi, m, n);

	double xj[21] = {0, 0.08, 0.16, 0.24, 0.32, 0.40, 0.48, 0.56, 0.64, 0.72, 0.8, 0.88, 0.96, 
	1.04, 1.12, 1.20, 1.28, 1.36, 1.44, 1.52, 1.6};

	FILE* p = fopen("resultat.txt", "w");
	for (int i = 0; i <= 20; i++) {
		s = Spline(xi, yi, m, xj[i], n);
		printf("xj = %f F(xj) = %f f(xj)-F(xj) = %.10lf\n", xj[i], s, f(xj[i]) - s);
		fprintf(p, "%f %f %f\n", xj[i], s, f(xj[i]));
	}
	fclose(p);
	delete[] xi;
	delete[] yi;
	delete[] m;
}
