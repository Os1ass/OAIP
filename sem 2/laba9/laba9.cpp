#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

const char* fName = "data.dat";
const char* rName = "result.txt";

struct person {
	char num[256];
	char fio[256];
	char adr[256];
	char date[256];
};

void read(person& a)
{
	if (cin.peek() == '\n')
		cin.ignore(32767, '\n');
	cout << "Введите номер: ";
	cin.getline(a.num, 256);
	cout << "Введите ФИО: ";
	cin.getline(a.fio, 256);
	cout << "Введите адрес: ";
	cin.getline(a.adr, 256);
	cout << "Введите дату постаноки на учет: ";
	cin.getline(a.date, 256);
}

void print(person a, int i, ostream& sout)
{
	sout << endl << "\t\t\t\t\t" << i + 1 << "-е лицо" << endl;
	sout << "Номер: " << a.num << endl;
	sout << "ФИО: " << a.fio << endl;
	sout << "Адрес: " << a.adr << endl;
	sout << "Дата постановки на учет: " << a.date << endl;
}

int fileSize(const char* fName)
{
	ifstream f;
	f.open(fName, ios_base::binary);
	f.seekg(0, ios_base::end);

	int size = f.tellg();
	f.close();
	return size;
}

int findNumber()
{
	long len = fileSize(fName);
	int ret = len / sizeof(person);
	return ret;
}

void printPerson()
{
	system("cls");
	int n = findNumber();
	cout << "В файле содержатся записи " << n << " лиц\n";

	person* sp = (person*)calloc(n, sizeof(person));
	ifstream fin(fName, ios::binary);
	fin.read((char*)sp, sizeof(person) * n);
	fin.close();

	for (int i = 0; i < n; i++)
		print(sp[i], i, cout);
	delete[] sp;
}

void add()
{
	person newPerson;
	read(newPerson);
	ofstream fout(fName, ios::binary | ios::app);

	fout.write((char*)&newPerson, sizeof(person));
	fout.close();
}

bool equal(char* a, char* b)
{
	if (strlen(a) != strlen(b))
		return false;
	int size = strlen(a);
	for (int i = 0; i < size; i++)
		if (a[i] != b[i])
			return false;
	return true;
}

void linFind()
{
	int n = findNumber();
	char key[256];

	cout << "\n\nВведите дату для поиска: ";
	cin >> key;
	cout << "\n\n\n";

	person* sp = (person*)calloc(n, sizeof(person));
	ifstream fin(fName, ios::binary);
	fin.read((char*)sp, sizeof(person) * n);
	fin.close();

	for (int i = 0; i < n; i++)
		if (equal(sp[i].date, key))
		{
			print(sp[i], i, cout);

			delete[] sp;
			return;
		}

	cout << "Такой даты не найдено\n";
	delete[] sp;
}

bool aLessThanB(char* a, char* b)
{
	int i = 0;
	while (a[i] && b[i])
	{
		if (a[i] < b[i])
			return true;
		if (a[i] > b[i])
			return false;
		i++;
	}

	if (b[i])
		return true;
	return false;
}

void swap(char* a, char* b)
{
	char c;
	for (int i = 0; i < 256; i++)
	{
		c = a[i];
		a[i] = b[i];
		b[i] = c;
	}
}

void swap(person& a, person& b)
{
	swap(a.num, b.num);
	swap(a.fio, b.fio);
	swap(a.adr, b.adr);
	swap(a.date, b.date);
}

void qSort(person* sp, int n)
{
	int* lArr = new int[2 * n];
	int* rArr = new int[2 * n];
	lArr[0] = 0; rArr[0] = n - 1;
	int cur = 0;

	while (cur >= 0)
	{
		int l = lArr[cur];
		int r = rArr[cur];
		cur--;
		int i = l, j = r;
		int m = (i + j) / 2;

		while (i <= j)
		{
			while (aLessThanB(sp[i].date, sp[m].date)) i++;
			while (aLessThanB(sp[m].date, sp[j].date)) j--;

			if (i <= j)
			{
				swap(sp[i], sp[j]);
				i++; j--;
			}
		}

		if (j > l)
		{
			cur++;
			lArr[cur] = l;
			rArr[cur] = j;
		}

		if (i < r)
		{
			cur++;
			lArr[cur] = i;
			rArr[cur] = r;
		}
	}
	delete[] lArr;
	delete[] rArr;
}

void sort(person* sp, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int m = i;

		for (int j = i + 1; j < n; j++)
			if (aLessThanB(sp[j].date, sp[m].date))
				m = j;

		if (i != m)
			swap(sp[i], sp[m]);
	}
}

int binFind(person* sp, int l, int r, char* key)
{
	if (r < l)
		return -1;

	int m = (l + r) / 2;
	if (equal(sp[m].date, key))
		return m;

	if (aLessThanB(sp[m].date, key))
		return binFind(sp, m + 1, r, key);
	else
		return binFind(sp, l, m - 1, key);
}

void sortAndFind()
{
	int n = findNumber();
	person* sp = (person*)calloc(n, sizeof(person));
	ifstream fin(fName, ios::binary);
	fin.read((char*)sp, sizeof(person) * n);
	fin.close();

	system("cls");
	cout << "Нажмите q для QuickSort, иначе - сортировка методом прямого выбора\n";
	if (_getch() == 'q')
		qSort(sp, n);
	else
		sort(sp, n);

	cout << "\nОтсортированный массив: ";
	for (int i = 0; i < n; i++)
		print(sp[i], i, cout);

	char key[256];
	cout << "\nВведите дату для бинарного поиска: ";
	cin >> key;

	int keyInd = binFind(sp, 0, n - 1, key);
	if (keyInd == -1)
		cout << "Такой даты нет\n";
	else
		print(sp[keyInd], keyInd, cout);

	delete[]sp;
}

void clear()
{
	cout << "\n\n\nВы хотите удалить файл со структурами?(y/n)";
	switch (_getch())
	{
	case 'y':
		remove(fName);
		cout << "\nФайл удален\n";
		break;
	case 'n':
		cout << "\nФайл не удален\n";
		break;
	default:
		cout << "\nНеизвестная команда\n";
		clear();
		break;
	}
}

bool open()
{
	ofstream fout(fName, ios::binary | ios::app);

	if (!fout.is_open())
	{
		cout << "Не удалось открыть файл!\n";
		return false;
	}

	cout << "Файл успешно открыт\n";
	fout.close();
	return true;
}

bool check()
{
	ifstream file;
	file.open(fName);

	if (!file)
		return false;

	file.close();
	return true;
}

void erase(int cur)
{
	int n = findNumber();
	person* sp = (person*)calloc(n, sizeof(person));
	ifstream fin(fName, ios::binary);
	fin.read((char*)sp, sizeof(person) * n);
	fin.close();

	ofstream fout(fName, ios::binary | ios::trunc);
	for (int i = 0; i < n; i++)
		if (i != cur)
			fout.write((char*)&sp[i], sizeof(person));

	fout.clear();
	delete[] sp;
}

void task()
{
	int n = findNumber();

	person* sp = (person*)calloc(n, sizeof(person));
	ifstream fin(fName, ios::binary);
	fin.read((char*)sp, sizeof(person) * n);
	fin.close();

	for (int i = n - 1; i > 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
			if (equal(sp[i].fio, sp[j].fio) || equal(sp[i].adr, sp[j].adr))
			{
				erase(i);
				continue;
			}
	}

	cout << "Записи с одинаковыми адресами или ФИО удалены\n";
	delete[] sp;

	printPerson();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	bool opened = check();

	while (true)
	{
		system("cls");
		cout << "\n\n\n"
			<< "\t\t\t\t\tНажмите\n"
			<< "\t\t\t1 - Создание\n"
			<< "\t\t\t2 - Просмотр\n"
			<< "\t\t\t3 - Добавление\n"
			<< "\t\t\t4 - Линейный поиск\n"
			<< "\t\t\t5 - Сортировка и двоичный поиск\n"
			<< "\t\t\tИначе - Решение индивидуального задания\n";

		switch (_getch())
		{

		case '1':
			if (opened)
				cout << "Файл уже создан\n";
			else
			{
				opened = open();
				if (!opened)
					return 1;
			}
			break;

		case '2':
			if (!opened)
				cout << "\nФайл не создан\n";
			else
				printPerson();
			break;

		case '3':
			if (!opened)
				cout << "\nФайл не создан\n";
			else
				add();
			break;

		case '4':
			if (!opened)
				cout << "\nФайл не создан\n";
			else
				linFind();
			break;

		case '5':
			if (!opened)
				cout << "\nФайл не создан\n";
			else
				sortAndFind();
			break;

		default:
			if (!opened)
				cout << "\nФайл не создан\n";
			else
			{
				task();
				clear();
			}
			return 0;
		}
		cout << "Нажмите любую клавишу\n";
		_getch();
	}
}