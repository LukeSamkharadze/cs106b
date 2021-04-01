/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>

#include "simpio.h"
#include "gwindow.h"
#include "gobjects.h"
#include "queue.h"

#include <math.h>

struct SierpinskiTriangle
{
	double x;
	double y;
	double length;
	int n;
	
	SierpinskiTriangle() { }

	SierpinskiTriangle(double x_, double y_, double length_, int n_)
	{
		x = x_;
		y = y_;
		length = length_;
		n = n_;
	}
};

void PrintStartingInfo()
{
	cout << "SIERPINSKI PRO" << endl;
	cout << "Enter model number and side length of sierpinski triangle" << endl;
	cout << "We will draw it using old classic iteration way" << endl << endl;

	getLine("Press ENTER to continue\n");
}

void DrawTriangle(GWindow& window, double x, double y, double length)
{
	GPoint endpoint = window.drawPolarLine(x - length/2., y + sqrt(3.) * length/4., length , 0);
	endpoint = window.drawPolarLine(endpoint.getX(), endpoint.getY(), length , 120);
	endpoint = window.drawPolarLine(endpoint.getX(), endpoint.getY(), length , -120);
}

void DrawReversedTriangle(GWindow& window, double x, double y, double length)
{
	GPoint endpoint = window.drawPolarLine(x - length/2., y - sqrt(3.)*length/4., length , 0);
	endpoint = window.drawPolarLine(endpoint.getX(), endpoint.getY(), length , -120);
	endpoint = window.drawPolarLine(endpoint.getX(), endpoint.getY(), length , -240);
}

void DrawSierpinskiTriangle(GWindow& window, double x, double y, int n, double length)
{
	DrawTriangle(window, x, y, length);

	if(n == 0) return;

	Queue<SierpinskiTriangle> sierpinskiTriangles;
	sierpinskiTriangles.enqueue(SierpinskiTriangle(x, y + sqrt(3.)*length/8., length/2., n-1));

	while(sierpinskiTriangles.isEmpty() == false)
	{
		SierpinskiTriangle currentTriangle = sierpinskiTriangles.dequeue();

		DrawReversedTriangle(window, currentTriangle.x, currentTriangle.y, currentTriangle.length);

		if(currentTriangle.n == 0)
			continue;

		sierpinskiTriangles.enqueue(SierpinskiTriangle(currentTriangle.x, currentTriangle.y - sqrt(3.)*currentTriangle.length/4. - sqrt(3.)*currentTriangle.length/8., currentTriangle.length/2., currentTriangle.n-1));
		sierpinskiTriangles.enqueue(SierpinskiTriangle(currentTriangle.x + currentTriangle.length/2., currentTriangle.y + (currentTriangle.length/2.)/sqrt(3.) - (currentTriangle.length/8.)/sqrt(3.), currentTriangle.length/2., currentTriangle.n-1));
		sierpinskiTriangles.enqueue(SierpinskiTriangle(currentTriangle.x - currentTriangle.length/2., currentTriangle.y + (currentTriangle.length/2.)/sqrt(3.) - (currentTriangle.length/8.)/sqrt(3.), currentTriangle.length/2., currentTriangle.n-1));
	}
}

int main() 
{
	PrintStartingInfo();

	double windowWidth = 1000;
	double windowHeight = 1080;

	int sierpinskiLevel = getReal("Enter sierpinski level (0-8): ");
	double sideLength = getReal("Enter triangle starting length (0-1000): ");

	GWindow window(windowWidth, windowHeight);
	
	while(true)
		DrawSierpinskiTriangle(window,window.getWidth()/2., window.getHeight()/2., sierpinskiLevel, sideLength);

    return 0;
}