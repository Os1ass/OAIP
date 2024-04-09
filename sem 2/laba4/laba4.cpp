#include <iostream>
#include <conio.h>
using namespace std;

struct stackChar
{
	char value;
	stackChar* next;
};

void del(stackChar* curNode)
{
	stackChar* rem;

	while (curNode)
	{
		rem = curNode;
		curNode = curNode->next;
		delete rem;
	}
}

void delBeg(stackChar*& begin)
{
	stackChar* rem = begin;
	begin = begin->next;
	delete rem;
}

stackChar* push(stackChar* begin, int newValue)
{
	stackChar* newNode = new stackChar;
	newNode->value = newValue;
	newNode->next = begin;
	return newNode;
}

struct stackDouble
{
	double value;
	stackDouble* next;
};

void del(stackDouble* curNode)
{
	stackDouble* rem;

	while (curNode)
	{
		rem = curNode;
		curNode = curNode->next;
		delete rem;
	}
}

void delBeg(stackDouble*& begin)
{
	stackDouble* rem = begin;
	begin = begin->next;
	delete rem;
}

stackDouble* push(stackDouble* begin, double newValue)
{
	stackDouble* newNode = new stackDouble;
	newNode->value = newValue;
	newNode->next = begin;
	return newNode;
}

void read(double& a)
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

int prior(char a)
{
	switch (a)
	{
	case '^':			return 5;
	case '*': case '/': return 4;
	case '-': case '+': return 3;
	case '(':           return 2;
	case ')':			return 1;
	default:			return 0;
	}
}

bool checkExpr(char str[])
{
	if (strlen(str) == 0)
	{
		cout << "Ошибка, пустая строка\n";
		return false;
	}

	if (prior(str[0]) != 0 && str[0] != '(')
	{
		cout << "Ошибка, первый символ ";
		if (prior(str[0]) > 2)
			cout << "операция\n";
		else
			cout << "закрывающая скобка\n";
		return false;
	}

	int balance = 0, prev;
	if (str[0] == '(')
		balance++;
	prev = prior(str[0]);

	for (int i = 1; str[i]; i++)
	{
		switch (str[i])
		{
		case ' ':
			break;

		case '(':
			if (prev == 0 || str[i - 1] == ')')
			{
				cout << "Ошибка, на " << i + 1 << " позиции не хватает операции\n";
				return false;
			}
			balance++;
			break;

		case ')':
			if (prev > 2 || str[i - 1] == '(' || balance == 0)
			{
				cout << "Ошибка, на " << i + 1 << " позиции ";
				if (balance == 0)
					cout << "нарушен баланс скобок\n";
				else
					if (prev > 2)
						cout << "не хватает переменной\n";
					else
						cout << "пустые скобки\n";
				return false;
			}
			balance--;
			break;

		default:
			if (prior(str[i]) > 2)
			{
				if (prev > 2 || str[i - 1] == '(')
				{
					cout << "Ошибка, на " << i + 1 << " позиции ";
					if (prev > 2)
						cout << "две подряд операции\n";
					else
						cout << "не хватает переменной\n";
					return false;
				}
			}
			else
			{
				if ((str[i] < 'a' || str[i] > 'z'))
				{
					cout << "Ошибка, на " << i + 1 << " позиции ";
					cout << "неизвестный символ\n";
					return false;
				}
				if (prev == 0 || str[i - 1] == ')')
				{
					cout << "Ошибка, на " << i + 1 << " позиции ";
					if (prev == 0)
						cout << "две буквы подряд\n";
					else
						cout << "не хватает операции\n";
					return false;
				}
			}
			break;
		}
		prev = prior(str[i]);
	}
	if (balance != 0)
	{
		cout << "Ошибка, нарушен баланс скобок\n";
		return false;
	}
	if (prev != 0 && str[strlen(str) - 1] != ')')
	{
		cout << "Ошибка, последний символ операция\n";
		return false;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	stackChar* beginChar;
	stackDouble* beginDouble;
	char str[256], opz[256];
	double vars[26];
	int i, j;

	while (true)
	{
		system("cls");
		cin.ignore(255, '\n');
		beginChar = nullptr;
		beginDouble = nullptr;
		i = j = 0;

		for (int i = 0; i < 26; i++)
			vars[i] = -1;
		do
		{
			cout << "Введите выражение: ";
			cin.getline(str, 256);
		} while (!checkExpr(str));

		while (str[i])
		{
			switch (str[i])
			{
			case ' ':
				break;

			case '(':
				beginChar = push(beginChar, '(');
				break;

			case ')':
				while (beginChar && beginChar->value != '(')
				{
					opz[j] = beginChar->value;
					j++;

					delBeg(beginChar);
				}
				delBeg(beginChar);
				break;

			default:
				if (prior(str[i]) > 2 && prior(str[i]) < 6)
				{
					while (beginChar && prior(beginChar->value) >= prior(str[i]))
					{
						opz[j] = beginChar->value;
						j++;

						delBeg(beginChar);
					}
					beginChar = push(beginChar, str[i]);
				}

				if (str[i] >= 'a' && str[i] <= 'z')
				{
					opz[j] = str[i];
					j++;

					vars[str[i] - 'a'] = 0;
				}
				break;
			}
			i++;
		}

		while (beginChar)
		{
			opz[j] = beginChar->value;
			j++;

			delBeg(beginChar);
		}

		cout << "ОПЗ: ";
		for (int i = 0; i < j; i++)
			cout << opz[i];
		cout << endl;

		for (int i = 0; i < 26; i++)
		{
			if (vars[i] == -1)
				continue;

			cout << "Введите значение " << (char)(i + 'a') << ": ";
			read(vars[i]);
		}

		i = 0;
		while (i < j)
		{
			if (opz[i] >= 'a' &&
				opz[i] <= 'z')
				beginDouble = push(beginDouble, vars[opz[i] - 'a']);

			else
			{
				double a, b, r = 0;
				if (beginDouble)
					b = beginDouble->value;
				else
					break;
				delBeg(beginDouble);
				if (beginDouble)
					a = beginDouble->value;
				else
					break;
				delBeg(beginDouble);

				switch (opz[i])
				{
				case '+':
					r = a + b;
					break;

				case '-':
					r = a - b;
					break;

				case '*':
					r = a * b;
					break;

				case '/':
					if (b == 0)
					{
						cout << "Ошибка, деление на ноль\n";
						del(beginDouble);
						beginDouble = nullptr;
						break;
					}

					r = a / b;
					break;

				case '^':
					r = pow(a, b);
					break;
				}

				beginDouble = push(beginDouble, r);
			}
			i++;
		}

		if (beginDouble != nullptr)
			cout << "Результат: " << beginDouble->value << endl;
		else
			cout << "Что-то пошло не так\n";

		del(beginDouble);
		beginDouble = nullptr;

		char c;
		cout << "\nХотите продолжить(y/n)?\n";
		c = _getch();

		if (c != 'y' && c != 'Y')
			break;
	}
}