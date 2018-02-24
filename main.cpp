#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
void initFunc();
void funReshape(int w, int h);
void funDisplay();
void funKeyboard(int key, int x, int y);
void mano();
void brazo();
void cilindro();
using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat desZ = -5.0f;
GLfloat rotY =  0.0f;

GLfloat rotZ =  0.0f;
void mano(){
   
   
    glPushMatrix();
    
  glTranslatef(0, -0.3, 0);
      glColor3f(1,1,1);
     // glRotatef(rotY,0,1,1);
      
      glRotatef(180,0,1,0);
  
    gluCylinder(gluNewQuadric(),0.1f,0.1f,0.1f,32,32);
     glPopMatrix();
     
}
void biceps(){
     glPushMatrix();
      glColor3f(0.0,0.0,1.0);
      glRotatef(90,1,0,0);
  
  gluCylinder(gluNewQuadric(),0.15f,0.1f,0.25f,32,32);
  glPopMatrix();
    
}
void triceps(){
    
      glColor3f(1.0,0.0,1.0);
      glRotatef(90,1,0,0);
  
      cilindro();
  
}
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.1419;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
void cilindro(){
    glColor3f(1,0,0);
     gluCylinder(gluNewQuadric(),0.2f,0.15f,0.5f,32,32);
     glTranslatef(0,0,0.5);
     
    glColor3f(0,1,0);
     drawHollowCircle(0,0,0.15);
     glTranslatef(0,0,-0.5);
     
    glColor3f(0,0,1);
     drawHollowCircle(0,0,0.2);
     glLoadIdentity();
}
void fase2(){
    
    glTranslatef(0,0,-3);
    glRotatef(rotY,1,0,0);
    glPushMatrix();
    
  glTranslatef(0, -0.5, 0);
    glRotatef(rotZ,1,0,0);
    glPushMatrix();
  glTranslatef(0, -0.3, 0.1);
      glColor3f(1,0.3,0.4);
     // glRotatef(rotY,0,1,1);
      glRotatef(180,0,1,0);
    gluCylinder(gluNewQuadric(),0.05f,0.05f,0.5f,32,32);
    glPopMatrix();
     mano();
    biceps();
    glPopMatrix();
}
void fase3(){
     fase2();
  
    
    triceps();
   
}
int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 3");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones específicas
    initFunc();
    
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutSpecialFunc(funKeyboard);
   
    
 // Bucle principal
    glutMainLoop();
    
    return 0;
}

void initFunc() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    
 // Modelo de sombreado
    glShadeModel(GL_FLAT);
    
}

void funReshape(int wnew, int hnew) {
    
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    w = wnew;
    h = hnew;
    
}

void funDisplay() {
    
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
 // Matriz de Proyección P (Cámara)
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;    
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
    fase3();

 // Intercambiamos los buffers
    glutSwapBuffers();
    
}
void funKeyboard(int key, int x, int y) {
    
    switch(key) {
        case GLUT_KEY_UP:
            if (desZ<=-20.0f){
                desZ=0.0f;
            }
            desZ -= 0.1f;
              rotZ-=5.0f;
              if( rotZ<=-90){
                  rotZ=0.0f;
              }
            break;
          
            
        case GLUT_KEY_RIGHT:
            rotY -= 5.0f;
            break;

        case GLUT_KEY_LEFT:
            rotY += 5.0f;
            break;
        case GLUT_KEY_DOWN:
            desZ += 0.1f;
            
            rotZ+=5.0f;
             if( rotZ>=0){
                  rotZ=0.0f;
              }
            break;
        default:
            desZ = -5.0f;  
            rotY = 0.0f;
            
            rotZ=0.0f;
    }
    
    glutPostRedisplay();
      
}
void repeat(){
    Sleep(10);
    rotZ += -0.2f;   
    glutPostRedisplay();
  
}