#include <iostream>
#include <conio.h>
#include <cmath>
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

void readNM(int& n, int& m, int method)
{
	int border = 2;
	if (method == 4)
		border = 3;

	cout << "Введите n(до 100): "; read(n);
	while (n < border || n > 100)
	{
		cout << "Ошибка! Неверное значение, попробуйте еще раз\n";
		cout << "Введите n: "; read(n);
	}
	cout << endl;

	cout << "Введите m(m >= n): "; read(m);
	while (m < border || m > 100 || m < n)
	{
		cout << "Ошибка! Неверное значение, попробуйте еще раз\n";
		cout << "Введите m: "; read(m);
	}
	cout << endl;
}

bool def(double& a, double& b, int& n, int& m, int method)
{
	switch (method)
	{
	case 1:
		a = -2; b = 3;
		n = 5; m = 10;
		break;

	case 2:
		a = 0; b = 3;
		n = 4; m = 6;
		break;

	case 3:
		a = 1; b = 8;
		n = 4; m = 6;
		break;

	case 4:
		a = 4; b = 7;
		n = 4; m = 6;
		break;

	default:
		cout << "Значения по умолчанию не найдены\n";
		return false;
	}

	cout << "Значения по умолчанию: a = " << a << ", b = " << b << ", n = " << n << ", m = " << m << endl;
	cout << "Нажмите 1 чтобы использовать значения по умолчанию, иначе - введите свои\n";
	if (_getch() == '1')
		return true;
	return false;
}

void readData(double& a, double& b, int& n, int& m, int method)
{
	if (def(a, b, n, m, method))
		return;

	readAB(a, b);
	readNM(n, m, method);
}

double f1(double x)
{
	return 4. * x - 7. * sin(x);
}

double f2(double x)
{
	return x * x - 10 * sin(x) * sin(x) + 2;
}

double f3(double x)
{
	return log(x) - 5 * cos(x);
}

double f4(double x)
{
	return exp(x) / (x * x * x) - sin(x) * sin(x) * sin(x) - 2;
}

double lagr(double* xArr, double xt, int n, double(*fun)(double)) 
{
	double e, L = 0;
	int j;

	for (int i = 0; i < n; i++) 
	{
		e = 1.;

		for (j = 0; j < n; j++)
			if (i != j)    
				e *= ((xt - xArr[j]) / (xArr[i] - xArr[j]));

		L += e * fun(xArr[i]);
	}

	return L;
}

double newt(double* xArr, double xt, int n, double(*fun)(double)) 
{
	double* d = new double[n];
	for (int i = 0; i < n; i++)
		d[i] = fun(xArr[i]);
	double p = 1;
	double N = fun(xArr[0]);

	for (int k = 1; k <= n - 1; k++)
	{
		for (int i = 1; i <= n - k; i++)
			d[i - 1] = (d[i - 1] - d[i]) / (xArr[i - 1] - xArr[i + k - 1]);
		p *= (xt - xArr[k - 1]);
		N += p * d[0];
	}

	delete[] d;
	return N;
} 

double lin(double* xArr, double xt, int n, double(*f)(double)) 
{
	double N = 0;
	int i = 1;

	for (i; i < n; i++)
		if (xArr[i] >= xt && xArr[i - 1] <= xt)
			break;

	N = f(xArr[i - 1]) + (xt - xArr[i - 1]) * (f(xArr[i]) - f(xArr[i - 1])) / (xArr[i] - xArr[i - 1]);
	return N;
}

double sqr(double* xArr, double xt, int n, double(*f)(double)) 
{
	double N = 1;
	int i = 1;

	for (i; i < n - 1; i++)
		if (xArr[i + 1] >= xt && xArr[i - 1] <= xt)
			break;
	cout << xArr[i] << ": ";

	N *= (xt - xArr[i - 1]);
	N *= (xt - xArr[i]);
	N *= (((f(xArr[i - 1]) - f(xArr[i])) / (xArr[i - 1] - xArr[i])) - 
		((f(xArr[i]) - f(xArr[i + 1])) / (xArr[i] - xArr[i + 1])));
	N /= (xArr[i - 1] - xArr[i + 1]);
	N += f(xArr[i - 1]) + (xt - xArr[i - 1]) * (f(xArr[i]) - f(xArr[i - 1])) / (xArr[i] - xArr[i - 1]);

	return N;
}	

void findArr(double* xArr, double a, double b, int n)
{
	double h = (b - a) / (n - 1.);
	xArr[0] = a;
	for (int i = 1; i < n; i++)
		xArr[i] = xArr[i - 1] + h;
}

void printArr(double* xArr, int n, double(*f)(double))
{
	cout << "Таблица значений для вычисления аппроксимации\n";
	for (int i = 0; i < n; i++)
		cout << setprecision(3) << "x = " << setw(6) << xArr[i] << " f(x) = " << setw(9) << setprecision(6) << f(xArr[i]) << endl;
	cout << endl;
}

double findApp(double* xArr, double a, double b, int n, int m, double(*method)(double*, double, int, double(*)(double)), double(*f)(double))
{
	double mPogr = 0;
	cout << fixed;
	double h = (b - a) / (m - 1.);
	for (double x = a; x <= b; x += h)
	{
		double y = method(xArr, x, n, f);
		if (fabs(y - f(x)) > mPogr)
			mPogr = fabs(y - f(x));
		cout << setprecision(3) << "x = " << setw(6) << x << " f(x) = " << setw(9) << setprecision(6) << f(x) << ", аппроксимация = " << y << endl;
	}
	return mPogr;
}

void method(int k)
{
	if (k == 0)
		cout << "Аппроксимация многочленом Лагранжа\n";
	if (k == 1)
		cout << "Аппроксимация многочленом Ньютона\n";
	if (k == 2)
		cout << "Аппроксимация линейной интерполяцией\n";
	if (k == 3)
		cout << "Аппроксимация квадратичной интерполяцией\n";
}

void find(double a, double b, double n, double m, double(*f)(double))
{
	double* xArr = new double[n];
	double mPogr[4];
	findArr(xArr, a, b, n);
	printArr(xArr, n, f);

	method(0);
	mPogr[0] = findApp(xArr, a, b, n, m, lagr, f);
	cout << endl; method(1);
	mPogr[1] = findApp(xArr, a, b, n, m, newt, f);
	cout << endl; method(2);
	mPogr[2] = findApp(xArr, a, b, n, m, lin, f);
	cout << endl; method(3);
	mPogr[3] = findApp(xArr, a, b, n, m, sqr, f);

	int minI = 0;
	for (int k = 1; k < 4; k++)
		if (mPogr[k] < mPogr[minI])
			minI = k;
	cout << "\nЛучший метод - "; method(minI);

	delete[] xArr;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b;
	int n, m;

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
			readData(a, b, n, m, 1);
			find(a, b, n, m, f1);
			break;

		case '2':
			readData(a, b, n, m, 2);
			find(a, b, n, m, f2);
			break;

		case '3':
			readData(a, b, n, m, 3);
			find(a, b, n, m, f3);
			break;

		case '4':
			readData(a, b, n, m, 4);
			find(a, b, n, m, f4);
			break;
		}
		cout << "\nЖелаете продолжить(y/n)\n";
		if (_getch() != 'y')
			break;
	}
}