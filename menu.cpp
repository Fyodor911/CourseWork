#include "menu.h"
#include <stdlib.h>

using namespace std;

Menu::Menu()
: occupancy(0)
, bestprofit(0)
, timeFeature(0, 0, 0)
{ }

Menu::~Menu()
{ }

bool Menu::mainMenu()//главное меню
{
	setlocale(LC_ALL, "Russian");
	system("cls");//очистка экрана
	int action;
	cout << "1. Ввод исходных данных." << endl // ввести данные 
		<< "2. Прсмотр исходных данных." << endl // посмотреть данные
		<< "3. Выполнение расчета." << endl // выполнить расчет
		<< "4. Просмотр результата." << endl //посмотреть результат
		<< "5. Просмотр времени выполнения функции." << endl // посмотреть время функции 
		<< "6. Выход." << endl // выход
		<< "Выберите действие: "; // введите действие 
	cin >> action;
	switch (action)
	{
	case 1:
	{
			  do {
				  system("cls");
				  input();
			  } while (input());
			  break;
	}
	case 2:
	{
			  do {
				  system("cls");
				  output();
			  } while (output());
			  break;
	}
	case 3:
	{
			  do {
				  system("cls");
				  calc();
			  } while (calc());
			  break;
	}
	case 4:
	{
			  do {
				  system("cls");
				  showResults();
			  } while (showResults());
			  break;
	}
	case 5:
	{
			  do {
				  system("cls");
				  showTime();
			  } while (showTime());
			  break;
	}
	case 6:
	{
			  return false;
	}
	default:
		return false;
	}
	return true;
}

bool Menu::input() //функция ввода данных (1)
{
	int action;
	cout << "1. Ввод данных вручную." << endl // ввести данные вручную
		<< "2. Сгенерировать данные случайным образом." << endl // сгенерировать данные
		<< "3. Загрузить данные из 'inputData.txt'." << endl // загрузить данные из inputData.txt
		<< "4. Возврат в главное меню." << endl // выход в главное меню
		<< "Выберите действие: "; // выберите действие
	cin >> action;
	switch (action)
	{
	case 1:
	{
		orders.input();// функция считывает массив Order-ов с клавиатуры
			  cout << "Всего ресурсов: ";//общие максимальные затраты ресурсов
			  cin >> occupancy;
			  break;
	}
	case 2:
	{
			  int size;
			  cout << "Введите количество заказов: ";//ввести сколько всего заказов
			  cin >> size;
			  cout << "Всего ресурсов: ";//общие максимальные затраты ресурсов
			  cin >> occupancy;
			  orders = OrderGroup(size);// конструктор, заполняющий случайным образом
			  cout << endl;
			  break;
	}
	case 3:
	{
			  ifstream fin("inputData.txt");
			  int size;
			  fin >> size;
			  for (int i = 0; i < size; i++) {
				  int id;
				  double p;
				  double r;
				  fin >> id;
				  fin >> p;
				  fin >> r;
				  orders.add(Order(id, p, r));
			  }
			  fin.close();
			  break;
	}
	case 4:
	{
			  return false;
	}
	default:
		return false;
	}
	return true;
}

bool Menu::output() // функция просмотра данных
{
	int action;
	cout << "1. Посмотереть данные." << endl // посмотереть данные 
		<< "2. Сохранить данные в файл 'KnapsackProblem.txt'." << endl // сохранить данные в файл KnapsackProblem.txt
		<< "3. Выход в главное меню." << endl // выход в главное меню
		<< "Выберите действие: "; // выберите действие 
	cin >> action;
	switch (action)
	{
	case 1:
	{
		orders.print();
			  getchar();
			  break;
	}
	case 2:
	{
			  ofstream fout;
			  fout.open("KnapsackProblem.txt");
			  fout << "Заказы:" << endl;
			  for (int i = 0; i < orders.orders.size(); i++) {
				  fout << "Номер заказа: " << orders.orders[i].id << ", Экономическая эффективность: " << orders.orders[i].profit
					  << ", Затраты ресурсов: " << orders.orders[i].resources << endl;
			  }
			  fout << "Всего ресурсов: " << occupancy << endl << endl;
			  fout.close();
			  cout << endl;
			  break;
	}
	case 3:
	{
			  return false;
	}
	default:
		return false;
	}
	return true;
}

bool Menu::calc() // функция подсчетов
{
	int action;
	cout << "1. Найти путем полного перебора." << endl // найти путем полного перебора
		<< "2. Найти эвристическим методом ." << endl // найти эвристическим методом 
		<< "3. Выход в главное меню." << endl // выход в главное меню
		<< "Выберите действие : "; // выберите действие 
	cin >> action;
	switch (action)
	{
	case 1:
	{
			  double start, finish;
			  start = clock();
			  bestOrders = getBestCombination1(orders, occupancy, bestprofit);
			  finish = clock();
			  timeFeature = TimeFeature(start, finish, orders.orders.size());
			  cout << endl;
			  break;
	}
	case 2:
	{
			  double start, finish;
			  start = clock();
			  bestOrders = getBestCombination2(orders, occupancy, bestprofit);
			  finish = clock();
			  timeFeature = TimeFeature(start, finish, orders.orders.size());
			  cout << endl;
			  break;
	}
	case 3:
	{
			  return false;
	}
	default:
		return false;
	}
	return true;
}

bool Menu::showTime() // функция нахождения времени
{
	int action;
	cout << "1. Посмотреть время функции." << endl // посмотреть время функции
		<< "2. Сохранить время функции в файл 'KnapsackProblem.txt'." << endl // сохранить время функции в файл KnapsackProblem.txt
		<< "3. Выход в главное меню." << endl // выход в главное меню
		<< "Выберите действие: "; // выбери действие
	cin >> action;
	switch (action)
	{
	case 1:
	{
			  timeFeature.print();
			  cout << endl;
			  break;
	}
	case 2:
	{
			  ofstream fout;
			  fout.open("KnapsackProblem.txt", ios_base::app);
			  fout << "Time feature:" << endl << "Size: " << timeFeature.size << ", time: " << timeFeature.time << endl;
			  fout.close();
			  cout << endl;
			  break;

	}
	case 3:
	{
			  return false;
	}
	default:
		return false;
	}
	return true;
}

bool Menu::showResults() // функция просмотра результатов
{
	int action;
	cout << "1. Посмотреть текущие результаты." << endl // посмотреть текущие результаты
		<< "2. Сохранить результаты в 'KnapsackProblem.txt'." << endl // сохранить результаты в KnapsackProblem.txt
		<< "3. Выход в главное меню." << endl // выход в главное меню
		<< "Выберите действие: "; // выбери действие 
	cin >> action;
	switch (action)
	{
	case 1:
	{
			  cout << "Лучшие заказы: ";
			  printIntArray(bestOrders.getIds(), bestOrders.orders.size());
			  cout << "Лучшая прибыль: " << bestprofit << endl << endl;
			  break;
	}
	case 2:
	{
			  ofstream fout;
			  fout.open("KnapsackProblem.txt", ios_base::app);
			  fout << "Лучшие заказы: ";
			  for (int i = 0; i < bestOrders.orders.size(); i++) {
				  fout << bestOrders.getIds()[i] << " ";
			  }
			  fout << endl << "Лучшая прибыль: " << bestprofit << endl << endl;
			  fout.close();
			  cout << endl;
			  break;
	}
	case 3:
	{
			  return false;
	}
	default:
		return false;
	}
	return true;
}
