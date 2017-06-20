// main.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		while (1)// ���� � ���������������� �����������.
		{
			cout << "\n\n����:\n";
			cout << "-0-����� �� ���������\n";
			cout << "-1-���������� �����\n";
			cout << "-2-�������� �����\n";
			cout << "-3-����� �����\n";
			cout << "-4-����� ������ � ����\n";
			cout << "�������� �������� �� ������ ����: ";
			cin >> choice;
			if (choice <= 4 && choice >= 0) break;
			cout << "�������� ����� �� ��������������� ���������:\n";
		}

		switch (choice)
		{
		case 0: return 0;

		case 1:
			cout << "\n������� ������������� ���� ������� ����� ��������: ";
			cin >> key;
			if (rootNode->addKey(key)) cout << "\n���� ������� ��������\n";
			else cout << "\n����� ���� ��� ����������\n";
			break;

		case 2:
			cout << "\n������� ������������� ���� ������� ����� ������ �� RB-������: ";
			cin >> key;
			rootNode->remove(key);
			cout << "\n���� ������ �� RB-������\n";
			break;

		case 3:
			cout << "\n������� ������������� ���� ��� ������ � RB-������: ";
			cin >> key;
			if (rootNode->search(key)) cout << "\n����� ���� ���������� � RB-������\n";
			else cout << "\n������ ����� �� ���������� � R�-������\n";
			break;

		case 4:
			ofstream fout;
			fout.open("RB-tree.gv");
			rootNode->output(fout);
			cout << "\n������ �������� � ���� RB-tree.gv � ������� DOT.\n";
			break;
		}
	}
}

