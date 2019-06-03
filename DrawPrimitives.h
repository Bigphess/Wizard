
#define GLFW_INCLUDE_GLU
//#include <GLFW/glfw3.h>
//#include <GL/gl.h>

#include <math.h>


/* PI */
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif


//pink
//glColor4f(0.96f, 0.61f, 0.69f,1.0f);
//brown
//glColor4f(0.37f, 0.15f, 0.12f,1.0f)
//237,87,53


void drawSphere(double r, int lats, int longs) {
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = r * sin(lat0);
        double zr0 = r *  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1  = r * sin(lat1);
        double zr1 = r * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f((GLfloat)(x * zr0), (GLfloat)(y * zr0), (GLfloat)z0);
            glVertex3f((GLfloat)(x * zr0), (GLfloat)(y * zr0), (GLfloat)z0);
            glNormal3f((GLfloat)(x * zr1), (GLfloat)(y * zr1), (GLfloat)z1);
            glVertex3f((GLfloat)(x * zr1), (GLfloat)(y * zr1), (GLfloat)z1);
        }
        glEnd();
    }
}


void solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
    glBegin(GL_LINE_LOOP);
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);

    gluCylinder(quadric, base, 0, height, slices, stacks);

    gluDeleteQuadric(quadric);
    glEnd();
}

// Added in Exercise 9 - Start *****************************************************************
void drawSnowman( bool female = 0)
{
    glRotatef( -90, 1, 0, 0 );
    glScalef(0.03f, 0.03f, 0.03f);

    // draw 3 white spheres
    glColor4f( 1.0, 1.0, 1.0, 1.0 );
    drawSphere( 0.8, 10, 10 );
    glTranslatef( 0.0f, 0.8f, 0.0f );
    drawSphere( 0.6, 10, 10 );
    if(female)
    {
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-0.2f, 0.05f, 0.3f);
        drawSphere( 0.32, 10, 10 );
        glTranslatef(0.4f, 0, 0);
        drawSphere( 0.32, 10, 10 );
        glPopMatrix();
    }
    glTranslatef( 0.0f, 0.6f, 0.0f );
    drawSphere( 0.4, 10, 10 );

    // draw the eyes
    glPushMatrix();
    glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
    glTranslatef( 0.2f, 0.2f, 0.2f );
    drawSphere( 0.066, 10, 10 );
    glTranslatef( 0, 0, -0.4f );
    drawSphere( 0.066, 10, 10 );
    glPopMatrix();

    // draw a nose
    glColor4f( 1.0f, 0.5f, 0.0f, 1.0f );
    glTranslatef( 0.3f, 0.0f, 0.0f );
    glRotatef( 90, 0, 1, 0 );
    solidCone( 0.1, 0.3, 10, 10 );
}
// Added in Exercise 9 - End *****************************************************************

double circle_scale = 0.01;

void Circle()
{
    glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串
    glVertex3f(0.0f, 0.0f, 0.0f);
    int i = 0;
    for (i = 0; i <= 390; i += 15)
    {
        float p = i * 3.14 / 180;
        glVertex3f(circle_scale * sin(p), circle_scale * cos(p), 0.0f);
    }
    glEnd();
}

void drawCyliner(){
    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    glColor4f(0.93f, 0.34f, 0.21f,1.0f);
    int i = 0;
    for (i = 0; i <= 390; i += 15)
    {
        float p = i * 3.14 / 180;
        glVertex3f(circle_scale * sin(p), circle_scale * cos(p), 0.5f);
        glVertex3f(circle_scale * sin(p), circle_scale * cos(p), 0.0f);
    }
    glEnd();
    Circle();
    glTranslatef(0, 0, 0.5);
    Circle();
}



static const float vertex_list[][3] =
{
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
};


static const GLint index_list[][2] =
{
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7},
    {0, 2},
    {1, 3},
    {4, 6},
    {5, 7},
    {0, 4},
    {1, 5},
    {7, 3},
    {2, 6}
};




void drawFullStar(){
    double z = 0.1f;
    const double PI = acos(0.) * 2;
    double L1=0.2*cos(36*PI/180);
    double L2=0.2*sin(36*PI/180);
    double L3=0.2*cos(72*PI/180);
    double L4=0.2*sin(72*PI/180);
    double L5=L2*tan(72*PI/180);
    double L6=L2/cos(72*PI/180);
    double L7=L6*sin(54*PI/180);
    double L8=L6*cos(54*PI/180)+0.2;

//    draw two stars
    glBegin(GL_POLYGON);     //设置绘制类型为多边形

    glColor3f(0.96f,0.83f,0.85f);

    glVertex3f(0.0f,0.0f,z);
    glVertex3f(0.0f,L5+L1,z);    //1
    glVertex3f(L2,L1,z);    //2
    glVertex3f(L2+L6,L1,z);    //3
    glVertex3f(L4,-L3,z);    //4
    glVertex3f(L7,-L8,z);    //5
    glVertex3f(0.0f,-0.2f,z);    //6
    glVertex3f(-L7,-L8,z);    //7
    glVertex3f(-L4,-L3,z);   //8
    glVertex3f(-L2-L6,L1,z);   //9
    glVertex3f(-L2,L1,z);   //10
    glVertex3f(0.0f,L5+L1,z);

    glVertex3f(0.0f,0.0f,-z);
    glVertex3f(0.0f,L5+L1,-z);    //1
    glVertex3f(L2,L1,-z);    //2
    glVertex3f(L2+L6,L1,-z);    //3
    glVertex3f(L4,-L3,-z);    //4
    glVertex3f(L7,-L8,-z);    //5
    glVertex3f(0.0f,-0.2f,-z);    //6
    glVertex3f(-L7,-L8,-z);    //7
    glVertex3f(-L4,-L3,-z);   //8
    glVertex3f(-L2-L6,L1,-z);   //9
    glVertex3f(-L2,L1,-z);   //10
    glVertex3f(0.0f,L5+L1,-z);

    glEnd();
    glFlush();

//    connect two stars
    glBegin(GL_QUAD_STRIP);
    glColor4f(0.96f, 0.61f, 0.69f,1.0f);
    glVertex3f(0.0f,L5+L1,z);
    glVertex3f(0.0f,L5+L1,-z);
    glVertex3f(L2,L1,z);
    glVertex3f(L2,L1,-z);
    glVertex3f(L2+L6,L1,z);
    glVertex3f(L2+L6,L1,-z);
    glVertex3f(L4,-L3,z);
    glVertex3f(L4,-L3,-z);
    glVertex3f(L7,-L8,z);
    glVertex3f(L7,-L8,-z);
    glVertex3f(0.0f,-0.2f,z);    //6
    glVertex3f(0.0f,-0.2f,-z);
    glVertex3f(-L7,-L8,z);    //7
    glVertex3f(-L7,-L8,-z);
    glVertex3f(-L4,-L3,z);
    glVertex3f(-L4,-L3,-z);  //8
    glVertex3f(-L2-L6,L1,z);
    glVertex3f(-L2-L6,L1,-z);  //9
    glVertex3f(-L2,L1,z);
    glVertex3f(-L2,L1,-z);   //10
    glVertex3f(0.0f,L5+L1,z);
    glVertex3f(0.0f,L5+L1,-z);

    glEnd();
    glFlush();


//    draw the balls

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f,L5+L1,0.0f);
    drawSphere( z/2, 10, 10 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(L2+L6,L1,0.0f);
    drawSphere( z/2, 10, 10 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(L7,-L8,0.0f);
    drawSphere( z/2, 10, 10 );
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-L7,-L8,0.0f);
    drawSphere( z/2, 10, 10 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-L2-L6,L1,0.0f);
    drawSphere( z/2, 10, 10 );
    glPopMatrix();

}


void drawWand(bool wave = 0){
    //    glPushMatrix();
    glRotated(-90, 1.0, 0.0, 0.0);
    glRotated(-90, 0.0, 1.0, 0.0);
    glScaled(0.1, 0.1, 0.1);
    drawCyliner();
    glTranslatef( 0.0, 0.0, 0.0 );
    glRotated(-90, 1.0, 0.0, 0.0);
    glRotated(-112.5, 0.0, 0.0, 1.0);
    glColor4f( 0.0, 0.0, 0.0, 1.0 );
    glScaled(0.3, 0.3, 0.3);
    drawFullStar();
}

void drawCylinder(GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks) {

  glPushMatrix();
  glRotatef(180, 0, 1, 0);
  glBegin(GL_QUAD_STRIP);
  GLUquadricObj* quadric = gluNewQuadric();
  gluQuadricDrawStyle(quadric, GLU_FILL);

  gluCylinder(quadric, base, top, height, slices, stacks);

  gluDeleteQuadric(quadric);
  glEnd();
  glPopMatrix();

}

void drawPetal(double r, int longs) {

  double theta, x, y, z;

  glBegin(GL_POLYGON);
  for (int i = 0; i < longs; i++) {
      theta = i * M_PI / (longs * 2);
      x = r * sin(2 * theta) * cos(theta);
      y = r * sin(2 * theta) * sin(theta);
      z = (-1) * abs(M_PI / 4 - theta) + M_PI / 4;
      glColor4f(1, z, z, 1);
      glVertex3f(x, y, z);
  }
  glEnd();

}


void drawLeaf(double r, int longs) {

    double theta, x, y, z;

    glBegin(GL_POLYGON);
    for (int i = 0; i < longs; i++) {
        theta = i * M_PI / (longs * 2);
        x = r * sin(2 * theta) * cos(theta);
        y = r * sin(2 * theta) * sin(theta);
        z = (-1) * abs(M_PI / 4 - theta) + M_PI / 4;
        glColor4f(z, 1, z, 1);
        glVertex3f(x, y, z);
    }
    glEnd();


    theta = M_PI / 4;
    x = r * sin(2 * theta) * cos(theta);
    y = r * sin(2 * theta) * sin(theta);
    z = (-1) * abs(M_PI / 4 - theta) + M_PI / 4;
    glBegin(GL_LINES);
    glColor4f(1, 1, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(x, y, z);
    glEnd();
}



void drawFlower() {

    glScalef(0.5, 0.5, 0.5);
    glColor4f(0.1, 0.9, 0.1, 1);
    drawCylinder(0.1, 0.1, 3, 20, 20);

    for (int i = 0; i < 5; i++) {
        drawPetal(2.5, 20);
        glRotatef(72, 0, 0, 1);
    }

    glPushMatrix();
    glTranslatef(0, 0, -1);
    drawLeaf(1.5, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0.15);
    glColor4f(1, 1, 0, 1);
    glScalef(0.2, 0.2, 0.2);
    drawSphere(1, 10, 10);
    glPopMatrix();
}

void drawDeadPetal(double r, int longs) {

  double theta, x, y, z;

  glBegin(GL_POLYGON);
  for (int i = 0; i < longs; i++) {
      theta = i * M_PI / (longs * 2);
      x = r * sin(2 * theta) * cos(theta);
      y = r * sin(2 * theta) * sin(theta);
      z = (-1) * abs(M_PI / 4 - theta) + M_PI / 4;
      glColor4f(1, 0.5, 0.4, 1);
      //glColor4f(1, z, 1, 1);
      glVertex3f(x, y, -z);
  }
  glEnd();

}

void drawDeadFlower() {
  glScalef(0.5, 0.5, 0.5);
  glColor4f(0.56, 0.45, 0.2, 1);
  drawCylinder(0.1, 0.1, 3, 20, 20);

  for (int i = 0; i < 2; i++) {
      drawDeadPetal(2.5, 20);
      glRotatef(100, 0, 0, 1);
  }


  glPushMatrix();
  glTranslatef(0, 0, 0.05);
  glColor4f(0.5, 0.4, 0.2, 1);
  glScalef(0.2, 0.2, 0.2);
  drawSphere(1, 10, 10);
  glPopMatrix();
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

void drawCup() {
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
	glBegin(GL_POLYGON);
	glColor4f(0.1, 0.3, 0.7, 0.3);

  //Water
	for (int i = 0; i < n; i++)
	{
		glVertex3f(1.6 * cos(2 * M_PI * i / n), 1.6 * sin(2 * M_PI * i / n), 1.5);
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
