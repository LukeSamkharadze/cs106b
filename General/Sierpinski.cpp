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

#include "gwindow.h"
#include "gobjects.h"
#include "simpio.h"

#include <math.h>

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
	if(n == -1)
		return;

	DrawReversedTriangle(window, x, y - sqrt(3.)*length/4. - sqrt(3.)*length/8., length/2.);
	DrawReversedTriangle(window, x + length/2., y + (length/2.)/sqrt(3.) - (length/8.)/sqrt(3.), length/2.);
	DrawReversedTriangle(window, x - length/2., y + (length/2.)/sqrt(3.) - (length/8.)/sqrt(3.), length/2.);

	DrawSierpinskiTriangle(window, x, y - sqrt(3.)*length/4. - sqrt(3.)*length/8., n-1, length/2.);
	DrawSierpinskiTriangle(window, x + length/2., y + (length/2.)/sqrt(3.) - (length/8.)/sqrt(3.), n-1, length/2.);
	DrawSierpinskiTriangle(window, x - length/2., y + (length/2.)/sqrt(3.) - (length/8.)/sqrt(3.), n-1, length/2.);
}

void MainDrawSierpinskiTriangle(GWindow& window, double x, double y, int n, double length)
{
	DrawTriangle(window, x, y, length);

	if(n == 0) return;

	DrawReversedTriangle(window, x, y + sqrt(3.)*length/8., length/2.);

	if(n == 1) return;

	DrawSierpinskiTriangle(window, x, y + sqrt(3.)*length/8., n-2, length/2.);
}

int main() 
{
	double windowWidth = 1000;
	double windowHeight = 1000;

	int sierpinskiLevel = getInteger("Enter sierpinski level (0-8): ");
	double sideLength = getReal("Enter triangle starting length (0-1000): ");

	GWindow window(windowWidth, windowHeight);
	
	while(true)
		MainDrawSierpinskiTriangle(window,window.getWidth()/2., window.getHeight()/2., sierpinskiLevel, sideLength);

    return 0;
}