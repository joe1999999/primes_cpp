#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to generate prime numbers up to a given limit
std::vector<int> generatePrimes(int limit) {
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to calculate the difference between square roots of consecutive primes
std::vector<double> calculateSquareRootDifferences(const std::vector<int>& primes) {
    std::vector<double> differences;
    for (size_t i = 1; i < primes.size(); ++i) {
        double sqrtCurrent = std::sqrt(primes[i]);
        double sqrtPrevious = std::sqrt(primes[i - 1]);
        double difference = sqrtCurrent - sqrtPrevious;
        differences.push_back(difference);
    }
    return differences;
}

// Global variables
std::vector<double> differences;
size_t currentSphereIndex = 0;

// OpenGL display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera
    gluLookAt(0, 0, 5,  // Camera position
              0, 0, 0,  // Look at point
              0, 1, 0); // Up direction

    if (currentSphereIndex < differences.size()) {
        // Render the current sphere
        glutSolidSphere(differences[currentSphereIndex], 20, 20);
    }

    glutSwapBuffers();
}

// OpenGL reshape function
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to set up lighting
void initLighting() {
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light source 0

    // Define light properties
    GLfloat lightPosition[] = {0.0f, 5.0f, 5.0f, 1.0f}; // Light position
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};  // Ambient light
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Diffuse light
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Specular light

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Define material properties
    GLfloat materialAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat materialDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat materialShininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
}

// Timer function to update the sphere index
void timer(int value) {
    if (currentSphereIndex < differences.size()) {
        currentSphereIndex++; // Move to the next sphere
        glutPostRedisplay();  // Trigger redraw
    }

    if (currentSphereIndex < differences.size()) {
        // Set the timer again for the next update
        glutTimerFunc(500, timer, 0);
    }
}

// Main function
int main(int argc, char** argv) {
    int limit;
    std::cout << "Enter the limit: ";
    std::cin >> limit;

    // Generate primes and calculate differences
    std::vector<int> primes = generatePrimes(limit);
    differences = calculateSquareRootDifferences(primes);

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sphere Visualization of Prime Differences");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set up lighting
    initLighting();

    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Set up the timer for the first update
    glutTimerFunc(500, timer, 0);

    // Start the main loop
    glutMainLoop();

    return 0;
}