#include<GL/glut.h>
#include<iostream>
using namespace std;

typedef double point[3];
int k;
point tetra[4] = {{0,250,-250},{0,0,250},{250,-250,-250},{-250,-250,-250}};

void triangle_draw(point p1, point p2, point p3){
    glBegin(GL_TRIANGLES);
    glVertex3dv(p1);
    glVertex3dv(p2);
    glVertex3dv(p3);
    glEnd();
}

void tetrahedron_draw(point p1,point p2,point p3,point p4){
    glColor3d(1,0,0);
    triangle_draw(p1,p2,p3);
    glColor3d(0,1,0);
    triangle_draw(p1,p3,p4);
    glColor3d(0,0,1);
    triangle_draw(p1,p4,p2);
    glColor3d(1,1,0);
    triangle_draw(p2,p3,p4);
}

void divide_tetrahedron(point p1, point p2, point p3, point p4, int k){
    point mid[6];
    if(k>0){
        for(int i=0;i<3;i++) mid[0][i] = (p1[i]+p2[i])/2; 
        for(int i=0;i<3;i++) mid[1][i] = (p1[i]+p3[i])/2; 
        for(int i=0;i<3;i++) mid[2][i] = (p1[i]+p4[i])/2; 
        for(int i=0;i<3;i++) mid[3][i] = (p2[i]+p3[i])/2; 
        for(int i=0;i<3;i++) mid[4][i] = (p3[i]+p4[i])/2; 
        for(int i=0;i<3;i++) mid[5][i] = (p2[i]+p4[i])/2;

        divide_tetrahedron(p1,mid[0],mid[1],mid[2],k-1); 
        divide_tetrahedron(mid[0],p2,mid[3],mid[5],k-1); 
        divide_tetrahedron(mid[1],mid[3],p3,mid[4],k-1); 
        divide_tetrahedron(mid[2],mid[5],mid[4],p4,k-1); 
    }else{
        tetrahedron_draw(p1,p2,p3,p4);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    divide_tetrahedron(tetra[0],tetra[1],tetra[2],tetra[3],k);
    glFlush();
}

void myInit(){
    glClearColor(0,0,0,1);
    glOrtho(-500,500,-500,500,-500,500);
}

int main(int argc, char **argv){
    cout << "Enter number of divisions: ";
    cin >> k;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Serpenski Gasket");
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    myInit();
    glutMainLoop();    
}
