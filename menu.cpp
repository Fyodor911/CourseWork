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

bool Menu::mainMenu()//������� ����
{
	setlocale(LC_ALL, "Russian");
	system("cls");//������� ������
	int action;
	cout << "1. ���� �������� ������." << endl // ������ ������ 
		<< "2. ������� �������� ������." << endl // ���������� ������
		<< "3. ���������� �������." << endl // ��������� ������
		<< "4. �������� ����������." << endl //���������� ���������
		<< "5. �������� ������� ���������� �������." << endl // ���������� ����� ������� 
		<< "6. �����." << endl // �����
		<< "�������� ��������: "; // ������� �������� 
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

bool Menu::input() //������� ����� ������ (1)
{
	int action;
	cout << "1. ���� ������ �������." << endl // ������ ������ �������
		<< "2. ������������� ������ ��������� �������." << endl // ������������� ������
		<< "3. ��������� ������ �� 'inputData.txt'." << endl // ��������� ������ �� inputData.txt
		<< "4. ������� � ������� ����." << endl // ����� � ������� ����
		<< "�������� ��������: "; // �������� ��������
	cin >> action;
	switch (action)
	{
	case 1:
	{
		orders.input();// ������� ��������� ������ Order-�� � ����������
			  cout << "����� ��������: ";//����� ������������ ������� ��������
			  cin >> occupancy;
			  break;
	}
	case 2:
	{
			  int size;
			  cout << "������� ���������� �������: ";//������ ������� ����� �������
			  cin >> size;
			  cout << "����� ��������: ";//����� ������������ ������� ��������
			  cin >> occupancy;
			  orders = OrderGroup(size);// �����������, ����������� ��������� �������
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

bool Menu::output() // ������� ��������� ������
{
	int action;
	cout << "1. ����������� ������." << endl // ����������� ������ 
		<< "2. ��������� ������ � ���� 'KnapsackProblem.txt'." << endl // ��������� ������ � ���� KnapsackProblem.txt
		<< "3. ����� � ������� ����." << endl // ����� � ������� ����
		<< "�������� ��������: "; // �������� �������� 
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
			  fout << "������:" << endl;
			  for (int i = 0; i < orders.orders.size(); i++) {
				  fout << "����� ������: " << orders.orders[i].id << ", ������������� �������������: " << orders.orders[i].profit
					  << ", ������� ��������: " << orders.orders[i].resources << endl;
			  }
			  fout << "����� ��������: " << occupancy << endl << endl;
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

bool Menu::calc() // ������� ���������
{
	int action;
	cout << "1. ����� ����� ������� ��������." << endl // ����� ����� ������� ��������
		<< "2. ����� ������������� ������� ." << endl // ����� ������������� ������� 
		<< "3. ����� � ������� ����." << endl // ����� � ������� ����
		<< "�������� �������� : "; // �������� �������� 
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

bool Menu::showTime() // ������� ���������� �������
{
	int action;
	cout << "1. ���������� ����� �������." << endl // ���������� ����� �������
		<< "2. ��������� ����� ������� � ���� 'KnapsackProblem.txt'." << endl // ��������� ����� ������� � ���� KnapsackProblem.txt
		<< "3. ����� � ������� ����." << endl // ����� � ������� ����
		<< "�������� ��������: "; // ������ ��������
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

bool Menu::showResults() // ������� ��������� �����������
{
	int action;
	cout << "1. ���������� ������� ����������." << endl // ���������� ������� ����������
		<< "2. ��������� ���������� � 'KnapsackProblem.txt'." << endl // ��������� ���������� � KnapsackProblem.txt
		<< "3. ����� � ������� ����." << endl // ����� � ������� ����
		<< "�������� ��������: "; // ������ �������� 
	cin >> action;
	switch (action)
	{
	case 1:
	{
			  cout << "������ ������: ";
			  printIntArray(bestOrders.getIds(), bestOrders.orders.size());
			  cout << "������ �������: " << bestprofit << endl << endl;
			  break;
	}
	case 2:
	{
			  ofstream fout;
			  fout.open("KnapsackProblem.txt", ios_base::app);
			  fout << "������ ������: ";
			  for (int i = 0; i < bestOrders.orders.size(); i++) {
				  fout << bestOrders.getIds()[i] << " ";
			  }
			  fout << endl << "������ �������: " << bestprofit << endl << endl;
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
