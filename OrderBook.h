#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>
struct Order // структура для каждого заказа
{
	Order(int i = 0, double p = 0, double r = 0);
	
		int id; // номер заказа
		double profit;	// Эк.эффективность
		double resources;	// Затраты ресурсов
	
};

struct OrderGroup {
	OrderGroup();// конструктор по умолчанию
	OrderGroup(int size);// конструктор, заполняющий случайным образом
	~OrderGroup();// деструктор

		int* getIds();// функция возвращает массив id у группы Order-ов
		Order getOrderByprofit(double p);

		double calcprofit();// функция считает общую Эк.эффективность у группы Order-ов
		double calcresources();// функция считает общие затраты ресурсов у группы Order-ов
	
		void add(const Order& order);
	
		void print();// функция печатает группу Order-ов
		void input();// функция считывает массив Order-ов с клавиатуры
		double* sortingprofits();// функция возвращет массив эффективностей, отсортированный по убыванию (пузырьком) 
	
		std::vector<Order> orders;
	
};

int iterCount(int count);// функция возводит 2 в степень count
OrderGroup getTakenOrders(bool* positions, OrderGroup orders);// функция возвращает массив Order-ов, на месте которых в массиве positions стоят единицы
void printIntArray(int* arr, int size);// функция печатает массив int-ов длины size
void printBoolArray(bool* arr, int size);// функция печатает массив bool-ов длины size
void printDoubleArray(double* arr, int size);// функция печатает массив double-ов длины size
bool isNull(bool* arr, int size);// функция возвращает true, если массив bool-ов длины size полностью заполнен нулями, в противном случае false
bool* nullArr(int size);// функция возваращает массив bool-ов длины size, заполненный нулями
void copyArrays(bool* from, bool* to, int size);// функция копирует данные из одного массива в другой
void getNext(bool* arr, int size);// функция прибавляет 1 к двоичному числу
OrderGroup getBestCombination1(OrderGroup orders, double occupancy, double& bestprofit);// функция выбирает лучшую комбинацию методом полного перебора
OrderGroup getBestCombination2(OrderGroup orders, double occupancy, double& bestprofit);// функция выбирает лучшую комбинацию эвристическим алгоритмом
