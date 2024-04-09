#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

void read(double& a)
{
	cin >> a;
	if (cin.fail() || cin.peek() != '\n')
	{
		a = 100.;
		cin.clear();
		cin.ignore(32767, '\n');
	}
}

void read(int& a)
{
	cin >> a;
	if (cin.fail() || cin.peek() != '\n')
	{
		a = -1;
		cin.clear();
		cin.ignore(32767, '\n');
	}
}

void readAB(double& a, double& b)
{
	cout << "Введите a(-20 - 15): "; read(a);
	while (a > 15 || a < -20)
	{
		cout << "Ошибка! Неверное значение, попробуйте еще раз\n";
		cout << "Введите a(-20 - 15): "; read(a);
	}
	cout << endl;

	cout << "Введите b(-15 - 20): "; read(b);
	while (b > 20 || b < -15 || b < a)
	{
		if (b < a)
			cout << "Ошибка! Конец отрезка не может быть раньше начала, попробуйте еще раз\n";
		else
			cout << "Ошибка! Неверное значение, попробуйте еще раз\n";
		cout << "Введите b(-15 - 20): "; read(b);
	}
	cout << endl;
}

void readM(int& m)
{
	cout << "Введите m: "; read(m);
	while (m < 1 || m > 1000)
	{
		cout << "Ошибка! Неверное значение, попробуйте еще раз\n";
		cout << "Введите m: "; read(m);
	}
	cout << endl;
}

void readEps(double& eps)
{
	cout << "Введите eps(> 0.00001): "; read(eps);
	while (eps < 0.000001)
	{
		cout << "Ошибка! Неверное значение, попробуйте еще раз\n";
		cout << "Введите eps(< 0.01): "; read(eps);
	}
	cout << endl;
}

bool def(double& a, double& b, int& m, double& eps, int method)
{
	double sum = 0;
	eps = 0.001;
	switch (method)
	{
	case 1:
		a = -2; b = 3;
		m = 10; sum = 5.983;
		break;

	case 2:
		a = 0; b = 3;
		m = 10; sum = -6.699;
		break;

	case 3:
		a = 1; b = 8;
		m = 10; sum = 8.896;
		break;

	case 4:
		a = 4; b = 7;
		m = 5; sum = 6.118;
		break;

	case 5:
		a = 5; b = 8;
		m = 7; sum = 6.067;
		break;

	case 6:
		a = 3; b = 6;
		m = 7; sum = -3.367;
		break;

	default:
		cout << "Значения по умолчанию не найдены\n";
		return false;
	}

	cout << "Значения по умолчанию: a = " << a << ", b = " << b << ", m = " << m << ", eps = " << eps << endl;
	cout << "Значение интеграла по умолчанию - " << sum << endl;
	cout << "Нажмите 1 чтобы использовать значения по умолчанию, иначе - введите свои\n";
	if (_getch() == '1')
		return true;
	return false;
}

void readData(double& a, double& b, int& m, double& eps, int method)
{
	if (def(a, b, m, eps, method))
		return;

	readAB(a, b);
	readM(m);
	readEps(eps);
}

double f1(double x)
{
	return 4. * x - 7. * sin(x);
}

double f2(double x)
{
	return x * x - 10. * sin(x) * sin(x);
}

double f3(double x)
{
	return log(x) - 5. * cos(x);
}

double f4(double x)
{
	return exp(x) / (x * x * x) - sin(x) * sin(x) * sin(x);
}

double f5(double x)
{
	return sqrt(x) - cos(x) * cos(x);
}

double f6(double x)
{
	return log(x) - 5 * sin(x) * sin(x);
}

double fSr(double a, double b, double(*f)(double))
{
	double h = b - a;
	double mid = (a + b) / 2.;
	return f(mid) * h;
}

double fTr(double a, double b, double(*f)(double))
{
	double h = b - a;
	return (f(a) + f(b)) / 2. * h;
}

double fSim(double a, double b, double(*f)(double))
{
	double h = b - a;
	double mid = (a + b) / 2.;
	return (f(a) + 4. * f(mid) + f(b)) * h / 6.;
}

double fAuto(double a, double b, double(*f)(double))
{
	double sTr = fTr(a, b, f);
	double sSr = fSr(a, b, f);
	return (sTr + 2. * sSr) / 3.;
}

double gauss2(double a, double b, double(*f)(double))
{
	double h = b - a;
	double mid = (a + b) / 2.;
	double d = h / 2. * 0.5773502692;
	return (f(mid - d) + f(mid + d)) * h / 2.;
}

double gauss3(double a, double b, double(*f)(double))
{
	double h = b - a;
	double mid = (a + b) / 2.;
	double d = h / 2. * 0.7745966692;
	return (5. / 9. * f(mid - d) + 8. / 9. * f(mid) + 5. / 9. * f(mid + d)) * h / 2.;
}

double findSum(double a, double b, int m, double(*method)(double, double, double(*)(double)), double(*f)(double))
{
	double h = (b - a) / m;
	double sum = 0;
	for (double x = a; x < b; x += h)
		sum += method(x, x + h, f);
	return sum;
}

double findPogr(double a, double b, int& mEps, double eps, double(*method)(double, double, double(*)(double)), double(*f)(double))
{
	mEps = 2;
	double s1 = findSum(a, b, mEps, method, f), s2;
	do
	{
		s2 = s1;
		mEps *= 2;
		s1 = findSum(a, b, mEps, method, f);
	} while (fabs(s2 - s1) >= eps);
	return s1;
}

void find(double a, double b, int m, double eps, double(*f)(double))
{
	int mEps = 0;
	cout << setw(37) << "Заданная m" << setw(21) << "Заданная точность\n";
	cout << "Формула средних:" << setw(19) << findSum(a, b, m, fSr, f) << setw(13) << findPogr(a, b, mEps, eps, fSr, f) << ", m = ";
	cout << mEps << "\nФормула трапеций:" << setw(18) << findSum(a, b, m, fTr, f) << setw(13) << findPogr(a, b, mEps, eps, fTr, f) << ", m = ";
	cout << mEps << "\nФормула Симпсона:" << setw(18) << findSum(a, b, m, fSim, f) << setw(13) << findPogr(a, b, mEps, eps, fSim, f) << ", m = ";
	cout << mEps << "\nАвтоматический метод 2:" << setw(12) << findSum(a, b, m, fAuto, f) << setw(13) << findPogr(a, b, mEps, eps, fAuto, f) << ", m = ";
	cout << mEps << "\nФормула Гаусса 2го порядка:" << setw(8) << findSum(a, b, m, gauss2, f) << setw(13) << findPogr(a, b, mEps, eps, gauss2, f) << ", m = ";
	cout << mEps << "\nФормула Гаусса 3го порядка:" << setw(8) << findSum(a, b, m, gauss3, f) << setw(13) << findPogr(a, b, mEps, eps, gauss3, f) << ", m = ";
	cout << mEps << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, eps;
	int m;

	while (true)
	{
		system("cls");
		cout << "\t\t\tНажмите\n"
			<< "\t\t1 -- 4x - 7 * sin(x)\n"
			<< "\t\t2 -- x^2 - 10 * sin(x)^2\n"
			<< "\t\t3 -- ln(x) - 5 * cos(x)\n"
			<< "\t\t4 -- e^x / x^3 - sin(x)^3\n"
			<< "\t\t5 -- sqrt(x) - cos(x)^2\n"
			<< "\t\t6 -- ln(x) - 5 * sin(x)^2\n";

		switch (_getch())
		{
		case '1':
			readData(a, b, m, eps, 1);
			find(a, b, m, eps, f1);
			break;

		case '2':
			readData(a, b, m, eps, 2);
			find(a, b, m, eps, f2);
			break;

		case '3':
		 	readData(a, b, m, eps, 3);
			find(a, b, m, eps, f3);
			break;

		case '4':
			readData(a, b, m, eps, 4);
			find(a, b, m, eps, f4);
			break;

		case '5':
			readData(a, b, m, eps, 5);
			find(a, b, m, eps, f5);
			break;

		case '6':
			readData(a, b, m, eps, 6);
			find(a, b, m, eps, f6);
			break;
		}

		cout << "Желаете продолжить(y/n)\n";
		if (_getch() != 'y')
			break;
	}
}