#include "graph.h"
#include <glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>


int main(int argc, char* argv[])
{
	setlocal(LC_ALL, "rus");
	glutInit(&argc, argv);
	graph = makeGraph();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Graph");
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMainLoop();
	return 0;
}