//used Dr. Pounds's code interact.c as the basic skeleton for this project

#include <GL/glut.h>
#include <stdio.h>
#include <iostream> 
#include <list> 
#include <math.h>
using namespace std;

//vertex, linseg, and triangle structs
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
list <vertex> vList;    //holds the vertices in the order they are drawn
list <triangle> TList;	//holds the triangles from tesselation
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

//draws the points on the screen
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

//draws a line segment on the screen using the old vertex and the new one created by the mouse
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

//erases point by coloring in white
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

//clears screen
void clearBox()
{
       glClear(GL_COLOR_BUFFER_BIT); 
       glFlush();
}

//returns true if two line segments are intersecting
bool linIntersect(linseg a, linseg b)
{
    bool intersect = false;

	//builds the vector equations
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
	
	//takes the determinant of the vector equations
    float d1 = (P1*P4) - (P2*P3);
    float d2 = (P5*P8) - (P6*P7);	//denominator
    float d3 = (P9*P12) - (P10*P11);

    float ua = d1/d2;
    float ub = d3/d2;
    
	//ua and ub must BOTH be inbetween 0 and 1 to intersect each other
    if(((0.0 < ua) && (ua < 1.0)) && (((0.0 < ub) && (ub < 1.0))))
    {
		intersect = true;
    }
    
	//calculate the x,y coordinates where the lines intersect
	float x = a.one.x + ua*(a.two.x - a.one.x);
    float y = a.one.y + ua*(a.two.y - a.one.y);
    
    return intersect;
}

//fills the polygon without using the tesselated triangles
void fillPoly(list <linseg> LList)
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3f(1.0f,0.0f,0.0f);	//red
    
	//draws the LList using the GL_POLYGON, which then lets us fill it
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

//draws all of the line segments in the Llist
void drawLinSegList(list <linseg> LList)
{
    glColor3f(1.0f,0.0f,0.0f);	//red
    //draws the LList using the GL_LINE_LOOP
	glBegin(GL_LINE_LOOP);
    for(list<linseg>::iterator it=LList.begin(); it!=LList.end(); it++)
    {
        glVertex2f((*it).one.x,(*it).one.y);
        glVertex2f((*it).two.x,(*it).two.y);
    }
    glEnd();
    glFlush();
}

//returns the original outline of the polygon
void returnPoly(list <linseg> LList)
{
    //clears the polygon
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
	drawLinSegList(LList);	//used to draw the original outline of the polygon
}

//calculates the crossproduct of three vertices and returns the vector product
vertex cp1(vertex v1, vertex v2, vertex v3)
{
    //creates the two vectors from the three vertices
	vertex a,b;
    a.x = v1.x - v2.x;
    a.y = v1.y - v2.y;
    a.z = 0.0;
    b.x = v3.x - v2.x;
    b.y = v3.y - v2.y;
    b.z = 0.0;

	//calculates the x,y,z components
    float t1 = a.y*b.z;
    float t2 = a.z*b.y;
    float x = (a.y*b.z) - (a.z*b.y);
    float y = (b.z*a.x) - (b.x*a.z);
    float z = (a.x*b.y) - (a.y*b.x);

	//creates a new vertex which stores the cross product vector
    vertex cpv;
    cpv.x = x;
    cpv.y = y;
    cpv.z = z;
    
    return cpv;
}

//determines whether the tesselation line is inside the polygon created
//a & b are the tesselation vertices, where a is the starting point, and b is the ending point
//c & d are a = c, d is the vertex inbetween the starting vertex and a
//e & f are a = c = e, f is the vertex after point a (helps create beta)  
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
	
	//calculate the dot product for alpha and beta
	float dpa = (v1.x*v2.x) + (v1.y*v2.y);
	float dpb = (v2.x*v3.x) + (v2.y*v3.y);

	//calculate the magnitude for each vector
	float v1m = sqrt((pow(v1.x,2.0))+(pow(v1.y,2.0)));
    float v2m = sqrt((pow(v2.x,2.0))+(pow(v2.y,2.0)));
	float v3m = sqrt((pow(v3.x,2.0))+(pow(v3.y,2.0)));

	//calculate alpha and beta
	float alpha = acos((dpa/(v1m*v2m)));
    float beta = acos((dpb/(v2m*v3m)));
    
	//return false if the angle is not interior	
	if(alpha > beta)
    {
        interior = false;
        cout << "angleCheck Failed" << endl;
    }

    return interior;
}	

//tesselates the polygon
void tess(list <vertex> vList, list <linseg> LLlist)                                    
{
	//draws all of the polygon lines on the screen
	drawLinSegList(LList);

	//boolean set to true if the starting vertex needs to be advanced
    bool advanceStart = false;

	//the fakeList is a list of vertices that can be freely deleted from so no points are lost
    list <vertex> fakeList = vList;

	list<vertex>::iterator its = fakeList.begin(); //keeps track of the 1st or starting vertex
    list<vertex>::iterator itn = fakeList.begin(); //keeps track of the 2nd vertex
    list<vertex>::iterator itnn = fakeList.begin();//keeps track of the 3rd vertex
    list<vertex>::iterator itl = fakeList.begin(); //keeps track of the 4th vertex
	
	//Tesselates while there are more than 3 vertices in the fakeList
	while(fakeList.size() > 3)
    {
		vertex last = fakeList.back();	//keeps track of the last vertex in the list
		vertex start,a,b,c;	//redeclares the vertices
		
		//handles moving the iterators to the next vertex in the list
		if(advanceStart == true)
		{
			if((*itl).x == last.x && (*itl).y == last.y)	//if the last iterator is pointing to the last element 
			{
				advanceStart = false;
				advance(its,1);
            	start = *its;
				advance(itn,1);
                a = *itn;
				advance(itnn,1);
                b = *itnn;
                itl = fakeList.begin();
				c = *itl;
			} else if((*itnn).x == last.x && (*itnn).y == last.y)	//if the 2nd to last iterator is pointing to the last element
			{
				advanceStart = false;
                advance(its,1);
                start = *its;
                advance(itn,1);
                a = *itn;
                itnn = fakeList.begin();
                b = *itnn;
                advance(itl,1);
                c = *itl;
			} else if((*itn).x == last.x && (*itn).y == last.y)		//if the 3rd to last iterator is pointing to the last element
            {
                advanceStart = false;
                advance(its,1);
                start = *its;
				itn = fakeList.begin();
                a = *itn;
                advance(itnn,1);
                b = *itnn;
                advance(itl,1);
                c = *itl;
			} else if((*its).x == last.x && (*its).y == last.y)		//if the start iterator is pointing to the last element
            {
                advanceStart = false;
                its = fakeList.begin();
				start = *its;
				advance(itn,1);
                a = *itn;
                advance(itnn,1);
                b = *itnn;
                advance(itl,1);
                c = *itl;
            } else					//advance the iterators all by 1
			{
				advanceStart = false;
				advance(its,1);
            	start = *its;
            	advance(itn,1);
            	a = *itn;
            	advance(itnn,1);
            	b = *itnn;
				advance(itl,1);
            	c = *itl;
			}
		} else						//advanceStart = false, used for when the start does not need to move
		{	
			//sets all of the iterators at the start
			its = fakeList.begin();
    		itn = fakeList.begin();
			itnn = fakeList.begin();
    		itl = fakeList.begin(); 
			
			//sets the iterators to the correct position in the list
    		start = *its;
    		advance(itn,1);
    		a = *itn;
    		advance(itnn,2);
    		b = *itnn;
    		advance(itl,3);
    		c = *itl;
		}		
		
		//calculates the cross product for the given vertices
        vertex cpv = cp1(start,a,b);
		
		//tests if it is ccw or cw
        if(cpv.z < 0.0)	//ccw
        {        
			//create linseg for tess line can see if any intersect
			linseg tess;
			tess.one = start;
			tess.two = b;
			
			//tests if there is an intersection with the current tesselation line segment with the entire list of line segments
			bool ib=false;	
            for(list<linseg>::iterator t1=LList.begin(); t1!=LList.end(); t1++)
            {
                ib = linIntersect(tess,*t1);
                if(ib == true)
                {
                	cout << "Intersection with the tess linseg." << endl;
					break;	//breaks the for loop, moves to the beginning of the while loop
                }
            }
			
			//determines whether the tesselation line is inside the polygon
			bool intAngle = AngleCheck(b,start,b,a,b,c);

			if(ib == false && intAngle == true)	//if there are no tesselation line intersections and the tesselation line is inside the polygon
			{					
                //adds the three vertices to a triangle and adds it to the triangle list
				triangle t;
				t.tone = start;
				t.ttwo = a;
				t.tthree = b;
				TList.push_back(t);
				
				//delete vertex a from the fakeList, and itn = itnn
				//cout <<"removed: "<< a.x << " "<< a.y<< endl;
				itn = fakeList.erase(itn);

                //prints the rest of fakeList after removal
            	/*for(list<vertex>::iterator i=fakeList.begin(); i!=fakeList.end(); i++)
            	{
                	cout << (*i).x <<" "<<(*i).y << endl;
            	}
				cout << " " << endl;*/				
			} else	//the start needs to be advanced
            {
                advanceStart = true; 	//the starting vertex needs to be advanced
            }
        }
		else	//cw
		{
			advanceStart = true;	//the staring vertex needs to be advanced
        }
    }
	//creates the last 3 vertices from fakeList
	list<vertex>::iterator it1=fakeList.begin();
	vertex v1,v2,v3;
    v1 = *it1;
    advance(it1,1);
    v2 = *it1;
    advance(it1,1);
    v3 = *it1;
	
	//adds the last three vertices to the TList	
	triangle t;
    t.tone = v1;
    t.ttwo = v2;
    t.tthree = v3;
    TList.push_back(t);

	//prints the triangles and gives the area of the triangles
	for(list<triangle>::iterator g=TList.begin(); g!=TList.end(); g++)
    {
		cout << "Triangle: " << endl;
		cout << (*g).tone.x << " " << (*g).tone.y << endl;
        cout << (*g).ttwo.x << " " << (*g).ttwo.y << endl;
        cout << (*g).tthree.x << " " << (*g).tthree.y << endl;
        
		drawLinSeg((*g).tone,(*g).ttwo);	//draws the tesselation line segment
		drawLinSeg((*g).tthree,(*g).ttwo);	//draws the line segment between vertices 2 and 3
		drawLinSeg((*g).tone,(*g).tthree);	//draws the line segment between vertices 1 and 3
		
		//calculates the area of the triangle
		vertex f = cp1((*g).tone,(*g).ttwo,(*g).tthree);
        float area = abs((f.z)/2);
        cout << "Area: " << area << endl;
	}
}

//fills the tesselation triangles
void fillTessPolygon()
{
	glColor3f(0.0f,0.0f,0.0f); 
	for(list<triangle>::iterator g=TList.begin(); g!=TList.end(); g++)
    {
        glColor3f(0.0f,0.0f,0.0f);

		glBegin(GL_POLYGON);
        glVertex2f((*g).tone.x,(*g).tone.y);
        glVertex2f((*g).ttwo.x,(*g).ttwo.y);
    	glVertex2f((*g).tthree.x,(*g).tthree.y);
		glEnd();
		glFlush();
    }	
}

void mouse( int button, int state, int x, int y )
{ 
	if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
  	{
        //tests if the polygon is not built and there is at least one vertex built
		if(poly == false && vList.size() > 0)
		{
			vertex prev_v = vList.back();	//gets the last vertex from the vList
			vertex v;	//new vertex from the mouse
			v.x = x;
			v.y = WINDOW_MAX_Y -y;
			vList.push_back(v); //stores the screen coordinates
			printf("v: %d   %d\n", x,y); //prints the screen coordinates
			linseg l;	//creates the a new linseg between the last vertex and the new one from the mouse 
			l.one = prev_v;
			l.two = v;
			
			bool ib1=false;	//tests if there is an intersection with the current line segment with the entire list of line segments
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
			LList.push_back(l);	//adds the line segment to the LList
			drawBox( x, WINDOW_MAX_Y -y );	//draws the vertex
			drawLinSeg(prev_v,v);		//draws the line segment
		} else if(poly == false && vList.size() == 0)	//tests if the polygon is not built and no vertex has been built
		{
			vertex v;	//creates the starting vertex
            v.x = x;
            v.y = WINDOW_MAX_Y -y;
            cout << "v: " << v.x << "   " << v.y << endl;
			vList.push_back(v);	//adds the vertex to the vList
		}
    }

  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )	//declares the polygon to be finished, creates the last line segment and adds it to the list
     {
        vertex last_v, start_v;
        last_v = vList.back();
        start_v = vList.front();
        linseg last_l;
        last_l.one = last_v;
        last_l.two = start_v;
        LList.push_back(last_l);
        drawLinSeg(last_v,start_v);
        poly = true;
	    eraseBox( x, WINDOW_MAX_Y -y );
     }
}

void keyboard( unsigned char key, int x, int y )
{ 
    //exits the program if q or Q is clicked
	if(key == 'q' || key == 'Q') {
		exit(0);
    }
	//fills the polygon with no tesselation when the polygon is completed
    if((key == 'f' || key == 'F') && poly == true) {
        fillPoly(LList);
    }
	//show the triangles used in the tesselation and the areas of the triangles
    if((key == 't' || key == 'T') && poly == true) {
        tess(vList,LList);
    }
	//fills in the triangles using the tesselation function
    if((key == 'p' || key == 'P') && poly == true) {
        fillTessPolygon();
    }
	//returns the screen to the original outline of the polygon
    if((key == 'l' || key == 'L') && poly == true) {
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
