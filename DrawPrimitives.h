
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


//kyo
double circle_scale = 0.01;

void Circle()
{
    glBegin(GL_TRIANGLE_FAN);
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
    GLfloat gray[] = {0.75f, 0.75f, 0.75f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
    glBegin(GL_QUAD_STRIP);
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


// kyo
void drawWand(){
    
    glRotated(-90, 1.0, 0.0, 0.0);
    glRotated(-90, 0.0, 1.0, 0.0);
    glScaled(0.08, 0.08, 0.08);
    drawCyliner();
    glTranslatef( 0.0, 0.0, 0.0 );
    glRotated(-90, 1.0, 0.0, 0.0);
    glRotated(-112.5, 0.0, 0.0, 1.0);
    glColor4f( 0.0, 0.0, 0.0, 1.0 );
    glScaled(0.3, 0.3, 0.3);
    drawFullStar();
}



//saito

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
    
    glScalef(0.007, 0.007, 0.007);
    glRotated(180, 1.0f, 0.0f, 0.0f);
    glColor4f(0.1, 0.9, 0.1, 1);
    glTranslatef(0, 0, 3);
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
    glPushMatrix();
    
    double theta, x, y, z;
    glColor4f(0.6, 0.3, 0.2, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < longs; i++) {
        theta = i * M_PI / (longs * 2);
        x = r * sin(2 * theta) * cos(theta);
        y = r * sin(2 * theta) * sin(theta);
        z = abs(M_PI / 4 - theta) - M_PI / 4;
        glVertex3f(x, y, -x*y);
    }
    glEnd();
    glPopMatrix();
}

void drawDeadFlower() {
    glRotated(180, 1, 0, 0);
    glScalef(0.008, 0.008, 0.008);
    glTranslatef(0, 0, 3);
    glColor4f(0.56, 0.44, 0.2, 1);
    drawCylinder(0.1, 0.1, 4, 20, 20);
    
    glRotated(180, 1, 0, 0);
    for (int i = 0; i < 20; i++) {
        glRotated(-160/20, 1, 0, 0);
        drawCylinder(0.1, 0.1, 0.1, 20, 20);
        glTranslatef(0, 0, -0.1);
    }
    drawCylinder(0.1, 0.1, 0.5, 20, 20);
    glTranslatef(0, 0, -0.5);
    
    glScalef(0.6, 0.6, 0.6);
    
    for (int i = 0; i < 5; i++) {
        drawDeadPetal(2, 20);
        glRotatef(72, 0, 0, 1);
    }
    
    glPushMatrix();
    glTranslatef(0, 0, -0.08);
    glColor4f(0.5, 0.4, 0.2, 1);
    glScalef(0.2, 0.2, 0.2);
    drawSphere(0.6, 10, 10);
    glPopMatrix();
}


// yuke
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

void drawdisk(double r)
{
    glBegin(GL_POLYGON);
    int n = 20;
    for (int i = 0; i < n; i++)
    {
        glVertex2f(r * cos(2 * M_PI * i / n), r * sin(2 * M_PI * i / n));
    }
    
    glEnd();
}

void drawCup(bool water) {
    
    GLfloat Va[] = { 1.0,1.0,1.0,1.0 };
    GLfloat Vd[] = { 0.6,0.6,0.6,1.0 };
    GLfloat Vs[] = { 0.6,0.6,0.6,1.0 };
    GLfloat Vp[] = { 1.0,1.0,1.0,1.0 };
    //
    glLightfv(GL_LIGHT0, GL_AMBIENT, Va);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Vd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Vs);
    glLightfv(GL_LIGHT0, GL_POSITION, Vp);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
//
    GLfloat earth_mat_ambient[]   = { 0.05,0.05,0.05,1.0};  //定义材质的环境光颜色，骗蓝色
    GLfloat earth_mat_diffuse[]   = {0.06f, 0.06f, 0.06f, 1.0f};  //定义材质的漫反射光颜色，偏蓝色
    GLfloat earth_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
//    GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射光颜色，为0
    GLfloat earth_mat_shininess   = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
////    glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
//    glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
    
    glColor4d(1.0, 1.0, 1.0, 1.0);
    //change position
    glScaled(0.01f, 0.01f, 0.01f);
    glRotated(180, 1.0f, 0.0f, 0.0f);
    
    drawsurfaces(0.8, 20, 20);
    glTranslatef(0.0, 0.0, 0.4);
    
    drawdisk(0.8);
    
//    //Water
//    drawdisk(1.6);
    if (water) {
    glBegin(GL_POLYGON);
    glColor4f(0.1, 0.3, 0.7, 0.3);
    //Water
    int n =20;
    for (int i = 0; i < n; i++)
    {
        glVertex3f(1.6 * cos(2 * M_PI * i / n), 1.6 * sin(2 * M_PI * i / n), 1.5);
    }
    glEnd();
    }
    
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}
