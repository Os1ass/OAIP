#include <iostream>                 //индивидуальное задание №1
#include <cmath>
#include <conio.h>
#include <iomanip>

using namespace std;

const double PI = 3.1415926;

int main()
{
	setlocale(LC_ALL, "Russian");
	double a = 0.1, b = 1, h = 0.1, n;
	cout << "Нажмите 0 чтобы оставить стандартные значения a, b и h, иначе - введите свои значения:\n";
	if (_getch() == '0')
		cout << "Используются стандартные значения a(0.1), b(1.0) и h(0.1)\n";
	else
	{
		cout << "Введите a\n"; cin >> a;
		cout << "Введите b\n"; cin >> b;
		cout << "введите h\n"; cin >> h;
	}
	cout << "Введите n\n";
	cin >> n;
	cout.precision(5);
	cout << fixed;
	for (double x = a; x <= b; x += h)
	{
		double s, y, r;
		y = sin(x);
		s = r = x;					// при k = 0, S(x) = x
		for (int k = 1; k <= n; k++)
		{
			r = -r * x * x / (2. * k * (2. * k + 1.));
			s += r;
		}
		cout << "При x = " << x << setw(25) << "S(x) =" << (s < 0 ? " " : " +") << s
			<< setw(25) << "Y(x) = " << y
			<< setw(30) << "|Y(x) - S(x)|= " << fabs(y - s) << endl;
	}
}