#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <string>

using namespace std;

struct student {
	char name[30];
	int year;
	int group;
	int phys;
	int math;
	int inf;
	int chem;
	double avgMark;
};

void create(student* students, int i)
{
	cout << "Введите фамилию\n"; cin >> students[i].name;
	cout << "Введите год рождения\n"; cin >> students[i].year;
	cout << "Введите номер группы\n"; cin >> students[i].group;
	cout << "Введите оценки за семестр:\nпо физике\n"; cin >> students[i].phys;
	cout << "по математике\n"; cin >> students[i].math;
	cout << "по информатике\n"; cin >> students[i].inf;
	cout << "по химии\n"; cin >> students[i].chem;
	cout << "Введите средний балл\n"; cin >> students[i].avgMark;
}

char* rus(const char* text)
{
	char* bufRus = new char[strlen(text)];
	OemToCharA(text, bufRus);
	return bufRus;
}

void print(student* students, int numSt)
{
	cout << "\n\n\n" << setw(50) << "Студенты:\n\n";
	for (int i = 0; i < numSt; i++)
	{
		cout << "Фамилия и инициалы: " << rus(students[i].name) << endl;
		cout << "Год рождения: " << students[i].year << endl;
		cout << "Номер группы: " << students[i].group << endl;
		cout << "Оценки за семестр: по физике: " << students[i].phys << endl;
		cout << "                   по математике: " << students[i].math << endl;
		cout << "                   по информатике: " << students[i].inf << endl;
		cout << "                   по химии: " << students[i].chem << endl;
		cout << "Средний балл: " << students[i].avgMark << endl;
	}
}

void change(student* students, int numSt)
{
	int n;
	cout << "Введите номер студента для изменения\n";
	do
	{
		cin >> n;
	} while (n < 0 || n >= numSt);

}

int main()
{
	cout.precision(2);
	cout << fixed;
	student* students = new student[30];
	int numSt = 0;
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		cout << "\n\n\n" << setw(20) << "Нажмите\n" << " 1 - Создание\n 2 - Просмотр\n 3 - Коррекция\n Иначе - решение индивидуального задания\n";
		char a = _getch();
		if (a == '1')
		{
			create(students, numSt);
			numSt++;
		}
		if (a == '2')
			print(students, numSt);
		if (a == '3')
			change(students, numSt);
		if (a == '4')
			break;
	}
	delete[]students;
}