#pragma once

#include "OrderBook.h"
#include "time.h"
#include <fstream>

struct Menu {
	Menu();
	~Menu();

	bool mainMenu();// ������� �������� ����
	bool input();// ������� ����� ������
	bool output();// ������� ��������� ������
	bool calc();// ������� ���������
	bool showTime();// ������� ���������� �������
	bool showResults();// ������� ��������� �����������

	OrderGroup orders;
	OrderGroup bestOrders;
	double occupancy; //����� ����� ��������
	double bestprofit; //������ �������(�������������)
	TimeFeature timeFeature;
};
