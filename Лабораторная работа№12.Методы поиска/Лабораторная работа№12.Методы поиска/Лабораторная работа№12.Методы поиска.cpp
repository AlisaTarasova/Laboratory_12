#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Date
{
	int Day, Month, Year;
};

struct Address
{
	int Home;
	string Street;
};

struct Human
{
	string FIO;
	Date DateOfBirth;
	Address Address1;

	void Generate()
	{
		string names[] = { "Андрей", "Михаил", "Сергей", "Артём", "Дмитрий" };
		string surnames[] = { "Петров" , "Соловьёв", "Иванов","Гончаров","Пушкин" };
		string patronymic[] = { "Андреевич", "Владимирович", "Максимович", "Кирилович", "Ильич" };

		string street[] = {"Ленина","Екатерининская","Революция","Карла Маркса","Куйбышева"};

		FIO = surnames[rand() % 5] + " " + names[rand() % 5] + " " + patronymic[rand() % 5];
		DateOfBirth.Day = 1 + rand() % 28;
		DateOfBirth.Month = 1 + rand() % 12;
		DateOfBirth.Year = 1800 + rand() % 220;
		Address1.Home = 1 + rand() % 50;
		Address1.Street = street[rand()%5];
	}

	void Print()
	{
		cout << "ФИО: " << FIO << endl;
		cout << "Дата рождения: " << DateOfBirth.Day << "." << DateOfBirth.Month << "." << DateOfBirth.Year << endl;
		cout << "Адрес: " << Address1.Street <<", "<< Address1.Home << endl<<endl;
	}
};

void Creation(Human*&hum, int n)
{ 
	for (int i = 0; i <n; i++)
	{
		hum[i].Generate();
	}
}

void Printmas(Human*& hum, int n)
{
	if (n > 0)
	{
		for (int i = 0; i < n; i++)
		{
			cout << "Элемент " << i + 1 << ": " << endl;
			hum[i].Print();
		}
	}
	else
		cout << "Массив пуст.";
}

void SaveFale(Human*& hum,int n)
{
	ofstream F("F1.txt");
	if (F.is_open())
	{
		for (int i = 0; i <n; i++)
		{
			F << "Элемент " << i + 1<<": " << endl;
			F << hum[i].FIO << endl;
			F << hum[i].DateOfBirth.Day<<"."<< hum[i].DateOfBirth.Month<< "."<< hum[i].DateOfBirth.Year << endl;
			F << hum[i].Address1.Street << ", " << hum[i].Address1.Home << endl << endl;
		}
		F.close();
		cout << "Массив записан в файл F1.txt." << endl;
	}
	else
		cout << "Не удалось открыть файл F1.txt для подсчёта строк.";
}

void ReadingFale()
{
	ifstream F("F1.txt");
	string str;
	if (F.is_open())
	{
		while (!F.eof())
		{
			getline(F,str);
			cout << str<<endl;
		}
		F.close();
	}
	else
		cout << "Не удалось открыть файл F1.txt для копирования." << endl;
}

int LinearSearch(Human*& hum, Human key, int n)
{
	for (int i = 0; i < n; i++)
	{
		if ((hum[i].DateOfBirth.Day == key.DateOfBirth.Day) && (hum[i].DateOfBirth.Month = key.DateOfBirth.Month) && (hum[i].DateOfBirth.Year == key.DateOfBirth.Year))
			return i;
	}
	return -1;
}

struct InterPolation
{
	int Index;
	long long  Data;
};

int InterPolationSearch(Human*& hum, Human info, int n)
{
	long long key = info.DateOfBirth.Day * 1000000 + info.DateOfBirth.Month* 10000 + info.DateOfBirth.Year;
	InterPolation*hum1 = new InterPolation[n];
	for (int i = 0; i < n; i++)
	{
		hum1[i].Index= i;
		hum1[i].Data = hum[i].DateOfBirth.Day * 1000000 + hum[i].DateOfBirth.Month * 10000 + hum[i].DateOfBirth.Year;
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j <n - i - 1; j++)
		{
			if (hum1[j].Data > hum1[j + 1].Data)
			{
				InterPolation t = hum1[j];
				hum1[j] = hum1[j + 1];
				hum1[j + 1] = t;
			}
		}
	}
	int mid;
	int left = 0;
	int right = n - 1;
	while (hum1[left].Data < key && hum1[right].Data > key)
	{
		mid = left + (((key - hum1[left].Data) * (right - left)) / (hum1[right].Data - hum1[left].Data));
		if (hum1[mid].Data < key)
		{
			left = mid + 1;
		}
		if (hum1[mid].Data> key)
		{
				right = mid - 1;
		}
	}
	if (hum1[left].Data == key)
	{
		return hum1[left].Index;
	}
	if (hum1[right].Data == key)
	{
		return hum1[right].Index;
	}
	return -1;
}

int SubstringInString(Human*& hum, Human key, int n)
{
	string keystr = to_string(key.DateOfBirth.Day + key.DateOfBirth.Month + key.DateOfBirth.Year);
	string fullystr="";
	string amountstr;
	int num = 0, k=0;
	for (int i = 0; i < n; i++)
	{
		fullystr = fullystr + to_string(hum[i].DateOfBirth.Day + hum[i].DateOfBirth.Month + hum[i].DateOfBirth.Year);
	}

	for (int i = 0; i < fullystr.size() - keystr.size(); i++)
	{
		k ++;
		int j = 0;
		amountstr = to_string(hum[num].DateOfBirth.Day + hum[num].DateOfBirth.Month + hum[num].DateOfBirth.Year);
		if (k == amountstr.size())
		{
			num++;
			k = 0;
		}
		while (fullystr[i + j] == keystr[j] && j < keystr.size())
		{
			j++;
			if (j == keystr.size())
				return num;
		}
	}
	return -1;
}

void Search(Human*& hum,int n)
{
	Human key;
	cout << endl << "Введите дату рождения, по которой необходимо искать элемент: ";
	cin >> key.DateOfBirth.Day>> key.DateOfBirth.Month >>key.DateOfBirth.Year;

	int linaer;

	linaer = LinearSearch(hum, key, n);
	cout << endl << "ЛИНЕЙНЫЙ ПОИСК:" << endl;
	if (linaer != -1)
		cout << "Человек с заданным днём рождения есть: " << hum[linaer].FIO << endl;
	else
		cout << "Человек с заданным днём рождения отсутствует." << endl;
	
	linaer = InterPolationSearch(hum,key,n);
	cout << endl << "ИНТЕРПОЛЯЦИОННЫЙ ПОИСК:" << endl;
	if (linaer != -1)
		cout << "Человек с заданным днём рождения есть: " << hum[linaer].FIO << endl;
	else
		cout << "Человек с заданным днём рождения отсутствует." << endl;


	linaer = SubstringInString(hum, key,n);
	cout << endl << "ПРЯМОЙ ПОИСК ПОДСТРОКИ В СТРОКЕ:" << endl;
	if (linaer != -1)
		cout << "Человек с заданным днём рождения есть: " << hum[linaer].FIO << endl;
	else
		cout << "Человек с заданным днём рождения отсутствует." << endl;
}

void Adding(Human*& hum, int n)
{
	int v1;
	int add=-1;
	cout << "1 - добавить по номеру" << endl;
	cout << "2 - добавить по ключевому полю" << endl;
	cin >> v1;

	if (v1 == 1)
	{
		while (add < 0 || add >=n)
		{
			cout << "Введите номер элемента,на место которого необходимо вставить элемент: ";
			cin >> add;
		}
		hum[add-1].Generate();
	}
	else 
		if (v1 == 2)
		{
			Human key;
			cout << endl << "Введите день рождения элемента, на место которого надо вставить элемент: ";
			cin >>  key.DateOfBirth.Day>>key.DateOfBirth.Month >>key.DateOfBirth.Year;
			int add = LinearSearch(hum, key, n);
			if (add != -1)
			{
				hum[add].Generate();
			}
			else
			{
				cout << "Элемент с заданным днём рождения не найден." << endl;
			}
		}
		else
		{
			cout << "Введено некорректное значение." << endl;
		}
}

void Delete(Human*& hum, int& n)
{
	int v2;
	cout << "1 - удаление по номеру элемента" << endl;
	cout << "2 - удаление по ключевому полю" << endl;
	cin >> v2;
	if (v2 ==1)
	{
		int del=-1;
		while (del < 0 || del >= n)
		{
			cout << "Введите номер элемента, который необходимо удалить: ";
			cin >> del;
		} 
		for (int i =del-1; i < n-1; i++)
		{
				hum[i] = hum[i+ 1];
		}
		n--;
	}
	else 
		if (v2 ==2)
		{
		Human key;
		cout << endl << "Введите день рождение, по которому надо удалить элемент: ";
		cin >> key.DateOfBirth.Day >> key.DateOfBirth.Month >> key.DateOfBirth.Year;
		int del = LinearSearch(hum, key,n);
		if (del != -1)
		{
			for (int i = del ; i < n - 1; i++)
			{
				hum[i] = hum[i + 1];
			}
			n--;
		}
		else
		{
			cout << "Такого элемента в списке нет." << endl;
		}
		}
	else
	{
		cout << "Введено некорректное значение." << endl;
	}
}

int main()
{
	setlocale(0, "");
	system("color F0");

	int n=0;

	while (n <= 0)
	{
		cout << "Введите размер массива: ";
		cin >> n;
	}

	Human* hum = new Human [n];

	int v=0;
	while (v<8)
	{
		cout << "МЕНЮ: " << endl;
		cout << "1-создание массива" << endl;
		cout << "2-поиск элемента" << endl;
		cout << "3-сохранить массив в файл" << endl;
		cout << "4-считать массив из файла" << endl;
		cout << "5-добавление элемента" << endl;
		cout << "6-удаление элемента" << endl;
		cout << "7-распечатать массив" << endl;
		cout << "8-выход" << endl;

		cout << "Введите № команды: ";
		cin >> v;
		cout << endl;

		switch(v)
		{
		case 1:Creation(hum, n); break;
		case 2:Search(hum, n); break;
		case 3:SaveFale(hum, n); break;
		case 4:ReadingFale(); break;
		case 6:Delete(hum, n); break;
		case 5:Adding(hum,n); break;
		case 7:Printmas(hum,n); break;
		}
	}
}

//ФИО, дата_рождения, адрес, дата_рождения

//Лабораторная работа №12. Поиск данных в динамических структурах по заданному ключу
//Задание
//1. Создать динамический массив из записей(в соответствии с вариантом), содержащий не менее 100 элементов.Для заполнения элементов массива использовать ДСЧ.
//2. Предусмотреть сохранение массива в файл и загрузку массива из файла.
//3. Предусмотреть возможность добавления и удаления элементов из массива(файла).
//4. Выполнить поиск элемента в массиве по ключу в соответствии с вариантом.Для поиска использовать метод линейного поиска, метод Прямого поиска подстроки в строке и интерполяционный метод.

//2. Методические указания
//1. Для выбора действий использовать меню.
//2. Для добавления элементов в файл использовать вспомогательную структуру для хранения элементов в оперативной памяти(список).Добавление должно осуществляться в начало, в конец файла и на позицию с заданным номером.
//3. Удаление должно осуществляться по ключевому полю и по номеру.Удаляемые из файла записи помечаются как удаленные, когда их количество превысит половину файла, их можно удалять.При удалении использовать вспомогательную структуру для хранения элементов в оперативной памяти(список).
//4. Предусмотреть возможность отмены последней операции удаления.
//5. Корректировка выполняется по ключу и по номеру.
//6. Предусмотреть команду «Сохранить изменения», по которой измененные данные из списка переписываются в файл.