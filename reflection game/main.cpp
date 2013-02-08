#include <iostream>
#include<cmath>
#include <stdlib.h> //Needed for "exit" function
#include<algorithm>
#include<cstdio>
#include<ctime>
//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
/*************************
 GLOBAL VARIABLES
 **************************/
#define s 1
using namespace std;
int c=0;
int r=0,l=0;
int mode3=0;
int nlines,nproj;
int total=0;
float dist;
float txy=0.1;
float linesxy[500][4];
float blocksxy[500][4];
float projxy[500][4];
float projpoint[500][2];
int nblocks;
int mode3count=0;

int projlines;
float projx1,projy1,projx2,projy2;
float projpointx,projpointy;
float mirrorx,mirrory;
float windowWidth, windowHeight;
int mode4=0;
float cdtheta=-0.01,ldtheta=0.01;
int randm=0;

/**********************
 FUNCTON TO FIND LENGTH OF LINE SEGMEN BETWEEN TWO POINTS
 ************************/
float length (float x1,float y1,float x2 , float y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
/**********************
FUNCTION TO SAVE THE PRESENT STATE IN A FILE NAMED 'output'
 ************************/
void savefile()
{
    int i;
    freopen("output","w",stdout);
    printf("%f %f\n",windowWidth, windowHeight);
	printf("%d\n",nproj);
    for(i=0;i<nproj;i++)
		printf("%f %f %f %f\n",projxy[i][0],projxy[i][1],projxy[i][2],projxy[i][3]);
    printf("%f\n",dist);
    printf("%d\n",projlines);
    printf("%d\n",nblocks);
    for(i=0;i<nblocks;i++)
		printf("%f %f %f %f\n",blocksxy[i][0],blocksxy[i][1],blocksxy[i][2],blocksxy[i][3]);
	total=nlines+nblocks+1;//+1 for one projector
    
	
	printf("%d\n",nlines);
    for(i=0;i<nlines;i++)
		printf("%f %f %f %f\n",linesxy[i][0],linesxy[i][1],linesxy[i][2],linesxy[i][3]);
}
/**********************
 FUNTION TO SET THE PROJECTOR POINT
 ************************/
void setprojector(float xx1,float yy1,float xx2,float yy2,float dd,int x)
{
    
    float midx = (xx1 + xx2)/2;
    float midy = (yy1+yy2)/2;
    double theta = atan2((yy2-yy1),(xx2-xx1));
    projpoint[x][0] =(midx + (dd * sin(theta))) ,projpoint[x][1]= (midy - (dd * cos(theta)) );
}

/**********************
FUNCTION TO ADD NEW PROJECTOR ON PRESSING 'P'
 ************************/
void addprojector()
{
    nproj++;
    projxy[nproj-1][0]=-3;
    projxy[nproj-1][1]=-5;
            projxy[nproj-1][2]=3;
        projxy[nproj-1][3]=-5;
    setprojector(projxy[nproj-1][0],projxy[nproj-1][1],projxy[nproj-1][2],projxy[nproj-1][3],dist,nproj-1);
}
/**********************
 FUNCTION TO ADD NEW BLOCK ON PRESSING 'B'
 ************************/

void addblock()
{
    nblocks++;
    blocksxy[nblocks-1][0]=-3;
    blocksxy[nblocks-1][1]=+5;
    blocksxy[nblocks-1][2]=3;
    blocksxy[nblocks-1][3]=+5;
    
}
/**********************
 FUNCTION TO ADD NEW MIRROR ON PRESSING 'M'
 ************************/

void addmirror()
{
    nlines++;
    linesxy[nlines-1][0]=-4;
    linesxy[nlines-1][1]=6;
    linesxy[nlines-1][2]=0;
    linesxy[nlines-1][3]=6;
    
}
/**********************
 FUNCTION TO ADD HANDLE PRESSING OF A KEY
 ************************/

void handleKeypress(unsigned char key, //The key that was pressed
						int x, int y) {    //The current mouse coordinates
	//printf("%c",key);
	switch (key) {
		case 'q':{
            savefile();
            exit(0);
        }//Escape key
			 //Exit the program
		case 'c':
        {
            c++;
            break;
        }
            
		case 'r':
			{
                
			if(c<nproj)
			{
                
                float t1=projxy[c][2] + (projxy[c][0]-projxy[c][2])*cos(cdtheta)-(projxy[c][1]-projxy[c][3])*sin(cdtheta);
				float t2=projxy[c][3] + (projxy[c][0]-projxy[c][2])*sin(cdtheta)+(projxy[c][1]-projxy[c][3])*cos(cdtheta);
				projxy[c][0]= t1;
				projxy[c][1]= t2;
            
                
			}
			else if (c>=nproj&& c<nproj+nlines)
			{
				float t1=linesxy[c-nproj][2] + (linesxy[c-nproj][0]-linesxy[c-nproj][2])*cos(cdtheta)-(linesxy[c-nproj][1]-linesxy[c-nproj][3])*sin(cdtheta);
				float t2=linesxy[c-nproj][3] + (linesxy[c-nproj][0]-linesxy[c-nproj][2])*sin(cdtheta)+(linesxy[c-nproj][1]-linesxy[c-nproj][3])*cos(cdtheta);
				linesxy[c-nproj][0]= t1;
				linesxy[c-nproj][1]= t2;
			}
			else if (c>=nproj+nlines && c<nproj+nlines+nblocks)
			{
                int sub=nproj+nlines;
                float t1=blocksxy[c-sub][2] + (blocksxy[c-sub][0]-blocksxy[c-sub][2])*cos(cdtheta)-(blocksxy[c-sub][1]-blocksxy[c-sub][3])*sin(cdtheta);
				float t2=blocksxy[c-sub][3] + (blocksxy[c-sub][0]-blocksxy[c-sub][2])*sin(cdtheta)+(blocksxy[c-sub][1]-blocksxy[c-sub][3])*cos(cdtheta);
				blocksxy[c-sub][0]= t1;
				blocksxy[c-sub][1]= t2;
				
			}
                 break;
			}
               
		case 'l':
			{
                if(c<nproj)
                {
                    
                    float t1=projxy[c][2] + (projxy[c][0]-projxy[c][2])*cos(ldtheta)-(projxy[c][1]-projxy[c][3])*sin(ldtheta);
                    float t2=projxy[c][3] + (projxy[c][0]-projxy[c][2])*sin(ldtheta)+(projxy[c][1]-projxy[c][3])*cos(ldtheta);
                    projxy[c][0]= t1;
                    projxy[c][1]= t2;
                    
                    
                }
                else if (c>=nproj&& c<nproj+nlines)
                {
                    float t1=linesxy[c-nproj][2] + (linesxy[c-nproj][0]-linesxy[c-nproj][2])*cos(ldtheta)-(linesxy[c-nproj][1]-linesxy[c-nproj][3])*sin(ldtheta);
                    float t2=linesxy[c-nproj][3] + (linesxy[c-nproj][0]-linesxy[c-nproj][2])*sin(ldtheta)+(linesxy[c-nproj][1]-linesxy[c-nproj][3])*cos(ldtheta);
                    linesxy[c-nproj][0]= t1;
                    linesxy[c-nproj][1]= t2;
                }
                else if (c>=nproj+nlines && c<nproj+nlines+nblocks)
                {
                    int sub=nproj+nlines;
                    float t1=blocksxy[c-sub][2] + (blocksxy[c-sub][0]-blocksxy[c-sub][2])*cos(ldtheta)-(blocksxy[c-sub][1]-blocksxy[c-sub][3])*sin(ldtheta);
                    float t2=blocksxy[c-sub][3] + (blocksxy[c-sub][0]-blocksxy[c-sub][2])*sin(ldtheta)+(blocksxy[c-sub][1]-blocksxy[c-sub][3])*cos(ldtheta);
                    blocksxy[c-sub][0]= t1;
                    blocksxy[c-sub][1]= t2;
                    
                }
                break;
			}
            case 'f':
            {
                txy+=0.2;
                cdtheta-=0.2;
                ldtheta+=0.2;
                break;
            }
        case 's':
        {
            txy-=0.1;
            cdtheta+=0.1;
            ldtheta-=0.1;
            break;
        }
        case 'z':
        {
         randm=(randm+1)%2;
            break;
        }
        case 't':
        {
         mode3=(mode3+1)%2;
        
            break;
        }
            case 'g':
        {
                    mode4=(mode4+1)%2;
            break;
        }
        case 'p':
        {
            addprojector();
            break;
        }
        case 'm':
        {
            addmirror();
            break;
        }
        case 'b':
        {
            addblock();
            break;
        }
        }
}


/**********************
 FUNCTION TO HANDLE WNDOW RESIZE
 ************************/

void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}
/**********************
 FUNCTION TO DRAW MOTION LINE ON PRESSING OF 'T'
 ************************/

void specialdraw(float x1,float y1,float x2,float y2)
{
    glLineWidth(2);
    if(mode3count%2==0)
     glLineStipple(4, 0xf0f0);
    else
        glLineStipple(4, 0x0f0f);
    glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES); //Begin quadrilateral coordinates
    //	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(s*x1, s*y1);
	glVertex2f(s*x2, s*y2);
    
	glEnd(); //End quadrilateral coordinates
	glFlush();
}
/**********************
 FUNCTION TO DRAW REGULAR LINES
 ************************/

void drawline(float x1,float y1,float x2,float y2)
{

    glDisable(GL_LINE_STIPPLE);

    glLineWidth(2);
	glBegin(GL_LINES); //Begin quadrilateral coordinates

	glVertex2f(s*x1, s*y1);
	glVertex2f(s*x2, s*y2);

	glEnd(); //End quadrilateral coordinates
	glFlush();
}
/**********************
 FUNCTION TO DRAW BLOCKS
 ************************/

void drawblock(float x1,float y1,float x2,float y2)
{
	glBegin(GL_LINES); //Begin quadrilateral coordinates
	//glColor3f(0.0f,0.0f,1.0f);
	glVertex2f(s*x1, s*y1);
	glVertex2f(s*x2, s*y2);

	glEnd(); //End quadrilateral coordinates
	glFlush();
}
/**********************
 FUNCTION TO FIND SLOPE OF A LINE
 ************************/

float findslope(float x1,float y1,float x2,float y2)
{
	float m=(y2-y1)*1.0/(x2-x1);
	return m;
}
/**********************
 FUNCTION TO FIND Y COORDINATE USING SLOPE AND OTHER 2 COORDINATES
 ************************/

float findy(float x1,float y1,float x,float slope)
{
	return (slope*(x-x1))+y1;
}
float ans;
float newx,newy,slope,endx;
float x3,y3,x4,y4;
float m1,n1;
void mirrorimage()
{
	if(m1==0)
	{
		mirrorx=newx;
		mirrory=-newy;
	}
	else
	{
	n1=-1/m1;
	float c=y3-m1*x3;
	float d=newy-n1*newx;
	float tempx=(-c+d)/(m1-n1);
	float tempy=(d*m1-c*n1)/(m1-n1);
	mirrorx=tempx*2-newx;
	mirrory=tempy*2-newy;
	}

}
int flag=0;
int mirrorno=-1;
/**********************
 FUNCTION TO CHECK CROSS PRODUCT
 ************************/

float checksign(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4){
    float v1i = (x2-x1);
    float v1j = (y2-y1);
    float v2i = (x4-x3);
    float v2j = (y4-y3);
    return (v1i * v2j - v1j * v2i);
}
/**********************
 FUNCTION TO CHECK COLLINEARITY
 ************************/

bool coll(float x1,float y1,float x2,float y2,float x3,float y3){

	        if(x2>=min(x1,x3) && x2 <= max(x1,x3) && y2 >= min(y1,y3) && y2 <= max(y1,y3))
			                return true;
		        else
				                return false;
}
/**********************
 FUNCTION TO FIND INTERSECTION OF THE RAY WITH NEXT OBJECT
 ************************/

float intersectionx(float x1,float y1,float x2,float y2,int mirrno)
{
	int i;
	float closerx=endx;
	float closery = findy(newx,newy,closerx,slope);
	float temp=endx,endy;
	float tempy = findy(newx,newy,temp,slope);
	for(i=0;i<nblocks;i++)
	{
	
		x3=blocksxy[i][0],y3=blocksxy[i][1],x4=blocksxy[i][2],y4=blocksxy[i][3];
		endx=((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
		endy=((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
		if(endx>-windowWidth/2 && endx<windowWidth/2)
		{
			if(endx>min(x3,x4) && endx<max(x3,x4))
			{
				if(!coll(endx,endy,newx,newy,temp,tempy)){
				if(length(newx,newy,endx,endy)<length(newx,newy,closerx,closery))
				{
					closerx=endx;
					closery=endy;
				flag=0;
				mirrorno=-1;
				}
				
				}
				else
					endx=temp;
			}
			else
			{
				endx=temp;
			}
		}
        
		//	}

	}
	for(i=0;i<nlines;i++)
	{
		if(i!=mirrno )
		{
			x3=linesxy[i][0],y3=linesxy[i][1],x4=linesxy[i][2],y4=linesxy[i][3];
			endx=((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
			if(endx>-windowWidth/2 && endx<windowWidth/2)
			{

				if(endx>min(x3,x4) && endx<max(x3,x4))
				{
					if(!coll(endx,endy,newx,newy,temp,tempy)){
						if(length(newx,newy,endx,endy)<length(newx,newy,closerx,closery))
						{
							closerx=endx;
							closery=endy;
							mirrorno=i;
							flag=1;
						}
						m1=(y4-y3)/(x4-x3);
						mirrorimage();//finds mirror image of newx and newy

				//	return endx;
					}
					else
						endx =temp;
				}
				else
				{
	//				flag=0;
					endx=temp;
				}
			}
		}
        
	}
//	flag=0;
	return closerx;
}
float oldx,oldy;
float unitlengthx;//if n lines then n-1 divisions
float unitlengthy;//if n lines then n-1 divisions
/**********************
 RECURSIVE FUNCTION TO TRACE THE PATH OF THE RAY TILL THE END
 ************************/

void trace(float newx,float newy, float slope)
{
		float endy=findy(newx,newy,endx,slope);
	
		endx=intersectionx(newx,newy,endx,endy,mirrorno);
		endy= findy(newx,newy,endx,slope);
		glColor3f(0.4f,0.5f,0.1f);
    if(mode3)
    {
        specialdraw(newx,newy,endx,endy);
        
    }
    else
		drawline(newx,newy,endx,endy);//from the point on projector line to infinity
		if(endx>=windowWidth/2|| endx<=-windowWidth/2)
		{
			flag=0;
			return; 
		}
		if(flag==1)//if reflected
		{
			oldx=newx,oldy=newy;
			newx=endx;
			newy=endy;
			slope=(endy-mirrory)/(endx-mirrorx);
			
			endx=windowWidth/2;
			endy= findy(newx,newy,endx,slope);
			if(checksign(oldx,oldy,newx,newy,linesxy[mirrorno][0],linesxy[mirrorno][1],linesxy[mirrorno][2],linesxy[mirrorno][3])*checksign(newx,newy,endx,endy,linesxy[mirrorno][0],linesxy[mirrorno][1],linesxy[mirrorno][2],linesxy[mirrorno][3])>0)
			{
				endx=-windowWidth/2;
				endy= findy(newx,newy,endx,slope);
			}
				
	//	drawline(newx,newy,endx,endy);//from the point on projector line to infinity
		flag=0;
		trace(newx,newy,slope);
		}
	//	endx=200;

	return ;
}
/**********************
 FUNCTION TO DRAW A NEW PROJECTOR
 ************************/

void drawprojector()
{	
	int i,j;
	
    for(j=0;j<nproj;j++)
    {
        
	float newx=projxy[j][0];newy=projxy[j][1];
	for(i=0;i<projlines;i++)
	{
        
		if(c<nproj&& j==c)
			glColor3f(0.2f,0.3f,0.4f);
		else
			glColor3f(0.4f,0.5f,0.1f);
		drawline(projpoint[j][0],projpoint[j][1],newx,newy);//joining projecting point to point on projecting line
		slope=findslope(newx,newy,projpoint[j][0],projpoint[j][1]);
		if(newx<projpoint[j][0])
		{
			endx=-windowWidth/2;
		}
		else
		{
			endx=windowWidth/2;
		}
		trace(newx,newy,slope);
        flag=0;
		mirrorno=-1;
		float mm1=i,mm2=projlines-1-i;
		newx=((mm1*projxy[j][0])+(mm2*projxy[j][2]))/(mm1+mm2);
		newy=((mm1*projxy[j][1])+(mm2*projxy[j][3]))/(mm1+mm2);
        
	}
    }
	

}

    

//Draws the 2D scene
void draw() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
    int j;
    for(j=0;j<nproj;j++)
        setprojector(projxy[j][0],projxy[j][1],projxy[j][2],projxy[j][3],dist,j);
	
	int i;
	glTranslatef(0.0f,0.0f,-20.0f);
	glColor3f(0.3f,0.2f,0.1f);
    for(i=0;i<nproj;i++)
    {
        drawline(projxy[i][0],projxy[i][1],projxy[i][2],projxy[i][3]);
    }
	for(i=0;i<nlines;i++)
    {
        if (c>=nproj&& c<nproj+nlines)
        {
            if(i==c-nproj)
            {
                glColor3f(0.2f,0.3f,0.4f);
                
            }
            else
                glColor3f(0.3f,0.2f,0.1f);
            drawline(linesxy[i][0],linesxy[i][1],linesxy[i][2],linesxy[i][3]);
        }
        else
        {glColor3f(0.3f,0.2f,0.1f);
            drawline(linesxy[i][0],linesxy[i][1],linesxy[i][2],linesxy[i][3]);
        }
        }
    for(i=0;i<nblocks;i++)
    {
        if (c>=nproj+nlines && c<nproj+nlines+nblocks)
        {int sub=nproj+nlines;
            if(i==c-sub)
            {
                glColor3f(0.2f,0.3f,0.4f);
                
            }
            else
                glColor3f(0.0f,0.0f,1.0f);
            drawblock(blocksxy[i][0],blocksxy[i][1],blocksxy[i][2],blocksxy[i][3]);
        }
        else
        {   glColor3f(0.0f,0.0f,1.0f);
            drawblock(blocksxy[i][0],blocksxy[i][1],blocksxy[i][2],blocksxy[i][3]);
        }
    }
    
	drawprojector();
}
void handleKeypress2(int key, int x, int y) {

	if(c<nproj)
	{

	    if (key == GLUT_KEY_LEFT)
	    {
		    projxy[c][0] -= txy;
		    projxy[c][2]-=txy;
	    }
	        if (key == GLUT_KEY_RIGHT)
		{
		    projxy[c][0] += txy;
		    projxy[c][2]+=txy;
	    	}
		 if (key == GLUT_KEY_UP)
		{
		    projxy[c][1] += txy;
		    projxy[c][3]+=txy;
	    	}
		 if (key == GLUT_KEY_DOWN)
		{
		    projxy[c][1] -= txy;
		    projxy[c][3]-=txy;
	    	}
	}
	else if (c>=nproj&& c<nproj+nlines)
	{
		if (key == GLUT_KEY_LEFT)
	    {
		    linesxy[c-nproj][0]-=txy;
		    linesxy[c-nproj][2]-=txy;
	    }
	        if (key == GLUT_KEY_RIGHT)
		{
		    linesxy[c-nproj][0]+=txy;
		    linesxy[c-nproj][2]+=txy;
	    	}
		 if (key == GLUT_KEY_UP)
		{
		    linesxy[c-nproj][1]+=txy;
		    linesxy[c-nproj][3]+=txy;
	    	}
		 if (key == GLUT_KEY_DOWN)
		{
		    linesxy[c-nproj][1]-=txy;
		    linesxy[c-nproj][3]-=txy;
	    	}

	}
	else if (c>=nproj+nlines && c<nproj+nlines+nblocks)
	{
		int sub=nproj+nlines;
		if (key == GLUT_KEY_LEFT)
	    {
		    blocksxy[c-sub][0]-=txy;
		    blocksxy[c-sub][2]-=txy;
	    }
	        if (key == GLUT_KEY_RIGHT)
		{
		    blocksxy[c-sub][0]+=txy;
		    blocksxy[c-sub][2]+=txy;
	    	}
		 if (key == GLUT_KEY_UP)
		{
		    blocksxy[c-sub][1]+=txy;
		    blocksxy[c-sub][3]+=txy;
	    	}
		 if (key == GLUT_KEY_DOWN)
		{
		    blocksxy[c-sub][1]-=txy;
		    blocksxy[c-sub][3]-=txy;
	    	}

	}
	else
		c-=nproj+nlines+nblocks;

	
}
/**********************
 FUNCTION TO MODIFY VARIABLES AT REGULAR INTERVALS
 ************************/

void update1(int value)
{
    if(mode3==1)
    {
        mode3count++;
        
    }
    glutTimerFunc(100, update1, 0);
    
}
float fx,fy;
/**********************
 FUNCTION TO ROTATE PROJECTOR ACCORDING TO THE MOUSE MOVEMENTS
 ************************/

void projrotate(int x,int y){
 
    int i;
    float rad,midx,midy,ang;
    fx=x;
    fy=y;
	fx -= (float)windowWidth/2;
	fy -= (float)windowHeight/2;
    fy*=-1;
	if(mode4){
		for(i=0;i<nproj;i++){
			 midx=(projxy[i][0]+projxy[i][2])/2;
			 midy=(projxy[i][1]+projxy[i][3])/2;
	
			 rad = length(projxy[i][0],projxy[i][1],projxy[i][2],projxy[i][3]);
			 ang = atan2((fx-midx),(midy-fy));
			rad = rad/2;
			projxy[i][0]= midx + rad * cos(ang);
			projxy[i][2]= midx - rad * cos(ang);
			projxy[i][1] = midy + rad * sin(ang);
			projxy[i][3] = midy - rad * sin(ang);
		}
	}
}
void update(int value) {
    
 
    if(randm==1)
    {
    //    printf("random\n");
        srand((unsigned)time(0));
        int i;
        int signrand=rand()%2;
        float random_integer;
        if(signrand==0)//0 stands for considering negitive random value
        {
            random_integer=-0.1;
        }
        else
            random_integer=0.1;
        int blrot=rand()%2;
        int mirrot=rand()%2;
        int projrot=rand()%2;
        if(blrot)
        {
           
            

            
            for(i=0;i<nblocks;i++)
            {
                float t1=blocksxy[i][2] + (blocksxy[i][0]-blocksxy[i][2])*cos(random_integer)-(blocksxy[i][1]-blocksxy[i][3])*sin(random_integer);
            float t2=blocksxy[i][3] + (blocksxy[i][0]-blocksxy[i][2])*sin(random_integer)+(blocksxy[i][1]-blocksxy[i][3])*cos(random_integer);
            blocksxy[i][0]= t1;
            blocksxy[i][1]= t2;
            }
            
        }
        else
        {
           // printf("else*\n");
            for(i=0;i<nblocks;i++)
            {
                blocksxy[i][0]+=random_integer;
                blocksxy[i][2]+=random_integer;
            }
            
        }
        if(projrot)
        {
         //   printf("if**\n");
            for(i=0;i<nproj;i++)
            {
            float t1=projxy[i][2] + (projxy[i][0]-projxy[i][2])*cos(random_integer)-(projxy[i][1]-projxy[i][3])*sin(random_integer);
            float t2=projxy[i][3] + (projxy[i][0]-projxy[i][2])*sin(random_integer)+(projxy[i][1]-projxy[i][3])*cos(random_integer);
            projxy[i][0]= t1;
            projxy[i][1]= t2;
            }
        }
        else
        {
       //     printf("else**\n");
            for(i=0;i<nproj;i++)
            {projxy[i][0]+=random_integer;
                projxy[i][2]+=random_integer;
            }
            
        }
        if(mirrot)
        {
     //       printf("if***\n");
            for(i=0;i<nlines;i++)
            {float t1=linesxy[i][2] + (linesxy[i][0]-linesxy[i][2])*cos(random_integer)-(linesxy[i][1]-linesxy[i][3])*sin(random_integer);
                float t2=linesxy[i][3] + (linesxy[i][0]-linesxy[i][2])*sin(random_integer)+(linesxy[i][1]-linesxy[i][3])*cos(random_integer);
                linesxy[i][0]= t1;
                linesxy[i][1]= t2;
            }
            
        }
        else
        {
   //         printf("else***\n");
            for(i=0;i<nblocks;i++)
            {linesxy[i][0]+=random_integer;
                linesxy[i][2]+=random_integer;
            }
            
        }
    }
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	//Create the window
    int i;
	freopen(argv[1],"r",stdin);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    scanf("%f%f",&windowWidth, &windowHeight);
	scanf("%d",&nproj);
    for(i=0;i<nproj;i++)
		scanf("%f%f%f%f",&projxy[i][0],&projxy[i][1],&projxy[i][2],&projxy[i][3]);
    scanf("%f",&dist);
    scanf("%d",&projlines); 
    scanf("%d",&nblocks);
    for(i=0;i<nblocks;i++)
		scanf("%f%f%f%f",&blocksxy[i][0],&blocksxy[i][1],&blocksxy[i][2],&blocksxy[i][3]);
	total=nlines+nblocks+1;//+1 for one projector
	
	scanf("%d",&nlines);
    for(i=0;i<nlines;i++)
		scanf("%f%f%f%f",&linesxy[i][0],&linesxy[i][1],&linesxy[i][2],&linesxy[i][3]);

	
	unitlengthx=(projx2-projx1)/(projlines-1);//if n lines then n-1 divisions
	unitlengthy=(projy2-projy1)/(projlines-1);//if n lines then n-1 divisions
	newx=projx1,newy=projy1;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
	//glutInitWindowSize(1000, 1000); //Set the window size
	glutCreateWindow("Graphics assignment 1");
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleKeypress2);
	glutReshapeFunc(handleResize);
    glutPassiveMotionFunc(projrotate);
	//printf("%f\n",projx1);
	glutTimerFunc(10, update, 0);
    glutTimerFunc(100, update1, 0);
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









