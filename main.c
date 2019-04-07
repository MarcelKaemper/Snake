#include <stdio.h>
#include <GL/glut.h>

// Callback functions
void render(void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char ** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Snake");
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	
	return 0;
}

void render(void){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glutPostRedisplay();
		glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){

}
