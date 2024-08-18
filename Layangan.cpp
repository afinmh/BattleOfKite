#include<windows.h>
#include<GL\glut.h>
#include <GL/glu.h>
#include<math.h>
#include <stdlib.h>
#include<stdio.h>
#define PI 3.1416

///==================================================///
///         Author@Shamim Hasan                       ///
///         Id: 151-15-4965                          ///
///         BSc In CSE                               ///
///         Daffodil International University        ///
///==================================================///

GLint i, j, k;
GLfloat sun_spin=0;
GLfloat ax=0,bx=0,cx=0,str=500.0,mn=500.0;
GLfloat sr=0.0,sg=0.749,sb=1.0;
GLfloat spin = 0.5;
GLfloat scale_factor = 1.0;
GLfloat dy = 0.5, dx = 0.5, a = 0.5;

//Inisialisasi Awal
void init(void){
	glClearColor(.40, .110, 1.0, 0.0); //Warna background
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1000.0, 0.0, 500.0); //Mengatur rentang x 0-1000 dan y 0-500
}

// ---------------------------------------------------------------- Dari Referensi 1 ------------------------------------------------------------------//
//Membuat Lingkaran untuk Kincir, Matahari, dan Awan
void circle(GLdouble rad){
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;
    glBegin(GL_POLYGON);
    {
        for( i = 0; i <=50; i++, theta += delTheta )
        {
            glVertex2f(rad * cos(theta),rad * sin(theta));
        }
    }
    glEnd();
}
//Membuat Matahari
void Sun_Model(){
    glPushMatrix();
    glTranslatef(200,400,0); //Inisialisasi pada titik x = 200  y = 400
    circle(30); //Memanggil fungsi circle dengan radian 30
    glPopMatrix();
}
//Mengatur perputaran Matahari
void Moving_Sun_Model(){
    glPushMatrix();
    glRotatef(-sun_spin, 0,0,1); //Rotasi pada sun spin yang diatur di fungsi move_right
    Sun_Model();
    glPopMatrix();
}
//Membuat Awan
void cloud(){
    glColor3f(1.25, 0.924, 0.930);
    //1
    glPushMatrix();
    glTranslatef(300,200,0);
    circle(15);
    glPopMatrix();
    //2
    glPushMatrix();
    glTranslatef(320,210,0);
    circle(15);
    glPopMatrix();
    //3
    glPushMatrix();
    glTranslatef(340,220,0);
    circle(16);
    glPopMatrix();
    //4
    glPushMatrix();
    glTranslatef(360,210,0);
    circle(15);
    glPopMatrix();
    //5
    glPushMatrix();
    glTranslatef(380,200,0);
    circle(15);
    glPopMatrix();
    //6
    glPushMatrix();
    glTranslatef(360,190,0);
    circle(20);
    glPopMatrix();
    //7
    glPushMatrix();
    glTranslatef(320,190,0);
    circle(20);
    glPopMatrix();
    //8
    glPushMatrix();
    glTranslatef(340,190,0);
    circle(20);
    glPopMatrix();
}



// ---------------------------------------------------------------- Dari Referensi 2 ------------------------------------------------------------------//
//Membuat Lapangan
void field(){
	
	glBegin(GL_POLYGON);
    glColor3f(0.533, 1.293, 0.0);
	glVertex2i(0, 50);
	glVertex2i(0, 70);
	glVertex2i(1000, 70);
	glVertex2i(1000, 50);
	glEnd();
    //Bawah
	glBegin(GL_POLYGON);
	glColor3f(0.1, 1.293, 0.0);
	glVertex2i(0, 0);
	glVertex2i(0, 50);
	glVertex2i(1000, 50);
	glVertex2i(1000, 0);
	glEnd();
}

//----------------------------Kincir Angin-------------------------//
//Membuat Tiang
void Windmill_Stand_Model(){
    glColor3f(0.38, 0.41, 0.36);
    glBegin(GL_POLYGON);
    glVertex2i(375, 100);
    glVertex2i(380, 240);
    glVertex2i(384, 240);
    glVertex2i(390, 100);
    glEnd();
}
//Membuat Pisau
void Windmill_Blade(){
    //Pisau 1
    glPushMatrix();
    glRotatef(spin,0,0,90);
    glBegin(GL_POLYGON);
    glVertex2i(-5, 0);
    glVertex2i(-85, -36);
    glVertex2i(-83, -37);
    glVertex2i(-3, -8);
    glEnd();
    glPopMatrix();
    //Pisau 2
    glPushMatrix();
    glRotatef(spin,0,0,90);
    glBegin(GL_POLYGON);
    glVertex2i(0, 5);
    glVertex2i(45, 70);
    glVertex2i(50, 73);
    glVertex2i(5, 0);
    glEnd();
    glPopMatrix();
    // Pisau 3
    glPushMatrix();
    glRotatef(spin,0,0,90);
    glBegin(GL_POLYGON);
    glVertex2i(68, -78);
    glVertex2i(0,0);
    glVertex2i(5, 5);
    glVertex2i(70, -77);
    glEnd();
    glPopMatrix();
}
//Menyatukan semua bagian
void Windmill(){
    //Tiang
    glColor3f(0.38, 0.41, 0.36);
    glPushMatrix();
    Windmill_Stand_Model();
    glPopMatrix();
    //titik
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(380,250,0);
    circle(10);
    glPopMatrix();
    ///Windmill_Rotary_Blades
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(380,251,0);
    Windmill_Blade();
    glPopMatrix();
}



// ---------------------------------------------------------------- Membuat Modifikasi ------------------------------------------------------------------//
//Membuat Layangan
void drawDiamond(){
    double x = 500;
    double y = 100 + dy + a;  // Tambahkan nilai dy pada posisi vertikal diamond
    double width = 150 * scale_factor;  // Skala lebar diamond
    double height = 250 * scale_factor;  // Skala tinggi diamond

    // Menggambar diamond dengan warna merah
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x, y + height / 4);
    glVertex2d(x - width / 2, y);
    glVertex2d(x, y - height / 2);
    glVertex2d(x + width / 2, y);
    glEnd();

    // Menggambar garis hitam di tengah diamond
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x, y + height / 4);
    glVertex2d(x, y - height / 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(x - width / 2, y);
    glVertex2d(x + width / 2, y);
    glEnd();
    
    if (dx <= 200) {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2d(x, y - height / 2);
        glVertex2d(x, y - height / 2 - 1000); // Sesuaikan panjang garis sesuai keinginan
        glEnd();
    }
}
//Membuat Layangan Musuh
void drawDiamond_musuh(){
    double x = 300 + dx;
    double y = 300;  // Tambahkan nilai dy pada posisi vertikal diamond
    double width = 57;  // Skala lebar diamond
    double height = 95;  // Skala tinggi diamond
    
    glColor3f(0.58, 0.0, 0.83);
    if (dy >= 230) {
        glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(-90, 0, 0, 1);
        glTranslatef(-x, -y, 0);
    }
    if (dx >= 350) {
        glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(90, 0, 0, 1);
        glTranslatef(-x, -y, 0);
    }
    
    glBegin(GL_POLYGON);
    glVertex2d(x, y + height / 4);
    glVertex2d(x - width / 2, y);
    glVertex2d(x, y - height / 2);
    glVertex2d(x + width / 2, y);
    glEnd();
    
    // Menggambar garis hitam di tengah diamond
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x, y + height / 4);
    glVertex2d(x, y - height / 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(x - width / 2, y);
    glVertex2d(x + width / 2, y);
    glEnd();
    if (dy >= 230) {
        glPopMatrix();
    }
    if (dx >= 350) {
        glPopMatrix();
    }
    
}



// ---------------------------------------------------------------- Layout Objek ------------------------------------------------------------------//
//Layout Matahri
void Sun(){
    glColor3f(1, 1, 0);
    glPushMatrix();
    Moving_Sun_Model();
    glPopMatrix();
}
//Layout Awan 1
void cloud_five(){
    glPushMatrix();
    glTranslatef(cx+-100,170,0);
    cloud();
    glPopMatrix();
}
//Layout Awan 2
void cloud_six(){
    glPushMatrix();
    glTranslatef(cx+-300,20,0);
    cloud();
    glPopMatrix();
}
//Layout Kincir 1
void Windmill_Two(){
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(508,-70,0);
    Windmill();
    glPopMatrix();
}
//Layout Kincir 2
void Windmill_Three(){
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(-250,-90,0);
    Windmill();
    glPopMatrix();
}
//Layout Layangan
void layangan(){
    glColor3f(0.0, 0.0, 1.0);
    drawDiamond();  // Memanggil fungsi untuk menggambar diamond
    glutSwapBuffers();
}

//Menampilkan semua objek
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
    Sun();
    Windmill_Three();
    Windmill_Two();
    cloud_five();
    drawDiamond_musuh();
    cloud_six();
    field();
    layangan();
	glFlush();
}

//Mengatur kecepatan semua objek yang bergerak
void move_right(){
    sun_spin = sun_spin + 0.001; //Mengatur kecepatan rotasi matahari
    spin = spin + 1; //Mengatur kecepetan rotasi kincir angin
    cx = cx + 0.5; //Mengatur kecepatan transisi awan
    if(cx > 1000){
        cx = -300; // Memindahkan awan ke titik semula
    } 

    if (dy < 230) {
        scale_factor *= 0.99965555555; // Mengatur Scalling
        dy += 0.06; //Mengatur translasi layangan merah terhadap sumbu y
    }
    else{
    	dy = 230;	
	}
	
	if (dy >= 230) {
		if (dx < 350) {
			dx += 0.08; //Mengatur translasi layangan musuh terhadap sumbu x
		}
		else{
			dx = 350;
		}
	}
	if (dx > 200) {
		scale_factor *= 0.9995222; // Mengatur Scalling
		a += 0.02; //Mengatur translasi layangan merah terhadap sumbu y
	}
    glutPostRedisplay();
}


//Mengatur input mouse
void mouse(int key, int state, int x, int y){
    switch (key)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(move_right);
        }
        break;
    case GLUT_MIDDLE_BUTTON:
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(NULL);
        }
        break;
    default:
        break;
    }
}

//Menjalankan semua fungsi
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1300, 600);
	glutCreateWindow("Battle of Kite");
	init();
	glutDisplayFunc(display); //Menampilkan Display
    glutMouseFunc(mouse);
	glutMainLoop(); //Untuk menjalankan
}
