// �������� ������ Node.

#pragma once

#include "stdafx.h"

class Node // ����� ����������� ���� � R�-������.
{
	bool color = 0; // ���� ����(True - �������, False - ������).
	Node* parent = NULL; // ��������� �� ������������ ����; � ��������� ���� ��������������� NULL.
	Node* lChild = NULL; // ��������� �� ����� �������� ����.
	Node* rChild = NULL; // ��������� �� ������ �������� ����.
	int *value = NULL; // ��������� �� �������� ����; � ����� ��������������� NULL.

	void restoreR(); // �������������� ������� ������ ����� ����������.
	void restoreB(); // �������������� ������� ������ ����� ��������.
	void rotateLeft(); //������� ��������� �����.
	void rotateRight(); // ������� ��������� ������.
	Node* getBrother(); // ���������� ��������� �� ����� ����.

public:
	~Node(); // ���������� ����.
	bool addKey(int key); // ���������� ����� � ������������ ���������� true - ����� / false - ���� ��� ����������.
	void remove(int key); // �������� ����� ���� �� ����������.
	bool search(int key); // ����� �����.
	void output(std::ofstream &fout); // ����� ������ � ���� � ����������� .gv.
};


