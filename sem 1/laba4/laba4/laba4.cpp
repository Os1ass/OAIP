#include <iostream>                 //индивидуальное задание №1
#include <cmath>
#include <conio.h>
#include <iomanip>

using namespace std;

const double PI = 3.1415926;

void read(double& a)
{
	while (true)
	{
		cout << "Введите значение:\n";
		cin >> a;
		if (cin.fail() || cin.peek() != '\n')
		{
			cout << "Ошибка! Неверный ввод\n";
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
			break;
	}
}

void writeAns(double, double, double, double);

double sum(double&, double, double);

int main()
{
	setlocale(LC_ALL, "Russian");
	double a = 0.1, b = 1, h = 0.1, n;
	cout << "Нажмите 0 чтобы оставить стандартные значения a, b и h, иначе - введите свои значения:\n";
	if (_getch() == '0')
		cout << "Используются стандартные значения a(0.1), b(1.0) и h(0.1)\n";
	else
	{
		cout << "Введите a\n"; read(a);
		cout << "Введите b\n"; read(b);
		cout << "введите h\n"; read(h);
	}
	cout << "Введите n\n";
	read(n);
	cout.precision(5);
	cout << fixed;
	if (a <= b)
		writeAns(a, b, h, n);
	else
		cout << "Ошибка, a > b\n";
}

void writeAns(double x, double b, double h, double n)
{
	double s, y;
	double r = x;																		//при k = 0, S(x) = x
	y = sin(x);
	s = sum(r, n, x); 
	cout << "При x = " << x << setw(25) << "S(x) =" << (s < 0 ? " " : " +") << s
							<< setw(25) << "Y(x) = " << y
							<< setw(30) << "|Y(x) - S(x)|= " << fabs(y - s) << endl;
	if (x + h <= b)
		writeAns(x + h, b, h, n);
}

double sum(double& r, double k, double x)
{
	if (k == 0)
		return r;
	double ret;
	ret = sum(r, k - 1, x);
	r = -r * x * x / (2. * k * (2. * k + 1.));
	return ret + r;
}