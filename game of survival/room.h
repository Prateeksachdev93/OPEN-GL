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

float tile_height=0.0;
int tile_rise_count=0;
GLuint _textureId; //The id of the texture
GLuint _textureId3; //The id of the texture

class room
{
public:
    
    void draw_BlackArea()
    
    {
        
        // glPushMatrix();
        if(tile_height==0)
            glColor3f(0.8f,0.4f,0.1f);
        else
            glColor3f(0.0f,0.0f,0.0f);


        
        //glTranslatef(1.5f,0.0f,0.0f);
        
    

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
        
        
  
     

      //  glColor3f(0.22f,0.69f,0.87f);//summer blue color

        glTexCoord2f(0.0f, 0.0f);

        glVertex3f(0.0f,0.0f,0.0f);

        glTexCoord2f(1.0f, 0.0f);

        glVertex3f(0.0f,0.0f,-1.5f);

        glTexCoord2f(1.0f, 1.0f);

        glVertex3f(0.0f,0.3f+tile_height,-1.5f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f,0.3f+tile_height,0.0f);
        
        glEnd();
        
        
        glBegin(GL_QUADS);
        
    //    glColor3f(0.22f,0.69f,0.87f);//summer blue color
        
        glTexCoord2f(0.0f, 0.0f);

        glVertex3f(1.5f,0.0f,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.5f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,0.0f);
        
        glEnd();
        
                
        glBegin(GL_QUADS);
        
  //      glColor3f(0.22f,0.69f,0.87f);//summer blue color
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f+tile_height,-1.5f);
        
        glEnd();
        if(tile_height==0)
            glColor3f(1.0f,1.0f,1.0f);
        else
            glColor3f(0.3f,0.4f,0.5f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        
        //Bottom
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        
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

        glVertex3f(0.0f,0.3f+tile_height,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.3f+tile_height,0.0f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f+tile_height,-1.5f);
        
        glEnd();
        
        //    glPopMatrix();
        
        
        glDisable(GL_TEXTURE_2D);

    }
    
    void draw_whiteArea()
    
    {
        
        
        
        if(tile_height==0)
            glColor3f(0.8f,0.4f,0.1f);
        else
            glColor3f(0.0f,0.0f,0.0f);


        // glPushMatrix();

        glBegin(GL_QUADS);
        
        
      //  glColor3f(0.62352f,0.372549f,0.623529f);//blue violet
      
        glTranslatef(0.0f,0.0f,0.0f);
        glTexCoord2f(0.0f, 0.0f);

        glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.0f,0.0f);
        glTexCoord2f(1.0f, 1.0f);
        //****************  printf("p.height %f\n",tile_height);
        glVertex3f(1.5f,0.3f+tile_height,0.0f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f+tile_height,0.0f);
        
        glEnd();
        
        
        
        
//        glColor3f(0.62352f,0.372549f,0.623529f);//blue violet
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0f, 0.0f);
      
        glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord2f(0.1f, 0.0f);
        
        glVertex3f(0.0f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f+tile_height,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f+tile_height,0.0f);
        
        glEnd();
        
        
        
        
        
        glBegin(GL_QUADS);
        
//        glColor3f(0.62352f,0.372549f,0.623529f);//blue violet
        glTexCoord2f(0.0f, 0.0f);
      
        glVertex3f(1.5f,0.0f,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.5f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,0.0f);
        
        glEnd();
        
        
        
        glBegin(GL_QUADS);
        
//        glColor3f(0.62352f,0.372549f,0.623529f);//blue violet
        glTexCoord2f(0.0f, 0.0f);

        glVertex3f(0.0f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.0f,-1.5f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f+tile_height,-1.5f);
        
        glEnd();
        
        
        
        
        if(tile_height==0)
            glColor3f(1.0f,1.0f,1.0f);
        else
            glColor3f(0.3f,0.4f,0.5f);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        
        //Bottom
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBegin(GL_QUADS);
        
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
        
//       glColor3f(1.0f,1.0f,1.0f);
        glTexCoord2f(0.0f, 0.0f);
      
        glVertex3f(0.0f,0.3f+tile_height,0.0f);
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.50f,0.3f+tile_height,0.0f);
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.3f+tile_height,-1.5f);
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.3f+tile_height,-1.5f);
        
        glEnd();
        
        // glPopMatrix();
        
        
                glDisable(GL_TEXTURE_2D);
    }
    void draw_wall()
    {
        
 
        glColor3f(1.0f,1.0f,1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId3);
        
        //Bottom
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.5f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,0.0f,0.5f);
        
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f,0.0f,0.5f);
        
        glEnd();
        
        
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(0.0f,2.5f,0.0f);
        
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,2.5f,0.0f);
        
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(1.5f,0.0f,0.0f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(1.5f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.5f,2.5f,0.0f);
        
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,2.5f,0.5f);
        
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(1.5f,0.0f,0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(0.0f,2.5f,0.0f);
        
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(0.0f,2.5f,0.5f);
        
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(0.0f,0.0f,0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,0.0f,0.5f);
        
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(0.0f,2.5f,0.5f);
        
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,2.5f,0.5f);
        
        glTexCoord2f(0.0f, 1.0f);
        
        glVertex3f(1.5f,0.0f,0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(0.0f,2.5f,0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        
        glVertex3f(1.5f,2.5f,0.0f);
        
        glTexCoord2f(1.0f, 1.0f);
        
        glVertex3f(1.5f,2.5f,0.5f);
        
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f,2.5f,0.5f);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);

        
         
    }
    void construct_wall()
    {
        float j=0.0,i;
        for(i=0.0;i<(4*3.0)/2;i+=1.5)
            
        {
            if(i!=3)
            {
            glPushMatrix();
            
            glTranslatef(i,0.0,j);
            draw_wall();
            
            
            glPopMatrix();
            }
            
        }
        
        i=6;
        
        for(j=0.0;j>(-8*1.5)/2;j-=1.5)
        {
            
            if(j!=-3)
            {
            glPushMatrix();
            
            glTranslatef(i,0.0,j);
            glRotatef(90,0,1,0);
            draw_wall();
            glPopMatrix();
            }
            
            
        }
        j=-4*1.5;
        for(i=0.0;i<(4*3.0)/2;i+=1.5)
            
        {
            if(i!=3)
            {
            glPushMatrix();
            
            glTranslatef(i,0.0,j);
            draw_wall();
            
            
            glPopMatrix();
            }
            
        }
        i=-0.5;
        
        for(j=0.0;j>(-8*1.5)/2;j-=1.5)
        {
            
            if(j!=-3)
            {
            glPushMatrix();
            
            glTranslatef(i,0.0,j);
            glRotatef(90,0,1,0);
            draw_wall();
            
            
            glPopMatrix();
            }
            
        }


        
    }
    void construct_four_walls()
    {
        float i=0,j=0;
        
        glPushMatrix();
        
        glTranslatef(i,0.0,j);
        construct_wall();
        
        
        glPopMatrix();
        
        
        j=0.0,i=6;
        
        glPushMatrix();
                
        glTranslatef(i,0.0,j);
        construct_wall();
                
                
        glPopMatrix();
        
        
        i=0,j=-6;
        
        glPushMatrix();
        
        glTranslatef(i,0.0,j);
        construct_wall();
        
        
        glPopMatrix();
        
        i=0,j=0;
        
        glPushMatrix();
        
        glTranslatef(i,0.0,j);
        construct_wall();
        
        
        glPopMatrix();
        
        i=6,j=-6;
        
        glPushMatrix();
        
        glTranslatef(i,0.0,j);
        construct_wall();
        
        
        glPopMatrix();
        
        
        
        
    }

    
    
};
