#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

// Callback functions
void render(void);
void keyboard(int key, int x, int y);

void delay();
int milisec = 50; // length of time to sleep, in miliseconds
struct timespec req = {0};

int posX = 0;
int posY = 0;
int tempX;
int tempY;
int fruitX = 20;
int fruitY = 20;
int tail = 0;

enum direction{u, d, l, r};
enum direction dir = r;

/* srand(time(NULL));   // Initialization, should only be called once. */

int main(int argc, char ** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Snake");
	glutDisplayFunc(render);
	glutSpecialFunc(keyboard);

	glutMainLoop();
	
	return 0;
}

void render(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float size = 0.02;
	int cols = 100;
	int rows = 100;

	for(int i = 0; i<=tail; i++){
		tempX = posX;
		tempY = posY;
	}

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
		printf("Score");
		fruitX = rand() % 100;
		fruitY = rand() % 100;
		tail++;
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
	glColor3f(1, 1, 1);
	glVertex2f(-1+size*posX,1-size*posY);
	glVertex2f(-1+size+size*posX,1-size*posY);
	glVertex2f(-1+size+size*posX,1-size-size*posY);
	glVertex2f(-1+size*posX,1-size-size*posY);
	glEnd();

	// Draw tail
	for(int i = 0; i<tail; i++){
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex2f(-1+size*tempX,1-size*tempY);
		glVertex2f(-1+size+size*tempX,1-size*tempY);
		glVertex2f(-1+size+size*tempX,1-size-size*tempY);
		glVertex2f(-1+size*tempX,1-size-size*tempY);
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
