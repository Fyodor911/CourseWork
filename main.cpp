#include "menu.h"
#include <string>

using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");
	Menu menu;
	cout << "������� ������� �����. ����� ������, ������� Enter.";
	getchar();//��������� ������� Enter
	while (menu.mainMenu()) //���� � menu.mainMenu = true ��������� ������ �������� ����
	{
		menu.mainMenu();
	};
}

