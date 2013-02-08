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


class Person{
public:
    float x,y,z;
    float legangle;
    float mrotate;//angle by which man is rotated
    float manx,manz;
    int changelook;
    int fall;
    float jump;
    float height;
    
    Person()
    {
        legangle=10;
        mrotate=180;
        manx=-14.0;
        manz=14.0;
        changelook=0;
        fall=0;
        jump=0;
        height=0.0;
        
    }
	void drawPerson (void) {
        
		glPushMatrix();
		//person
        
        
        //glTranslatef(0.0f, 0.05f, -10.0f);//to place the man at the right position
        glScalef(0.4,0.4,0.4);
        glTranslatef(manx, 2.6f+height, manz);
        glRotatef(mrotate,0.0f, 1.0f, 0.0f);
        glPushMatrix();
		glTranslatef(0.0f, 3.0f, 0.0f);
		glColor3f(0.8, 1.0, 0.4);
		//head
		glutSolidSphere( 1.0, 20.0, 20.0);
        //eyes
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(0.2f,0.0f, 1.2f);
        glutSolidSphere( 0.1, 20.0, 20.0);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(-0.2f,0.0f, 1.2f);
        glutSolidSphere( 0.1, 20.0, 20.0);
        glPopMatrix();
        
		//body
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
        glTranslatef(0.0f,-0.7f, 0.0f);
		glRotatef(90.0f,1.0f, 0.0f, 0.0f);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		
		gluCylinder(quadratic,0.5f,1.2f,2.7f,100,100);
        
		//right shoulder
        glColor3f(0.5, 0.2, 0.4);
		glPushMatrix();
		
        glRotatef(legangle,1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f,0.1f, 0.0f);
		glRotatef(-60.0f,0.0f, 1.0f, 0.0f);
        
		GLUquadricObj *quadratic1;
		quadratic1 = gluNewQuadric();
		gluCylinder(quadratic1,0.2f,0.2f,2.2f,32,32);
		glPopMatrix();
        
        
		//right leg
        glColor3f(0.4, 0.2, 0.4);
        glPushMatrix();
        
		
        
        glTranslatef(0.6f,0.0f, 3.0f);
        glRotatef(-legangle,1.0f, 0.0f, 0.0f);
        
		GLUquadricObj *quadratic4;
		quadratic4 = gluNewQuadric();
		gluCylinder(quadratic4,0.2f,0.2f,1.5f,32,32);
		glPopMatrix();
		//left shoulder
        glColor3f(0.5, 0.2, 0.4);
        glPushMatrix();
        
        glRotatef(-legangle,1.0f, 0.0f, 0.0f);
        
        
		glTranslatef(0.0f,0.1f, 0.0f);
		glRotatef(60.0f,0.0f, 1.0f, 0.0f);
		GLUquadricObj *quadratic2;
		quadratic2 = gluNewQuadric();
		gluCylinder(quadratic2,0.2f,0.2f,2.2f,32,32);
		glPopMatrix();
        
		//left leg
        glColor3f(0.5, 0.2, 0.4);
        glPushMatrix();
        
        
		glTranslatef(-0.4f,-0.0f, 3.0f);
        glRotatef(legangle,1.0f, 0.0f, 0.0f);
		
		GLUquadricObj *quadratic3;
		quadratic3 = gluNewQuadric();
		gluCylinder(quadratic3,0.2f,0.2f,1.5f,32,32);
		glPopMatrix();
        
        glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		//glutWireCube(2);
	}
    
};
