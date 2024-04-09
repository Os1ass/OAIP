#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

struct stack
{
	int value;
	stack* next;
};

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

stack* push(stack* begin, int newValue)
{
	stack* newNode = new stack;
	newNode->value = newValue;
	newNode->next = begin;
	return newNode;
}

void print(stack* curNode)
{
	while (curNode)
	{
		cout << curNode->value << '\t';
		curNode = curNode->next;
	}
	cout << endl;
}

void sortAdr(stack*& begin)
{
	begin = push(begin, 0);
	stack* sorted = nullptr;

	while (begin->next->next != sorted)
	{
		stack* curNode;
		for (curNode = begin; curNode->next->next != sorted; curNode = curNode->next)
			if (curNode->next->value > curNode->next->next->value)
			{
				stack* a = curNode->next;
				stack* b = curNode->next->next;

				a->next = b->next;
				b->next = a;
				curNode->next = b;
			}

		sorted = curNode->next;
	}
	
	stack* rem = begin;
	begin = begin->next;
	delete rem;
}

void sortVal(stack* begin)
{
	stack* sorted = nullptr;

	while (begin->next != sorted)
	{
		stack* curNode;
		for (curNode = begin; curNode->next != sorted; curNode = curNode->next)
			if (curNode->value > curNode->next->value)
			{
				int c = curNode->value;
				curNode->value = curNode->next->value;
				curNode->next->value = c;
			}

		sorted = curNode;
	}
}

stack* findMin(stack* curNode)
{
	stack* min = curNode;

	while (curNode)
	{
		if (min->value > curNode->value)
			min = curNode;

		curNode = curNode->next;
	}

	return min;
}

stack* replace(stack* begin, stack* min)
{
	stack* curNode = begin->next;	
	while (curNode->next != min)
		curNode = curNode->next;
	curNode->next = nullptr;

	return begin->next;
}

void del(stack* curNode)
{
	stack* rem;

	while (curNode)
	{
		rem = curNode;
		curNode = curNode->next;
		delete rem;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	stack* begin = nullptr;

	while (true)
	{
		system("cls");
		cout << "\n\t\t\t Нажмите"
			<< "\n\t\t 0 - Создать стек"
			<< "\n\t\t 1 - Добавить элемент в стек"
			<< "\n\t\t 2 - Просмотреть стек"
			<< "\n\t\t 3 - Сортировка"
			<< "\n\t\t 4 - Решение задачи"
			<< "\n\t\t Иначе выход из программы\n\n\n";

		switch (_getch())
		{
		case '0':
		{
			if (begin)
			{
				cout << "Стек создан\n";
				break;
			}

			int n = -1;
			do
			{
				cout << "Введите количество элементов: ";
				read(n);
			} while (n < 1);

			for (int i = 0; i < n; i++)
			{
				int newValue = rand() % 21 - 10;
				begin = push(begin, newValue);
			}
			
			cout << "Стек создан, " << n << " элементов добавлено\n";
			break;
		}
		case '1':
		{
			int newValue;
			cout << "Введите значение нового элемента: ";
			read(newValue);

			begin = push(begin, newValue);

			cout << "Элемент добавлен\n";
			break;
		}
		case '2':
		{
			if (!begin)
			{
				cout << "Стек пуст\n";
				break;
			}

			cout << "Стек:\t";
			print(begin);

			break;
		}
		case '3':
		{
			if (!begin)
			{
				cout << "Стек пуст\n";
				break;
			}

			system("cls");
			cout << "\n\t\t\t Нажмите"
				<< "\n\t\t 0 - Сортировка по адресам"
				<< "\n\t\t Иначе - Сортировка по значениям\n\n\n";

			if (_getch() == '0')
				sortAdr(begin);
			else
				sortVal(begin);

			cout << "Выполнена сортировка\n";
			break;
		}
		case '4':
		{
			if (!begin)
			{
				cout << "Стек пуст\n";
				break;
			}

			stack* min = findMin(begin);
			if (begin == min)
			{
				cout << "Первый элемент - минимальный\n";
				break;
			}
			if (begin->next == min)
			{
				cout << "Второй элемент - минимальный\n";
				break;
			}

			stack* newBegin = replace(begin, min);
			begin->next = min;

			cout << "Первый стек:\t";
			print(begin);
			cout << "Второй стек:\t";
			print(newBegin);

			cout << "Очистить память и закончить программу?(y/n)\n";
			if (_getch() == 'y')
			{
				del(begin);
				del(newBegin);
				cout << "Память очищена\n";
				return 0;
			}

			cout << "Нажмите 1, чтобы оставить первый стек, иначе - второй стек\n";
			if (_getch() == '1')
			{
				del(newBegin);
				cout << "Выбран первый стек\n";
			}
			else
			{
				del(begin);
				begin = newBegin;
				cout << "Выбран второй стек\n";
			}
			break;
		}
		default:
		{
			del(begin);
			return 0;
		}
		}

		cout << "Нажмите любую клавишу чтобы продолжить\n";
		_getch();
	}
}