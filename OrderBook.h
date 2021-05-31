#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>
struct Order // ��������� ��� ������� ������
{
	Order(int i = 0, double p = 0, double r = 0);
	
		int id; // ����� ������
		double profit;	// ��.�������������
		double resources;	// ������� ��������
	
};

struct OrderGroup {
	OrderGroup();// ����������� �� ���������
	OrderGroup(int size);// �����������, ����������� ��������� �������
	~OrderGroup();// ����������

		int* getIds();// ������� ���������� ������ id � ������ Order-��
		Order getOrderByprofit(double p);

		double calcprofit();// ������� ������� ����� ��.������������� � ������ Order-��
		double calcresources();// ������� ������� ����� ������� �������� � ������ Order-��
	
		void add(const Order& order);
	
		void print();// ������� �������� ������ Order-��
		void input();// ������� ��������� ������ Order-�� � ����������
		double* sortingprofits();// ������� ��������� ������ ��������������, ��������������� �� �������� (���������) 
	
		std::vector<Order> orders;
	
};

int iterCount(int count);// ������� �������� 2 � ������� count
OrderGroup getTakenOrders(bool* positions, OrderGroup orders);// ������� ���������� ������ Order-��, �� ����� ������� � ������� positions ����� �������
void printIntArray(int* arr, int size);// ������� �������� ������ int-�� ����� size
void printBoolArray(bool* arr, int size);// ������� �������� ������ bool-�� ����� size
void printDoubleArray(double* arr, int size);// ������� �������� ������ double-�� ����� size
bool isNull(bool* arr, int size);// ������� ���������� true, ���� ������ bool-�� ����� size ��������� �������� ������, � ��������� ������ false
bool* nullArr(int size);// ������� ����������� ������ bool-�� ����� size, ����������� ������
void copyArrays(bool* from, bool* to, int size);// ������� �������� ������ �� ������ ������� � ������
void getNext(bool* arr, int size);// ������� ���������� 1 � ��������� �����
OrderGroup getBestCombination1(OrderGroup orders, double occupancy, double& bestprofit);// ������� �������� ������ ���������� ������� ������� ��������
OrderGroup getBestCombination2(OrderGroup orders, double occupancy, double& bestprofit);// ������� �������� ������ ���������� ������������� ����������
