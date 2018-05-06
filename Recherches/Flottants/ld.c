#include <math.h>
#include <stdio.h>
double osef(double a)
{
	return 1 - a;
}
double osef2(double a)
{
	return 1.f - a;
}
int main()
{
	long double a = -0.0000025;
	double b = -0.00000025;
	printf("%Lf\n%f\n", a, b);
	long double c = expl(a);
	double d = exp(b);
	printf("%Lf\n%f\n", c, d);
	printf("Size:\n%lu\n%lu\n", sizeof(long double), sizeof(double));
	printf("Fonction osef:\n");
	printf("%f\n%f\n", osef(0.2), osef2(0.2));
	return 0;
}
