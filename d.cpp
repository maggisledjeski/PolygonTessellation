#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

struct vertex {
    int x, y;
};
struct linseg {
    vertex one;
    vertex two;
    //build line equation
    //    //draw line equation
};
    //
void linIntersect(linseg a, linseg b)
{
    float P1 = b.one.x - a.one.x;
    float P2 = -(b.two.x - b.one.x);
    float P3 = b.one.y - a.one.y;
    float P4 = -(b.two.y - b.one.y);
    
    float P5 = a.two.x - a.one.x;
    float P6 = -(b.two.x - b.one.x);
    float P7 = a.two.y - a.one.y;
    float P8 = -(b.two.y - b.one.y);

    float P9 = a.two.x - a.one.x;
    float P10 = -(b.one.x - a.one.x);
    float P11 = a.two.y - a.one.y;
    float P12 = -(b.one.y - a.one.y);

    float d1 = (P1*P4) - (P2*P3);
    float d2 = (P5*P8) - (P6*P7);
    float d3 = (P9*P12) - (P10*P11);

    float ua = d1/d2;
    float ub = d3/d2;
    printf("ua: %f\nub: %f\n",ua,ub);
}

int main(int argc, char** argv)
{
	vertex v1;
	v1.x = -7;
	v1.y = -1;
	
	vertex v2;
	v2.x = 8;
	v2.y = 3;

	vertex v3;
        v3.x = -2;
        v3.y = 1;

        vertex v4;
        v4.x = -1;
        v4.y = -2;

	linseg a,b;
	a.one = v1;
	a.two = v2;
	b.one = v3;
	b.two = v4;
	
        linIntersect(a,b);	
	
}
