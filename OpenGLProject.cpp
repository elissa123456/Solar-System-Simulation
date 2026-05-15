#include <GL/glut.h>
#include <cmath>
#include <string>

#define PI 3.1415926535898

// Planets Angles
float angleMercury = 0;
float angleVenus = 0;
float angleEarth = 0;
float angleMars = 0;
float angleJupiter = 0;
float angleSaturn = 0;
float angleUranus = 0;
float angleNeptune = 0;

// variables for keyboard controls
bool isPaused = false;
float speed = 0.2f;

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-2, 2, -2, 2);
}

// Draw circle
void drawCircle(float cx, float cy, float r, bool filled) {

    if (filled)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++) {
        float a = 2 * PI * i / 100;
        glVertex2f(cx + r * cos(a), cy + r * sin(a));
    }
    glEnd();
}

// Draw text
void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
}

// Saturn ring
void drawRing(float cx, float cy) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float a = 2 * PI * i / 100;
        glVertex2f(cx + 0.09 * cos(a), cy + 0.04 * sin(a));
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float cx = 0, cy = 0;

    // Orbits 
    glColor3f(1, 1, 1);
    for (int i = 1;i <= 8;i++)
        drawCircle(cx, cy, i * 0.2, false);

    // Sun
    glColor3f(1, 0.5, 0);
    drawCircle(cx, cy, 0.12, true);

    // Planets

    float mX = 0.2 * cos(angleMercury), mY = 0.2 * sin(angleMercury);
    glColor3f(0.6, 0.6, 0.6);
    drawCircle(mX, mY, 0.03, true);
    drawText(mX, mY + 0.05, "Mercury");

    float vX = 0.4 * cos(angleVenus), vY = 0.4 * sin(angleVenus);
    glColor3f(1, 0.7, 0.2);
    drawCircle(vX, vY, 0.04, true);
    drawText(vX, vY + 0.06, "Venus");

    float eX = 0.6 * cos(angleEarth), eY = 0.6 * sin(angleEarth);
    glColor3f(0.2, 0.5, 1);
    drawCircle(eX, eY, 0.045, true);
    drawText(eX, eY + 0.06, "Earth");

    float maX = 0.8 * cos(angleMars), maY = 0.8 * sin(angleMars);
    glColor3f(0.8, 0.3, 0.1);
    drawCircle(maX, maY, 0.04, true);
    drawText(maX, maY + 0.06, "Mars");

    float jX = 1.0 * cos(angleJupiter), jY = 1.0 * sin(angleJupiter);
    glColor3f(0.8, 0.6, 0.4);
    drawCircle(jX, jY, 0.08, true);
    drawText(jX, jY + 0.1, "Jupiter");

    float sX = 1.2 * cos(angleSaturn), sY = 1.2 * sin(angleSaturn);
    glColor3f(0.9, 0.8, 0.5);
    drawCircle(sX, sY, 0.07, true);
    drawRing(sX, sY);
    drawText(sX, sY + 0.1, "Saturn");

    float uX = 1.4 * cos(angleUranus), uY = 1.4 * sin(angleUranus);
    glColor3f(0.5, 0.9, 1);
    drawCircle(uX, uY, 0.06, true);
    drawText(uX, uY + 0.1, "Uranus");

    float nX = 1.6 * cos(angleNeptune), nY = 1.6 * sin(angleNeptune);
    glColor3f(0.2, 0.4, 1);
    drawCircle(nX, nY, 0.06, true);
    drawText(nX, nY + 0.1, "Neptune");

    // Instructions
    glColor3f(1, 1, 1);
    drawText(-1.8, -1.8, "PRESS SPACE TO Pause | +: TO SPEED UP | -: TO SlOW DOWN");

    glFlush();
}

void update() {
    if (!isPaused) {
        angleMercury += 0.05 * speed;
        angleVenus += 0.035 * speed;
        angleEarth += 0.025 * speed;
        angleMars += 0.02 * speed;
        angleJupiter += 0.01 * speed;
        angleSaturn += 0.008 * speed;
        angleUranus += 0.006 * speed;
        angleNeptune += 0.004 * speed;
    }

    glutPostRedisplay();
}

// Keyboard control function 
void keyboard(unsigned char key, int x, int y) {
    switch (key) {

    case '+':
        speed += 0.1f;
        if (speed > 3.0f) speed = 3.0f; // max speed
        break;

    case '-':
        speed -= 0.1f;
        if (speed < 0.05f) speed = 0.05f; // minimum speed
        break;

    case ' ':
        isPaused = !isPaused;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Solar System");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}