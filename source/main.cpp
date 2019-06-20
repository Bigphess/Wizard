

#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>


#include <iostream>
#include <iomanip>
#include <opencv2/core.hpp>    // include OpenCV core headers
#include <opencv2/imgproc.hpp> // include image processing headers
#include <opencv2/highgui.hpp> // include GUI-related headers


#include "PoseEstimation.h"
#include "MarkerTracker.h"
#include "DrawPrimitives.h"


// You need to change the size of window and the value of scale when you use different camera


struct Position { double x,y,z; };

bool debugmode = false;
bool balldebug = false;

float resultTransposedMatrix[16];
float snowmanLookVector[4];
int towards = 0x005A;
int towardsList[2] = {0x005a, 0x0272};
int towardscounter = 0;
Position ballpos;
int ballspeed = 100;

//camera settings
// if use web camera
//const int camera_width  = 640;
//const int camera_height = 480;
// if use mac's camera
const int camera_width  = 1280;
const int camera_height = 720;
const int virtual_camera_angle = 30;
unsigned char bkgnd[camera_width*camera_height*3];


//add_tanaka start
bool cup = false;
bool flower = false;
float predist_cup = 0.0;
float predist_flower = 0.0;
//add_tanaka end


void InitializeVideoStream( cv::VideoCapture &camera ) {
    if( camera.isOpened() )
        camera.release();

    camera.open(0); // open the default camera
    if ( camera.isOpened()==false ) {
        std::cout << "No webcam found, using a video file" << std::endl;
        camera.open("MarkerMovie.mpg");
        if ( camera.isOpened()==false ) {
            std::cout << "No video file found. Exiting."      << std::endl;
            exit(0);
        }
    }
}


/* program & OpenGL initialization */
void initGL(int argc, char *argv[])
{
    // initialize the GL library
    // pixel storage/packing stuff
    glPixelStorei(GL_PACK_ALIGNMENT, 1);// for glReadPixels
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // for glTexImage2D
    glPixelZoom(1.0, -1.0);
    // Added in Exercise 8 - End *****************************************************************
    // enable and set colors
    glEnable( GL_COLOR_MATERIAL );
    glClearColor( 0, 0, 0, 1.0 );

    // enable and set depth parameters
    glEnable( GL_DEPTH_TEST );
    glClearDepth( 1.0 );

}

void display(GLFWwindow* window, const cv::Mat &img_bgr, std::vector<Marker> &markers)
{
    const auto camera_image_size = sizeof(unsigned char) *img_bgr.rows*img_bgr.cols * 3;
    auto background_buffer_size = sizeof(bkgnd);
    memcpy(bkgnd, img_bgr.data, background_buffer_size);
    
    int width0, height0;
    glfwGetFramebufferSize(window, &width0, &height0);

    // clear buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draw background image
    glDisable( GL_DEPTH_TEST );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0.0, camera_width, 0.0, camera_height );

    glRasterPos2i( 0, camera_height-1 );
    glDrawPixels( camera_width, camera_height, GL_BGR, GL_UNSIGNED_BYTE, bkgnd );

    glPopMatrix();

    glEnable(GL_DEPTH_TEST);


    // move to marker-position
    glMatrixMode( GL_MODELVIEW );


//    14b7for testing **********************
//    float resultMatrix_14B7[16];
//    for(int i=0; i<markers.size(); i++){
//        const int code =markers[i].code;
//        if(code == 0x14B7) {
//            for(int j=0; j<16; j++)
//                resultMatrix_14B7[j] = markers[i].resultMatrix[j];
//        }
//
//    }
//
//
//    for (int x=0; x<4; ++x)
//        for (int y=0; y<4; ++y)
//            resultTransposedMatrix[x*4+y] = resultMatrix_14B7[y*4+x];
//
//
//
//    float scale = 0.3;
//    resultTransposedMatrix[12] *= scale;  // x方向のスケール調整
//    resultTransposedMatrix[13] *= scale;  // y方向のスケール調整
//
//
//    //glLoadTransposeMatrixf( resultMatrix );
//    glLoadMatrixf( resultTransposedMatrix );
//    drawCup();
//14b7 for testing end *****************************

    
//    takana ******************
    
    float resultMatrix_005A[16];
    float resultMatrix_21ee[16];
    float resultMatrix_1d59[16];
    for(int i=0; i<markers.size(); i++){
        const int code =markers[i].code;


        //change makar_id here
        //object(cup)->14b7
        //object(flower) -> 1d59
        //魔法棒 -> 21ee

        if(code == 0x14b7) {
            for(int j=0; j<16; j++)
                resultMatrix_005A[j] = markers[i].resultMatrix[j];
        }else if(code == 0x21ee){
            for(int j=0; j<16; j++)
                resultMatrix_21ee[j] = markers[i].resultMatrix[j];
        }else if(code == 0x1d59){
            for(int j=0; j<16; j++)
                resultMatrix_1d59[j] = markers[i].resultMatrix[j];
        }
    }

    float scale = 0.3; //0.5 for web camera
    resultMatrix_005A[3] *= scale;
    resultMatrix_005A[7] *= scale;
    resultMatrix_21ee[3] *= scale;
    resultMatrix_21ee[7] *= scale;
    resultMatrix_1d59[3] *= scale;
    resultMatrix_1d59[7] *= scale;
    
    
    //    wand
    for (int x=0; x<4; ++x)
        for (int y=0; y<4; ++y)
            resultTransposedMatrix[x*4+y] = resultMatrix_21ee[y*4+x];
    glLoadMatrixf( resultTransposedMatrix );
    drawWand();
    
    float offset[4];
    offset[0] = -0.04 * resultMatrix_21ee[0] + resultMatrix_21ee[3];
    offset[1] = -0.04 * resultMatrix_21ee[4] + resultMatrix_21ee[7];
    offset[2] = -0.04 * resultMatrix_21ee[8] + resultMatrix_21ee[11];
    offset[3] = -0.04 * resultMatrix_21ee[12] + resultMatrix_21ee[15];
    
    /*****debug for wand position****
      glLoadIdentity();
      glTranslatef((float)offset[0]/offset[3],(float)offset[1]/offset[3],(float)offset[2]/offset[3]);
      glColor4f(1,0,0,1);
      drawSphere(0.008,10,10);
    /*********************************/
    
    float dff_x = pow(resultMatrix_005A[3]-offset[0]/offset[3],2);
    float dff_y = pow(resultMatrix_005A[7]-offset[1]/offset[3],2);
    float dff_z = pow(resultMatrix_005A[11]-offset[2]/offset[3],2);
    //printf("%f\n",sqrt(dff_x + dff_y + dff_z));
    float dist_cup =sqrt(dff_x + dff_y + dff_z);
    if(predist_cup >= 0.03 && dist_cup < 0.03 &&( predist_cup - dist_cup < 0.1 )) cup = !cup;
    printf("dist = %f,%f,%f\n",dff_x ,dff_y ,dff_z);
    printf("%f\n",sqrt(dff_x + dff_y + dff_z));
    if(cup){
        printf("true\n");
    }else{
        printf("false\n");
    }
    
    dff_x = pow(offset[0]/offset[3]-resultMatrix_1d59[3],2);
    dff_y = pow(offset[1]/offset[3]-resultMatrix_1d59[7],2);
    dff_z = pow(offset[2]/offset[3]-resultMatrix_1d59[11],2);

    float dist_flower =sqrt(dff_x + dff_y + dff_z);
    if(predist_flower >= 0.03 && dist_flower < 0.03 &&( predist_flower - dist_flower < 0.1 )) flower = !flower;
    
    
    //flower
    for (int x=0; x<4; ++x)
        for (int y=0; y<4; ++y)
            resultTransposedMatrix[x*4+y] = resultMatrix_1d59[y*4+x];
    glLoadMatrixf( resultTransposedMatrix );
    
    if(flower){
        drawFlower();
    }else{
        drawDeadFlower();
    }
    
    
    //cup
    for (int x=0; x<4; ++x)
        for (int y=0; y<4; ++y)
            resultTransposedMatrix[x*4+y] = resultMatrix_005A[y*4+x];
    glLoadMatrixf( resultTransposedMatrix );
    drawCup(cup);
    

    
    predist_cup = dist_cup;
    predist_flower = dist_flower;
//    tanaka **********************
    
    
    

    int key = cv::waitKey (10);
    if (key == 27) exit(0);
}

void reshape( GLFWwindow* window, int width, int height ) {

    // set a whole-window viewport
    glViewport( 0, 0, (GLsizei)width, (GLsizei)height );

    // create a perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 30, ((GLfloat)width/(GLfloat)height), 0.01, 100 );

    // invalidate display
    //glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    cv::VideoCapture cap;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    // initialize the window system
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(camera_width/2, camera_height/2, "Wizards", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Set callback functions for GLFW
    glfwSetFramebufferSizeCallback(window, reshape);

    glfwMakeContextCurrent(window);
    glfwSwapInterval( 1 );

    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    reshape(window, window_width, window_height);

    glViewport(0, 0, window_width, window_height);

    // initialize the GL library
    initGL(argc, argv);

    // setup OpenCV
    cv::Mat img_bgr;
    InitializeVideoStream(cap);
    const double kMarkerSize = 0.048;// 0.048; // [m]
    MarkerTracker markerTracker(kMarkerSize,87,95);

    std::vector<Marker> markers;
    //    float resultMatrix[16];
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        markers.resize(0);
        /* Capture here */
        cap >> img_bgr;

        if(img_bgr.empty()){
            std::cout << "Could not query frame. Trying to reinitialize." << std::endl;
            InitializeVideoStream(cap);
            cv::waitKey(1000); /// Wait for one sec.
            continue;
        }

        /* Track a marker */
        markerTracker.findMarker( img_bgr, markers);///resultMatrix);
        

        /* Render here */
        display(window, img_bgr, markers);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;

}
