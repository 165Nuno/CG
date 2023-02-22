#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

GLdouble x_mover;
GLdouble y_mover;
GLdouble z_mover;
GLfloat x_angulo;
GLfloat y_angulo;
GLfloat z_angulo;
GLfloat escala = 1.0;
GLenum modo = GL_FILL;



void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


// o translate tem de estar antes do teclado e depois do lookat, com variáveis globais
// o angulo é em graus, e o eixo de rotação é o vetor que define o espeto de um frango

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity(); // Destroi todas as entidades feitas, é mesmo necessário acontecer
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, modo);

// put axis drawing in here
	glBegin(GL_LINES);
	// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
	// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

// put the geometric transformations here
glTranslatef(x_mover,y_mover,z_mover);
glRotatef(x_angulo,1,0,0);
glRotatef(y_angulo,0,1,0);
glRotatef(z_angulo,0,0,1);
glScalef(escala,escala,escala);



// put pyramid drawing instructions here

// -> Triângulos da base
	glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 2.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 2.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 2.0f);
		glVertex3f(2.0f, 0.0f, 2.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();


	// Triângulos dos lados
	glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 2.0f, 2.0f);
		glVertex3f(2.0f, 0.0f, 2.0f);
		glVertex3f(1.0f, 3.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	// outra face
	glBegin(GL_TRIANGLES);
		glColor3f(2.0f, 0.0f, 2.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 3.0f, 1.0f);
		glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(2.0f, 2.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 3.0f, 1.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);
	glEnd();
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 2.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 2.0f);
		glVertex3f(1.0f, 3.0f, 1.0f);
	glEnd();
	
	glutPostRedisplay();
	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void teclado (unsigned char key, int x, int y){

	switch(key){
		case 'w': y_mover += 0.5;break;
		case 's': y_mover -= 0.5;break;
		case 'a': x_mover -= 0.5;break;
		case 'd': x_mover += 0.5;break;
		case 'q': z_mover += 0.5;break;
		case 'e': z_mover -= 0.5;break;
		case 'x': x_angulo += 3; break;
		case 'y': y_angulo += 3; break;
		case 'z': z_angulo += 3; break;
		case '+': escala+= 0.05;break;
		case '-': escala-= 0.05;break;
		case 'k': modo = GL_LINE;break;
		case 'l': modo = GL_FILL;break;
		case 'ç': modo = GL_POINT;break;
	}
}






int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM TP2");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(teclado);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

