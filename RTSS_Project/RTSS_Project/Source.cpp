//
//  main.cpp
//  Ders 6
//
//  Created by Gurel Erceis on 3/17/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//
// Thing to install and test before writing any code
// glm
// assimp (http://assimp.sourceforge.net/main_downloads.html)

// Haftaya Odev
// att = 1.0 / (Kc + Kl*d + Kq*d2)
//where d stands for the distance between the position of the light and the currenlty processed vertex:
//
//In OpenGL terms, attenuation factors are defined by:
//
//glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f );	
//glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION , 0.0f );	
//glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION , 0.0002 );

// (gl_LightSource[0].constantAttenuation + 
// (gl_LightSource[0].linearAttenuation*d) + 
// (gl_LightSource[0].quadraticAttenuation*d*d) );

#define RESOURCE_PATH ""
// "C:\\Users\\Gurel\\Dropbox\\Ders 7\\Ders 7\\"
#ifdef _WIN32
#include <stdio.h>
#include <windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/glut.h>
//#include <glut.h>
#else if __APPLE__
#include <GLUT/GLUT.h>
#endif

#include <iostream>
#include "Scene.h"

#include "ScreenSpaceShaderNode.h"
#include "NormalShaderNode.h"
#include "ColorFillNode.h"
#include "DiffusePerPixelNode.h"
#include "DiffusePerVertexNode.h"
#include "SimpleEffect.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"



#define WINDOW_TITLE_PREFIX "Ders 7"

void IdleFunction(void);
void ResizeFunction(int Width, int Height);
void setupScene();

unsigned FrameCount = 0;

int CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0, mouseX = 0, mouseY = 0;

SceneNode* pad1;
SceneNode* pad2;
Light* light;

Camera *camera;

Scene* scene;

float directionX = 1;
float directionY = 0.5;
float speed = 0.001;

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    scene->draw();
    
    glutSwapBuffers();
    FrameCount++;
}

GLboolean wire = false;

static void Key(unsigned char key, int x, int y)
{
    printf("%d", key);
    switch (key) {
		case 27: // ESC
			exit(0);
            break;
        case 'q': 
			pad1->rotate(5.f, 0, 1.0f, 0);
            pad2->rotate(5.f, 0, 1.0f, 0);
            break;
        case 'e': 
			pad1->rotate(-5.f, 0, 1.0f, 0);
            pad2->rotate(-5.f, 0, 1.0f, 0);
            break;
        case 'a':
            light->translate(-100, 0, 0);
            break;
        case 'd':
            light->translate(100, 0, 0);
            break;
        case 'w': 
            if( !wire )
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
               glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
                wire=!wire;
            break;
	}
}
void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
    scene->resize();
}

static void timerCallback (int value)
{
    if (0 != value) {
		char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));
        
		sprintf(
                TempString,
                "%s: %d Frames Per Second @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FrameCount * 4,
                CurrentWidth,
                CurrentHeight
                );
        
		glutSetWindowTitle(TempString);
		free(TempString);
	}
	FrameCount = 0;
	glutTimerFunc(250, timerCallback, 1);
}

void IdleFunction(void)
{
	glutPostRedisplay();
}

void setupScene(){
    scene = new Scene();
    
    pad1 = new DiffusePerPixelNode("Batman.obj");
    
    pad2 = new DiffusePerVertexNode("Batman.obj");

    pad1->translate(-80, 0, 0);
    
    pad2->translate(80, 0, 0);
    
    scene->addNode(pad1);
    scene->addNode(pad2);
    
    camera = new Camera();
    
    camera->translate(0.f, 100.f, 400.f);

    scene->setCamera(camera);
    
    scene->addEffect(new SimpleEffect(&CurrentWidth,&CurrentHeight));
    
    light = new Light();
    light->translate(0, 300.f, 400.f);
    
    scene->addLight(light);
}

int main (int argc, char ** argv)
{
    
    GLenum type;
    
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth,CurrentHeight);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("");
#ifdef _WIN32
    GLenum err = glewInit();
	if (GLEW_OK != err)
	{
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("GLSL Version: %s\n",glslVersion);
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    
    printf("GL Version: %s\n",glVersion);
    
    glClearColor(0.0, 1.0, 0.0, 1.0);
    // Z-Buffer i aciyoruz
    glEnable(GL_DEPTH_TEST);
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
    
       
    setupScene();
    
    timerCallback(0);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutIdleFunc(IdleFunction);
    glutMainLoop();
    
    return 0;
}


