#include <GL/glut.h>
#include <cmath>

// Fungsi untuk menggambar bola (sphere)
void drawSphere(float radius) {
    glutSolidSphere(radius, 20, 20);
}

// Fungsi untuk menggambar silinder (cylinder)
void drawCylinder(float baseRadius, float topRadius, float height) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, baseRadius, topRadius, height, 20, 20);
    gluDeleteQuadric(quad);
}

void drawCone(float base, float height) {
    glutSolidCone(base, height, 20, 20); // 20 segmen untuk kehalusan
}

// Fungsi untuk menggambar lantai
void drawGround() {
    glColor3f(0.5f, 0.5f, 0.3f); // Sky blue
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -0.5f, -5.0f);
    glVertex3f(-5.0f, -0.5f, 5.0f);
    glVertex3f(5.0f, -0.5f, 5.0f);
    glVertex3f(5.0f, -0.5f, -5.0f);
    glEnd();
}

// Fungsi untuk menggambar tangan dengan jari
void drawHandWithFingers() {
    // Lengan
    glColor3f(0.4f, 0.2f, 0.1f); // Warna coklat untuk kayu
    drawCylinder(0.013f, 0.013f, 0.3f);

    // Jari-jari
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.3f); // Posisi ujung lengan

    // Jari tengah (lurus ke atas)
    glPushMatrix();
    glRotatef(0, 1.0f, 0.0f, 0.0f); // Rotasi ke atas
    drawCylinder(0.01f, 0.01f, 0.2f);
    glPopMatrix();

    // Jari kiri (miring ke kiri)
    glPushMatrix();
    glRotatef(0, 1.0f, 0.0f, 0.0f); // Rotasi ke atas
    glRotatef(-30, 0.0f, 1.0f, 0.0f); // Miring ke kiri
    drawCylinder(0.01f, 0.01f, 0.2f);
    glPopMatrix();

    // Jari kanan (miring ke kanan)
    glPushMatrix();
    glRotatef(0, 1.0f, 0.0f, 0.0f); // Rotasi ke atas
    glRotatef(30, 0.0f, 1.0f, 0.0f); // Miring ke kanan
    drawCylinder(0.01f, 0.01f, 0.2f);
    glPopMatrix();

    glPopMatrix(); 
}

// Fungsi untuk menggambar snowman
void drawSnowman() {
    // Badan bawah
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    drawSphere(0.5f);
    glPopMatrix();

    // Badan tengah
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    drawSphere(0.35f);
    glPopMatrix();

    // Kepala
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    drawSphere(0.25f);

    // Mata
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(-0.07f, 0.07f, 0.23f); drawSphere(0.03f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.07f, 0.07f, 0.23f); drawSphere(0.03f); glPopMatrix();

    // Hidung wortel
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.25f);
    glRotatef(0, 1.0f, 0.0f, 0.0f); // Mengarah ke depan
    drawCone(0.03f, 0.2f);
    glPopMatrix();

    // Topi (alas topi dan tabung)
    glColor3f(0.1f, 0.1f, 0.1f); // Hitam
    // Alas topi
    glPushMatrix();
    glTranslatef(0.0f, 0.23f, 0.0f);
    glScalef(1.5f, 0.1f, 1.5f);
    drawSphere(0.2f);
    glPopMatrix();
    // Tabung topi
    glPushMatrix();
    glTranslatef(0.0f, 0.24f, 0.0f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    drawCylinder(0.12f, 0.12f, 0.3f);
    glPopMatrix();

    glPopMatrix(); // Tutup kepala

    // Tombol baju
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(0.0f, 0.6f, 0.35f); drawSphere(0.025f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.45f, 0.32f); drawSphere(0.025f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.75f, 0.32f); drawSphere(0.025f); glPopMatrix();

    // Lengan kiri 
    glPushMatrix();
    glTranslatef(-0.33f, 0.6f, 0.0f); // Posisi lengan kiri
    glRotatef(-90, 1.0f, 1.0f, 0.0f); // Rotasi ke atas
    drawHandWithFingers(); // Gambar tangan dengan jari
    glPopMatrix();

    // Lengan kanan 
    glPushMatrix();
    glTranslatef(0.33f, 0.6f, 0.0f); // Posisi lengan kanan
    glRotatef(-90, 1.0f, -1.0f, 0.0f); // Rotasi ke atas
    drawHandWithFingers(); // Gambar tangan dengan jari
    glPopMatrix();
}

// Variabel global untuk kamera
float cameraX = 0.0f, cameraY = 1.0f, cameraZ = 5.0f; // Posisi awal kamera
float cameraLX = 0.0f, cameraLY = 0.0f, cameraLZ = -1.0f; // Arah pandangan kamera
float cameraAngle = 0.0f; // Sudut rotasi horizontal kamera (dalam radian)
float cameraVerticalAngle = 0.0f; // Sudut rotasi vertikal kamera (dalam radian)
float cameraSpeed = 0.1f; // Kecepatan gerak kamera

void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ) {
    cameraX = posX;
    cameraY = posY;
    cameraZ = posZ;

    cameraLX = targetX - posX;
    cameraLY = targetY - posY;
    cameraLZ = targetZ - posZ;

    float len = sqrt(cameraLX*cameraLX + cameraLY*cameraLY + cameraLZ*cameraLZ);
    cameraLX /= len;
    cameraLY /= len;
    cameraLZ /= len;

    // Hitung sudut untuk dukungan rotasi dinamis
    cameraAngle = atan2(cameraLX, -cameraLZ);
    cameraVerticalAngle = asin(cameraLY);
}

// Fungsi untuk menangani input keyboard
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Maju
            cameraX += cameraLX * cameraSpeed;
            cameraZ += cameraLZ * cameraSpeed;
            break;
        case 's': // Mundur
            cameraX -= cameraLX * cameraSpeed;
            cameraZ -= cameraLZ * cameraSpeed;
            break;
        case 'a': // Memutar ke kiri
            cameraAngle -= 0.05f; // Kurangi sudut rotasi horizontal
            break;
        case 'd': // Memutar ke kanan
            cameraAngle += 0.05f; // Tambah sudut rotasi horizontal
            break;
        case 'q': // Menghadap ke atas
            cameraVerticalAngle += 0.05f; // Tambah sudut rotasi vertikal
            if (cameraVerticalAngle > M_PI / 2) cameraVerticalAngle = M_PI / 2; // Batas atas
            break;
        case 'e': // Menghadap ke bawah
            cameraVerticalAngle -= 0.05f; // Kurangi sudut rotasi vertikal
            if (cameraVerticalAngle < -M_PI / 2) cameraVerticalAngle = -M_PI / 2; // Batas bawah
            break;
        case 'z': // Naik (posisi kamera)
            cameraY += cameraSpeed;
            break;
        case 'x': // Turun (posisi kamera)
            cameraY -= cameraSpeed;
            break;
        case '1': // Plan View 
    		setCamera(0.0f, 12.0f, 0.001f, 0.0f, 0.0f, 0.0f);
    		break;
        case '2': // Front View
            setCamera(0.0f, 2.5f, 8.0f, 0.0f, 1.0f, 0.0f);
            break;
        case '3': // Side View (Right)
            setCamera(8.0f, 2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
            break;
        case '4': // Isometric View 
            setCamera(6.0f, 6.0f, 6.0f, 0.0f, 0.5f, 0.0f);
            break;
        case '5': // Dimetric View
            setCamera(7.0f, 5.0f, 7.0f, 0.0f, 0.5f, 0.0f);
            break;
        case '6': // Trimetric View
            setCamera(8.0f, 4.0f, 6.0f, 0.0f, 0.5f, 0.0f);
            break;
        case '7': // Perspektif 1 titik hilang
            setCamera(6.0f, 1.0f, 6.0f, 0.0f, 1.0f, 0.0f);
            break;
        case '8': // Perspektif 2 titik hilang
            setCamera(6.0f, 2.5f, 6.0f, 0.0f, 1.0f, 0.0f);
            break;
        case '9': // Perspektif 3 titik hilang
            setCamera(6.0f, 7.0f, 6.0f, 0.0f, 1.0f, 0.0f);
            break;
        case '0': // Default View
    		setCamera(0.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f);
    		break;
    }

    // Perbarui arah pandangan kamera
    cameraLX = cos(cameraVerticalAngle) * sin(cameraAngle);
    cameraLY = sin(cameraVerticalAngle);
    cameraLZ = -cos(cameraVerticalAngle) * cos(cameraAngle);

    glutPostRedisplay(); // Meminta redisplay setelah posisi kamera berubah
}

// Fungsi untuk menggambar adegan
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 
              cameraX + cameraLX, cameraY + cameraLY, cameraZ + cameraLZ, 
              0.0f, 1.0f, 0.0f);

    drawGround(); // Menggambar lantai
    drawSnowman(); // Menggambar manusia

    glutSwapBuffers();
}

// Fungsi inisialisasi
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.75f, 0.88f, 1.0f, 1.0f); // Biru sangat muda (soft blue)
}

// Fungsi untuk mengatur ukuran jendela
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Snowman");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeyboard);

    glutMainLoop();
    return 0;
}
