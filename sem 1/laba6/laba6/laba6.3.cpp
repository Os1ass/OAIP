#include <iostream>
using namespace std;

void read(int& a)
{
	while (true)
	{
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

bool check(double* a, int m)
{
	for (int j = 0; j < (m / 2); j++)
	{
		if (a[j] != a[m - j - 1])
			return false;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int i, n, m;						
	double** a;
	double* b;
	do
	{
		cout << "Введите n, количество строк:\n";
		read(n);
	} while (n < 1);
	do
	{
		cout << "Введите m, количество столбцов:\n";
		read(m);
	} while (m < 1);
	a = new double*[n];
	b = new double[n];
	cout << "Введите массив размером " << n << 'x' << m << ":\n";
	for (i = 0; i < n; i++) 	
	{
		a[i] = new double[m];
		for (int j = 0; j < m; j++)
			cin >> a[i][j];
		if (check(a[i], m))
			b[i] = 1;
		else
			b[i] = 0;
	}
	cout << "Вектор B:\n";
	for (int i = 0; i < n; i++)
	{
		delete[] a[i];
		cout << b[i] << endl;
	}
	delete[] a;
	delete[] b;
}
