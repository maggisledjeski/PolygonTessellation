#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

bool ccwb;
struct vertex {
    int x, y,z;
};
struct linseg {
    vertex one;
    vertex two;
    //vertex three;
    //build line equation
    //draw line equation
};
    
vertex cp(linseg a, linseg b)
{
    vertex v1,v2,v3,v4;
    v1 = a.one;
    v2 = a.two;
    v3 = b.one;
    v4 = b.two;
    
    float x = (v1.y*v2.z)-(v1.z*v2.y);
    float y = (v1.z *v2.x) - (v1.x *v2.z);
    float z = (v1.x*v2.y) - (v1.y *v2.x);
    printf("x: %f   y: %f   z: %f\n",x,y,z);

    vertex cpv;
    cpv.x = x;
    cpv.y = y;
    cpv.z = z;
    printf("x: %f   y: %f   z: %f\n",cpv.x,cpv.y,cpv.z);  
    return cpv;
}

bool ccw(float cpvz)
{
    bool ccwb = false;
    if(cpvz < 0.0)
    {
        ccwb = true;
	cout << "True!" << endl;
    }
/*    else
    {
        ccbw = false;
    }*/
    //return ccbw;
}

float Determinant2(vertex a, vertex b)
{
    //printf("a.x: %f    a.y: %f    b.x: %f    b.y: %f\n",a.x,a.y,b.x,b.y);
    float d = (a.x * b.y) - (a.y * b.x);
    //printf("%f\n",d);
    return d;
}

void linIntersect(linseg a, linseg b)
{
    float P1 = b.one.x - a.one.x;
    float P2 = -(b.two.x - b.one.x);
    float P3 = b.one.y - a.one.y;
    float P4 = -(b.two.y - b.one.y);
    
    //float c1 = Determinant2(a.one,a.two);
    //float c2 = Determinant2(b.one,b.two);

    float P5 = a.two.x - a.one.x;
    float P6 = -(b.two.x - b.one.x);
    float P7 = a.two.y - a.one.y;
    float P8 = -(b.two.y - b.one.y);

    float P9 = a.two.x - a.one.x;
    float P10 = b.one.x - a.one.x;
    float P11 = a.two.y - a.one.y;
    float P12 = b.one.y - a.one.y;

    float d1 = (P1*P4) - (P2*P3);
    float d2 = (P5*P8) - (P6*P7);
    float d3 = (P9*P12) - (P10*P11);
    
    //printf("d1: %f    d2: %f   d3: %f\n",d1,d2,d3);

    //float u1 = c1/d2;
    //float u2 = c2/d2;
    float ua = d1/d2;
    float ub = d3/d2;
    printf("ua: %f\nub: %f\n",ua,ub);
    //printf("u1: %f\nu2: %f\n",u1,u2);
    float x = a.one.x + ua*(a.two.x - a.one.x);
    float y = a.one.y + ua*(a.two.y - a.one.y);
    printf("x = %f\ny = %f\n",x,y);

}

int main(int argc, char** argv)
{
	vertex v1;
	v1.x = -7.0;
	v1.y = -1.0;
	v1.z = 0.0;

	vertex v2;
	v2.x = 8.0;
	v2.y = 3.0;
	v2.z = 0.0;

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
	vertex cpv = cp(a,b);	
	float z = cpv.z;
	bool ccwb = ccw(z);
	if(ccwb == true){
		cout << "TRUE!" << endl;
	}
    //printf("x: %f   y: %f   z: %f\n",cpv.x,cpv.y,z);

}
