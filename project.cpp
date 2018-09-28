

// An OpenGL Keyboard and Mouse Interaction Program

#include <GL/glut.h>
#include <stdio.h>
#include <iostream> 
#include <list> 
#include <math.h>
#define PI 3.14159265358979
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
    vertex one;
    vertex two;
	vertex three;
};
list <linseg> LList;
list <triangle> tList;
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
		cout << a.one.x <<" "<<a.one.y<< endl;
		cout << a.two.x << " " <<a.two.y <<endl;
		cout << b.one.x <<" "<<b.one.y<< endl;
        cout << b.two.x << " " <<b.two.y <<endl;
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

vertex cp(linseg a1, linseg b1)
{
    vertex v1,v2,v3,v4;
    v1 = a1.one;
    v2 = a1.two;
    v3 = b1.one;
    v4 = b1.two;
	//create the points, (x1-x2,y1-y2,0) (x4-x2,y4-y2,0) v2 = v3
	vertex a,b;
	a.x = v1.x - v2.x;
	a.y = v1.y - v2.y;
	a.z = 0.0;
	b.x = v4.x - v2.x;
	b.y = v4.y - v2.y;
	b.z = 0.0;
	//create the cp vertex
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

bool AngleCheck(vertex a, vertex b, vertex c, vertex d, vertex e, vertex f)//linseg tess, linseg l1, linseg l2)
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
	float dp1 = v1.x*v2.x;
    float dp2 = v1.y*v2.y;
    float dpa = dp1 + dp2;

	float dp3 = v2.x*v3.x;
    float dp4 = v2.y*v3.y;
    float dpb = dp3 + dp4;

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
    }

    return interior;
}	

void tess(list <vertex> vList,list <triangle> tList)                                    
{
	cout<<"vList:"<<endl;
	for(list<vertex>::iterator i=vList.begin(); i!=vList.end(); i++)
    {
    	cout << (*i).x <<" "<<(*i).y << endl;
    }
	//counts the number of cw vertices to keep track of where the start vertex should be
    int cwCount = 0;
	int count = 0;
    while(vList.size() > 3)
    {
        list<vertex>::iterator its = vList.begin();	//keeps track of the starting vertex
		vertex start = vList.front();	//first vertex in vList
		list<vertex>::iterator itn = vList.begin();	//keeps track of the next vertices
				
		//stores the next 2 vertices from the start in vList to a and b
		vertex a,b;
        if(cwCount > 0)	//handles the number of cw vertices
		{
			advance(its,cwCount);	//advances its to new start
			start = *its;
			advance(itn,cwCount+1);	//advances itn to the next element after the start
        	a = *itn;
        	advance(itn,1);			//advances itn to the next element after a
        	b = *itn;
		} else 
		{
			advance(itn,1);	//advances itn to the next element after the start
        	a = *itn;
        	advance(itn,1);	//advances itn to the next element after a
        	b = *itn;
		}
		
		//calculates the cross product for the given vertices
        vertex cpv = cp1(start,a,b);
		//tests ccw or cw
        if(cpv.z < 0.0 && count < 8)
        {
            cout <<"ccw"<<endl;
            
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
					cwCount++;
					break;	//breaks the for loop, moves the start by 1, goes to start of while
                }
            }
			advance(itn,1);
			vertex c = *itn;
			bool intAngle = AngleCheck(start,b,a,b,b,c);
			if(ib == false && intAngle == true && count < 8)	//if there are no tess line intersections
			{					
				//draws the tess line
				glBegin(GL_LINES);
				glVertex2f(start.x,start.y);
				glVertex2f(b.x,b.y);
				glEnd();
				glFlush();
				
				//adds to tList
				triangle t;
				t.one = start;
				t.two = a;
				t.three = b;
            	tList.push_back(t);
				
				//creates the vertex to delete from vList, and removes it
				vertex d = *prev(prev(itn));
            	cout <<"removed: "<< d.x << " "<< d.y<< endl;
            	vList.erase(prev(prev(itn)));

				//prints the rest of vList after removal
            	for(list<vertex>::iterator i=vList.begin(); i!=vList.end(); i++)
            	{
                	cout << (*i).x <<" "<<(*i).y << endl;
            	}
				count++;
			}
        }
		else	//cw
		{
			
			cout <<cpv.z<<endl;
			break;
		}
    }
	//will need to fix, code for when the last triangle is added
	/*list<vertex>::iterator it1=vList.begin();
	triangle t1;
	t1.one = start;
	advance(it1,1);
	t1.two = *it1;
	advance(it1,1);
	t1.three = *it1;
	tList.push_back(t1);*/
}

void mouse( int button, int state, int x, int y )
{ 
	if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
  	{
        //tests if the polygon is not built and there is at least one vertex built
		if(poly == false && vList.size() > 0)
		{
			vertex prev_v = *prev(vList.end());
			vertex v;
			v.x = x;
			v.y = WINDOW_MAX_Y -y;
			vList.push_back(v); //stores the screen coordinates
			//lList.push_back(v);
			printf("v: %d   %d\n", x,y);
			linseg l;
			linseg prev_l = *prev(LList.end());
			l.one = prev_v;
			l.two = v;
			bool ib1=false;
			for(list<linseg>::iterator it=LList.begin(); it!=LList.end(); it++)
			{
				ib1 = linIntersect(l,*it);
				//there is an intersect present with the current linseg and the one being tested and resets the bool
				if(ib1 == true)
				{
					cout << "there is an intersect with the last linseg drawn." << endl;
					ib1 = false;
				}
		
			}
			LList.push_back(l);
			Determinant2(prev_v,v);
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
    if ((key == 'f' || key == 'F') && poly == true) {
        //draw polygon filled in with no tesselation
        fillPoly(LList);
    }
    if ((key == 't' || key == 'T') && poly == true) {
        //show the triangles used in the tesselation and the areas of the triangles IN THE ORDER THEY ARE DRAWN
        tess(vList,tList);
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

