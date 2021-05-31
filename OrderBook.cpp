#include "OrderBook.h"

using namespace std;

Order::Order(int i, double p, double r)	// ����������� � ����� �����������
: id(i)				// �������������� ���� id ���������� i
, profit(p)				// �������������� ���� profit(�������) ���������� p
, resources(r)				// �������������� ���� resources(�������) ���������� r
{ }

// ������� �������� 2 � ������� count
int iterCount(int count)
{
	return pow(2, count);
}

// ����������� �� ���������
OrderGroup::OrderGroup()
{ }

// �����������, ����������� ��������� �������
OrderGroup::OrderGroup(int size)
{
	srand(time(0));
	for (int i = 0; i < size; i++) {
		add(Order(i, 1 + rand() % 10, 1 + rand() % 10));
	}
}

// ����������
OrderGroup::~OrderGroup()
{
	orders.clear();
}

// ������� ���������� ������ id � ������ Order-��
int* OrderGroup::getIds()
{
	int* ids = new int[orders.size()]; // size ����������� �-��� ��� �������, � ����� ������ ����� ���������� ������  
	for (int i = 0; i < orders.size(); i++) {
		ids[i] = orders[i].id;
	}
	return ids;
}

Order OrderGroup::getOrderByprofit(double p)
{
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i].profit == p) {
			return orders[i];
		}
	}
	return Order();
}

// ������� ������� ����� ������� � ������ Order-��
double OrderGroup::calcprofit()
{
	double totalprofit = 0;
	for (int i = 0; i < orders.size(); i++) {
		totalprofit += orders[i].profit;
	}
	return totalprofit;
}

// ������� ������� ����� ������� � ������ Order-��
double OrderGroup::calcresources()
{
	double totalResources = 0;
	for (int i = 0; i < orders.size(); i++) {
		totalResources += orders[i].resources;
	}
	return totalResources;
}

// ������� ��������� Order � ������ Order-��
void OrderGroup::add(const Order& order)
{
	orders.push_back(order);
}

// ������� ���������� ������ Order-��, �� ����� ������� � ������� positions ����� �������
OrderGroup getTakenOrders(bool* positions, OrderGroup orders)
{
	OrderGroup newOrders;
	for (int i = 0; i < orders.orders.size(); i++) {
		if (positions[i] == 1) {
			newOrders.add(orders.orders[i]);
		}
	}
	return newOrders;
}

// ������� �������� ������ int-�� ����� size
void printIntArray(int* arr, int size)
{
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// ������� �������� ������ bool-�� ����� size
void printBoolArray(bool* arr, int size)
{
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// ������� �������� ������ double-�� ����� size
void printDoubleArray(double* arr, int size)
{
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// ������� �������� ������ Order-��
void OrderGroup::print()
{
	cout << "������:" << endl;
	for (int i = 0; i < orders.size(); i++) {
		cout << "�����: " << orders[i].id << ", ������������� �������������(�������): " << orders[i].profit << ", ������� ��������: " << orders[i].resources << endl;
	}
	cout << endl;
}

// ������� ��������� ������ Order-�� � ����������
void OrderGroup::input()
{
	int size;
	cout << "	���������� �������: "; 
	cin >> size;
	for (int i = 0; i < size; i++) {
		cout << "	�������� ���������� " << i << " ������:" << endl;
		int id;
		double p;
		double r;
		cout << "	������� �����: ";
		cin >> id;
		cout << "	������� ������������� �������������(�������): ";
		cin >> p;
		cout << "	������� ����������, ������������� ��������: ";
		cin >> r;
		add(Order(id, p, r));
	}
	cout << endl;
}

// ������� ��������� ������ ��������, ��������������� �� �������� (���������) 
double* OrderGroup::sortingprofits()
{
	int size = orders.size();
	double* profits = new double[size];
	for (int i = 0; i < size; i++) {
		profits[i] = orders[i].profit;
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (profits[j] < profits[j + 1]) {
				double temp = profits[j];
				profits[j] = profits[j + 1];
				profits[j + 1] = temp;
			}
		}
	}

	return profits;
}

// ������� ���������� true, ���� ������ bool-�� ����� size ��������� �������� ������, � ��������� ������ false
bool isNull(bool* arr, int size)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == 1) {
			return false;
		}
	}
	return true;
}

// ������� ����������� ������ bool-�� ����� size, ����������� ������
bool* nullArr(int size)
{
	bool* arr = new bool[size];
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
	return arr;
}

// ������� �������� ������ �� ������ ������� � ������
void copyArrays(bool* from, bool* to, int size)
{
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}

// ������� ���������� 1 � ��������� �����
void getNext(bool* arr, int size)
{
	if (size == 0) {
		return;
	}

	if (arr[0] == 0) {
		arr[0] = 1;
	}
	else {
		arr[0] = 0;
		getNext(arr + 1, size - 1);
	}
}

// ������� �������� ������ ���������� ������� ������� ��������
OrderGroup getBestCombination1(OrderGroup orders, double occupancy, double& bestprofit)
{
	int size = orders.orders.size();		// ����� Order-��
	bool* opt = new bool[size];			// ����������� �������
	bool* positions = nullArr(size);	// ������� �������, �� �� ����������� �����
	double currentBestprofit = 0;		// ���������� �������
	OrderGroup bestOrders;				// ��������� ������

	for (int i = 0; i < iterCount(size); i++) {
		OrderGroup currentOrders = getTakenOrders(positions, orders);		//  currentOrders - ������� Order-�
		double currentResources = currentOrders.calcresources();
		if (currentResources <= occupancy) {
			double currentprofit = currentOrders.calcprofit();
			if (currentprofit > currentBestprofit) {
				copyArrays(positions, opt, size);
				bestOrders = currentOrders;
				currentBestprofit = currentprofit;
			}
		}
		getNext(positions, size);
	}

	bestprofit = currentBestprofit;

	return bestOrders;
}

// ������� �������� ������ ���������� ������������� ����������
OrderGroup getBestCombination2(OrderGroup orders, double occupancy, double& bestprofit)
{
	int size = orders.orders.size();
	OrderGroup bestOrders;
	OrderGroup temp;
	double* profits = orders.sortingprofits();
	int counter = 0;

	while (temp.calcresources() <= occupancy) {
		temp.add(orders.getOrderByprofit(profits[counter]));
		if (temp.calcresources() <= occupancy) {
			bestOrders.add(orders.getOrderByprofit(profits[counter]));
		}
		counter++;
	}

	bestprofit = bestOrders.calcprofit();

	return bestOrders;
}
