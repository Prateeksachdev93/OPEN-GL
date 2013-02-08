#include <iostream>
#include<cstdio>
#include <stdlib.h> //Needed for "exit" function

#include "person.h"
#include "room.h"
#include "floor.h"
#include "imageloader.h"
#include "gifts.h"
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




using namespace std;
int gift_count=0;
float i;
int k=0;
float tile_rise[4];
GLuint _displayListId_blackArea; //The OpenGL id of the display list

GLuint _displayListId_whiteArea; //The OpenGL id of the display list
float tile_x[4]={0},tile_z[4]={0};//default height tile coordinates
int holes=3;
float width_screen,height_screen;
int tile_up=1;
float backup=0.0;
int holeslist[3];
int helicopter_view=0;
float helicopter_x=0.0;
float helicopter_y=15.0,helicopter_z=15.0;
/******
 
 OBJECTS OF VARIOUS CLASSES
 
 ******/


Person p;
gifts g;
fl f;
room r;

void handleKeypress(unsigned char key,int x,int y)

{
    
    switch(key)
    
    {
            
        case 27:
        {
            printf("*************Your Score= %d***********\n",gift_count);
            exit(0);
        }
        case 'j':
        {
            p.jump=1;
            break;
        }
        case 'l':
        {
            p.changelook+=1;
            break;
        }
        case 'h':
        {
            helicopter_view=(helicopter_view + 1)%2;
            break;
        }
            case 'w':
        {
            helicopter_z-=0.5;
            break;
        }
            
        
	    case 's':
        {
            helicopter_z+=0.5;
            break;
        }
            case 'd':
        {
            helicopter_x+=0.5;
            break;
        }
            case 'f':
        {
            helicopter_x-=0.5;
            break;
        }
        case 'a':
        {
            helicopter_x-=0.5;
            break;
        }
        case 'q':
        {
            helicopter_y+=0.5;
            break;
        }
        case 'e':
        {
            helicopter_y-=0.5;
            break;
        }

            
    }
    
}



void handleResize(int w,int h)

{
    
    glViewport(0,0,w,h);
    width_screen=w;
    height_screen=h;
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    gluPerspective(45.0,(double)w/(double)h,1.0,200);

    gluLookAt(0.0f,15.5f, 15.0f,
              
              0.0f,0.0f,0.0f,
              
              0.0f,1.0f,0.0f);
  //  printf("handle\n");
            
    
    
}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}



void initRendering()

{
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_COLOR_MATERIAL);

    
    glClearColor(0.0f,0.0f,0.2f,1.0f);
    glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0

    
    //Set up a display list for drawing a cube
    
    _displayListId_blackArea = glGenLists(1); //Make room for the display list
    
    glNewList(_displayListId_blackArea, GL_COMPILE); //Begin the display list
    
    r.draw_BlackArea(); //Add commands for drawing a black area to the display list
    
    glEndList(); //End the display list
    
    
    
    //Set up a display list for drawing a cube
    
    _displayListId_whiteArea = glGenLists(2); //Make room for the display list
    
    glNewList(_displayListId_whiteArea, GL_COMPILE); //Begin the display list
    
    r.draw_whiteArea(); //Add commands for drawing a black to the display list
    
    glEndList(); //End the display list
    
    Image* image = loadBMP("grass.bmp");
	_textureId = loadTexture(image);
    delete image;
    Image* image2 = loadBMP("wat1.bmp");
    _textureId2 = loadTexture(image2);
    delete image2;
    
    Image* image3 = loadBMP("wall1.bmp");
    _textureId3 = loadTexture(image3);
    delete image3;

}

void drawScene()

{
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    GLfloat ambientColor[] = {0.8f, 1.0f, 0.8f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	//Add directed light
	//GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	//GLfloat lightPos0[] = {-5.0f, 10.0f, -5.0f, 0.0f};
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    p.drawPerson();
   // p1.drawPerson();
    
    glTranslatef(-4*1.5, 0.0, 4*1.5);
    
   
   //******** printf("man coordinates %f %f\n******************\n",(p.manx+14)*0.4,(p.manz-14)*0.4);
    int x,block=0;
    
    for(float j=10.0;j>(-15*1.5);j-=1.5)
        
    {
        
        
        
        for(i=-width_screen/2;i<width_screen/2;i+=1.5)
        {
            
            
                
                glPushMatrix();
                
                
                glTranslatef(i,-1.0,j);
                
                
                f.draw_BlackArea();
                
                
                glPopMatrix();
                
                
                
        
            
        }
        
    }
    
        /**************
            DRAW WALL
         **************/
    
    
    for(float j=0.0;j>(-8*1.5);j-=1.5)
        
    {
        
        k++;
        
        for(i=0.0;i<(4*3.0);i+=3.0)
            
        {
            
            block++;
            if(block==tile_rise[0] || block==tile_rise[1] || block==tile_rise[2] || block==tile_rise[3])
            {
                tile_height=backup;

                if(tile_height<1 && tile_up)
                    tile_up=1;
                else
                    tile_up=0;
                

              
                
            }

            for( x=0;x<holes;x++)
            {
                if(holeslist[x]==block)
                {

                    break;
                }
        }
            
            
            /*******************
                        MAKE GIFTS
             **************************/
             
            if((p.manx+14)*0.4 >= g.x-0.5 &&(p.manx+14)*0.4 <= g.x+0.5 && (p.manz-14)*0.4>=g.z-0.5 && (p.manz-14)*0.4<=g.z+0.5)
            {
                gift_count++;
                g.set_gift_coord();
                g.make_gift();
                
            }
            else
            {
                g.make_gift();
            }
                
            
            
            
            
            
            
            /************
             
             WALL DETECTION
             **************/

            
                
               if((p.manx+14)*0.4 < 0  && !((p.manz-14)*0.4<=-3 && (p.manz-14)*0.4>=-4.5) &&  !((p.manz-14)*0.4<=-9 && (p.manz-14)*0.4>=-10.5)  )
            {
                p.manx+=0.05;
            // p.fall=1;
            }
            else if((p.manx+14)*0.4 < 0)
                 p.fall=1;
            if((p.manx+14)*0.4>11  && !((p.manz-14)*0.4<=-3 && (p.manz-14)*0.4>=-4.5) && !((p.manz-14)*0.4<=-9 && (p.manz-14)*0.4>=-10.5) )
             {
                p.manx-=0.05;
             }
             else if((p.manx+14)*0.4>11 )
                 p.fall=1;
            if((p.manz-14)*0.4 >0 && !((p.manx+14)*0.4>=3 && (p.manx+14)*0.4<=4.5) && !((p.manx+14)*0.4>=9 && (p.manx+14)*0.4<=10.5))
            {
                p.manz-=0.05;
             //   p.fall=1;
            }
             else if((p.manz-14)*0.4 >0 )
                p.fall=1;
            if((p.manz-14)*0.4 < -11 && !((p.manx+14)*0.4>=3 && (p.manx+14)*0.4<=4.5) && !((p.manx+14)*0.4>=9 && (p.manx+14)*0.4<=10.5))
            {
                p.manz+=0.05;
                //   p.fall=1;
            }
            else if((p.manz-14)*0.4 < -11 )
                p.fall=1;
            
            
            
            
            
            
            /******************
             MIDDLE WALL DETECTION
             
             ********************/
            if((p.manx+14)*0.4<=6.5 && (p.manx+14)*0.4>=5 && ((int)p.mrotate/90)%4==1 && !((p.manz-14)*0.4<=-3 && (p.manz-14)*0.4>=-4.5) &&  !((p.manz-14)*0.4<=-9 && (p.manz-14)*0.4>=-10.5))
                p.manx-=0.05;
            
            if((p.manz-14)*0.4>=-6.5 && (p.manz-14)*0.4<=-5 && ((int)p.mrotate/90)%4==2 && !((p.manx+14)*0.4>=3 && (p.manx+14)*0.4<=4.5) && !((p.manx+14)*0.4>=9 && (p.manx+14)*0.4<=10.5))
                p.manz+=0.05;

            if((p.manx+14)*0.4<=6.5 && (p.manx+14)*0.4>=5 && ((int)p.mrotate/90)%4==3 && !((p.manz-14)*0.4<=-3 && (p.manz-14)*0.4>=-4.5) &&  !((p.manz-14)*0.4<=-9 && (p.manz-14)*0.4>=-10.5))
                p.manx+=0.05;
            
            if((p.manz-14)*0.4>=-6.5 && (p.manz-14)*0.4<=-5 && ((int)p.mrotate/90)%4==0 && !((p.manx+14)*0.4>=3 && (p.manx+14)*0.4<=4.5) && !((p.manx+14)*0.4>=9 && (p.manx+14)*0.4<=10.5))
                p.manz-=0.05;
           
            
                    
            
            
            
            /************
             
             HOLES DETECTION
             
             **************/
            
            if(x<holes && k%2==0)
            {

                if((p.manx+14)*0.4>i-0.5 &&  (p.manx+14)*0.4< i+1.5 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5 && p.jump!=1)
                {   // printf("p.fall\n");
                    p.fall=1;
                }
            }
            else if(x<holes && k%2!=0)
            {

                if((p.manx + 14)*0.4>i+1.5-0.5 && (p.manx+14)*0.4 < i+3 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5 && p.jump!=1)
                {
                    p.fall=1;
                }
                
            }
            
            /************
             
             BLOCK DETECTION
             ********************/
            if(tile_height>0.1 && k%2==0)
            {
                if((p.manx + 14)*0.4>i-0.5 && (p.manx+14)*0.4 < i+1.5 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5)
                {
                    if(((int)p.mrotate/90)%4==1 )
                        p.manx-=0.55;
                    if(((int)p.mrotate/90)%4==2 )
                        p.manz+=0.55;
                    if(((int)p.mrotate/90)%4==3 )
                        p.manx+=0.55;
                    if(((int)p.mrotate/90)%4==0 )
                        p.manz-=0.55;
                }
                
            }
            
            /***********************
             
             DETECT COLLISION WITH BLOCKS
             
             **********************/
            if(tile_height>0.1 && k%2!=0)
            {
                if((p.manx + 14)*0.4>i+1.5-0.5 && (p.manx+14)*0.4 < i+3 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5)
                {
                    if(((int)p.mrotate/90)%4==1 )
                        p.manx-=0.55;
                    if(((int)p.mrotate/90)%4==2 )
                        p.manz+=0.55;
                    if(((int)p.mrotate/90)%4==3 )
                        p.manx+=0.55;
                    if(((int)p.mrotate/90)%4==0 )
                        p.manz-=0.55;
                }
                
            }
            

            
            if(k%2==0 && x>=holes)
                
            {
                
                glPushMatrix();
                
                glTranslatef(i,0.0,j);
                
                
                r.draw_BlackArea();
                

                
                glPopMatrix();
                
                
                
            }
            
            else if(x>=holes)
            {
                
                glPushMatrix();

                glTranslatef(i+1.5,0.0,j);
                
                
                r.draw_BlackArea();
                
                
                glPopMatrix();
                
                
                
            }
            tile_height=0;
        }
        
    }
    
    for(float j=0.0;j>(-8*1.5);j-=1.5)
        
    {
        
        k++;
        
        for(i=0.0;i<(4*3.0);i+=3.0)
            
        {
            block++;
            if(block==tile_rise[0] || block==tile_rise[1] || block==tile_rise[2] || block==tile_rise[3])
            {
                tile_height=backup;

                    if(tile_height<1 && tile_up)
                        tile_up=1;
                    else
                        tile_up=0;
                                
                
            }

            for( x=0;x<holes;x++)
                if(holeslist[x]==block)
                    break;
            
            
            /**********
             
             HOLES DETECTION
             
             *************/
            
            
            if(x<holes && k%2!=0)
            {

                if((p.manx +14)*0.4 >i-0.5 &&  (p.manx +14)*0.4 < i+1.5 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5 && p.jump!=1)
                {
                    p.fall=1;
                }
            }
            else if(x<holes && k%2==0)
            {

                if((p.manx +14)*0.4 >i+1.5-0.5 && (p.manx +14)*0.4 < i+3 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5 && p.jump!=1)
                { //  printf("p.fall\n");
                    p.fall=1;
                }
                
            }

            
            
            /************
             
             BLOCK DETECTION
             ********************/
            
            if(tile_height>0.1 && k%2!=0)
            {
                if((p.manx + 14)*0.4>i-0.5 && (p.manx+14)*0.4 < i+1.5 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5)
                {
                    if(((int)p.mrotate/90)%4==1 )
                        p.manx-=0.55;
                    if(((int)p.mrotate/90)%4==2 )
                        p.manz+=0.55;
                    if(((int)p.mrotate/90)%4==3 )
                        p.manx+=0.55;
                    if(((int)p.mrotate/90)%4==0 )
                        p.manz-=0.55;
                }
                
            }

            
            if(tile_height>0.1 && k%2==0)
            {
                if((p.manx + 14)*0.4>i+1.5-0.5 && (p.manx+14)*0.4 < i+3 && (p.manz-14)*0.4>j-1.5 && (p.manz-14)*0.4<j+0.5)
                {
                    if(((int)p.mrotate/90)%4==1 )
                        p.manx-=0.55;
                    if(((int)p.mrotate/90)%4==2 )
                        p.manz+=0.55;
                    if(((int)p.mrotate/90)%4==3 )
                        p.manx+=0.55;
                    if(((int)p.mrotate/90)%4==0 )
                        p.manz-=0.55;
                }
                
            }

            
            
            
            if(k%2!=0 && x>=holes)
                
            {
                
                glPushMatrix();

                
                glTranslatef(i,0.0,j);
                
                
                r.draw_whiteArea();
                
                              
                glPopMatrix();
                
                
                
            }
            
            else if(x>=holes)
            {
                
                glPushMatrix();
                               glTranslatef(i+1.5,0.0,j);
                
                
                r.draw_whiteArea();
                
                glPopMatrix();
                
                
                
            }
            tile_height=0;
        }
        
    }
    tile_rise_count=0;
    
    r.construct_four_walls();//constructing wall around room
    
    
    glutSwapBuffers();
    
    
    
    
    
    
    
}
float up=0;
void update(int value) {

    
    glutPostRedisplay();

    
    srand ( time(NULL) );
    for(int i=0;i<holes;i++)
    {
        holeslist[i]=rand()%64;
    }
    


    glutTimerFunc(3000, update, 0);
    
}

void update3(int value)
{
    glutPostRedisplay();

    if(p.jump==1)
    {
        if(((int)p.mrotate/90)%4==3)
        {
            p.manx-=0.55;
        }
        if(((int)p.mrotate/90)%4==1)
        {
            p.manx+=0.55;
        }
        if(((int)p.mrotate/90)%4==2)
        {
            p.manz-=0.55;
        }
        if(((int)p.mrotate/90)%4==0)
        {
            p.manz+=0.55;
        }
        if(p.height<1 && up==0)
        {
            p.height+=0.3;
        }
        if(p.height>1 && up==0){
            up=1;
            // printf("yo");
        }
        if(p.height>0 && up==1)
        {
            p.height-=0.3;
            //printf("hehe");
        }
        if(p.height<0 && up==1)
        {
            p.jump=0;
            up=0;
        }
        //printf("%f\n",p.height);
        
    }
    if(p.fall==1)
        p.height-=1.0;
    
 
    glutTimerFunc(100, update3, 0);

        
}
void update4(int value)
{
    if(tile_up)
    {
        backup+=0.1;
    }
    else
    {
        backup-=0.1;
        if(backup<=0)
            tile_up=1;
    }
    glutTimerFunc(1000, update4, 0);

    
}
void update2(int value)
{
    glViewport(0,0,width_screen,height_screen);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    gluPerspective(45.0,(double)width_screen/(double)height_screen,1.0,200);
    if(helicopter_view==1)
    {
        gluLookAt(helicopter_x,helicopter_y, helicopter_z,
                  
                  0.0,0.0, 0.0,
                  
                  0.0f,1.0f,0.0f);
        
    }
    else
    {
    if(p.changelook%3==0)
    {
   //     printf("look\n");
        gluLookAt(0.0f,15.5f, 15.0f,
                  
                  0.0f,0.0f,0.0f,
                  
                  0.0f,1.0f,0.0f);

    }
    else if(p.changelook%3==1)
    {
        gluLookAt(0.0f,15.5f, -2.0f,
                  
                  0.0f,0.0f,0.0f,
                  
                  0.0f,1.0f,0.0f);
    }
    else
    {
      //  printf("look change\n");
        if(((int)p.mrotate/90)%4==0)
        {
        //    printf("look change1\n");
            gluLookAt((p.manx)*0.4,5.5f+p.height, (p.manz)*0.4,
                      
                      (p.manx)*0.4,3.0f+p.height, (p.manz)*0.4+2,
                      
                      0.0f,1.0f,0.0f);
            
        }
        else if(((int)p.mrotate/90)%4==1)
        {
          //  printf("look change2\n");
            gluLookAt((p.manx)*0.4,5.5f+p.height, (p.manz)*0.4,
                      
                      0.4*(p.manx)+2,3.0f+p.height, (p.manz)*0.4,
                      
                      0.0f,1.0f,0.0f);
            
        }
        else if(((int)p.mrotate/90)%4==2)
        {
           // printf("look change3\n");
            gluLookAt(0.4*(p.manx),5.5f+p.height, 0.4*(p.manz),
                      
                      0.4*(p.manx),3.0f+p.height, 0.4*(p.manz)-2,
                      
                      0.0f,1.0f,0.0f);
            
        }
        else if(((int)p.mrotate/90)%4==3)
        {
           // printf("look change4\n");
            gluLookAt(0.4*(p.manx),5.5f+p.height, 0.4*(p.manz),
                      
                      0.4*(p.manx)-2,3.0f+p.height, 0.4*(p.manz),
                      
                      0.0f,1.0f,0.0f);
            
        }
        
    }
    }
    glutTimerFunc(10, update2, 0);

}




void handleKeypress2(int key, int x, int y) {
    if (p.legangle==30)
        p.legangle=-30;
    else
        p.legangle=30;
    if (key == GLUT_KEY_LEFT)
    {
        p.mrotate+=90;
        //        manx-=0.5;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        p.mrotate+=270;
        //      manx+=0.5;
    }
    if (key == GLUT_KEY_UP)
    {
        //mrotate=180;
        if(((int)p.mrotate/90)%4==0)
            p.manz+=0.5;
        if(((int)p.mrotate/90)%4==1)
            p.manx+=0.5;
        if(((int)p.mrotate/90)%4==2)
            p.manz-=0.5;
        if(((int)p.mrotate/90)%4==3)
            p.manx-=0.5;
        
        //    manz-=0.5;
    }
    if (key == GLUT_KEY_DOWN)
    {
        p.mrotate+=180;
        //    manz+=0.5;
    }
    if(key=='w')
        printf("w pressed");
}
int main(int argc,char** argv)

{
    
    glutInit(&argc,argv);
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    
    glutInitWindowSize(800,800);
    
    
    
    glutCreateWindow("assignment2");
    
    initRendering();
    
    glutFullScreen();
    srand(time(NULL));
    for(int i=0;i<4;i++)
        tile_rise[i]=rand()%64;
    
    glutDisplayFunc(drawScene);
    
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleKeypress2);
    glutReshapeFunc(handleResize);
    
    glutTimerFunc(3000, update, 0);
    glutTimerFunc(10, update2, 0);
    glutTimerFunc(100, update3, 0);
    glutTimerFunc(1000, update4, 0);


    
    
    
    glutMainLoop();
    
    
    
    return 0;
    
    
    
}

