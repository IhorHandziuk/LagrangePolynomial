#include <GL/freeglut.h>
#include "LagrangePolynomial.h"

LagrangePolynomial lagrangePolynomial;
int window_w = 670;
int window_h = 670;
const float gl_width = 100;
const float gl_height = 100;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(6.0);

    glBegin(GL_LINES);
    glColor3d(0, 0.1, 0);
    for (int z = -100; z <= 100; z++) {
        glVertex2i(z, 100);
        glVertex2i(z, -100);
        glVertex2i(100, z);
        glVertex2i(-100, z);
    }
    glColor3d(0, 1, 0);
    glVertex2i(0, -100);
    glVertex2i(0, 100);
    glVertex2i(-100, 0);
    glVertex2i(100, 0);
    glEnd();

    if (lagrangePolynomial.getPoints().size() > 1) {
        float step = 0.001;
        glBegin(GL_LINE_STRIP);
        glColor3f(1, 0, 0);
        for (float m = -gl_width / 2; m <= gl_width / 2; m += step) {
            glVertex2d(m, lagrangePolynomial.getPolynomialAtPoint(m));
        }
        glEnd();
    }

    glBegin(GL_POINTS);
    for (auto point : lagrangePolynomial.getPoints()) {
        glVertex2d(point.first, point.second);
    }
    glEnd();

    glutSwapBuffers();
}

void keypress(unsigned char key, int x, int y) {
    int translDst = 3;
    switch (key) {
        case 'w':
            glTranslatef(0, translDst, 0);
            break;
        case 'a':
            glTranslatef(translDst, 0, 0);
            break;
        case 's':
            glTranslatef(0, -translDst, 0);
            break;
        case 'd':
            glTranslatef(-translDst, 0, 0);
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void mouseFunc(int button, int state, int xWindow, int yWindow) {
    float normalizedX = static_cast<float >(xWindow) / window_w;
    float normalizedY = static_cast<float >(yWindow) / window_h;
    float x = normalizedX * gl_width - gl_width / 2;
    float y = normalizedY * gl_height - gl_height / 2;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lagrangePolynomial.addPoint(x, y);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        lagrangePolynomial.removePoint(x, y);
    }
}

void reshape(int w, int h) {
    window_w = w;
    window_h = h;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, gl_width, gl_height, 0);
    glViewport(0, 0, w, h);
    glTranslatef(gl_width / 2, gl_height / 2, 0);
}

int main(int argc, char **argv) {
    FreeConsole();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(676, 0);
    glutCreateWindow("LagrangePolynomial");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_2D);
    gluOrtho2D(0, gl_width, gl_height, 0);
    glTranslatef(gl_width / 2, gl_height / 2, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keypress);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseFunc);

    glutMainLoop();
    return EXIT_SUCCESS;
}