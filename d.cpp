#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <math.h>
#define PI 3.14159265358979
using namespace std;

bool ccwb;
struct vertex {
    float x,y,z;
};
struct linseg {
    vertex one;
    vertex two;
    //vertex three;
    //build line equation
    //draw line equation
};
list <vertex> vList;    
vertex cp(linseg a1, linseg b1)
{
    vertex v1,v2,v3,v4;
    v1 = a1.one;
    v2 = a1.two;
    v3 = b1.one;
    v4 = b1.two;

    //create the points v2 = v3
    vertex a,b;
    a.x = v1.x - v2.x;
    a.y = v1.y - v2.y;
    a.z = 0.0;
    b.x = v4.x - v2.x;
    b.y = v4.y - v2.y;
    b.z = 0.0;
    float t1 = a.y*b.z;
    float t2 = a.z*b.y;
    float x = (a.y*b.z) - (a.z*b.y);
    float y = (b.z*a.x) - (b.x*a.z);
    float z = (a.x*b.y) - (a.y*b.x);
    
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

vertex cp1(vertex v1, vertex v2, vertex v3)
{
	vertex a,b;
    a.x = v1.x - v2.x;
    a.y = v1.y - v2.y;
    a.z = 0.0;
    b.x = v3.x - v2.x;
    b.y = v3.y - v2.y;
    b.z = 0.0;
    float t1 = a.y*b.z;
    float t2 = a.z*b.y;
    float x = (a.y*b.z) - (a.z*b.y);
    float y = (b.z*a.x) - (b.x*a.z);
    float z = (a.x*b.y) - (a.y*b.x);
    
    vertex cpv;
    cpv.x = x;
    cpv.y = y;
    cpv.z = z;
    printf("x: %f   y: %f   z: %f\n",cpv.x,cpv.y,cpv.z);
    return cpv;
}

bool degreeCheck(linseg tess, linseg l1, linseg l2)
{
	vertex a,b,c,d,e,f;
	a = tess.one;
	b = tess.two;
	c = l1.one;
	d = l1.two;
	e = l2.one;
	f = l2.two;

	//calculate alpha
	//create the vector points b = c
	vertex v1,v2;
    v1.x = a.x - b.x;
    v1.y = a.y - b.y;
    v2.x = c.x - d.x;
    v2.y = c.y - d.y;
	
	cout << v1.x << " " << v1.y << endl;
	cout << v2.x << " " << v2.y << endl;

	float dp1 = v1.x*v2.x;
	float dp2 = v1.y*v2.y;
	float dp = dp1 + dp2;
	cout << dp << endl;
	
	//calculate magnitude of v1, v2
	float v1m = sqrt((pow(v1.x,2.0))+(pow(v1.y,2.0)));
	float v2m = sqrt((pow(v2.x,2.0))+(pow(v2.y,2.0)));
	
	float alpha = acos((dp/(v1m*v2m))) * 180.0/PI;
	cout << alpha << endl;
	
}

void tesselate(list <vertex> vList)
{
	vertex start = vList.front();
	list<vertex>::iterator it=vList.begin(); 
	while(vList.size() > 3)
    {
        vertex a,b;
		advance(it,1);
		a = *it;
		advance(it,1);
		b = *it;
		vertex cpv = cp1(start,a,b);
        if(cpv.z < 0.0)
		{
			cout <<"ccw"<<endl;
			//vList.remove((*it));
			//cout<<*prev((*it).x)<<" " << *prev((*it).y)<<endl;
			//cout << b.x << " "<< b.y<<endl;
			vertex c = *prev(it);
			cout <<"removed: "<< c.x << " "<< c.y<< endl;
			vList.erase(prev(it));
			//vList.remove(a.y);
			for(list<vertex>::iterator i=vList.begin(); i!=vList.end(); i++)
			{
				cout << (*i).x <<" "<<(*i).y << endl;
			}
		}
    }
    //draw and add last triangle to list and screen
    
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

	vertex v3; //same as v2 because they are connected
    v3.x = 8.0;
    v3.y = 3.0;

    vertex v4;
    v4.x = -1.0;
    v4.y = -2.0;
	
	vertex v5,v6,v7,v8;
	v5.x = 0.0;
	v5.y = 0.0;
	v6.x = 2.0;
	v6.y = 2.0;
	v7.x = 0.0;
	v7.y = 4.0;
	v8.x = 1.0;
	v8.y = 2.0;
	linseg a,b,c,d;
	a.one = v1;
	a.two = v2;
	b.one = v3;
	b.two = v4;
	c.one = v5;
	c.two = v6;
	
	d.one = v6;
	d.two = v7;
	
	degreeCheck(a,b,c);
	
	/*vList.push_back(v5);
	vList.push_back(v6);
	vList.push_back(v7);
	vList.push_back(v8);
	tesselate(vList);

    linIntersect(a,b);	
	//vertex cpv = cp(c,d);	
	vertex cpv = cp1(v5,v6,v7);
	float z = cpv.z;
	//bool ccwb = ccw(z);
	if(ccwb == true){
		//cout << "CCW!" << endl;
	}
    //printf("x: %f   y: %f   z: %f\n",cpv.x,cpv.y,z);
	*/
}
