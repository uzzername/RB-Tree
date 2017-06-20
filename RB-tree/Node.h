// Описание класса Node.

#pragma once

#include "stdafx.h"

class Node // Класс реализующий узлы в RВ-дереве.
{
	bool color = 0; // Цвет узла(True - красный, False - черный).
	Node* parent = NULL; // Указатель на родительский узел; у корневого узла подразумевается NULL.
	Node* lChild = NULL; // Указатель на левый дочерний узел.
	Node* rChild = NULL; // Указатель на правый дочерний узел.
	int *value = NULL; // Указатель на значение узла; У листа подразумевается NULL.

	void restoreR(); // Восстановление свойств дерева после добавления.
	void restoreB(); // Восстановление свойств дерева после удаления.
	void rotateLeft(); //Поворот поддерева влево.
	void rotateRight(); // Поворот поддерева вправо.
	Node* getBrother(); // Возвращает указатель на брата узла.

public:
	~Node(); // Деструктор узла.
	bool addKey(int key); // Добавление ключа с возвращением результата true - успех / false - ключ уже существует.
	void remove(int key); // Удаление ключа если он существует.
	bool search(int key); // Поиск ключа.
	void output(std::ofstream &fout); // Вывод дерева в файл с расширением .gv.
};


