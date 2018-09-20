

// An OpenGL Keyboard and Mouse Interaction Program

#include <GL/glut.h>
#include <stdio.h>
#include <iostream> 
#include <list> 
using namespace std;
// These are defined in a global scope

//list <vertex> vList;
//global linked list of line segments
//global linked list of triangles
struct vertex {
    float x, y, z;
};
struct linseg {
    vertex one;
    vertex two;
    //build line equation
    //draw line equation
};
struct triangle {
    //maybe three lines
    int x1, y1;
    int x2, y2;
    int x3, y3;
};
list <linseg> LList;
list <vertex> lList;	//list of vertices that can make the linseg list
list <vertex> vList;
bool poly = false;
GLubyte red, green, blue;
int COLORS_DEFINED;

// Specity the values to place and size the window on the screen

const int WINDOW_POSITION_X = 100;
const int WINDOW_POSITION_Y = 100;
const int WINDOW_MAX_X = 400;
const int WINDOW_MAX_Y = 400;

// Specify the coordinate ranges for the world coordinates in the 2D Frame

const float WORLD_COORDINATE_MIN_X = 0.0;
const float WORLD_COORDINATE_MAX_X = 400.0;
const float WORLD_COORDINATE_MIN_Y = 0.0;
const float WORLD_COORDINATE_MAX_Y = 400.0;


void myglutInit( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y); /* set pixel window */
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y); /* place window top left on display */
    glutCreateWindow("Mouse and Keyboard Interaction"); /* window title */
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


void drawBox( int x, int y )
{
    typedef GLfloat point[2];     
    point p;
 
    glColor3ub( red, green, blue );
   
    p[0] = x;
    p[1] = y;  
    
        glBegin(GL_POINTS);
            glVertex2fv(p); 
        glEnd();
        glFlush();
}

/* //will need to add pointers to point to vectors
float dP2 (vector a, vector b) //calculates the dot product for two vectors with 2 components each
{
    float s1 = a1*b1;
    float s2 = a2*b2;
    float dp2 = s1 + s2;
    return dp2;
}

float dP3 (vector a, vector b) //calculates the dot product for two vectors with 3 components each
{
    float s1 = a1*b1;
    float s2 = a2*b2;
    float s3 = a3*b3;
    float dp3 = s1 + s2 + s3;
    return dp3;
}
*/

/*void drawLinSeg(int x1, int x2, int y1, int y2)
{
    //connects lines to eachother but not to the previous line
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
    glFlush();
}*/

void drawLinSeg(vertex old_v, vertex new_v)
{
    if(old_v.x == 0 && old_v.y == 0)
    {
    	old_v.x = new_v.x;
        old_v.y = new_v.y;
    }
    glBegin(GL_LINE_LOOP);
    glVertex2i(old_v.x,old_v.y);
    glVertex2i(new_v.x,new_v.y);
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

void tess(bool poly, list <linseg> LList)//do I need anything else brought in 
{
}

float Determinant2(vertex a, vertex b)
{
    float d = (a.x * b.y) - (a.y * b.x);
//    printf("%f",d);
    return d;
}

void CP2(bool poly, list <linseg> LList)
{
    if(poly == true)
    {
        //run
        LList.front().one;
        //LList
    }
    else
    {
        printf("the polygon is not finished, left click on window to finsh the polygon");
    }
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
		cout << intersect << endl;
    }
    float x = a.one.x + ua*(a.two.x - a.one.x);
    float y = a.one.y + ua*(a.two.y - a.one.y);
    //printf("x = %f\ny = %f\n",x,y);
    
    return intersect;
}
void mouse( int button, int state, int x, int y )
{ 

  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
     {
        //printf ("%d   %d\n", x, y); //prints the mouse coordinates
	if(poly == false){
	vertex prev_v = *prev(vList.end());
	vertex v;
	v.x = x;
	v.y = WINDOW_MAX_Y -y;
	vList.push_back(v); //stores the screen coordinates
	//lList.push_back(v);
	printf("v: %d   %d\n", v.x,v.y);
	linseg l;
	linseg prev_l = *prev(LList.end());
	l.one = prev_v;
	l.two = v;
	bool ib1=false,ib2=false;
	for(list<linseg>::iterator it=LList.begin(); it!=LList.end(); ++it)
	{
		ib1 = linIntersect(l,*it);
		//there is an intersect present with the current linseg and the one being tested and resets the bool
		if(ib1 == true)
		{
			cout << "there is an intersect with the last linseg drawn." << endl;
			ib1 = false;
		}
		
	}
	if(ib2 == false)
	{
		LList.push_back(l);
	}
	//printf("L1: %d     %d\n", LList.back().one.x,LList.back().one.y);
        //printf("L2: %d     %d\n\n",LList.back().two.x,LList.back().two.y);
	drawLinSeg(prev_v,v);
	Determinant2(prev_v,v);
	drawBox( x, WINDOW_MAX_Y -y );	
	}
	/*if(lList.size() == 2)
	{
		//adds lList vertices to the linseg l, which is added to the LList <linseg>
		linseg l;
		l.one = lList.front();
		l.two = lList.back();
		printf("l1: %d     %d\n", l.one.x,l.one.y);
                printf("l2: %d     %d\n\n",l.two.x,l.two.y);
		lList.pop_back();
		lList.pop_back();
		if(lList.empty())
		{
			printf("list <vertex> lList is empty!\n");
		}
		//adds the linseg l to the end of the LList
		LList.push_back(l);
		printf("L1: %d     %d\n", LList.back().one.x,LList.back().one.y);
                printf("L2: %d     %d\n\n",LList.back().two.x,LList.back().two.y);
		
		//calculate the equations for the line, send to equation list?
		//does the line interect any other lines?
		//draw the line
		
		drawLinSeg(LList.back().one.x,LList.back().two.x,LList.back().one.y,LList.back().two.y);
	}*/
        //drawBox( x, WINDOW_MAX_Y -y );
     }

  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
     {
        printf ("%d   %d\n", x, y);
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
    if (key == 'f' || key == 'F') {
        //draw polygon filled in with no tesselation
    }
    if (key == 't' || key == 'T') {
        //show the triangles used in the tesselation and the areas of the triangles IN THE ORDER THEY ARE DRAWN
    }
    if (key == 'p' || key == 'P') {
        //polygons filled in after tesselation
    }
    if (key == 'l' || key == 'L') {
        //should return the screen to the original outline of the polygon
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

