

// An OpenGL Keyboard and Mouse Interaction Program

#include <GL/glut.h>
#include <stdio.h>
#include <iostream> 
#include <list> 
#include <math.h>
#define PI 3.14159265358979
using namespace std;
// These are defined in a global scope

struct vertex {
    float x, y, z;
};
struct linseg {
    vertex one;
    vertex two;
};
struct triangle {
    vertex tone;
    vertex ttwo;
	vertex tthree;
};
list <linseg> LList;    //holds the line segments
list <vertex> tList;    //holds the triangle vertices
list <vertex> vList;    //holds the vertices in the order they are drawn
bool poly = false;      //whether the polygon is finished or not

GLubyte red, green, blue;
int COLORS_DEFINED;

// Specity the values to place and size the window on the screen
const int WINDOW_POSITION_X = 800;
const int WINDOW_POSITION_Y = 800;
const int WINDOW_MAX_X = 800;
const int WINDOW_MAX_Y = 800;

// Specify the coordinate ranges for the world coordinates in the 2D Frame
const float WORLD_COORDINATE_MIN_X = 0.0;
const float WORLD_COORDINATE_MAX_X = 800.0;
const float WORLD_COORDINATE_MIN_Y = 0.0;
const float WORLD_COORDINATE_MAX_Y = 800.0;

void myglutInit( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y); /* set pixel window */
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y); /* place window top left on display */
    glutCreateWindow("Polygon Tesselation"); /* window title */
}

void myInit(void)
{ 
/* standard OpenGL attributes */
      glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
      glColor3f(1.0, 0.0, 0.0); /* draw in red */
      glPointSize(1.0);

      COLORS_DEFINED = 0;

/* set up viewing window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
                 WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
      glMatrixMode(GL_MODELVIEW);
}

void display( void )
{
/* define a point data type */

    typedef GLfloat point[2];     
    point p; /* A point in 2-D space */

    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

    if (!COLORS_DEFINED) {
       red   = 255;
       green = 0; 
       blue  = 0;
    }

    glColor3ub( red, green, blue ); 

    /* define point */

    //p[0] = 100; 
    //p[1] = 100;
   
    /* plot new point */

    glBegin(GL_POINTS);
    glVertex2fv(p); 
    glEnd();
    glFlush(); /* clear buffers */
}

void drawBox( float x, float y )
{
    typedef GLfloat point[2];     
    point p;
 
    glColor3ub( red, green, blue );
   
    //p[0] = x;
    //p[1] = y;  
    
     glBegin(GL_POINTS);
     glVertex2fv(p); 
     glEnd();
     glFlush();
}

void drawLinSeg(vertex old_v, vertex new_v)
{
    if(old_v.x == 0 && old_v.y == 0)
    {
    	old_v.x = new_v.x;
        old_v.y = new_v.y;
	}
    glBegin(GL_LINE_LOOP);
    glVertex2f(old_v.x,old_v.y);
    glVertex2f(new_v.x,new_v.y);
    glEnd();
    glFlush();
}

void eraseBox( int x, int y )
{
    typedef GLfloat point[2];     
    point p;

    glColor3f( 1.0, 1.0, 1.0 );

    p[0] = x;
    p[1] = y;  

    glBegin(GL_POINTS);
      glVertex2fv(p); 
    glEnd();
    glFlush();
}

void clearBox()
{
       glClear(GL_COLOR_BUFFER_BIT); 
       glFlush();
}

bool linIntersect(linseg a, linseg b)
{
    bool intersect = false;
    int P1 = b.one.x - a.one.x;
    int P2 = -(b.two.x - b.one.x);
    int P3 = b.one.y - a.one.y;
    int P4 = -(b.two.y - b.one.y);
    
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

    float ua = d1/d2;
    float ub = d3/d2;
    //printf("ua: %f\nub: %f\n",ua,ub);
    if(((0.0 < ua) && (ua < 1.0)) && (((0.0 < ub) && (ub < 1.0))))
    {
		intersect = true;
/*		cout << a.one.x <<" "<<a.one.y<< endl;
		cout << a.two.x << " " <<a.two.y <<endl;
		cout << b.one.x <<" "<<b.one.y<< endl;
        cout << b.two.x << " " <<b.two.y <<endl;*/
    }
    float x = a.one.x + ua*(a.two.x - a.one.x);
    float y = a.one.y + ua*(a.two.y - a.one.y);
    //printf("x = %f\ny = %f\n",x,y);
    
    return intersect;
}

void fillPoly(list <linseg> LList)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_POLYGON);
	for(list<linseg>::iterator it=LList.begin(); it!=LList.end(); it++)
    {
    	glVertex2f((*it).one.x,(*it).one.y);
		glVertex2f((*it).two.x,(*it).two.y);
    }
	glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFlush();
}
void drawLinSegList(list <linseg> LList)
{
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    for(list<linseg>::iterator it=LList.begin(); it!=LList.end(); it++)
    {
        glVertex2f((*it).one.x,(*it).one.y);
        glVertex2f((*it).two.x,(*it).two.y);
    }
    glEnd();
    glFlush();
}

void returnPoly(list <linseg> LList)
{
    for(list<linseg>::iterator it=LList.begin(); it!=LList.end(); it++)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    	glBegin(GL_POLYGON);
		glVertex2f((*it).one.x,(*it).one.y);
        glVertex2f((*it).two.x,(*it).two.y);
    	glEnd();
    	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    	glFlush();
	}
	drawLinSegList(LList);
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
    printf("cross product:     x: %f   y: %f   z: %f\n",cpv.x,cpv.y,cpv.z);
    return cpv;
}

bool AngleCheck(vertex a, vertex b, vertex c, vertex d, vertex e, vertex f)
{
    bool interior = true;
    
	//calculate the vectors 
	vertex v1,v2,v3;
    v1.x = b.x - a.x;
    v1.y = b.y - a.y;
    v2.x = d.x - c.x;
    v2.y = d.y - c.y;
    v3.x = f.x - e.x;
    v3.y = f.y - e.y;
	cout << "v1: "<<v1.x <<" "<<v1.y << endl;
	cout << "v2: "<<v2.x <<" "<<v2.y << endl;
	cout << "v3: "<<v3.x <<" "<<v3.y << endl;

	//calculate the dot product for alpha and beta
	float dpa = (v1.x*v2.x) + (v1.y*v2.y);
	float dpb = (v2.x*v3.x) + (v2.y*v3.y);

	//calculate the magnitude for each vector
	float v1m = sqrt((pow(v1.x,2.0))+(pow(v1.y,2.0)));
    float v2m = sqrt((pow(v2.x,2.0))+(pow(v2.y,2.0)));
	float v3m = sqrt((pow(v3.x,2.0))+(pow(v3.y,2.0)));

	//calculate alpha and beta
	float alpha = acos((dpa/(v1m*v2m)));// * 180.0/PI;
    float beta = acos((dpb/(v2m*v3m)));// * 180.0/PI;
    cout << "alpha: " << alpha << endl;
	cout << "beta: " << beta << endl;

	//return false if the angle is not interior	
	if(alpha > beta)
    {
        interior = false;
        cout << "angleCheck Failed" << endl;
    }

    return interior;
}	

void tess(list <vertex> vList,list <vertex> tList, list <linseg> LLlist)                                    
{
	drawLinSegList(LList);
    cout<<"vList:"<<endl;
	for(list<vertex>::iterator i=vList.begin(); i!=vList.end(); i++)
    {
    	cout << (*i).x <<" "<<(*i).y << endl;
    }
	//counts the number of cw vertices to keep track of where the start vertex should be
    int Count = 0;
	int intersectCount = 0;
    while(vList.size() > 3)
    {
        list<vertex>::iterator its = vList.begin();	//keeps track of the starting vertex
		vertex start = vList.front();	//first vertex in vList
		list<vertex>::iterator itn = vList.begin();	//keeps track of the next vertices
        list<vertex>::iterator itnn = vList.begin();		
		list<vertex>::iterator itl = vList.begin();
		//stores the next 2 vertices from the start in vList to a and b
		vertex a,b,c;
        if(Count <= vList.size()-4)//2)	//handles the number of cw vertices
		{
			advance(its,Count);	//advances its to new start
			start = *its;
			advance(itn,Count+1);	//advances itn to the next element after the start
        	a = *itn;
        	advance(itnn,Count+2);	//advances itn to the next element after a
        	b = *itnn;
            advance(itl,Count+3);
            c = *itl;
		} else 
		{
			advance(its,Count+1 - vList.size()+1);
            start = *its;
            advance(itn,Count+2 - vList.size()+1);	//advances itn to the next element after the start
        	a = *itn;
        	advance(itnn,Count+3 - vList.size()+1);	//advances itn to the next element after a
        	b = *itnn;
            advance(itl,Count+4 - vList.size()+1);
            c = *itl;
		}
		
		//calculates the cross product for the given vertices
        vertex cpv = cp1(start,a,b);
		//tests ccw or cw
        if(cpv.z < 0.0)
        {        
			//create linseg for tess line can see if any intersect
			linseg tess;
			tess.one = start;
			tess.two = b;

			bool ib=false;
            for(list<linseg>::iterator t1=LList.begin(); t1!=LList.end(); t1++)
            {
                ib = linIntersect(tess,*t1);
                //there is an intersect present with the tess linseg and the one being tested
                if(ib == true)
                {
                	cout << "there is an intersect with the tess linseg." << endl;
					//cwCount++;
					break;	//breaks the for loop, moves the start by 1, goes to start of while
                }
            }
			
			bool intAngle = AngleCheck(start,b,a,b,b,c);
			if(ib == false && intAngle == true)	//if there are no tess line intersections
			{					
				/*//draws the tess line
				glBegin(GL_LINES);
				glVertex2f(start.x,start.y);
				glVertex2f(b.x,b.y);
				glEnd();
				glFlush();*/
				
                //adds to tList
				tList.push_back(start);
                tList.push_back(a);
                tList.push_back(b);
				
				//delete vertex a from vList, and itn = itnn
				cout <<"removed: "<< a.x << " "<< a.y<< endl;
            	itn = vList.erase(itn);
                //vList.erase(itn);
                cout << "vList: " << endl;
				//prints the rest of vList after removal
            	for(list<vertex>::iterator i=vList.begin(); i!=vList.end(); i++)
            	{
                	cout << (*i).x <<" "<<(*i).y << endl;
            	}
				
			} else
            {
                cout << "AngleCheck Fail or tess line intersection fail" <<endl;
                /*if(Count == vList.size())
                {
                    Count = 0;
                }
                else {
                    Count++;
                }*/
                Count++;
                cout << "cwCount (A): " << Count << endl;
            }
        }
		else	//cw
		{
			//cwCount++;
			cout <<cpv.z<<endl;
			/*if(Count == vList.size())
            {
                Count = 0;
            }
            else {
                Count++;
            }*/
            Count++;
            //break;
            cout << "cwCount: "<<Count << endl;
            //break;
		}
        if(Count > 20)
        {
            break;
        }
    }
	//creates the last 3 vertices from vList
	list<vertex>::iterator it1=vList.begin();
	vertex v1,v2,v3;
    v1 = *it1;
    advance(it1,1);
    v2 = *it1;
    advance(it1,1);
    v3 = *it1;

    //adds the last 3 vertices to the tList
    tList.push_back(v1);
    tList.push_back(v2);
    tList.push_back(v3);

    int i = 0;  //counts to 3, prints the vertices in their triangles    
    for(list<vertex>::iterator p=tList.begin(); p!=tList.end(); p++)
    {
        if(i % 3 == 0)
        {
            cout << "Triangle: " << endl;
            list<vertex>::iterator y = p;
            vertex s,f;
            s = *y;
            advance(y,2);
            f = *y;
            //cout << "s: " << s.x << " " << s.y << endl;
            //cout << "f: " << f.x << " " << f.y << endl;
            drawLinSeg(s,f);
        }
        
        cout << (*p).x << " " << (*p).y << endl;
        i++;
    }

}

void mouse( int button, int state, int x, int y )
{ 
	if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
  	{
        //tests if the polygon is not built and there is at least one vertex built
		if(poly == false && vList.size() > 0)
		{
			vertex prev_v = vList.back();//*prev(vList.end());
			vertex v;
			v.x = x;
			v.y = WINDOW_MAX_Y -y;
			vList.push_back(v); //stores the screen coordinates
			//lList.push_back(v);
			printf("v: %d   %d\n", x,y);
			linseg l;
			linseg prev_l = LList.back();//*prev(LList.end());
			l.one = prev_v;
			l.two = v;
			bool ib1=false;
			for(list<linseg>::iterator it=LList.begin(); it!=LList.end(); it++)
			{
				ib1 = linIntersect(l,*it);
				//there is an intersect present with the current linseg and the one being tested and resets the bool
				if(ib1 == true)
				{
					cout << "there is an intersect with the last line segment drawn." << endl;
					ib1 = false;
				}
		
			}
			LList.push_back(l);
			drawBox( x, WINDOW_MAX_Y -y );
			drawLinSeg(prev_v,v);	
		} else if(poly == false && vList.size() == 0)	//tests if the polygon is not built and no vertex has been built
		{
			printf("v: %d   %d\n", x,y);
			vertex v;
            v.x = x;
            v.y = WINDOW_MAX_Y -y;
            vList.push_back(v);
		}
		//drawLinSeg(prev_v,v);
		//drawBox( x, WINDOW_MAX_Y -y );
    }

  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
     {
        vertex last_v, start_v;
        last_v = vList.back();
        start_v = vList.front();
        linseg last_l;
        last_l.one = last_v;
        last_l.two = start_v;
        LList.push_back(last_l);
        drawLinSeg(last_v,start_v);
        //printf ("%d   %d\n", x, y);
        poly = true;
	    eraseBox( x, WINDOW_MAX_Y -y );
     }
  
  if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
     {
        printf ("%d   %d\n", x, y);
        clearBox();
     }

}


void keyboard( unsigned char key, int x, int y )
{ 
    if (key == 'q' || key == 'Q') {
	exit(0);
    }
    if ((key == 'f' || key == 'F') && poly == true) {
        //draw polygon filled in with no tesselation
        fillPoly(LList);
    }
    if ((key == 't' || key == 'T') && poly == true) {
        //show the triangles used in the tesselation and the areas of the triangles IN THE ORDER THEY ARE DRAWN
        tess(vList,tList,LList);
    }
    if ((key == 'p' || key == 'P') && poly == true) {
        //polygons filled in after tesselation
    }
    if ((key == 'l' || key == 'L') && poly == true) {
        //should return the screen to the original outline of the polygon
        returnPoly(LList);
    }
}


int main(int argc, char** argv)
{

    myglutInit(argc,argv); /* Set up Window */
    myInit(); /* set attributes */

    // Now start the standard OpenGL glut callbacks //
    
    glutMouseFunc(mouse);  /* Define Mouse Handler */
    glutKeyboardFunc(keyboard); /* Define Keyboard Handler */
    glutDisplayFunc(display); /* Display callback invoked when window opened */
    glutMainLoop(); /* enter event loop */
}

