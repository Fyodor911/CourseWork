#include "menu.h"
#include <string>

using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");
	Menu menu;
	cout << "Доброго времени суток. Чтобы начать, нажмите Enter.";
	getchar();//считывает нажатие Enter
	while (menu.mainMenu()) //пока у menu.mainMenu = true выполняет задачу главного меню
	{
		menu.mainMenu();
	};
}

