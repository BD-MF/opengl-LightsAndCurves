#include <stdlib.h>
#include <glut.h>
#include <vector>
#include <iostream>

using namespace std;

//Define struct for a 2D point.
struct Point
{
	double xVal;
	double yVal;
};

//Define vector to hold 
vector<Point> controlPoints;

//Utility function that translates a mouse coordinate to actual view coordinates.
void addPointFromClick(int x, int y)
{
	//Define a new point that will be added.
	Point newControlPoint;

	//Calculate and set point values accordingly.
	newControlPoint.xVal = x * (20.0 / 800.0);
	newControlPoint.yVal = (800.0 - y) * (20.0 / 800.0);

	//Add new point to control point vector.
	controlPoints.push_back(newControlPoint);
}

double chooseBlendingFunction(int i, double u)
{
	//Compare the i and u values, and return the proper calculation.
	if (i > u)
	{
		return 0;
	}
	else if ((i + 1) > u)
	{
		return (pow(u, 3)) / 6;
	}
	else if ((i + 2) > u)
	{
		return ((-3 * pow(u, 3)) + (3 * pow(u, 2)) + (3 * (u + 1))) / 6;
	}
	else if ((i + 3) > u)
	{
		return ((3 * pow(u, 3)) - (6 * pow(u, 2)) + 4) / 6;
	}
	else if ((i + 4) > u)
	{
		return pow((1 - u), 3) / 6;
	}
	else 
	{
		return 0;
	}
}

//Function that will use the collection of control points to draw a cubic B-spline curve.
void drawBSpline()
{
	if (controlPoints.size() != 0)
	{
		glBegin(GL_LINE_STRIP);

		glColor3f(1.0, 0.0, 0.0);

		double xToPlot = 0;
		double yToPlot = 0;

		for (double u = 3; u <= (controlPoints.size() + 1); u += .1)
		{
			for (int i = 1; i <= controlPoints.size(); i++)
			{
				xToPlot += chooseBlendingFunction(i, u) * controlPoints[i - 1].xVal;
				yToPlot += chooseBlendingFunction(i, u) * controlPoints[i - 1].yVal;
				//glVertex2d(xToPlot, yToPlot);
			}
			glVertex2d(xToPlot, yToPlot);
		}

		glEnd();
	}
	else 
	{
		cout << "There are no control points defined...\n";
	}
}

//Display function called whenever glutPostRedisplay() is called. Contains OpenGL display commands and/or calls
//other methods which use display commands.
void display(void)
{
	//Clear the current color from the color buffer bit.
	glClear(GL_COLOR_BUFFER_BIT);

	drawBSpline();

	glFlush();
}

//Function called whenever a mouse button is pressed.
void mouse(int button, int state, int x, int y)
{
	//Make sure the button is being pressed, not released.
	if (state == GLUT_DOWN)
	{
		//For left clicks, add the point to the control point vector.
		if (button == GLUT_LEFT_BUTTON)
		{
			addPointFromClick(x, y);
		}
		//When the user right clicks, draw B-Spline curve with control points defined in vector.
		else if (button == GLUT_RIGHT_BUTTON)
		{
			glutPostRedisplay();
		}
	}
}

//Function called when a button on the keyboard is pressed.
void keyboard(unsigned char key, int x, int y)
{
	//If the user presses 'q', clear out the current control points.
	if (key == 'q')
	{
		controlPoints.clear();
		glutPostRedisplay();
	}
}

//Initialization function that is called before the main loop is entered. Sets up constants such as camera, projection,
//and background colors.
void init(void)
{
	//Set background color to white.
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//Set up window to be a 20x20 coordinate space.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 20, 0, 20);

	//Load the modelview matrix and clear it out.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Main setup method.
void main(int argc, char** argv)
{
	//Call glut initialization functions setting single buffer mode, rgb color scale, initial window position and size,
	//and window title.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Curves");

	//Finish initializing by setting up camera, projection, etc.
	init();

	//Register custom display function with glut.
	glutDisplayFunc(display);

	//Register mouse function with glut.
	glutMouseFunc(mouse);

	//Register keyboard function with glut.
	glutKeyboardFunc(keyboard);

	//Enter the glut main loop and listen for events.
	glutMainLoop();
}