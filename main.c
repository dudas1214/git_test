#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//estrutura de dados com atributos da forma e numero maximo de figuras
#include "Forma.h"
#define  MAXFIGURES 20
#define TOOLBAR_HEIGHT 80
//array de estruturas do tipo figura
Forma arrayfigures[MAXFIGURES];

//variaveis globais para  nao se apagar entre cada frame
int figurecount;
int displaycount = 0;
int fillcolor = 0;
int linecolor = 0;
int figuretype = 0;
int clickstate = 0;
int x_inicial, y_inicial;
int x_cursor = 0;
int y_cursor = 0;
int wX = 600;
int wY = 600;
//callbacks
void mydisplay() {
    displaycount++;
    printf("A janela foi desenhada %i vezes. \n", displaycount);

	//limpa o ecra
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < figurecount; i++){
        desenhafigura(arrayfigures[i]);
    }
    glColor3ub(50, 50, 50);
    glRectf(0,wY , wX, 600- TOOLBAR_HEIGHT);

    if(fillcolor == 1){
        glColor3ub(255, 0, 0);
        glRectf(0,wY , 80, 600- TOOLBAR_HEIGHT);
    }
    if(fillcolor == 2){
        glColor3ub(0, 255, 255);
        glRectf(0,wY , 80, 600- TOOLBAR_HEIGHT);
    }
    if(fillcolor == 3){
        glColor3ub(0, 0, 255);
        glRectf(0,wY , 80, 600- TOOLBAR_HEIGHT);
    }
    if(linecolor == 1){
        glColor3ub(255, 255, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, wY);
            glVertex2f(80, wY);
            glVertex2f(80, wY-TOOLBAR_HEIGHT);
            glVertex2f(0, wY-TOOLBAR_HEIGHT);
        glEnd();
    }
        if(linecolor == 2){
        glColor3ub(0, 255, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, wY);
            glVertex2f(80, wY);
            glVertex2f(80, wY-TOOLBAR_HEIGHT);
            glVertex2f(0, wY-TOOLBAR_HEIGHT);
        glEnd();
    }
        if(linecolor == 3){
        glColor3ub(255, 0, 255);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, wY);
            glVertex2f(80, wY);
            glVertex2f(80, wY-TOOLBAR_HEIGHT);
            glVertex2f(0, wY-TOOLBAR_HEIGHT);
        glEnd();
    }
    //figurinha toolbar
    if(figuretype == 1){
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
            glVertex2f(15, wY-15);
            glVertex2f(65, wY-15);
            glVertex2f(65, wY-45);
            glVertex2f(15, wY-45);
        glEnd();
    }
    if(figuretype == 2){
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
            glVertex2f(20, wY-15);
            glVertex2f(50, wY-15);
            glVertex2f(35, wY-45);
        glEnd();
    }
    if(figuretype == 3){
        glColor3ub(255, 255, 255);
        glBegin(GL_LINES);
            glVertex2f(15, wY-15);
            glVertex2f(65, wY-65);
        glEnd();
    }
    if(figuretype == 4){
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
            glVertex2f(15, wY-15);
            glVertex2f(65, wY-15);
            glVertex2f(65, wY-65);
            glVertex2f(15, wY-65);
        glEnd();
    }

    if(clickstate == 1){
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
            glVertex2f(x_inicial, y_inicial);
            glVertex2f(x_cursor, y_inicial);
            glVertex2f(x_cursor, y_cursor);
            glVertex2f(x_inicial, y_cursor);
        glEnd();
    }

    //toolbar


    glutSwapBuffers();
}
void mymouse(int button, int state, int x, int y){
    int inv_y= wY-y;//!!!ver melhor porque e que e invertido

    if(state==GLUT_DOWN){
        printf("O botão %i do rato clicou em x=%i e y=%i \n",button, x, inv_y);
        if(button == GLUT_LEFT_BUTTON){
                if(clickstate == 0&& inv_y < wY - TOOLBAR_HEIGHT){
                    x_inicial = x;
                    y_inicial = inv_y;
                    x_cursor = x;
                    y_cursor = inv_y;
                    clickstate = 1;
                }
                else if(clickstate == 1){
                    int x_final, y_final;
                    if(figurecount<MAXFIGURES){
                        if(x> x_inicial){
                            x_final = x_inicial;
                        }
                        else{
                             x_final = x;
                        }
                        if( inv_y > y_inicial){
                            y_final = y_inicial;
                        }
                        else{
                             y_final = inv_y;
                        }
                        int w = abs(x - x_inicial);
                        int h = abs(inv_y - y_inicial);
                    if(inv_y < wY - TOOLBAR_HEIGHT){
                        figurecount=criafigura(arrayfigures, figurecount, x_final, y_final, w, h, fillcolor, linecolor, figuretype);
                    }
                    }
                    else printf("O limite maximo de figuras foi atingido, apaga para desenhares de novo.\n");
                clickstate = 0;
                    }
                glutPostRedisplay();
                }


        if(button == GLUT_RIGHT_BUTTON){
            int indice = procurafigura(arrayfigures, figurecount, x, inv_y);
        if(indice != -1){
            printf("figura %d apagada em (%.0f, %.0f)\n",
                   indice, arrayfigures[indice].x, arrayfigures[indice].y);
            figurecount = apagafigura(arrayfigures, figurecount, indice);
            glutPostRedisplay();
        } else {
            printf("nenhuma figura debaixo do cursor do rato.\n");
        }
        }
        glutPostRedisplay();
    }
    }



void mykeyboard(unsigned char key, int x, int y){
    if (key == 'q' || key == 'Q') {
        printf("Encerraste o programa...\n");
        exit(0);
    }
    switch(key){
    case '1':
        fillcolor = 1;
        glutSwapBuffers();
        break;
    case '2':
        fillcolor = 2;
        break;
    case '3':
        fillcolor = 3;
        break;
    case '4':
        linecolor = 1;
        break;
    case '5':
        linecolor = 2;
        break;
    case '6':
        linecolor = 3;
        break;
    case 'r':
    case 'R':
        figuretype = 1;
        break;
    case 't':
    case 'T':
        figuretype = 2;
        break;
    case 'l':
    case 'L':
        figuretype = 3;
        break;
    case 's':
    case 'S':
        figuretype = 4;
        break;
    case 'd':
    case 'D': {
        int inv_y = wY - y;
        int indice = procurafigura(arrayfigures, figurecount, x, inv_y);
        if(indice != -1){
            printf("Tecla D: figura %d apagada em (%.0f, %.0f)\n",
                   indice, arrayfigures[indice].x, arrayfigures[indice].y);
            figurecount = apagafigura(arrayfigures, figurecount, indice);
            glutPostRedisplay();
        } else {
            printf("Tecla D: nenhuma figura debaixo do cursor do rato.\n");
        }
        break;
        }
    }
}

void mypassivemotion(int x, int y){
    if(clickstate == 1){
        x_cursor = x;
        y_cursor = wY - y;
        glutPostRedisplay();
    }
}
//desenhos e afins
void init(){
    //cor de fundo
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, wX , 0.0, wY);

    //gera numeros aleatorios para posicoes aleatorias das figuras
    srand(time(NULL));




}
int main(int argc, char** argv) {
	glutInit(&argc, argv);        /* Freeglut needs this line!*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(wX, wY);
	glutCreateWindow("Trabalho");

	init();

	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykeyboard);
	glutPassiveMotionFunc(mypassivemotion);
	glutMainLoop();
	return 0;
}



