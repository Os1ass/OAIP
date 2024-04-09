#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

struct node
{
	int value;
	node* next;
	node* prev;
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

void create(node*& beg, node*& end)
{
	beg = end = new node;
	beg->value = rand() % 21 - 10;
	beg->next = beg->prev = nullptr;
}

node* pushBeg(int val, node* beg)
{
	node* newNode = new node;

	newNode->value = val;
	newNode->next = beg;
	newNode->prev = nullptr;

	beg->prev = newNode;
	return newNode;
}

node* pushEnd(int val, node* end)
{
	node* newNode = new node;

	newNode->value = val;
	newNode->next = nullptr;
	newNode->prev = end;

	end->next = newNode;
	return newNode;
}

void printFromBeg(node* curNode)
{
	while (curNode)
	{
		cout << curNode->value << '\t';
		curNode = curNode->next;
	}
	cout << endl;
}

void printFromEnd(node* curNode)
{
	while (curNode)
	{
		cout << curNode->value << '\t';
		curNode = curNode->prev;
	}
	cout << endl;
}

node* findMin(node* curNode)
{
	node* min = curNode;

	while (curNode)
	{
		if (min->value > curNode->value)
			min = curNode;

		curNode = curNode->next;
	}

	return min;
}

node* replace(node* begin, node* min)
{
	begin->next->prev = min->prev->next = nullptr;
	return begin->next;
}

void del(node* curNode)
{
	node* rem;

	while (curNode)
	{
		rem = curNode;
		curNode = curNode->next;
		delete rem;
	}
}

bool remove(node* beg, int val)
{
	node* curNode = beg;
	while (curNode && curNode->value != val)
		curNode = curNode->next;

	if (curNode == nullptr)
		return false;

	if (curNode->prev != nullptr)
		curNode->prev->next = curNode->next;
	if (curNode->next != nullptr)
		curNode->next->prev = curNode->prev;

	delete curNode;
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	node* beg = nullptr;
	node* end = nullptr;

	while (true)
	{
		system("cls");
		cout << "\n\t\t\t Нажмите"
			<< "\n\t\t 0 - Создать список"
			<< "\n\t\t 1 - Добавить элемент в начало"
			<< "\n\t\t 2 - Добавить элемент в конец"
			<< "\n\t\t 3 - Просмотреть список"
			<< "\n\t\t 4 - Удалить элемент из списка по значению"
			<< "\n\t\t Иначе - решение задачи\n\n\n";

		switch (_getch())
		{
		case '0':
		{
			if (beg)
			{
				cout << "Список создан\n";
				break;
			}

			create(beg, end);

			cout << "Список создан, 1 элемент добавлен\n";
			break;
		}
		case '1':
		{
			int val;
			cout << "Введите значение нового элемента: ";
			read(val);

			beg = pushBeg(val, beg);

			cout << "Элемент добавлен в начало\n";
			break;
		}
		case '2':
		{
			int val;
			cout << "Введите значение нового элемента: ";
			read(val);

			end = pushEnd(val, end);

			cout << "Элемент добавлен в конец\n";
			break;
		}
		case '3':
		{
			if (!beg)
			{
				cout << "Список пуст\n";
				break;
			}

			cout << "С начала:\t";
			printFromBeg(beg);
			cout << "С конца:\t";
			printFromEnd(end);

			break;
		}
		case '4':
		{
			if (!beg)
			{
				cout << "Список пуст\n";
				break;
			}

			int val;
			cout << "Введите значение, которое хотите удалить\n";
			read(val);

			if (remove(beg, val))
				cout << "Элемент удален\n";
			else
				cout << "Такие элементы не найдены\n";

			break;
		}
		default:
		{
			if (!beg)
			{
				cout << "Список пуст\n";
				break;
			}

			node* min = findMin(beg);
			if (beg == min)
			{
				cout << "Первый элемент - минимальный\n";
				break;
			}
			if (beg->next == min)
			{
				cout << "Второй элемент - минимальный\n";
				break;
			}

			node* newBeg = replace(beg, min);
			beg->next = min;
			min->prev = beg;

			cout << "Первый список:\t";
			printFromBeg(beg);
			cout << "Второй список:\t";
			printFromBeg(newBeg);

			cout << "Очистить память и закончить программу?(y/n)\n";
			if (_getch() == 'y')
			{
				del(beg);
				del(newBeg);
				cout << "Память очищена\n";
				return 0;
			}

			cout << "Нажмите 1, чтобы оставить первый стек, иначе - второй стек\n";
			if (_getch() == '1')
			{
				del(newBeg);
				cout << "Выбран первый стек\n";
			}
			else
			{
				del(beg);
				beg = newBeg;
				cout << "Выбран второй стек\n";
			}
		}
		}

		cout << "Нажмите любую клавишу чтобы продолжить\n";
		_getch();
	}
}