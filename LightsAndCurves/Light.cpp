
#include <stdlib.h>
#include <glut.h>
#include<math.h>
typedef float point[4];


int mode;
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | 	GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
 
    GLfloat mat_specular[]={1.0, 0.0, 0.0, 0.0};
    GLfloat mat_diffuse[]={1.0, 0.0, 0.0, 0.0};
    GLfloat mat_ambient[]={1.0, 0.0, 0.0, 0.0};
    GLfloat mat_shininess={0.0};
  
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidTeapot(0.5);

 
    glTranslatef(-2.0, 0.0,0.0);

	// 
	GLfloat mat_specular1[]={0.0, 0.0, 1.0, 1.0};
    GLfloat mat_diffuse1[]={0.0, 0.0, 1.0, 1.0};
    GLfloat mat_ambient1[]={0.0, 0.0, 1.0, 1.0};
	GLfloat mat_shininess1={30.0};
  


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess1);
	glutSolidTeapot(0.5);

    
    glTranslatef( 4.0, 0.0,0.0);
	GLfloat mat_specular2[]={0.0, 1.0, 0.0, 0.0};
	GLfloat mat_diffuse2[]={0.0, 1.0, 0.0, 0.0};
	GLfloat  mat_ambient2[]={0.0, 1.0, 0.0, 0.0};
   GLfloat mat_shininess2={100.0};

	/*GLfloat mat_specular2[]={0.628281,0.555802,0.366065 , 0.0};
	GLfloat mat_diffuse2[]={0.75164,0.60648,0.22648 , 0.0};
	GLfloat  mat_ambient2[]={0.24725,0.1995,0.0745, 0.0};
   GLfloat mat_shininess2={51.2};*/

	/*	GLfloat mat_specular2[]={0.19225,0.19225,0.19225 , 0.0};
	GLfloat mat_diffuse2[]={0.50754,0.50754,0.50754 , 0.0};
	GLfloat  mat_ambient2[]={0.508273,0.508273,0.508273, 0.0};
   GLfloat mat_shininess2={51.2};*/
  

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess2);
	glutSolidTeapot(0.5);


    glFlush();
}
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    display();
}

void myinit()
{ /* GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess={100.0};*/

    GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
//	GLfloat light_diffuse[]={0.0, 0.0, 1.0, 1.0};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

///*	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);*/
//
    glShadeModel(GL_SMOOTH); 
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);  
    glEnable(GL_DEPTH_TEST); 
    glClearColor (1.0, 1.0, 1.0, 1.0);
//    glColor3f (0.0, 0.0, 0.0);
}

//void myinit()
//{  GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
//    GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
//    GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
//    GLfloat mat_shininess={100.0};
//    GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
//    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
//    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//
//	/*glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);*/
//
//    glShadeModel(GL_SMOOTH); 
//    glEnable(GL_LIGHTING); 
//    glEnable(GL_LIGHT0);  
//    glEnable(GL_DEPTH_TEST); 
//    glClearColor (1.0, 1.0, 1.0, 1.0);
//    glColor3f (0.0, 0.0, 0.0);
//}


void main(int argc, char **argv)
{
//    n=5;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | 	GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Teapot");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
}


