#include "point.h"
#include<iostream>
using namespace std;

Point::Point() //default values
    : x(0), y(0)
{
}
Point::Point(int num1, int num2)// values passed through point
    : x(num1), y(num2)
{

}
void Point::setX(int n) //set X value
{
    x = n;
}
void Point::setY(int n) {
    y = n;
}
int Point::getX() const // return x
{
    return x;

}
int Point::getY() const // return y
{
    return y;
}
void Point::display() const //output function
{
    cout << "( " << getX() << " , " << getY() << ")";
}

double Point::distance(const Point& point2) // distance between 2 points
{
    return sqrt(pow(point2.getX() - getX(), 2) + pow(point2.getY() - getY(), 2));

}
