#include <iostream>
#include <stdlib.h> //Needed for "exit" function
//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

#include <iostream>
#include<time.h>
#include <cmath>


class gifts{
public:
    float x,z,angle;
    
    gifts()
    {
        x=rand()%12;
        z=(rand()%12)*(-1);
        angle=0;

    }
    void make_gift()
    {
        glPushMatrix();
        
        srand ( time(NULL) );
        angle++;
        
        
        //glColor3f(1/(rand()%3+1), 1/(rand()%3+0.5), 1/(rand()%3+0.3));
        glColor3f(1.0,1.0,1.0);
        glTranslatef(x, 1.0f, z);
        glRotatef(angle,0,1,0);
        
        glBegin(GL_LINE_LOOP); // Drawing a star by using 10 vertices for the outer rims of a star
        glVertex3f (0, 0.5, 0); //Specify the next 10 vertices
        glVertex3f (-0.2, 0.2, 0); //Specify the next 10 vertices
        glVertex3f (-0.5, 0.1, 0);
        glVertex3f (-0.2, -0.1, 0);
        glVertex3f (-0.3, -0.5, 0);
        glVertex3f (0, -0.2, 0);
        glVertex3f (0.3, -0.5, 0);
        glVertex3f (0.2, -0.1, 0);
        glVertex3f (0.5, 0.1, 0);
        glVertex3f (0.2, 0.2, 0);
        glVertex3f (0, 0.5, 0);
        glEnd(); //
        
        glBegin(GL_LINES); //Draw 10 lines radiating from (0,0,0) to each vertice
        glVertex3f (0, 0.5, 0); //1st vertix to connect the origin to form a line
        glVertex3f (0, 0, 0);
        glVertex3f (-0.2, 0.2, 0); //2nd vertix
        glVertex3f (0, 0, 0);
        glVertex3f (-0.5, 0.1, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (-0.2, -0.1, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (-0.3, -0.5, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (0, -0.2, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (0.3, -0.5, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (0.2, -0.1, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (0.5, 0.1, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (0.2, 0.2, 0);
        glVertex3f (0, 0, 0);
        glColor3f (0.5, 0.5, 1.0); //Set the color to blue
        glVertex3f (0, 0.5, 0);// last vertix
        glVertex3f (0, 0, 0);
        glEnd();
        
        glutSolidSphere( 0.1, 20.0, 20.0);
        
        glPopMatrix();
    }
    void set_gift_coord()
    {
        
        x=rand()%12;
        z=(rand()%12)*(-1);
        
      /*  while(x>=5.5 && x<= 7.5 && z<=-5.5 && z>=-7.5)
        {
            
            x=rand()%12;
            z=(rand()%12)*(-1);
            
        }*/
    }
    
};
