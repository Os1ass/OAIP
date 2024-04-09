#include <iostream>
#include <conio.h>
using namespace std;

void read(int& a)
{
	while (true)
	{
		cin >> a;
		if (cin.fail() || cin.peek() != '\n')
		{
			cout << "Ошибка! Попробуйте еще раз\n";
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
			break;
	}
}

int gcdRec(int n, int m)
{
	if (m % n == 0)
		return n;
	return gcdRec(m % n, n);
}

int gcd(int n, int m)
{
	while (n > 0)
	{
		if (m % n == 0)
			return n;
		int c = n;
		n = m % c;
		m = c;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n = 0, m = 0;
	char kod;

	while (true)
	{
		system("cls");

		cout << "\n\t\t\t Нажмите"
			<< "\n\t\t 0 - НОД без рекурсии"
			<< "\n\t\t 1 - НОД с рекурсией"
			<< "\n\t\t Иначе - Выход\n\n\n";
		kod = _getch();

		if (kod != '1' &&
			kod != '0')
			break;

		do 
		{
			cout << "Введите первое число: ";
			read(n);
		} while (n < 1);
		
		do
		{
			cout << "Введите второе число: ";
			read(m);
		} while (m < 1);

		if (n > m)
		{
			int c = n;
			n = m;
			m = c;
		}

		cout << "\nНОД: ";
		cout << gcd(n, m) << endl;
		cout << gcdRec(n, m) << endl;

		cout << "\nНажмите любую клавишу";
		kod = _getch();
	}
}