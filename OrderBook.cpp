#include "OrderBook.h"

using namespace std;

Order::Order(int i, double p, double r)	// конструктор с тремя параметрами
: id(i)				// инициализируем поле id переменной i
, profit(p)				// инициализируем поле profit(прибыль) переменной p
, resources(r)				// инициализиурем поле resources(ресурсы) переменной r
{ }

// функция возводит 2 в степень count
int iterCount(int count)
{
	return pow(2, count);
}

// конструктор по умолчанию
OrderGroup::OrderGroup()
{ }

// конструктор, заполняющий случайным образом
OrderGroup::OrderGroup(int size)
{
	srand(time(0));
	for (int i = 0; i < size; i++) {
		add(Order(i, 1 + rand() % 10, 1 + rand() % 10));
	}
}

// деструктор
OrderGroup::~OrderGroup()
{
	orders.clear();
}

// функция возвращает массив id у группы Order-ов
int* OrderGroup::getIds()
{
	int* ids = new int[orders.size()]; // size стандартная ф-ция для вектора, в любой момент можно посмотреть размер  
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

// функция считает общую прибыль у группы Order-ов
double OrderGroup::calcprofit()
{
	double totalprofit = 0;
	for (int i = 0; i < orders.size(); i++) {
		totalprofit += orders[i].profit;
	}
	return totalprofit;
}

// функция считает общие затраты у группы Order-ов
double OrderGroup::calcresources()
{
	double totalResources = 0;
	for (int i = 0; i < orders.size(); i++) {
		totalResources += orders[i].resources;
	}
	return totalResources;
}

// функция добавляет Order в группу Order-ов
void OrderGroup::add(const Order& order)
{
	orders.push_back(order);
}

// функция возвращает массив Order-ов, на месте которых в массиве positions стоят единицы
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

// функция печатает массив int-ов длины size
void printIntArray(int* arr, int size)
{
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// функция печатает массив bool-ов длины size
void printBoolArray(bool* arr, int size)
{
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// функция печатает массив double-ов длины size
void printDoubleArray(double* arr, int size)
{
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// функция печатает группу Order-ов
void OrderGroup::print()
{
	cout << "Заказы:" << endl;
	for (int i = 0; i < orders.size(); i++) {
		cout << "Номер: " << orders[i].id << ", экономическая эффективность(прибыль): " << orders[i].profit << ", Затраты ресурсов: " << orders[i].resources << endl;
	}
	cout << endl;
}

// функция считывает массив Order-ов с клавиатуры
void OrderGroup::input()
{
	int size;
	cout << "	Количество заказов: "; 
	cin >> size;
	for (int i = 0; i < size; i++) {
		cout << "	Введение параметров " << i << " заказа:" << endl;
		int id;
		double p;
		double r;
		cout << "	Введите номер: ";
		cin >> id;
		cout << "	Введите экономическую эффективность(прибыль): ";
		cin >> p;
		cout << "	Введите количество, затрачиваемых ресурсов: ";
		cin >> r;
		add(Order(id, p, r));
	}
	cout << endl;
}

// функция возвращет массив прибылей, отсортированный по убыванию (пузырьком) 
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

// функция возвращает true, если массив bool-ов длины size полностью заполнен нулями, в противном случае false
bool isNull(bool* arr, int size)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == 1) {
			return false;
		}
	}
	return true;
}

// функция возваращает массив bool-ов длины size, заполненный нулями
bool* nullArr(int size)
{
	bool* arr = new bool[size];
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
	return arr;
}

// функция копирует данные из одного массива в другой
void copyArrays(bool* from, bool* to, int size)
{
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}

// функция прибавляет 1 к двоичному числу
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

// функция выбирает лучшую комбинацию методом полного перебора
OrderGroup getBestCombination1(OrderGroup orders, double occupancy, double& bestprofit)
{
	int size = orders.orders.size();		// число Order-ов
	bool* opt = new bool[size];			// оптимальное решение
	bool* positions = nullArr(size);	// текущие позиции, их мы увеличивать будем
	double currentBestprofit = 0;		// наибольшая прибыль
	OrderGroup bestOrders;				// наилучшая группа

	for (int i = 0; i < iterCount(size); i++) {
		OrderGroup currentOrders = getTakenOrders(positions, orders);		//  currentOrders - текущие Order-ы
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

// функция выбирает лучшую комбинацию эвристическим алгоритмом
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
