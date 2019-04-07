#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <string.h>

// Callback functions
void render(void);
void keyboard(int key, int x, int y);

void delay();

int milisec = 50; // length of time to sleep, in miliseconds
struct timespec req = {0};

int posX = 0;
int posY = 0;
int fruitX = 20;
int fruitY = 20;
int tailX[100] = {};
int tailY[100] = {};
int tailLength = 0;

enum direction{u, d, l, r};
enum direction dir = r;

float size = 0.02;
int cols = 100;
int rows = 100;

/* srand(time(NULL));   // Initialization, should only be called once. */

int main(int argc, char ** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Snake");
	glutDisplayFunc(render);
	glutSpecialFunc(keyboard);

	glutMainLoop();
	
	return 0;
}

void render(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRasterPos2d(-1.0,-1.0);
	glColor3f(0,0,0);
	char ks[3];
	sprintf(ks,"%d",tailLength);
	for(int i = 0; i<strlen(ks); i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ks[i]);
	}

	for(int i = tailLength; i>0; i--){
		tailX[i] = tailX[i-1];
		tailY[i] = tailY[i-1];
	}
	tailX[0] = posX;
	tailY[0] = posY;

	if(dir == r){
		posX++;
	}else if(dir == l){
		posX--;
	}else if(dir == u){
		posY--;
	}else if(dir == d){
		posY++;
	}

	if((posX == fruitX) && (posY == fruitY)){
		fruitX = rand() % 100;
		fruitY = rand() % 100;
		tailLength++;
	}

	// Draw fruit
	glBegin(GL_POLYGON);
	glColor3f(0.55, 1, 0.55);
	glVertex2f(-1+size*fruitX,1-size*fruitY);
	glVertex2f(-1+size+size*fruitX,1-size*fruitY);
	glVertex2f(-1+size+size*fruitX,1-size-size*fruitY);
	glVertex2f(-1+size*fruitX,1-size-size*fruitY);
	glEnd();

	// Draw head
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-1+size*posX,1-size*posY);
	glVertex2f(-1+size+size*posX,1-size*posY);
	glVertex2f(-1+size+size*posX,1-size-size*posY);
	glVertex2f(-1+size*posX,1-size-size*posY);
	glEnd();

	for(int i = 0; i<tailLength; i++){
		if((tailX[i] == posX) && (tailY[i] == posY)){
			exit(1);
		}
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex2f(-1+size*tailX[i],1-size*tailY[i]);
		glVertex2f(-1+size+size*tailX[i],1-size*tailY[i]);
		glVertex2f(-1+size+size*tailX[i],1-size-size*tailY[i]);
		glVertex2f(-1+size*tailX[i],1-size-size*tailY[i]);
		glEnd();
	}

	delay();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(int key, int x, int y){
	if(key == GLUT_KEY_RIGHT){
		dir = r;
	}else if(key == GLUT_KEY_LEFT){
		dir = l;
	}else if(key == GLUT_KEY_UP){
		dir = u;
	}else if(key == GLUT_KEY_DOWN){
		dir = d;
	}
}

void delay(){
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000000L;
	nanosleep(&req, (struct timespec *)NULL);
}

