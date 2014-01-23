#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include "light.h"
#include <GL/glaux.h>
#include <iostream>
using namespace std;

#pragma comment (lib, "glaux.lib") 

unsigned int textures[1];
//Вывести лог
void showLog()
{
	cout<<"In order to set the state by default, please, push the \"=\" key."
		<<endl
		<<"-------------------------------------------------------------------"
		<<endl
		<<"MOVING"<<endl
		<<"left:\t4, right:\t6"<<endl
		<<"up:\t8, down:\t2"<<endl
		<<"..........................."<<endl
		<<"ROTATION around axis:"<<endl
		<<"X (x/X): "<<rX<<endl
		<<"Y (y/Y): "<<rY<<endl
		<<"Z (z/Z): "<<rZ<<endl
		<<"SCALE: (+/-)"<<endl
		<<"by X: "<<sX<<endl
		<<"by Y: "<<sY<<endl/**/
		/*<<"angles for axis (rAngle, no keys) - "<<endl
		<<"aX: "<<aX<<endl
		<<"aY: "<<aY<<endl
		<<"aZ: "<<aZ<<endl*/
		/*
		<<"..........................."<<endl
		<<"LIGHTING:"<<endl
		<<"Left light:"<<endl
		<<"Move left/right (l:L):\t"<<lposLeft[0]<<endl
		<<"Move up/down (;::):\t"<<lposLeft[1]<<endl
		//<<"z (':\"): "<<lposLeft[2]<<endl
		<<"Right light:"<<endl
		<<"Move left/right (a:A):\t"<<lposLeft[0]<<endl // l:L ;:: ':"
		<<"Move up/down (s:S):\t"<<lposLeft[1]<<endl //
		//<<"z (d:D): "<<lposLeft[2]<<endl */
		<<endl;//
}
//Загрузить текстуру
void loadTextures()
{
	cout<<"Choose the texture:"<<endl
		<<"1 -\t\t\tstone"<<endl
		<<"2 -\t\t\twood"<<endl
		<<"any another value -\t"<<"specular"<<endl;
	cin>>Tx;
	
	cout<<"You have choosen: ";
	
	LPCSTR pic="default.bmp";
	
	switch (Tx)
	{
		case 1:
			cout<<"stone";
			pic="stone2.bmp";
			break;
		case 2:
			cout<<"wood";
			pic="wood11.bmp";
			break;
		default:
			cout<<"specular";
			break;
	}
	cout<<endl;
	if(Tx==1||Tx==2)
	{	
		// образ текстуры 
		AUX_RGBImageRec *texture1 = auxDIBImageLoadA(pic);
		glGenTextures(1, &textures[0]);
		glBindTexture(GL_TEXTURE_2D,textures[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		const GLdouble s_coeffs[] ={1,0,0,1};
		glEnable (GL_TEXTURE_GEN_S);
		glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGendv (GL_S, GL_EYE_PLANE,s_coeffs);
	}
}
/*	       
	 ()   .	*/
void prepareProjection()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	if (w<=h) glOrtho(	oL,
						oR,
						oB*(GLfloat)h/(GLfloat)w,
						oT*(GLfloat)h/(GLfloat)w,
						oNear,
						oFar
					 );
	else	  glOrtho(  oL*(GLfloat)w/(GLfloat)h,
						oR*(GLfloat)w/(GLfloat)h,
						oB,
						oT,
						oNear,
						oFar
					 );
}
// 
void prepareMaterial()
{
	//  () 
	glClearColor(0.1,0.0,0.3,1.0);
	//  
	glShadeModel(GL_SMOOTH);
	// 
	glMaterialfv(	GL_FRONT_AND_BACK,
					GL_SPECULAR,	//   
					mat_specular
				);
	glMaterialfv(	GL_FRONT_AND_BACK,
					GL_SHININESS,	//   
					mat_shininess
				);
}
// 
void enableLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
// 
//
void setLightLeft()
{
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//   
	//   (x,y,z,w)
	GLfloat light_position[]={
						lposLeft[0],
						lposLeft[1],
						lposLeft[2],
						lposLeft[3]
					}; // x,y,z,w
	GLfloat light_diffuse[]		={1.0,0.0,0.0,1.0};
	GLfloat light_specular[]	={1.0,1.0,1.0,1.0};
	// 
	prepareMaterial();
	// 
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	enableLight();
	glEnable(GL_LIGHT0);
}
//
void setLightRight()
{
	//   
	//   (x,y,z,w)
	GLfloat light_position[]={
						lposRight[0],
						lposRight[1],
						lposRight[2],
						lposRight[3]
					}; // x,y,z,w
	GLfloat light_diffuse[]		={0.0,0.0,1.0,1.0};
	GLfloat light_specular[]	={1.0,1.0,1.0,1.0};
	// 
	prepareMaterial();
	// 
	glLightfv(GL_LIGHT1,GL_POSITION,light_position);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular);
	// 
	enableLight();
	glEnable(GL_LIGHT1);
}
//  
void init(void)
{
	setLightLeft();
	setLightRight();
	//
	glClearColor(0.1,0.0,0.3,1.0);
	// 
	GLfloat dlight_power[]={ 1.0,0.9,0.8,1.0 };	// rgba
	GLfloat dlight_position[]={ 0.0,10.0,4.5,1.0 }; // x, y, z, w
	glLightfv(GL_LIGHT2,GL_DIFFUSE,dlight_power);
	glLightfv(GL_LIGHT2,GL_POSITION,dlight_position);
	//  
	GLfloat alight_power[]={ 1.0,1.0,1.0,1.0 };	// rgba
	glLightfv(GL_LIGHT3,GL_AMBIENT,alight_power);

	enableLight();
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	//---------------------------
	loadTextures();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0,4.0,-4.0,4.0,-10.0,10.0); // left right bottom top
	glMatrixMode(GL_MODELVIEW);
}
//   
void Reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	prepareProjection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// 
void display(void)
{
	/*cout<<"Display!"<<endl
		<<"width: "<<glutGet(GLUT_WINDOW_WIDTH)<<endl
		<<"height:"<<glutGet(GLUT_WINDOW_HEIGHT)
		<<endl; */
	showLog();
	//объявить квадратичный объект
	GLUquadricObj* qobj;
	//очистить буфер
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//указать цвет очистки
	glColor3f(1.0,1.0,1.0);
	//включить левый источник света
	setLightLeft();
	//...и правый
	setLightRight();
	
	//
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	
	//переместить объект влево/вправо
	glTranslatef ( trnslX, trnslY, trnslZ );
	//повернуть
	glRotatef(rAngle,rX,rY,rZ);
	//масштабировать 
	glScalef(sX,sY,sZ);
	//создать квадратичный объект
	qobj = gluNewQuadric();
	//назначить объекту тип заливки
	gluQuadricDrawStyle(qobj,GLU_FILL);
	//рассчитать нормали
	gluQuadricNormals(qobj,GLU_SMOOTH);
	//привязать ранее загруженную текстуру
	gluQuadricTexture(qobj, true);
	//указать тип созданного объекта (сфера)
	gluSphere(qobj,0.33,50,20);
	//---------------------------------
	glFlush();
}
//  
void setRotationAngle(float &aXYZ, float &rXYZ, int d)
{	
	//   
	rX=rY=rZ=0.0;		
	// назначить ось вращения (x/y/z)
	rXYZ = 1.0;			
	// рассчитать угол вращения для выбранной оси
	if(d==1) aXYZ+=angleStep;	
	if(d==-1)aXYZ-=angleStep;	
	// установить угол вращения для выбранной оси
	rAngle=aXYZ;		
}
//   
void setLightPos(float &light, int sign)
{
	if(sign==1) light+=lposStep;
	if(sign==-1)light-=lposStep;
}
//   
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // .    ASCII : http://www.theasciicode.com.ar/
	{	
		// передвижение вправо/влево
		case 52:	// 4
			trnslX-=stepTransform;
			break;
		case 54:	// 6
			trnslX+=stepTransform;
			break;
		case 56:	// 8
			trnslY+=stepTransform;
			break;
		case 50:	// 2
			trnslY-=stepTransform;
			break;
		//-------------------------
		// вращение
		case 120:	// x
			setRotationAngle(aX, rX, 1);
			break;
		case 88:	// X
			setRotationAngle(aX, rX, -1);
			break;
		case 121:	// y
			setRotationAngle(aY, rY, 1);
			break;
		case 89:	// Y
			setRotationAngle(aY, rY, -1);
			break;		
		case 122:	// z
			setRotationAngle(aZ, rZ, 1);
			break;
		case 90:	// Z
			setRotationAngle(aZ, rZ, -1);
			break;
		//----------------------------
		// изменение позиции освещения
		// свет СЛЕВА
		//  X
		case 97:	//a
			setLightPos(lposLeft[0],-1); // 
			break;
		case 65:	//A
			setLightPos(lposLeft[0],1);  // 
			break;
		//  Y
		case 115:	//s
			setLightPos(lposLeft[1],-1); // 
			break;
		case 83:	//S
			setLightPos(lposLeft[1],1); // 
			break;
		//  Z
		case 100:	//d
			setLightPos(lposLeft[2],-1); // 			
			break;
		case 68:	//D
			setLightPos(lposLeft[2],1); // 			
			break;
		
		// свет СПРАВА
		case 108:	//l
			setLightPos(lposRight[0],-1);
			break;
		case 76:	//L
			setLightPos(lposRight[0],1);
			break;
		case 59:	//;
			setLightPos(lposRight[1],-1);
			break;
		case 58:	//:
			setLightPos(lposRight[1],1);
			break;
		case 39:	//'
			setLightPos(lposRight[2],-1);
			break;
		case 34:	//"
			setLightPos(lposRight[2],1);
			break;
		//............................
		// масштабирование
		case 43: // +
			sX+=zoom;
			sY+=zoom;
			break;
		case 45: // -
			sX-=zoom;
			sY-=zoom;
			break;
		//----------------------------
		case 61: // = 
		
			trnslX = trnslY = trnslZ = trnslInit;
			//-----------------------------------
			// сбросить значения активной оси и угла вращения 
			aX = aY = aZ = rX = rY = rZ = rAngle = 0.0;
			// приенить угол вращения по умолчанию ко всем осям
			glRotatef(0.0,1.0,0.0,0.0);
			glRotatef(0.0,0.0,1.0,0.0);
			glRotatef(0.0,0.0,0.0,1.0);
			// сбросить масштаб
			sX=sY=sZ=sDefault;
			// сбросить параметры освещения
			//------------------------------
			lposLeft[0]=LPLeft[0];
			lposLeft[1]=LPLeft[1];
			lposLeft[2]=LPLeft[2];
			lposLeft[3]=LPLeft[3];
			//------------------------------
			lposRight[0]=LPRight[0];
			lposRight[1]=LPRight[1];
			lposRight[2]=LPRight[2];
			lposRight[3]=LPRight[3];
			break;
			//     . "":
		case 32: exit(0);
			break;
	}
	if(key!=32) 
	{
		/*	вызвать матрицы,
			рассчитать ортографическую проекцию.
			Вызов выполняется здесь, а не в display, 
			чтобы избежать его повторения при инициализации*/
		prepareProjection();
		//
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(1000,100);
	glutCreateWindow("Square");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}