#include <iostream>
#include <iomanip>
#include <conio.h>
#include "myQueue.h"
using namespace std;

int readKey()
{
	int key;
	cout << "Введите ключ: ";
	while (true)
	{
		cin >> key;
		if (cin.fail() || cin.peek() != '\n' || key > 999 || key < -99)
		{
			cout << "Ошибка! Попробуйте еще раз\n";
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
			break;
	}
	return key;
}

person readInfo()
{
	person info;

	do {
		cout << "Введите номер паспорта:\n";
		cin >> info.pass;
	} while (strlen(info.pass) > 10);

	do {
		cout << "Введите имя:\n";
		cin >> info.name;
	} while (strlen(info.name) > 10);

	return info;
}

tree* newLeaf(int key, person info)
{
	tree* newNode = new tree;
	newNode->key = key;
	newNode->left = newNode->right = nullptr;
	for (int i = 0; i < 256; i++)
	{
		newNode->info.name[i] = info.name[i];
		newNode->info.pass[i] = info.pass[i];
	}
	return newNode;
}

int findHeight(tree* cur)
{
	if (!cur)
		return 0;

	int left = findHeight(cur->left) + 1;
	int right = findHeight(cur->right) + 1;

	return left > right ? left : right;
}

int findDiff(tree* cur)
{
	return findHeight(cur->left) - findHeight(cur->right);
}

int findKol(tree* cur)
{
	if (!cur)
		return 0;
	return findKol(cur->left) + findKol(cur->right) + 1;
}

tree* rotateRight(tree* cur)
{
	tree* left = cur->left;
	cur->left = left->right;
	left->right = cur;
	return left;
}

tree* rotateLeft(tree* cur)
{
	tree* right = cur->right;
	cur->right = right->left;
	right->left = cur;
	return right;
}

tree* balance(tree* cur)
{
	int heightDiff = findDiff(cur);

	if (heightDiff == 2)
	{
		if (findDiff(cur->left) < 0)
			cur->left = rotateLeft(cur->left);
		return rotateRight(cur);
	}

	if (heightDiff == -2)
	{
		if (findDiff(cur->right) > 0)
			cur->right = rotateRight(cur->right);
		return rotateLeft(cur);
	}

	return cur;
}

tree* add(tree* newNode, tree* cur)
{
	if (!cur)
	{
		cout << "Элемент добавлен\n";
		return newNode;
	}
	
	if (newNode->key < cur->key)
		cur->left = add(newNode, cur->left);
	if (newNode->key > cur->key)
		cur->right = add(newNode, cur->right);

	if (newNode->key == cur->key)
		cout << "Ошибка! Элемент с таким ключом уже добавлен\n";

	return balance(cur);
}

tree* findKey(tree* cur, int key)
{
	while (cur != nullptr)
	{
		if (cur->key == key)
			return cur;

		if (key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	return cur;
}

tree* findMax(tree* cur)
{
	return cur->right ? findMax(cur->right) : cur;
}

tree* removeMax(tree* cur)
{
	if (!cur->right)
		return cur->left;

	cur->right = removeMax(cur->right);
	return balance(cur);
}

tree* removeKey(tree* cur, int key)	
{
	if (cur == nullptr)
	{
		cout << "Ошибка! элемента с таким ключом нет\n";
		return cur;
	}

	if (key < cur->key)
		cur->left = removeKey(cur->left, key);

	else
	if (key > cur->key)
		cur->right = removeKey(cur->right, key);

	else
	{
		tree* left = cur->left;
		tree* right = cur->right;
		delete cur;

		if (!left)
			return right;

		tree* max = findMax(left);
		max->left = removeMax(left);
		max->right = right;

		cout << "Элемент удален\n";
		return max;
	}

	return cur;
}

void getData(tree* cur, int* key, person* info, int& k)
{
	if (cur->left)
		getData(cur->left, key, info, k);

	key[k] = cur->key;
	info[k] = cur->info;
	k++;

	if (cur->right)
		getData(cur->right, key, info, k);
}

void printTr(tree* root, bool ind)
{
	if (!root)
	{
		cout << "Дерево пустое\n";
		return;
	}

	myQueue tr;
	create(tr, root);
	int h = findHeight(root);
	int kolT = pow(2, h + 1) - 1, level = -1, kolN = 0;
	int leafs = 0;

	while (tr.begin)
	{
		if (kolN == 0)
		{
			if (ind && level != -1)
			{
				for (int i = 0; i < (kolT >> 1); i++)
					cout << "   ";

				cout << "\t\tКоличество листьев на " << level + 1 << " уровне: " << leafs;
				leafs = 0;
			}

			kolT >>= 1;
			cout << endl;

			for (int i = 0; i < (kolT >> 1); i++)
				cout << "   ";

			level++;
			kolN = pow(2, level);
		}

		tree* cur = tr.begin->ver;

		if (ind && cur && !cur->left && !cur->right)
			leafs++;

		if (cur)
			cout << setw(3) << cur->key;
		else
			cout << "   ";

		kolN--;
		if (kolN != 0)
			for (int i = 0; i < kolT; i++)
				cout << "   ";

		if (cur)
		{
			pushEnd(tr, cur->left);
			pushEnd(tr, cur->right);
		}
		delBeg(tr);
	}
	cout << endl;
}

void printIn(tree* root)
{
	if (!root)
		return;

	int n = findKol(root);

	int* key = new int[n];
	person* info = new person[n];

	n = 0;
	getData(root, key, info, n);

	cout << "Ключ:    ";
	for (int i = 0; i < n; i++)
		cout << setw(11) << key[i];
	cout << "\nИмя:     ";
	for (int i = 0; i < n; i++)
		cout << setw(11) << info[i].name;
	cout << "\nПаспорт: ";
	for (int i = 0; i < n; i++)
		cout << setw(11) << info[i].pass;
	cout << "\n\n";

	delete[] key;
	delete[] info;
}

void clear(tree* cur)
{
	if (!cur)
		return;
	clear(cur->left);
	clear(cur->right);
	delete[] cur;
}

void task(tree* cur)
{
	if (!cur)
		return;
	if (!(cur->left && cur->right) && cur->key % 2 == 0)
	{
		tree* half = new tree;
		half->left = half->right = nullptr;
		half->key = cur->key / 2;
		cur->left = half;
		return;
	}
	task(cur->left);
	task(cur->right);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	tree* root = nullptr;

	while (true)
	{
		system("cls");
		cout << "\n\t\t\t Нажмите"
			<< "\n\t\t 0 - Добавить элемент в дерево"
			<< "\n\t\t 1 - Вывести дерево"
			<< "\n\t\t 2 - Удалить элемент по ключу"
			<< "\n\t\t 3 - Zalupa"
			<< "\n\t\t Иначе - решение задачи\n\n\n";

		switch (_getch())
		{
		case '0':
			root = add(newLeaf(readKey(), readInfo()), root);
			break;

		case '1':
			printTr(root, 0);
			printIn(root);
			break;

		case '2':
			root = removeKey(root, readKey());
			break;

		case '3':
			task(root);
			break;
		default:
			printTr(root, 1);
			printIn(root);
			clear(root);
			return 0;

		}
		cout << "\n\n\nНажмите любую клавишу чтобы продолжить\n";
		_getch();
	}
	clear(root);
}