#include <iostream>
#include <string>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string s;
	cout << "Введите строку:\n";
	getline(cin, s);
	int ans = 0, i = 0, size = s.length();
	while (i < size)
	{
		int pos = 1;
		while ((s[i] < '0' || s[i] > '9') && s[i] != '-' && i < size)   //проход до начала числа
			i++;
		if (i == size)                                                  //если строка кончилась - выходим
			break;
		if (s[i] == '-')												//если число отрицательное
		{
			pos = -1;
			i++;
		}
		string n = "";													//инциализация строки для числа
		while (s[i] >= '0' && s[i] <= '9')								//запись числа в строку
		{
			n += s[i];
			i++;
		}
		int a = 0, d = 1;
		if (n.length() > 8)
			continue;
		for (int j = n.length() - 1; j >= 0; j--, d *= 10)				//преобразование строки в число
			a += (n[j] - '0') * d;
		a *= pos;
		if (n.length() > 0)												//вывод числа
			ans += a;
	}
	cout << ans << endl;
}
