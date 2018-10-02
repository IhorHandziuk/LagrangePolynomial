#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include <string>

using namespace std;
#define max_N 15;

int N = max_N;

double **points = new double *[N];
double **swap_points = new double *[N];

double *a = new double[N];
double *b = new double[N];
double *coeff = new double[N + 1];

void swaping(int k, double **arr, double **swap_arr) {

    swap_arr[0][0] = arr[k][0];
    int l = 1, m = 1;
    while (l <= N - 1) {
        if (l - 1 == k) m++;
        swap_arr[l][0] = arr[m - 1][0];
        l++;
        m++;
    }
}

void solve(int len, double mult, int shift) {
    if (len > 1) {
        solve(len - 1, mult * a[len - 1], shift + 1);
        solve(len - 1, mult * b[len - 1], shift);
    } else {
        coeff[shift + 1] += a[0] * mult;
        coeff[shift] += b[0] * mult;
    }
}

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

    glBegin(GL_LINE_STRIP);
    double L;
    double F = 1;
    glColor3f(1, 0, 0);
    for (double m = -20; m <= 20; m += 0.01) {
        for (int i = 0; i < N; i++) {
            swaping(i, points, swap_points);
            for (int j = 1; j < N; j++) {
                F *= (m - swap_points[j][0]) / (points[i][0] - swap_points[j][0]);
            }
            L += points[i][1] * F;
            F = 1;
        }
        glVertex2d(m, L);
        L = 0;
    }
    glEnd();

    glBegin(GL_POINTS);
    for (int i = 0; i <= N - 1; i++) {
        for (int j = 0; j <= 1; j++)
            glVertex2d(points[i][0], points[i][1]);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    cout << "Enter N: ";
    cin >> N;
    coeff[N] = 0;
    for (int i = 0; i < N; i++) {
        a[i] = 0;
        b[i] = 0;
        coeff[i] = 0;
        points[i] = new double[2];
        swap_points[i] = new double[2];
    }

    cout << "Enter " << N << " points " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= 1; j++)
            cin >> points[i][j];
    }

    for (int i = 0; i < N; i++) {
        swaping(i, points, swap_points);
        for (int j = 1; j < N; j++) {
            b[j] = 1 / (points[i][0] - swap_points[j][0]);
            a[j] = (-1) * swap_points[j][0] / (points[i][0] - swap_points[j][0]);
        }
        a[0] = points[i][1];
        solve(N, 1, 0);
    }
    for (int e = 1; e <= N; e++)
        cout << coeff[e] << " ";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(670, 670);
    glutInitWindowPosition(676, 0);
    glutCreateWindow("Polinom");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_2D);
    gluOrtho2D(-20, 20, -20, 20);
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
