#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void read(int& a)
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

void swap(int& a, int& b)
{
	int c;
	c = a;
	a = b;
	b = c;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int n, a[10];
	int r = 0;
	long long ans = 1;
	do
	{
		cout << "Введите размер массива(1-10):\n";
		read(n);
	} while (n < 1 || n > 10);
	cout << "Введите массив:\n";
	cout << "Нажмите 0, чтобы сформировать массив рандомно, иначе - введите элементы с клавиатуры:\n";
	if (_getch() == '0')
		for (int i = 0; i < n; i++)
			a[i] = rand() % 10 + 1;
	else
		for (int i = 0; i < n; i++)
		{
			cout << i + 1 << " элемент:\n";
			read(a[i]);
		}
	cout << "Массив:\n";
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
	int nMin, nMax;
	nMin = nMax = 0;
	for (int i = 1; i < n; i++)
	{ 
		if (a[nMin] > a[i])
			nMin = i;

		if (a[nMax] < a[i])
			nMax = i;
	}
	cout << "Номер минимума: " << nMin + 1<< endl;
	cout << "Номер максимума: " << nMax + 1 << endl;
	if (nMin > nMax)
		swap(nMin, nMax);
	for (int i = nMin + 1; i < nMax; i++)
	{
		ans *= a[i];
		if (a[i] == 0)
			break;
	}
	if (nMin == nMax)
		cout << "Массив состоит из одинаковых элементов.\n";
	else
	if (nMax - nMin == 1)
		cout << "Максимум и минимум являются соседними элементами.\n";
	else
		cout << "Ответ: " << ans << endl;
}
