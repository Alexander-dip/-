#pragma once
#include <glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

int kolver;//Количество вершин
int** pomoshnikinter;//Вспомогательный массив для оценок пути
int* itog;//Массив для пути
int*** matrsmezh;//Матрица смежности
const int predel = 20;//Максимальное кол-во вершин
int KVersh;//Изменяемая переменная для количества вершин

class Graph//Класс графа
{
	bool* VV = new bool[VL.size()];//Переменная типа bool для обозначения посещённых вершин
	vector<int> VL;//Переменная для работы с библиотекой <vector> и её функциями

public:
	int adjMatrix[predel][predel] = { 0 };//Матрица смежности
	Graph();//Строитель
	~Graph();//Разрушитель
	void InsertEdge(const int& V1, const int& V2, int Massa);//Связь вершин ребром
	void DeleteVertex();//Удаление вершин
	int GetVertPos(const int& POS);//Позиция вершины
	void DrawGraph();//Отрисовка  графа
	void InsertVertex(const int& POS);//Добавление вершин	
	void Print();//Отрисовка  матрицы смежности в консоли
	bool Empty();//Проверка на пустой граф
	bool Full();//Проверка на полный граф
};

int RAD;

struct vertCoord//Структура для координат
{
	int x, y;
};
vertCoord vertC[20];

void Graph::DeleteVertex()
{
	this->VL.pop_back();//Удаление вершины с помощью встреонной функции библиотеки <vector>
}

void Graph::InsertVertex(const int& POS)
{
	if (!this->Full())//Если не полный
	{
		this->VL.push_back(POS);//Вставка вершины с помощью встроенной функции библиотеки <vector>
	}
	else
	{
		cout << "Граф полон. " << endl;
		return;
	}
}

bool Graph::Empty()
{
	if (this->VL.size() != 0)//Если не пуст - false, если нет - true
		return false;
	else
		return true;
}

bool Graph::Full()
{
	return (VL.size() == predel);//Присвоение максимального количества вершин
}


int Graph::GetVertPos(const int& POS)
{
	for (int i = 0; i < this->VL.size(); ++i) //Цикл от количества вершин
	{
		if (this->VL[i] == POS)//Если есть совпадение
			return i;
	}
	return -1;
}

Graph::Graph()//Строитель
{
	for (int i = 0; i < predel; ++i)
	{
		for (int j = 0; j < predel; ++j)
		{
			this->adjMatrix[i][j] = 0;
		}
	}
}

Graph::~Graph() {}//Разрушитель

Graph makeGraph()
{
	Graph graph;
	int KReber, NachVer, KonVer, WeiReb;
	cout << "Кол-во вершин: "; cin >> KVersh; cout << endl;//Ввод количества вершин
	cout << "Кол-во рёбер: "; cin >> KReber; cout << endl;//Ввод количества рёбер
	for (int i = 1; i <= KVersh; ++i)//Цикл от количества вершин 
	{
		int* vertPtr = &i;//Присвоение указателю адреса i
		graph.InsertVertex(*vertPtr);//Функция вставки вершины
	}

	for (int i = 0; i < KReber; ++i) //Цикл от количества рёбер
	{
		cout << "Начальная верщина: "; cin >> NachVer; cout << endl;//Ввод начальной вершины
		int* sourceVertPtr = &NachVer;//Присвоение указателю адреса начальной вершины
		cout << "Конечная вершина: "; cin >> KonVer; cout << endl;//Ввод конечной вершины
		int* targetVertPtr = &KonVer;//Присвоение указателю адреса конечной вершины

		cout << "Вес ребра: "; cin >> WeiReb; cout << endl;//Ввод веса ребра
		graph.InsertEdge(*sourceVertPtr, *targetVertPtr, WeiReb);//Функция вставки ребра
	}
	cout << endl;
	return graph;
}

void Graph::InsertEdge(const int& V1, const int& V2, int Massa)
{
	if (this->GetVertPos(V1) != (-1) && this->GetVertPos(V2) != (-1))//Если обе вершины уже есть
	{
		int vertPos1 = GetVertPos(V1);//Присвоение позиций вершин
		int vertPos2 = GetVertPos(V2);
		if (this->adjMatrix[vertPos1][vertPos2] != 0//Если дорога есть
			&& this->adjMatrix[vertPos2][vertPos1] != 0)
		{
			cout << "Дорога уже есть" << endl;//Дорога уже есть
			return;
		}
		else
		{
			this->adjMatrix[vertPos1][vertPos2] = Massa;//Ввод в матрицу веса ребра
			this->adjMatrix[vertPos2][vertPos1] = Massa;
		}
	}
	else
	{
		cout << "Невозможно вставить вершину" << endl;//Невозможно вставить вершину
		return;
	}
}

void Graph::Print()
{
	if (!this->Empty()) //Проверка на пустоту переменной graph
	{
		cout << "Матрица смежности: " << endl;//Матрица смежности
		for (int i = 0, vertListSize = this->VL.size(); i < vertListSize; ++i)
		{
			cout << this->VL[i] << " ";//Вывод номера дороги
			for (int j = 0; j < vertListSize; ++j) //Цикл вывода матрицы
			{
				cout << " " << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
}

Graph graph;//Активация переменной класса Graph

void Vig(int*** matrsmezh, int kolver, int** pomoshnikinter, int* path)//Использование метода ветвей и границ
{
	for (int l = 0; l < kolver; l++)//Циклы от количествава вершин
	{
		for (int i = 0; i < kolver; i++)
		{
			int min = 1000000;//Оценивание путей по длине и ширине
			for (int j = 0; j < kolver; j++)
				if (matrsmezh[i][j] && min > *matrsmezh[i][j])//Сравнение минимума и длины пути
					min = *matrsmezh[i][j];
			for (int j = 0; j < kolver; j++)
				if (matrsmezh[i][j])
					*matrsmezh[i][j] -= min;//Декремент длины пути до 0
		}
		for (int j = 0; j < kolver; j++)//Та же процедура, только для глубины
		{
			int min = 1000000;
			for (int i = 0; i < kolver; i++)
				if (matrsmezh[i][j] && min > *matrsmezh[i][j])
					min = *matrsmezh[i][j];
			for (int i = 0; i < kolver; i++)
				if (matrsmezh[i][j])
					*matrsmezh[i][j] -= min;
		}
		for (int i = 0; i < kolver; i++)//Цикл обнуления вспомогательного массива
			for (int j = 0; j < kolver; j++)
				pomoshnikinter[i][j] = 0;

		for (int i = 0; i < kolver; i++)//Цикл для заполнения массива “весом” путей
			for (int j = 0; j < kolver; j++)
			{
				if (matrsmezh[i][j] && !*matrsmezh[i][j])//Если не указатель на массив
				{
					int Hmin = 1000000;
					int Vmin = 1000000;
					for (int l = 0; l < kolver; l++)//Цикл от количества вершин
						if (l != i && matrsmezh[l][j] && hmin > *matrsmezh[l][j])//Если длина пути меньше минимальной по высоте и i != l
							hmin = *matrsmezh[l][j];//Присвоение указателя на массив со значением пути

					for (int l = 0; l < kolver; l++)//Цикл от количества вершин
						if (l != j && matrsmezh[i][l] && vmin > *matrsmezh[i][l])//Если длина пути меньше минимальной по ширине и i не равно l
							vmin = *matrsmezh[i][l];//Присвоение указателя на массив со значением пути

					pomoshnikinter[i][j] = hmin + vmin;//Заполнение вспомогательного массива "ценами" путей
				}
			}
		int mcost = 0, mi = 0, mj = 0;
		for (int i = 0; i < kolver; i++)
			for (int j = 0; j < kolver; j++)
				if (matrsmezh[i][j] && mcost < pomoshnikinter[i][j])//Если минимальный путь меньше значения в массиве
				{
					mcost = pomoshnikinter[i][j];//Присвоение цены пути
					mi = i;//Присвоение индексов для минимального пути
					mj = j;
				}
		path[mi] = mj;//Составление массива минимального пути
		//Редукция строк и столбцов
		for (int i = 0; i < kolver; i++)
			matrsmezh[i][mj] = nullptr;//Присвоение нулевого указателя по ширине
		for (int i = 0; i < kolver; i++)
			matrsmezh[mi][i] = nullptr;//Присвоение нулевого указателя по высоте
		matrsmezh[mj][mi] = nullptr;//Присвоение нулевого указателя по ширине и высоте
	}
}

void Prepare(int***& matrsmezh, int& kolver, int**& pomoshnikinter, int*& itog)//Функция подготовки
{
	kolver = KVersh;//Присвоение количества вершин
	pomoshnikinter = new int* [kolver];//Динамический вспомогательный массив
	itog = new int[kolver];//Динамический массив для пути
	matrsmezh = new int** [kolver];//Динамическая матрица смежности
	for (int i = 0; i <= kolver; i++)//Цикл для инициализации вспомогательного динамического массива
	{
		pomoshnikinter[i] = new int[kolver];
	}
	for (int i = 0; i < kolver; i++)//Цикл для инициализации динамический матрицы
	{
		matrsmezh[i] = new int* [kolver];
		for (int j = 0; j < kolver; j++)
		{
			if (graph.adjMatrix[i][j] == 0)//Проверка массива на отсутствие дорог и присвоение нулевого указателя
			{
				matrsmezh[i][j] = nullptr;
				continue;
			}
			matrsmezh[i][j] = new int(graph.adjMatrix[i][j]);//Цикл для инициализации динамический матрицы
		}
	}
}

void MinPath(int*** matrsmezh, int kolver, int** pomoshnikinter, int* itog)//Функция нахождения минимального пути
{
	Prepare(matrsmezh, kolver, pomoshnikinter, itog);//Функция подготовки
	int s = 0;//Переменная для длины минимального пути
	Vig(matrsmezh, kolver, pomoshnikinter, itog);//Функция для метода ветвей и границ
	for (int i = 0, j = 0; i < kolver; i++)
	{
		j = itog[i];//Присвоение j номера следующего номера вершины пути
		s += graph.adjMatrix[i][j];//Добавление длины пути
	}
	cout << "Минимальный путь: ";//Минимальный путь
	int temp = 0;
	for (int l = 0; l < kolver;)
	{
		for (int i = 0, j = 0; i < kolver; i++)
		{
			if (temp == 0 || i + 1 == temp)
			{
				if (temp == 0) cout << i + 1;//Вывод номера начальной вершины
				j = itog[i];
				temp = j + 1;
				if (temp > 0)	cout << " -> " << temp;//Вывод пути
				l++;//Инкремент подсчёта количества вершин
			}
		}
	}
	cout << " = " << s;//Вывод длины минимального пути
	cout << endl;
}

void setCoord(int i, int kolver)//Функция для координат вершин и радиуса кругов
{
	int RAD_;
	int x0 = 1200 / 2;//Расположение центра
	int y0 = 800 / 2;
	RAD = 5 * (800 / 13) / kolver;//Вычисление радиуса
	RAD_ = 800 / 2 - RAD - 10;
	float theta = 2.0f * 3.1415926f * float(i) / float(kolver);//Вычисление угла для положения вершины в зависимости от количества вершин
	float Y1 = RAD_ * cos(theta) + y0;//Координаты вершин
	float X1 = RAD_ * sin(theta) + x0;
	vertC[i].x = X1;//Присвоение координат
	vertC[i].y = Y1;
}

void CircEdgeText(int nom, int X1, int Y1)//Отрисовка текста в вершинах и на рёбрах
{
	string s = to_string(nom);
	glRasterPos2i(X1 - 5, Y1 - 5);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
}

void drawCircle(int x, int y, int RAD)//Отрисовка круга с заданными координатами и радиусом
{
	glColor3f(0, 1, 0.5);
	float X1, Y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)//Цикл for для отрисовки 360 точек
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		Y1 = RAD * cos(theta) + y;
		X1 = RAD * sin(theta) + x;;
		glVertex2f(X1, Y1);
	}
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)//Цикл for для отрисовки 360 точек
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = RAD * cos(theta) + y;
		x2 = RAD * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawVertex(int kolver)//Отрисовка вершин с текстом
{
	for (int i = 0; i < kolver; i++)//Цикл от количества вершин
	{
		drawCircle(vertC[i].x, vertC[i].y, RAD);//Отрисовка круга с заданными координатами и радиусом
		CircEdgeText(i + 1, vertC[i].x, vertC[i].y);//Отрисовка текста в вершинах и на рёбрах
	}
}

void drawLine(int text, int x0, int y0, int X1, int Y1)//Отрисовка линий, соединяющих две вершины
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);//Координаты начальной вершины
	glVertex2i(X1, Y1);//Координаты конечной вершины
	glEnd();
	CircEdgeText(text, (x0 + X1) / 2 + 10, (y0 + Y1) / 2 + 10);//Отрисовка  текста для ребра
}

void Graph::DrawGraph()//Отрисовка графа
{
	int kolver = VL.size();//Кол-во вершин
	for (int i = 0; i < kolver; i++)
	{
		setCoord(i, kolver);//Задание координат вершинам
	}
	for (int i = 0; i < kolver; i++)
	{
		for (int j = i + 1; j < kolver; j++)
		{
			int a = adjMatrix[i][j];
			if (a != 0)//Проверка на наличие дороги
			{
				drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);//Отрисовка линий, соединяющих две вершины
			}
		}
	}
	drawVertex(kolver);//Отрисовка вершины
}

void MenuText(string text, int X1, int Y1)//Отрисовка текста в меню
{
	string s = text;
	glRasterPos2i(X1 + 5, Y1 - 20);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
}

void drawMenu()//Отрисовка  меню с кнопками
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(150, 0);
	glVertex2i(150, 150);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, 30);
	glVertex2i(150, 30);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, 60);
	glVertex2i(150, 60);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, 90);
	glVertex2i(150, 90);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, 120);
	glVertex2i(150, 120);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, 150);
	glVertex2i(150, 150);
	glEnd();
	glColor3d(0, 0, 0);
	MenuText("Add vertex", 0, 150);
	glColor3d(0, 0, 0);
	MenuText("Delete vertex", 0, 120);
	glColor3d(0, 0, 0);
	MenuText("Print matrix", 0, 90);
	glColor3d(0, 0, 0);
	MenuText("New matrix", 0, 60);
	glColor3d(0, 0, 0);
	MenuText("Answer", 0, 30);
}

void mouseClick(int btn, int stat, int x, int y)//Функция для действий прик клике мыши
{
	if (stat == GLUT_DOWN) //Проверка на нажатие
	{
		if (x > 0 && x < 150 && y > 650 && y < 680)//Проверка на координаты положения мыши
		{
			int NachVer;
			int KonVer;
			int WeiReb;


			cout << "Введите начальную вершину: "; cin >> NachVer; cout << endl;//Ввод начальной вершины
			int* sourceVertPtr = &NachVer;//Присвоение указателю адреса начальной вершины
			cout << "Введите конечную вершину: "; cin >> KonVer; cout << endl;//Ввод конечной вершины
			int* targetVertPtr = &KonVer;//Присвоение указателю адреса конечной вершины

			if (NachVer > KVersh || KonVer > KVersh) //Вставка новой вершины если номер конечной или начальной больше количества вершин
			{
				KVersh++;//Инкремент переменной для количества вершин
				int* vertPtr = &KVersh;//Присвоение указателю адреса новой вершины
				graph.InsertVertex(*vertPtr);//Функция вставки вершины
			}

			cout << "Введите вес ребра: "; cin >> WeiReb; cout << endl;//Ввод веса ребра
			graph.InsertEdge(*sourceVertPtr, *targetVertPtr, WeiReb); //Вызов функции для вставки ребра
		}
		if (x > 0 && x < 150 && y > 680 && y < 710)//Проверка на координаты положения мыши
		{
			int NachVer;

			cout << "Введите вершину: "; cin >> NachVer; cout << endl;//Ввод номера вершины для удаления
			int* sourceVertPtr = &NachVer;//Присвоение указателю адреса удаляемой вершины
			if (NachVer == KVersh)//Если удаляемая вершина = кол-ву вершин
			{
				KVersh--;//Декремент количества вершин
				graph.DeleteVertex();//Функция удаления вершины
			}
			else cout << "Невозможно удалить вершину \kolver";
		}
		if (x > 0 && x < 150 && y >  710 && y < 740)//Проверка на координаты положения мыши
		{
			graph.Print();//Отрисовка матрицы смежности в консоли
		}
		if (x > 0 && x < 150 && y >  740 && y < 770)//Проверка на координаты положения мыши
		{
			graph = makeGraph();//Вызов функции для создания нового графа
		}
		if (x > 0 && x < 150 && y > 770 && y < 800)//Проверка на координаты положения мыши
		{
			MinPath(matrsmezh, kolver, pomoshnikinter, itog);//Функция вычисления минимальной длины пути из 1 в 1 с посещением всех вершин
		}
	}
	glutPostRedisplay();
}

void display()//Отрисовка главного окна программы с параметрами
{
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1200, 0, 800);
	glViewport(0, 0, 1200, 800);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	graph.DrawGraph();
	drawMenu();
	glutSwapBuffers();
}
