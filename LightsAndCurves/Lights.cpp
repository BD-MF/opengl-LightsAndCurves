#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void addLight(void);

//Define struct to be used to hold coordinates for points read in from .poly file.
struct point
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

//Define struct to hold references to the 3 points that make up a face of the object being drawn.
struct face
{
	int point1;
	int point2;
	int point3;
};

struct light
{
	GLenum lightName;
	GLfloat light_ambient[4];
	GLfloat light_diffuse[4];
	GLfloat light_specular[4];
	GLfloat light_pos[4];
};

struct material
{
	GLfloat mat_specular[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_ambient[4];
	GLfloat shininess;
};

light lights[5];
material materials[9];

int displayMode = 2;
int activeLight = 0;
int currentMaterial = 0;
bool lightMode = false;

//Initialize vectors to populate from the .poly file.
std::vector<point> pts;
std::vector<face> faces;

//Function that sets up all the required lights for the program.
void setupLights()
{
	//Create the 5 unique lights and store them in the lights array.
	light light1;
	light1.lightName = GL_LIGHT0;
	light1.light_ambient[0] = 0.0, light1.light_ambient[1] = 0.0, light1.light_ambient[2] = 0.0, light1.light_ambient[3] = 1.0;
	light1.light_diffuse[0] = 1.0, light1.light_diffuse[1] = 1.0, light1.light_diffuse[2] = 1.0, light1.light_diffuse[3] = 1.0;
	light1.light_specular[0] = 1.0, light1.light_specular[1] = 1.0, light1.light_specular[2] = 1.0, light1.light_specular[3] = 1.0;
	light1.light_pos[0] = 1.0, light1.light_pos[1] = 1.0, light1.light_pos[2] = 3.0, light1.light_pos[3] = 1.0;
	lights[0] = light1;

	light light2;
	light2.lightName = GL_LIGHT0;
	light2.light_ambient[0] = 0.0, light2.light_ambient[1] = 0.0, light2.light_ambient[2] = 0.0, light2.light_ambient[3] = 1.0;
	light2.light_diffuse[0] = 1.0, light2.light_diffuse[1] = 0.0, light2.light_diffuse[2] = 0.0, light2.light_diffuse[3] = 1.0;
	light2.light_specular[0] = 1.0, light2.light_specular[1] = 0.0, light2.light_specular[2] = 0.0, light2.light_specular[3] = 1.0;
	light2.light_pos[0] = -1.0, light2.light_pos[1] = -1.0, light2.light_pos[2] = 3.0, light2.light_pos[3] = 1.0;
	lights[1] = light2;

	light light3;
	light3.lightName = GL_LIGHT0;
	light3.light_ambient[0] = 0.0, light3.light_ambient[1] = 0.0, light3.light_ambient[2] = 0.0, light3.light_ambient[3] = 1.0;
	light3.light_diffuse[0] = 0.0, light3.light_diffuse[1] = 0.3, light3.light_diffuse[2] = 0.0, light3.light_diffuse[3] = 1.0;
	light3.light_specular[0] = 0.0, light3.light_specular[1] = 0.3, light3.light_specular[2] = 0.0, light3.light_specular[3] = 1.0;
	light3.light_pos[0] = -1.0, light3.light_pos[1] = -1.0, light3.light_pos[2] = 0.0, light3.light_pos[3] = 1.0;
	lights[2] = light3;

	light light4;
	light4.lightName = GL_LIGHT0;
	light4.light_ambient[0] = 0.0, light4.light_ambient[1] = 0.0, light4.light_ambient[2] = 0.0, light4.light_ambient[3] = 1.0;
	light4.light_diffuse[0] = 0.0, light4.light_diffuse[1] = 0.0, light4.light_diffuse[2] = 0.6, light4.light_diffuse[3] = 1.0;
	light4.light_specular[0] = 0.0, light4.light_specular[1] = 0.0, light4.light_specular[2] = 0.6, light4.light_specular[3] = 1.0;
	light4.light_pos[0] = 0.0, light4.light_pos[1] = 0.0, light4.light_pos[2] = 6.0, light4.light_pos[3] = 1.0;
	lights[3] = light4;

	light light5;
	light5.lightName = GL_LIGHT0;
	light5.light_ambient[0] = 0.0, light5.light_ambient[1] = 0.0, light5.light_ambient[2] = 0.0, light5.light_ambient[3] = 1.0;
	light5.light_diffuse[0] = 0.3, light5.light_diffuse[1] = 0.0, light5.light_diffuse[2] = 0.7, light5.light_diffuse[3] = 1.0;
	light5.light_specular[0] = 0.3, light5.light_specular[1] = 0.0, light5.light_specular[2] = 0.7, light5.light_specular[3] = 1.0;
	light5.light_pos[0] = 0.0, light5.light_pos[1] = 2.0, light5.light_pos[2] = 3.0, light5.light_pos[3] = 1.0;
	lights[4] = light5;
}

//Function that configures all materials for the program.
void setupMaterials()
{
	//Populate the materials array with material configurations. mat1-mat3 represent gems, mat4-mat6 represent metals, and mat7-mat9
	//represent plastics.
	//Emerald
	material mat1;
	mat1.mat_ambient[0] = 0.0215, mat1.mat_ambient[1] = 0.1745, mat1.mat_ambient[2] = 0.0215, mat1.mat_ambient[3] = 1.0;
	mat1.mat_diffuse[0] = 0.07568, mat1.mat_diffuse[1] = 0.61424, mat1.mat_diffuse[2] = 0.07568, mat1.mat_diffuse[3] = 1.0;
	mat1.mat_specular[0] = 0.633, mat1.mat_specular[1] = 0.727811, mat1.mat_specular[2] = 0.633, mat1.mat_specular[3] = 1.0;
	mat1.shininess = 76.8;
	materials[0] = mat1;
	//Obsidian
	material mat2;
	mat2.mat_ambient[0] = 0.05375, mat2.mat_ambient[1] = 0.05, mat2.mat_ambient[2] = 0.06625, mat2.mat_ambient[3] = 1.0;
	mat2.mat_diffuse[0] = 0.18275, mat2.mat_diffuse[1] = 0.17, mat2.mat_diffuse[2] = 0.22525, mat2.mat_diffuse[3] = 1.0;
	mat2.mat_specular[0] = 0.332741, mat2.mat_specular[1] = 0.328634, mat2.mat_specular[2] = 0.346435, mat2.mat_specular[3] = 1.0;
	mat2.shininess = 38.4;
	materials[1] = mat2;
	//Ruby
	material mat3;
	mat3.mat_ambient[0] = 0.1745, mat3.mat_ambient[1] = 0.01175, mat3.mat_ambient[2] = 0.01175, mat3.mat_ambient[3] = 1.0;
	mat3.mat_diffuse[0] = 0.61424, mat3.mat_diffuse[1] = 0.04136, mat3.mat_diffuse[2] = 0.04136, mat3.mat_diffuse[3] = 1.0;
	mat3.mat_specular[0] = 0.727811, mat3.mat_specular[1] = 0.626959, mat3.mat_specular[2] = 0.626959, mat3.mat_specular[3] = 1.0;
	mat3.shininess = 76.8;
	materials[2] = mat3;
	//Bronze
	material mat4;
	mat4.mat_ambient[0] = 0.2125, mat4.mat_ambient[1] = 0.1275, mat4.mat_ambient[2] = 0.054, mat4.mat_ambient[3] = 1.0;
	mat4.mat_diffuse[0] = 0.714, mat4.mat_diffuse[1] = 0.4284, mat4.mat_diffuse[2] = 0.18144, mat4.mat_diffuse[3] = 1.0;
	mat4.mat_specular[0] = 0.393548, mat4.mat_specular[1] = 0.271906, mat4.mat_specular[2] = 0.166721, mat4.mat_specular[3] = 1.0;
	mat4.shininess = 25.6;
	materials[3] = mat4;
	//Chrome
	material mat5;
	mat5.mat_ambient[0] = 0.25, mat5.mat_ambient[1] = 0.25, mat5.mat_ambient[2] = 0.25, mat5.mat_ambient[3] = 1.0;
	mat5.mat_diffuse[0] = 0.4, mat5.mat_diffuse[1] = 0.4, mat5.mat_diffuse[2] = 0.4, mat5.mat_diffuse[3] = 1.0;
	mat5.mat_specular[0] = 0.774597, mat5.mat_specular[1] = 0.774597, mat5.mat_specular[2] = 0.774597, mat5.mat_specular[3] = 1.0;
	mat5.shininess = 76.8;
	materials[4] = mat5;
	//Gold
	material mat6;
	mat6.mat_ambient[0] = 0.24725, mat6.mat_ambient[1] = 0.1995, mat6.mat_ambient[2] = 0.0745, mat6.mat_ambient[3] = 1.0;
	mat6.mat_diffuse[0] = 0.75164, mat6.mat_diffuse[1] = 0.60648, mat6.mat_diffuse[2] = 0.22648, mat6.mat_diffuse[3] = 1.0;
	mat6.mat_specular[0] = 0.628281, mat6.mat_specular[1] = 0.555802, mat6.mat_specular[2] = 0.366065, mat6.mat_specular[3] = 1.0;
	mat6.shininess = 51.2;
	materials[5] = mat6;
	//Cyan Plastic
	material mat7;
	mat7.mat_ambient[0] = 0.0, mat7.mat_ambient[1] = 0.1, mat7.mat_ambient[2] = 0.06, mat7.mat_ambient[3] = 1.0;
	mat7.mat_diffuse[0] = 0.0, mat7.mat_diffuse[1] = 0.50980392, mat7.mat_diffuse[2] = 0.50980392, mat7.mat_diffuse[3] = 1.0;
	mat7.mat_specular[0] = 0.50196078, mat7.mat_specular[1] = 0.50196078, mat7.mat_specular[2] = 0.50196078, mat7.mat_specular[3] = 1.0;
	mat7.shininess = 32;
	materials[6] = mat7;
	//White Plastic
	material mat8;
	mat8.mat_ambient[0] = 0.0, mat8.mat_ambient[1] = 0.0, mat8.mat_ambient[2] = 0.0, mat8.mat_ambient[3] = 1.0;
	mat8.mat_diffuse[0] = 0.55, mat8.mat_diffuse[1] = 0.55, mat8.mat_diffuse[2] = 0.55, mat8.mat_diffuse[3] = 1.0;
	mat8.mat_specular[0] = 0.7, mat8.mat_specular[1] = 0.7, mat8.mat_specular[2] = 0.7, mat8.mat_specular[3] = 1.0;
	mat8.shininess = 32;
	materials[7] = mat8;
	//Yellow Plastic
	material mat9;
	mat9.mat_ambient[0] = 0.0, mat9.mat_ambient[1] = 0.0, mat9.mat_ambient[2] = 0.0, mat9.mat_ambient[3] = 1.0;
	mat9.mat_diffuse[0] = 0.5, mat9.mat_diffuse[1] = 0.5, mat9.mat_diffuse[2] = 0.0, mat9.mat_diffuse[3] = 1.0;
	mat9.mat_specular[0] = 0.6, mat9.mat_specular[1] = 0.6, mat9.mat_specular[2] = 0.6, mat9.mat_specular[3] = 1.0;
	mat9.shininess = 32;
	materials[8] = mat9;
}

//Initial setup function called once when the program starts.
void init(void)
{
	//Call function to prepare lights and their attributes.
	setupLights();

	//Call function to set up materials and their attributes.
	setupMaterials();

	//Turn on smooth shading, enable lighting, depth testing, and auto normalization, and set background color to white.
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);  
    glEnable(GL_DEPTH_TEST); 
	glEnable(GL_NORMALIZE);
    glClearColor (1.0, 1.0, 1.0, 1.0);

	//Set up the projection matrix.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.5, 2.5, -2.5, 2.5, -2.5, 2.5);
}

//Read .poly file and populate point and face vectors with necessary information.
void readFromFile()
{
	//Set up file and string streams, and initialize necessary variables.
	int vertices, faces1;
	std::ifstream infile("bunny.poly");

	std::string line;
	std::getline(infile, line);
	std::istringstream iss(line);
	std::string throwOut;

	//Verify that file was successfully opened.
	if (infile.is_open())
	{
		std::cout << "File was opened \n";
	}
	//Verify that there was no issue reading the first line of the file.
	if (!(iss >> throwOut >> vertices))
	{
		std::cout << iss.str();
		std::cout<<"There was an error reading the first line \n";
	}
	else
	{
		//Read the second line of the file, and verify that there was no issue reading it.
		std::getline(infile, line);
		std::istringstream iss(line);
		 if (!(iss >> throwOut >> faces1))
		 {
			 std::cout << "There was an error reading the second line \n";
		 }
		 else
		 {
			 char type;
			 //Read each line of the file and parse it accordingly.
			 while (std::getline(infile, line))
			 {
				 std::istringstream iss(line);
				 iss >> type;
				 //If the line is denoted as a face, add the required point indexes to the new face, and push that face into the faces vector.
				 if (type == 'f')
				 {
					 face face_to_add;
					 iss >> face_to_add.point1 >> face_to_add.point2 >> face_to_add.point3;
					 faces.push_back(face_to_add);
				 }
				 //If the line is denoted as a vertex, add the coordinates to the newly created point, and add it to the points vector.
				 else if (type == 'v')
				 {
					 point point_to_add;
					 iss >> point_to_add.x >> point_to_add.y >> point_to_add.z;
					 pts.push_back(point_to_add);
				 }
				 //If an unrecognized character is encountered, print error.
				 else
				 {
					 std::cout << "Something went wrong...";
				 }
			 }
			 //Let the user know the file was successfully read.
			 std::cout << "Finished reading vertices \n";
		 }
	}
}

//Function that plots the points that were read in from the .poly file.
void plotPoints()
{
	//Assign material properties that are currently selected.
	glMaterialfv(GL_FRONT, GL_SPECULAR, materials[currentMaterial].mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materials[currentMaterial].mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[currentMaterial].mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, materials[currentMaterial].shininess);

	for (int i = 0; i < faces.size(); i++)
	{
		//Check for wireframe display mode.
		if (displayMode == 0)
		{
			glBegin(GL_LINE_LOOP);
		}
		else
		{
			glBegin(GL_POLYGON);
		}
		//If display mode is not wireframe, add 1 vertex normal.
		if (displayMode != 0)
		{
			glNormal3f(pts[(faces[i].point1) - 1].x, pts[(faces[i].point1) - 1].y, pts[(faces[i].point1) - 1].z);
		}
		//Plot vertex 1.
		glVertex3f(pts[(faces[i].point1) - 1].x, pts[(faces[i].point1) - 1].y, pts[(faces[i].point1) - 1].z);
		//If display mode is interpolative shading, add a second vertex normal.
		if (displayMode == 2)
		{
			glNormal3f(pts[(faces[i].point2) - 1].x, pts[(faces[i].point2) - 1].y, pts[(faces[i].point2) - 1].z);
		}
		//Plot vertex 2.
		glVertex3f(pts[(faces[i].point2) - 1].x, pts[(faces[i].point2) - 1].y, pts[(faces[i].point2) - 1].z);
		//If display mode is interpolative shading, add a third vertex normal.
		if (displayMode == 2)
		{
			glNormal3f(pts[(faces[i].point3) - 1].x, pts[(faces[i].point3) - 1].y, pts[(faces[i].point3) - 1].z);
		}
		//Plot vertex 3 and end the drawing.
		glVertex3f(pts[(faces[i].point3) - 1].x, pts[(faces[i].point3) - 1].y, pts[(faces[i].point3) - 1].z);
		glEnd();
	}
	//Tell the user when the plotting has finished.
	printf("Finished plotting \n");
}

void addLight(void)
{
	//Configure and enable the active light.
	GLenum currentLight = lights[activeLight].lightName;
	glLightfv(currentLight, GL_AMBIENT, lights[activeLight].light_ambient);
	glLightfv(currentLight, GL_DIFFUSE, lights[activeLight].light_diffuse);
	glLightfv(currentLight, GL_SPECULAR, lights[activeLight].light_specular);
	glLightfv(currentLight, GL_POSITION, lights[activeLight].light_pos);
	glEnable(currentLight);
}

//Function called to do the drawing after lighting has been set up.
void drawPoly(void)
{
	//Switch to MODELVIEW matrix, clear it out, and set drawing mode to fill.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//Call method that plots the points.
	plotPoints();
}

//Display function that is called whenever glutPostRedisplay() is called. Calls setup functions and drawing functions.
void display()
{
	//Clear the color buffer bit.
	glClear(GL_COLOR_BUFFER_BIT | 	GL_DEPTH_BUFFER_BIT);

	//Switch to MODELVIEW.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Add whichever light is selected.
	addLight();

	//Call function to draw poly object.
	drawPoly();

	glFlush();
}

//Function called whenever a key is pressed.
void keyboard(unsigned char key, int x, int y)
{
	//If the program is in light mode, allow user to toggle through lights 1-5.
	if (lightMode)
	{
		//Decrease light index.
		if (key == '1')
		{
			if (activeLight > 0)
			{
				activeLight--;
			}
		}
		//Increase light index.
		else if (key == '2')
		{
			if (activeLight < 4)
			{
				activeLight++;
			}
		}
	}

	glutPostRedisplay();
}
//Function called when a main menu option is selected.
void mainMenu(GLint menuOption)
{
	switch (menuOption)
	{
	case 0: //Toggle lightmode if it is selected.
		lightMode = !lightMode; 
		break;
	case 1: //Exit if the user clicked on exit. 
		exit(0);
	}
	glutPostRedisplay();
}
//Function called when a display submenu option is selected.
void displaySubMenu(GLint displayOption)
{
	//Switch display mode accordingly.
	displayMode = displayOption;
	glutPostRedisplay();
}
//Function called when a material submenu option is selected.
void materialSubMenu(GLint materialOption)
{
	//Left empty because every option in this submenu is already bound to a separate submenu.
}
//Function called when a plastic submenu option is selected.
void plasticSubMenu(GLint plasticOption)
{
	//Assign new material accordingly.
	currentMaterial = plasticOption;
	glutPostRedisplay();
}
//Function called when a metal submenu option is selected.
void metalSubMenu(GLint metalOption)
{
	//Assign new material accordingly.
	currentMaterial = metalOption;
	glutPostRedisplay();
}
//Function called when a gem submenu option is selected.
void gemSubMenu(GLint gemOption)
{
	//Assign new material accordingly.
	currentMaterial = gemOption;
	glutPostRedisplay();
}

//Main setup method.
void main(int argc, char** argv)
{
	//Sub menu identifiers
	GLint materialMenu, gemMenu, metalMenu, plasticMenu, displayMenu;

	//Initialize glut, set up single buffer display, rgb color scale, and set the window position, size, and title.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Lights");

	//Call init function.
	init();

	//Read in vertices and faces from .poly file.
	readFromFile();

	//Register display function with glut.
	glutDisplayFunc(display);
	//Create menu and menu options for gem material selection.
	gemMenu = glutCreateMenu(gemSubMenu);
		glutAddMenuEntry("Emerald", 0);
		glutAddMenuEntry("Obsidian", 1);
		glutAddMenuEntry("Ruby", 2);
	//Create menu and menu options for metal material selection.
	metalMenu = glutCreateMenu(metalSubMenu);
		glutAddMenuEntry("Bronze", 3);
		glutAddMenuEntry("Chrome", 4);
		glutAddMenuEntry("Gold", 5);
	//Create menu and menu options for plastic material selection.
	plasticMenu = glutCreateMenu(plasticSubMenu);
		glutAddMenuEntry("Cyan Plastic", 6);
		glutAddMenuEntry("White Plastic", 7);
		glutAddMenuEntry("Yellow Plastic", 8);
	//Create menu and menu options for material submenu selection.
	materialMenu = glutCreateMenu(materialSubMenu);
		glutAddSubMenu("Gems", gemMenu);
		glutAddSubMenu("Metals", metalMenu);
		glutAddSubMenu("Plastics", plasticMenu);
	//Create menu and menu options for display submenu selection.
	displayMenu = glutCreateMenu(displaySubMenu);
		glutAddMenuEntry("WireFrame", 0);
		glutAddMenuEntry("Constant Shading", 1);
		glutAddMenuEntry("Interpolative Shading", 2);
	//Create menu and menu options for the main menu.
	glutCreateMenu(mainMenu);
		glutAddSubMenu("Display Mode", displayMenu);
		glutAddSubMenu("Materials", materialMenu);
		glutAddMenuEntry("Toggle Lights Mode", 0);
		glutAddMenuEntry("Exit Program", 1);

	//Bind main menu to the right mouse button.
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//Register keyboard function with glut.
	glutKeyboardFunc(keyboard);

	//Enter glut main loop and listen for events.
	glutMainLoop();
}