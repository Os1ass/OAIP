#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

struct root
{
	double x;
	int it;
};

void read(double& a)
{
	while (true)
	{
		cin >> a;
		if (cin.fail() || cin.peek() != '\n')
		{
			a = 100.;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
			break;
	}
}

void readAB(double& a, double& b)
{
	cout << "Введите начало отрезка(-10 - 5): "; read(a);
	while (a < -10. || a > 5.)
	{
		cout << "Неверное значение! Попробуйте еще раз\n";
		cout << "Введите начало отрезка(-10 - 5): "; read(a);
	}

	cout << "Введите конец отрезка(-5 - 10): "; read(b);
	while (b < -5. || b > 10. || b <= a)
	{
		if (b <= a)
			cout << "Конец отрезка должен быть больше начала!";
		else
			cout << "Неверное значение!";

		cout << " Попробуйте еще раз\n";
		cout << "Введите конец отрезка(-5 - 10): "; read(b);
	}
}

void readEps(double& eps)
{
	cout << "Введите точность(меньше 0.01): "; read(eps);
	while (eps > 0.01 || eps < 0.000000001)
	{
		if (eps < 0.000000001)
			cout << "Слишком маленькое значение!";
		else
			cout << "Слишком большое значение!";

		cout << "Попробуйте еще раз\n";
		cout << "Введите точность(меньше 0.01): "; read(eps);
	}
}

void readH(double& h, double border)
{
	cout << "Введите шаг(0.1 - " << border << "): "; read(h);
	while (h < 0.1 || h > border)
	{
		cout << "Неверное значение! Попробуйте еще раз\n";
		cout << "Введите шаг(0.1 - " << border << "): "; read(h);
	}
}

bool def(double& a, double& b, double& h, double& eps, int method)
{
	switch (method)
	{
	case 1:
		a = -2; b = 2;
		break;

	case 2:
		a = -1; b = 3;
		break;

	case 3:
		a = 1; b = 8;
		break;

	case 4:
		a = 4; b = 7;
		break;

	default:
		cout << "Значения по умолчанию не найдены\n";
		return false;
	}

	h = 0.1; eps = 0.001;
	cout << "Значения по умолчанию: a = " << a << ", b = " << b << ", h = " << h << ", eps = " << eps << endl;
	cout << "Нажмите 1 чтобы использовать значения по умолчанию, иначе - введите свои\n";
	if (_getch() == '1')
		return true;
	return false;
}

void readData(double& a, double& b, double& h, double& eps, int method)
{
	if (def(a, b, h, eps, method))
		return;

	readAB(a, b);
	readEps(eps);
	readH(h, 1);
}

void method(int k)
{
	if (k == 0)
		cout << "Метод простой итерации\n";
	if (k == 1)
		cout << "Метод Ньютона\n";
	if (k == 2)
		cout << "Метод секущих\n";
	if (k == 3)
		cout << "Метод Вегстейна\n";
}

void printRoots(root* xArr, int n, double(*f)(double))
{
	if (n == 0)
	{
		cout << "Корней на отрезке не найдено\n";
		return;
	}
	double mPogr[4] = { 0, 0, 0, 0 };

	cout << endl << "                     Метод простой итерации     "
		<< "                Метод Ньютона         "
		<< "                Метод секущих         "
		<< "               Метод Вегстейна        \n";
	cout << "Номер корня:    Корень:    Функция:    Итерации:"
		<< "      Корень:    Функция:    Итерации:"
		<< "      Корень:    Функция:    Итерации:"
		<< "      Корень:    Функция:    Итерации:\n";
	cout.precision(4);
	cout << fixed;

	for (int i = 0; i < n / 4; i++)
	{
		cout << setw(6) << i + 1 << setw(17) << xArr[i].x << setw(11) << f(xArr[i].x) << setw(9) << xArr[i].it
			<< setw(18) << xArr[i + 1].x << setw(11) << f(xArr[i + 1].x) << setw(9) << xArr[i + 1].it
			<< setw(18) << xArr[i + 2].x << setw(11) << f(xArr[i + 2].x) << setw(9) << xArr[i + 2].it
			<< setw(18) << xArr[i + 3].x << setw(11) << f(xArr[i + 3].x) << setw(9) << xArr[i + 3].it << endl;
		for (int k = 0; k < 4; k++)
			if (fabs(f(xArr[i + k].x)) > mPogr[k])
				mPogr[k] = fabs(f(xArr[i + k].x));
	}

	int minI = 0;
	for (int k = 1; k < 4; k++)
		if (mPogr[k] < mPogr[minI])
			minI = k;
	cout << "Лучший метод - "; method(minI);
}

double f1(double x)
{
	return 4. * x - 7. * sin(x);
}

double df1(double x)
{
	return 4. - 7. * cos(x);
}

double f2(double x)
{
	return x * x - 10. * sin(x) * sin(x) + 2.;
}

double df2(double x)
{
	return 2. * x - 10. * sin(2. * x);
}

double f3(double x)
{
	return log(x) - 5 * cos(x);
}

double df3(double x)
{
	return 1. / x + 5. * sin(x);
}

double f4(double x)
{
	return exp(x) / (x * x * x) - sin(x) * sin(x) * sin(x) - 2;
}

double df4(double x)
{
	return (x - 3.) / (x * x * x * x) * exp(x) - 3. * sin(x) * sin(x) * cos(x);
}

root prIt(double(*f)(double), double(*df)(double), double a, double b, double eps)
{
	root ret;
	ret.it = 0;

	double x = (a + b) / 2., d;
	double l = 0.1;
	if (f(b) > 0)
		l *= -1;

	do
	{
		ret.it++;
		d = l * f(x);
		x += d;
	} while (fabs(d) > eps);

	ret.x = x;
	return ret;
}

root newt(double(*f)(double), double(*df)(double), double a, double b, double eps)
{
	root ret;
	ret.it = 0;

	double x = (a + b) / 2., d;

	do
	{
		ret.it++;
		d = fabs(f(x) / df(x));
		x -= f(x) / df(x);
	} while (d > eps);

	ret.x = x;
	return ret;
}

root sec(double(*f)(double), double(*df)(double), double a, double b, double eps)
{
	root ret;
	ret.it = 0;

	double d = 1, q = (b - a) / 2.;
	double x = (b + a) / 2.;

	do
	{
		ret.it++;
		d = f(x) * q / (f(x) - f(x - q));
		x -= d;
	} while (fabs(d) > eps);

	ret.x = x;
	return ret;
}

root veg(double(*f)(double), double(*df)(double), double a, double b, double eps)
{
	root ret;
	ret.it = 0;

	double d = 1;
	double x0 = a, x1 = b;

	do
	{
		ret.it++;
		d = f(x1) * (x1 - x0) / (f(x1) - f(x0));
		x0 = x1; x1 -= d;
	} while (fabs(d) > eps);

	ret.x = x1;
	return ret;
}

void findX(double a, double b, double h, double eps, double(*f)(double), double(*df)(double))
{
   	root* xArr = new root[(b - a) / h * 4];
	int kol = 0;

	for (double x = a; x + h <= b; x += h)
	{
		if (f(x) * f(x + h) < 0)
		{
			xArr[kol] = prIt(f, df, x, x + h, eps);
			kol++;
			xArr[kol] = newt(f, df, x, x + h, eps);
			kol++;
			xArr[kol] = sec(f, df, x, x + h, eps);
			kol++;
			xArr[kol] = veg(f, df, x, x + h, eps);
			kol++;
		}
	}

	printRoots(xArr, kol, f);
	delete[] xArr;
}

int main()
{
	setlocale(LC_ALL, "russian");
	double a, b, h, eps;

	while (true)
	{
		system("cls");
		cout << "\t\t\tНажмите\n"
			<< "\t\t1 -- 4x - 7 * sin(x)\n"
			<< "\t\t2 -- x^2 - 10 * sin(x)^2 + 2\n"
			<< "\t\t3 -- ln(x) - 5 * cos(x)\n"
			<< "\t\t4 -- e^x / x^3 - sin(x)^3 - 2\n";

		switch (_getch())
		{
		case '1':
			readData(a, b, h, eps, 1);
			findX(a, b, h, eps, f1, df1);
			break;

		case '2':
			readData(a, b, h, eps, 2);
			findX(a, b, h, eps, f2, df2);
			break;

		case '3':
			readData(a, b, h, eps, 3);
			findX(a, b, h, eps, f3, df3);
			break;

		case '4':
			readData(a, b, h, eps, 4);
			findX(a, b, h, eps, f4, df4);
			break;
		}
		cout << "Желаете продолжить(y/n)\n";
		if (_getch() != 'y')
			break;
	}
}