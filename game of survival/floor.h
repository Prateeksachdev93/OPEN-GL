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


#include "imageloader.h"

GLuint _textureId2; //The id of the texture
class fl
{
public:
    
    void draw_BlackArea()
    
    {
        
        // glPushMatrix();
        
        glColor3f(1.0f,1.0f,1.0f);
        
        
        //glTranslatef(1.5f,0.0f,0.0f);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        
        //Bottom
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        
        
        glBegin(GL_QUADS);
        //******************* printf("p.height %f\n",tile_height);
        
        //     glColor3f(0.22f,0.69f,0.87f);//summer blue color
        
        
       glTranslatef(0.0f,0.0f,0.0f);
        
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.50f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.5f,0.3f+tile_height,0.0f);
        
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f,0.3f+tile_height,0.0f);
        
        glEnd();
        
        
        
        glBegin(GL_QUADS);
        
        
        //  glColor3f(0.22f,0.69f,0.87f);//summer blue color
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,-1.5f);
        
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f,-1.5f);
        
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f,0.3f,0.0f);
        
        glEnd();
        
        
                
        
        glBegin(GL_QUADS);
        
        //    glColor3f(0.22f,0.69f,0.87f);//summer blue color
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(1.5f,0.0f,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.5f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f,0.0f);
        
        glEnd();
                
        glBegin(GL_QUADS);
        
        //      glColor3f(0.22f,0.69f,0.87f);//summer blue color
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f,-1.5f);
        
        glEnd();
        
        
        
        
        glBegin(GL_QUADS);
        
        //        glColor3f(0.5f,0.5f,0.5f);
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.0f,0.0f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.0f,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.0f,-1.5f);
        
        glEnd();
        
        
        
        
        glBegin(GL_QUADS);
        
        //        glColor3f(0.5f,0.5f,0.5f);
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.3f,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.3f,0.0f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f,-1.5f);
        
        glEnd();
        
        //    glPopMatrix();
        
        
        glDisable(GL_TEXTURE_2D);
        
    }
    
    
};
