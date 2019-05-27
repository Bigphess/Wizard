#define GLFW_INCLUDE_GLU
#include <glfw/glfw3.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif



void init(int argc, char* argv[])
{
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void drawsurfaces(double p, int lats, int longs) {
	int i, j;
		for (i = 1; i <= (lats); i++) {
		double lat0 = M_PI * ( (double)(i - 1) / (4*lats));
		
		double z0 = (p / (1 - sin(lat0)))* sin(lat0) + p / 2;
		double zr0 = (p / (1 - sin(lat0))) * cos(lat0);

		double lat1 = M_PI * ( (double)i / (4 * lats));
		
		double z1 = (p / (1 - sin(lat1))) * sin(lat1) + p / 2;
		double zr1 = (p / (1 - sin(lat1))) * cos(lat1);
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3d(x * zr0, y * zr0, z0);
			glVertex3d(x * zr0, y * zr0, z0);
			glNormal3d(x * zr1, y * zr1, z1);
			glVertex3d(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}


void display(GLFWwindow* window)
{

	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, ((double)width / (double)height), 10, 100);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);





	glColor4d(1.0, 1.0, 1.0, 1.0);
	drawsurfaces(0.8, 20, 20);
	glTranslatef(0.0, 0.0, 0.4);

	glBegin(GL_POLYGON);
	int n = 20;
	for (int i = 0; i < n; i++)
	{
		glVertex2f(0.8 * cos(2 * M_PI * i / n), 0.8 * sin(2 * M_PI * i / n));  
	}

	glEnd();

	GLfloat Va[] = { 0.3,0.3,0.3,1.0 };
	GLfloat Vd[] = { 0.6,0.6,0.6,1.0 };
	GLfloat Vs[] = { 0.6,0.6,0.6,1.0 };
	GLfloat Vp[] = { 0.0,0.0,1.0,0.25 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, Va);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Vd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Vs);
	glLightfv(GL_LIGHT0, GL_POSITION, Vp);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	
}

void reshape(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, ((GLfloat)width / (GLfloat)height), 10, 100);
	gluLookAt(0.0, -10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char* argv[]) {

	GLFWwindow* window;


	if (!glfwInit())
		return -1;

		window = glfwCreateWindow(640, 480, "cup", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	glfwSetFramebufferSizeCallback(window, reshape);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	init(argc, argv);

	while (!glfwWindowShouldClose(window))
	{

		display(window);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}