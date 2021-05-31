#pragma once

#include "OrderBook.h"
#include "time.h"
#include <fstream>

struct Menu {
	Menu();
	~Menu();

	bool mainMenu();// функция главного меню
	bool input();// функция ввода данных
	bool output();// функция просмотра данных
	bool calc();// функция подсчетов
	bool showTime();// функция нахождения времени
	bool showResults();// функция просмотра результатов

	OrderGroup orders;
	OrderGroup bestOrders;
	double occupancy; //Общее число ресурсов
	double bestprofit; //лучшая прибыль(эффективность)
	TimeFeature timeFeature;
};
