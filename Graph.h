#pragma once
#include <glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

int kolver;//���������� ������
int** pomoshnikinter;//��������������� ������ ��� ������ ����
int* itog;//������ ��� ����
int*** matrsmezh;//������� ���������
const int predel = 20;//������������ ���-�� ������
int KVersh;//���������� ���������� ��� ���������� ������

class Graph//����� �����
{
	bool* VV = new bool[VL.size()];//���������� ���� bool ��� ����������� ���������� ������
	vector<int> VL;//���������� ��� ������ � ����������� <vector> � � ���������

public:
	int adjMatrix[predel][predel] = { 0 };//������� ���������
	Graph();//���������
	~Graph();//�����������
	void InsertEdge(const int& V1, const int& V2, int Massa);//����� ������ ������
	void DeleteVertex();//�������� ������
	int GetVertPos(const int& POS);//������� �������
	void DrawGraph();//���������  �����
	void InsertVertex(const int& POS);//���������� ������	
	void Print();//���������  ������� ��������� � �������
	bool Empty();//�������� �� ������ ����
	bool Full();//�������� �� ������ ����
};

int RAD;

struct vertCoord//��������� ��� ���������
{
	int x, y;
};
vertCoord vertC[20];

void Graph::DeleteVertex()
{
	this->VL.pop_back();//�������� ������� � ������� ���������� ������� ���������� <vector>
}

void Graph::InsertVertex(const int& POS)
{
	if (!this->Full())//���� �� ������
	{
		this->VL.push_back(POS);//������� ������� � ������� ���������� ������� ���������� <vector>
	}
	else
	{
		cout << "���� �����. " << endl;
		return;
	}
}

bool Graph::Empty()
{
	if (this->VL.size() != 0)//���� �� ���� - false, ���� ��� - true
		return false;
	else
		return true;
}

bool Graph::Full()
{
	return (VL.size() == predel);//���������� ������������� ���������� ������
}


int Graph::GetVertPos(const int& POS)
{
	for (int i = 0; i < this->VL.size(); ++i) //���� �� ���������� ������
	{
		if (this->VL[i] == POS)//���� ���� ����������
			return i;
	}
	return -1;
}

Graph::Graph()//���������
{
	for (int i = 0; i < predel; ++i)
	{
		for (int j = 0; j < predel; ++j)
		{
			this->adjMatrix[i][j] = 0;
		}
	}
}

Graph::~Graph() {}//�����������

Graph makeGraph()
{
	Graph graph;
	int KReber, NachVer, KonVer, WeiReb;
	cout << "���-�� ������: "; cin >> KVersh; cout << endl;//���� ���������� ������
	cout << "���-�� ����: "; cin >> KReber; cout << endl;//���� ���������� ����
	for (int i = 1; i <= KVersh; ++i)//���� �� ���������� ������ 
	{
		int* vertPtr = &i;//���������� ��������� ������ i
		graph.InsertVertex(*vertPtr);//������� ������� �������
	}

	for (int i = 0; i < KReber; ++i) //���� �� ���������� ����
	{
		cout << "��������� �������: "; cin >> NachVer; cout << endl;//���� ��������� �������
		int* sourceVertPtr = &NachVer;//���������� ��������� ������ ��������� �������
		cout << "�������� �������: "; cin >> KonVer; cout << endl;//���� �������� �������
		int* targetVertPtr = &KonVer;//���������� ��������� ������ �������� �������

		cout << "��� �����: "; cin >> WeiReb; cout << endl;//���� ���� �����
		graph.InsertEdge(*sourceVertPtr, *targetVertPtr, WeiReb);//������� ������� �����
	}
	cout << endl;
	return graph;
}

void Graph::InsertEdge(const int& V1, const int& V2, int Massa)
{
	if (this->GetVertPos(V1) != (-1) && this->GetVertPos(V2) != (-1))//���� ��� ������� ��� ����
	{
		int vertPos1 = GetVertPos(V1);//���������� ������� ������
		int vertPos2 = GetVertPos(V2);
		if (this->adjMatrix[vertPos1][vertPos2] != 0//���� ������ ����
			&& this->adjMatrix[vertPos2][vertPos1] != 0)
		{
			cout << "������ ��� ����" << endl;//������ ��� ����
			return;
		}
		else
		{
			this->adjMatrix[vertPos1][vertPos2] = Massa;//���� � ������� ���� �����
			this->adjMatrix[vertPos2][vertPos1] = Massa;
		}
	}
	else
	{
		cout << "���������� �������� �������" << endl;//���������� �������� �������
		return;
	}
}

void Graph::Print()
{
	if (!this->Empty()) //�������� �� ������� ���������� graph
	{
		cout << "������� ���������: " << endl;//������� ���������
		for (int i = 0, vertListSize = this->VL.size(); i < vertListSize; ++i)
		{
			cout << this->VL[i] << " ";//����� ������ ������
			for (int j = 0; j < vertListSize; ++j) //���� ������ �������
			{
				cout << " " << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
}

Graph graph;//��������� ���������� ������ Graph

void Vig(int*** matrsmezh, int kolver, int** pomoshnikinter, int* path)//������������� ������ ������ � ������
{
	for (int l = 0; l < kolver; l++)//����� �� ������������ ������
	{
		for (int i = 0; i < kolver; i++)
		{
			int min = 1000000;//���������� ����� �� ����� � ������
			for (int j = 0; j < kolver; j++)
				if (matrsmezh[i][j] && min > *matrsmezh[i][j])//��������� �������� � ����� ����
					min = *matrsmezh[i][j];
			for (int j = 0; j < kolver; j++)
				if (matrsmezh[i][j])
					*matrsmezh[i][j] -= min;//��������� ����� ���� �� 0
		}
		for (int j = 0; j < kolver; j++)//�� �� ���������, ������ ��� �������
		{
			int min = 1000000;
			for (int i = 0; i < kolver; i++)
				if (matrsmezh[i][j] && min > *matrsmezh[i][j])
					min = *matrsmezh[i][j];
			for (int i = 0; i < kolver; i++)
				if (matrsmezh[i][j])
					*matrsmezh[i][j] -= min;
		}
		for (int i = 0; i < kolver; i++)//���� ��������� ���������������� �������
			for (int j = 0; j < kolver; j++)
				pomoshnikinter[i][j] = 0;

		for (int i = 0; i < kolver; i++)//���� ��� ���������� ������� ������ �����
			for (int j = 0; j < kolver; j++)
			{
				if (matrsmezh[i][j] && !*matrsmezh[i][j])//���� �� ��������� �� ������
				{
					int Hmin = 1000000;
					int Vmin = 1000000;
					for (int l = 0; l < kolver; l++)//���� �� ���������� ������
						if (l != i && matrsmezh[l][j] && hmin > *matrsmezh[l][j])//���� ����� ���� ������ ����������� �� ������ � i != l
							hmin = *matrsmezh[l][j];//���������� ��������� �� ������ �� ��������� ����

					for (int l = 0; l < kolver; l++)//���� �� ���������� ������
						if (l != j && matrsmezh[i][l] && vmin > *matrsmezh[i][l])//���� ����� ���� ������ ����������� �� ������ � i �� ����� l
							vmin = *matrsmezh[i][l];//���������� ��������� �� ������ �� ��������� ����

					pomoshnikinter[i][j] = hmin + vmin;//���������� ���������������� ������� "������" �����
				}
			}
		int mcost = 0, mi = 0, mj = 0;
		for (int i = 0; i < kolver; i++)
			for (int j = 0; j < kolver; j++)
				if (matrsmezh[i][j] && mcost < pomoshnikinter[i][j])//���� ����������� ���� ������ �������� � �������
				{
					mcost = pomoshnikinter[i][j];//���������� ���� ����
					mi = i;//���������� �������� ��� ������������ ����
					mj = j;
				}
		path[mi] = mj;//����������� ������� ������������ ����
		//�������� ����� � ��������
		for (int i = 0; i < kolver; i++)
			matrsmezh[i][mj] = nullptr;//���������� �������� ��������� �� ������
		for (int i = 0; i < kolver; i++)
			matrsmezh[mi][i] = nullptr;//���������� �������� ��������� �� ������
		matrsmezh[mj][mi] = nullptr;//���������� �������� ��������� �� ������ � ������
	}
}

void Prepare(int***& matrsmezh, int& kolver, int**& pomoshnikinter, int*& itog)//������� ����������
{
	kolver = KVersh;//���������� ���������� ������
	pomoshnikinter = new int* [kolver];//������������ ��������������� ������
	itog = new int[kolver];//������������ ������ ��� ����
	matrsmezh = new int** [kolver];//������������ ������� ���������
	for (int i = 0; i <= kolver; i++)//���� ��� ������������� ���������������� ������������� �������
	{
		pomoshnikinter[i] = new int[kolver];
	}
	for (int i = 0; i < kolver; i++)//���� ��� ������������� ������������ �������
	{
		matrsmezh[i] = new int* [kolver];
		for (int j = 0; j < kolver; j++)
		{
			if (graph.adjMatrix[i][j] == 0)//�������� ������� �� ���������� ����� � ���������� �������� ���������
			{
				matrsmezh[i][j] = nullptr;
				continue;
			}
			matrsmezh[i][j] = new int(graph.adjMatrix[i][j]);//���� ��� ������������� ������������ �������
		}
	}
}

void MinPath(int*** matrsmezh, int kolver, int** pomoshnikinter, int* itog)//������� ���������� ������������ ����
{
	Prepare(matrsmezh, kolver, pomoshnikinter, itog);//������� ����������
	int s = 0;//���������� ��� ����� ������������ ����
	Vig(matrsmezh, kolver, pomoshnikinter, itog);//������� ��� ������ ������ � ������
	for (int i = 0, j = 0; i < kolver; i++)
	{
		j = itog[i];//���������� j ������ ���������� ������ ������� ����
		s += graph.adjMatrix[i][j];//���������� ����� ����
	}
	cout << "����������� ����: ";//����������� ����
	int temp = 0;
	for (int l = 0; l < kolver;)
	{
		for (int i = 0, j = 0; i < kolver; i++)
		{
			if (temp == 0 || i + 1 == temp)
			{
				if (temp == 0) cout << i + 1;//����� ������ ��������� �������
				j = itog[i];
				temp = j + 1;
				if (temp > 0)	cout << " -> " << temp;//����� ����
				l++;//��������� �������� ���������� ������
			}
		}
	}
	cout << " = " << s;//����� ����� ������������ ����
	cout << endl;
}

void setCoord(int i, int kolver)//������� ��� ��������� ������ � ������� ������
{
	int RAD_;
	int x0 = 1200 / 2;//������������ ������
	int y0 = 800 / 2;
	RAD = 5 * (800 / 13) / kolver;//���������� �������
	RAD_ = 800 / 2 - RAD - 10;
	float theta = 2.0f * 3.1415926f * float(i) / float(kolver);//���������� ���� ��� ��������� ������� � ����������� �� ���������� ������
	float Y1 = RAD_ * cos(theta) + y0;//���������� ������
	float X1 = RAD_ * sin(theta) + x0;
	vertC[i].x = X1;//���������� ���������
	vertC[i].y = Y1;
}

void CircEdgeText(int nom, int X1, int Y1)//��������� ������ � �������� � �� �����
{
	string s = to_string(nom);
	glRasterPos2i(X1 - 5, Y1 - 5);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
}

void drawCircle(int x, int y, int RAD)//��������� ����� � ��������� ������������ � ��������
{
	glColor3f(0, 1, 0.5);
	float X1, Y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)//���� for ��� ��������� 360 �����
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
	for (int i = 0; i < 360; i++)//���� for ��� ��������� 360 �����
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = RAD * cos(theta) + y;
		x2 = RAD * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawVertex(int kolver)//��������� ������ � �������
{
	for (int i = 0; i < kolver; i++)//���� �� ���������� ������
	{
		drawCircle(vertC[i].x, vertC[i].y, RAD);//��������� ����� � ��������� ������������ � ��������
		CircEdgeText(i + 1, vertC[i].x, vertC[i].y);//��������� ������ � �������� � �� �����
	}
}

void drawLine(int text, int x0, int y0, int X1, int Y1)//��������� �����, ����������� ��� �������
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);//���������� ��������� �������
	glVertex2i(X1, Y1);//���������� �������� �������
	glEnd();
	CircEdgeText(text, (x0 + X1) / 2 + 10, (y0 + Y1) / 2 + 10);//���������  ������ ��� �����
}

void Graph::DrawGraph()//��������� �����
{
	int kolver = VL.size();//���-�� ������
	for (int i = 0; i < kolver; i++)
	{
		setCoord(i, kolver);//������� ��������� ��������
	}
	for (int i = 0; i < kolver; i++)
	{
		for (int j = i + 1; j < kolver; j++)
		{
			int a = adjMatrix[i][j];
			if (a != 0)//�������� �� ������� ������
			{
				drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);//��������� �����, ����������� ��� �������
			}
		}
	}
	drawVertex(kolver);//��������� �������
}

void MenuText(string text, int X1, int Y1)//��������� ������ � ����
{
	string s = text;
	glRasterPos2i(X1 + 5, Y1 - 20);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
}

void drawMenu()//���������  ���� � ��������
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

void mouseClick(int btn, int stat, int x, int y)//������� ��� �������� ���� ����� ����
{
	if (stat == GLUT_DOWN) //�������� �� �������
	{
		if (x > 0 && x < 150 && y > 650 && y < 680)//�������� �� ���������� ��������� ����
		{
			int NachVer;
			int KonVer;
			int WeiReb;


			cout << "������� ��������� �������: "; cin >> NachVer; cout << endl;//���� ��������� �������
			int* sourceVertPtr = &NachVer;//���������� ��������� ������ ��������� �������
			cout << "������� �������� �������: "; cin >> KonVer; cout << endl;//���� �������� �������
			int* targetVertPtr = &KonVer;//���������� ��������� ������ �������� �������

			if (NachVer > KVersh || KonVer > KVersh) //������� ����� ������� ���� ����� �������� ��� ��������� ������ ���������� ������
			{
				KVersh++;//��������� ���������� ��� ���������� ������
				int* vertPtr = &KVersh;//���������� ��������� ������ ����� �������
				graph.InsertVertex(*vertPtr);//������� ������� �������
			}

			cout << "������� ��� �����: "; cin >> WeiReb; cout << endl;//���� ���� �����
			graph.InsertEdge(*sourceVertPtr, *targetVertPtr, WeiReb); //����� ������� ��� ������� �����
		}
		if (x > 0 && x < 150 && y > 680 && y < 710)//�������� �� ���������� ��������� ����
		{
			int NachVer;

			cout << "������� �������: "; cin >> NachVer; cout << endl;//���� ������ ������� ��� ��������
			int* sourceVertPtr = &NachVer;//���������� ��������� ������ ��������� �������
			if (NachVer == KVersh)//���� ��������� ������� = ���-�� ������
			{
				KVersh--;//��������� ���������� ������
				graph.DeleteVertex();//������� �������� �������
			}
			else cout << "���������� ������� ������� \kolver";
		}
		if (x > 0 && x < 150 && y >  710 && y < 740)//�������� �� ���������� ��������� ����
		{
			graph.Print();//��������� ������� ��������� � �������
		}
		if (x > 0 && x < 150 && y >  740 && y < 770)//�������� �� ���������� ��������� ����
		{
			graph = makeGraph();//����� ������� ��� �������� ������ �����
		}
		if (x > 0 && x < 150 && y > 770 && y < 800)//�������� �� ���������� ��������� ����
		{
			MinPath(matrsmezh, kolver, pomoshnikinter, itog);//������� ���������� ����������� ����� ���� �� 1 � 1 � ���������� ���� ������
		}
	}
	glutPostRedisplay();
}

void display()//��������� �������� ���� ��������� � �����������
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
