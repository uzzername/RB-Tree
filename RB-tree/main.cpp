// main.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Node.h"


#define DEBUG 1

using namespace std;

Node *rootNode = new Node();

int main()
{
	setlocale(LC_ALL, "rus");

	int choice = 0, key = 0;

#if DEBUG
	for (int i = 1; i <= 30; i++) rootNode->addKey(i);
#endif

	while (1)
	{
		while (1)// Цикл с пользовательским интерфейсом.
		{
			cout << "\n\nМеню:\n";
			cout << "-0-Выход из программы\n";
			cout << "-1-Добавление ключа\n";
			cout << "-2-Удаление ключа\n";
			cout << "-3-Поиск ключа\n";
			cout << "-4-Вывод дерева в файл\n";
			cout << "Выберите действие из списка меню: ";
			cin >> choice;
			if (choice <= 4 && choice >= 0) break;
			cout << "Сделайте выбор из предполагаемого диапазона:\n";
		}

		switch (choice)
		{
		case 0: return 0;

		case 1:
			cout << "\nВведите целочисленный ключ который будет добавлен: ";
			cin >> key;
			if (rootNode->addKey(key)) cout << "\nКлюч успешно добавлен\n";
			else cout << "\nТакой ключ уже существует\n";
			break;

		case 2:
			cout << "\nВведите целочисленный ключ который будет удален из RB-дерева: ";
			cin >> key;
			rootNode->remove(key);
			cout << "\nКлюч удален из RB-дерева\n";
			break;

		case 3:
			cout << "\nВведите целочисленный ключ для поиска в RB-дереве: ";
			cin >> key;
			if (rootNode->search(key)) cout << "\nТакой ключ существует в RB-дереве\n";
			else cout << "\nТакого ключа не существует в RВ-дереве\n";
			break;

		case 4:
			ofstream fout;
			fout.open("RB-tree.gv");
			rootNode->output(fout);
			cout << "\nДерево выведено в файл RB-tree.gv в формате DOT.\n";
			break;
		}
	}
}

