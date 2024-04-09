#include <iostream>                 //индивидуальное задание №7
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

int main()
{
	setlocale(LC_ALL, "Russian");
	double a = 0.1, b = 1, h = 0.1, n;
	cout << "Нажмите 0 чтобы оставить стандартные значения a, b и h, иначе - введите свои значения:\n";
	switch(_getch())
	{
	case '0': 
		cout << "Используются стандартные значения a(0.1), b(1.0) и h(0.1)\n"; 
		break;
	default:
		cout << "Введите a\n"; read(a);
		cout << "Введите b\n"; read(b);
		cout << "введите h\n"; read(h);
		break;
	}
	cout << "Введите n\n";
	read(n);
	cout.precision(5);
	cout << fixed;
	for (double x = a; x <= b; x += h)
	{
		double s = 0, y;
		y = (-1) * log(1 - 2. * x * cos(PI / 3) + x * x) / 2;
		double a = x;
		for (int k = 1; k <= n; k++, a *= x)
			s += a * cos(k * PI / 3) / k;
		cout << "При x = " << x << setw(25) << "S(x) =" << (s < 0 ? " " : " +") << s
								<< setw(25) << "Y(x) = " << y 
								<< setw(30) << "|Y(x) - S(x)|= " << fabs(y - s) << endl;
	}
}
