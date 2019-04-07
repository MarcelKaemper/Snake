#include <stdio.h>
#include <GL/glut.h>

// Callback functions
void render(void);
void keyboard(int key, int x, int y);

int posX = 0;
int posY = 0;
int fruitX = 20;
int fruitY = 20;

enum direction{u, d, l, r};
enum direction dir = r;

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

	if(dir == r){
		posX++;
	}else if(dir == l){
		posX--;
	}else if(dir == u){
		posY--;
	}else if(dir == d){
		posY++;
	}



	for(int i = 0; i<cols; i++){
		for(int j = 0; j<rows; j++){
			glBegin(GL_POLYGON);
			if((i == posY) && (j == posX)){
				glColor3f(1, 1, 1);
				glVertex2f(-1+size*j,1-size*i);
				glVertex2f(-1+size+size*j,1-size*i);
				glVertex2f(-1+size+size*j,1-size-size*i);
				glVertex2f(-1+size*j,1-size-size*i);
			}else if((i == fruitX) && (j == fruitY)){
				glColor3f(0, 1, 0.55);
				glVertex2f(-1+size*j,1-size*i);
				glVertex2f(-1+size+size*j,1-size*i);
				glVertex2f(-1+size+size*j,1-size-size*i);
				glVertex2f(-1+size*j,1-size-size*i);
			}else{
				glColor3f(0, 0, 0);
			}


			glEnd();
			glFlush();
		}
	}		

	glutPostRedisplay();
	glutSwapBuffers();
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
