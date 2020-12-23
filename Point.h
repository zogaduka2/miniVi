
#ifndef Point_H
#define Point_H


class Point {

public:
    Point();
    Point(int, int);
    void setX(int);
    void setY(int);
    int getX() const;
    int getY() const;
    void display() const;
    double distance(const Point&);

private:
    int x;
    int y;


};


#endif