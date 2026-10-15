#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//estrutura de dados com atributos da forma e numero maximo de figuras
#include "Forma.h"
#define  MAXFIGURES 20
#define TOOLBAR_HEIGHT 80
#define PI 3.14159265f
#define PONTOS_CIRCULO 360
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
//ver isto dos offsets!!!
int selectedfigure = -1;
float offset_x = 0;
float offset_y = 0;
//callbacks
void desenha_texto(float x, float y, const char *texto) {
    glRasterPos2f(x, y);
    while (*texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *texto);
        texto++;
    }
}
void mydisplay() {
    displaycount++;
    printf("A janela foi desenhada %i vezes. \n", displaycount);

	//limpa o ecra
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < figurecount; i++){
        desenhafigura(arrayfigures[i]);
    }
    glColor3ub(50, 50, 50);
    glRectf(0,wY , wX, wY - TOOLBAR_HEIGHT);
    glColor3ub(245, 121, 0);
    glBegin(GL_LINES);
            glVertex2f(80, wY-40);
            glVertex2f(wX, wY-40);
        glEnd();
//estados toolbar

    // ARRANJA O CODIGO AQUI ---
    if(fillcolor == 1){
            glColor3ub(255, 0, 0);
            glRectf(0, wY - TOOLBAR_HEIGHT, 80, wY);
             }
    else if(fillcolor == 2) {
            glColor3ub(0, 255, 255);
        glRectf(0, wY - TOOLBAR_HEIGHT, 80, wY);
        }

    else if(fillcolor == 3) {
            glColor3ub(0, 0, 255);
    glRectf(0, wY - TOOLBAR_HEIGHT, 80, wY);
     }
    else if(fillcolor == 4) {
        glColor3ub(255, 255, 0);
        glRectf(0, wY - TOOLBAR_HEIGHT, 80, wY);
        }
    else if(fillcolor == 5) {
        glColor3ub(0, 255, 0);
        glRectf(0, wY - TOOLBAR_HEIGHT, 80, wY);
         }

    // ARRANJA O CODIGO AQUI ---
    if(linecolor == 1)      glColor3ub(255, 255, 0);
    else if(linecolor == 2) glColor3ub(0, 255, 0);
    else if(linecolor == 3) glColor3ub(255, 0, 255);
    else if(linecolor == 4) glColor3ub(255, 255, 255);
    else if(linecolor == 5) glColor3ub(255, 128, 0);
    else                    glColor3ub(180, 180, 180);

    glBegin(GL_LINE_LOOP);
        glVertex2f(0, wY);
        glVertex2f(80, wY);
        glVertex2f(80, wY - TOOLBAR_HEIGHT);
        glVertex2f(0, wY - TOOLBAR_HEIGHT);
    glEnd();

    //botoes de cima (preenchimento)
    // 1: Vermelho
    glColor3ub(130, 130, 130);
    glRectf(97, wY - 35, 127, wY - 5);
    glColor3ub(255, 0, 0);
    glRectf(100, wY - 32, 124, wY - 8);

    // 2: Ciano
    glColor3ub(130, 130, 130);
    glRectf(137, wY - 35, 167, wY - 5);
    glColor3ub(0, 255, 255);
    glRectf(140, wY - 32, 164, wY - 8);

    // 3: Azul
    glColor3ub(130, 130, 130);
    glRectf(177, wY - 35, 207, wY - 5);
    glColor3ub(0, 0, 255);
    glRectf(180, wY - 32, 204, wY - 8);

    // 4: Amarelo
    glColor3ub(130, 130, 130);
    glRectf(217, wY - 35, 247, wY - 5);
    glColor3ub(255, 255, 0);
    glRectf(220, wY - 32, 244, wY - 8);

    // 5: Verde
    glColor3ub(130, 130, 130);
    glRectf(257, wY - 35, 287, wY - 5);
    glColor3ub(0, 255, 0);
    glRectf(260, wY - 32, 284, wY - 8);


    //botoes de baixo (contorno)

    // 1: Amarelo
    glColor3ub(130, 130, 130);
    glRectf(97, wY - 75, 127, wY - 45);
    glColor3ub(255, 255, 0);
    glRectf(100, wY - 72, 124, wY - 48);

    // 2: Verde
    glColor3ub(130, 130, 130);
    glRectf(137, wY - 75, 167, wY - 45);
    glColor3ub(0, 255, 0);
    glRectf(140, wY - 72, 164, wY - 48);

    // 3: Magenta
    glColor3ub(130, 130, 130);
    glRectf(177, wY - 75, 207, wY - 45);
    glColor3ub(255, 0, 255);
    glRectf(180, wY - 72, 204, wY - 48);

    // 4: Branco
    glColor3ub(130, 130, 130);
    glRectf(217, wY - 75, 247, wY - 45);
    glColor3ub(255, 255, 255);
    glRectf(220, wY - 72, 244, wY - 48);

    // 5: Laranja
    glColor3ub(130, 130, 130);
    glRectf(257, wY - 75, 287, wY - 45);
    glColor3ub(255, 128, 0);
    glRectf(260, wY - 72, 284, wY - 48);


    //texto ao lado dos botões
    glColor3ub(220, 220, 220);
    desenha_texto(305, wY - 24, "Preenchimento");
    desenha_texto(305, wY - 64, "Contorno");

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
    if(figuretype == 5){//ver isto melhor
        glColor3ub(255, 255, 255);
        glBegin(GL_LINE_LOOP);
            // centrado na caixa de 80x80 (x=40, y=wY-40) com raio 20
            for(int i = 0; i < PONTOS_CIRCULO; i++){
                float angulo = 2.0f * 3.14159265f * (float)i / (float)PONTOS_CIRCULO;
                glVertex2f(40 + 20 * cosf(angulo), (wY - 40) + 20 * sinf(angulo));
            }
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
glFlush();

}
void mymouse(int button, int state, int x, int y){
    int inv_y= wY-y;//!!!ver melhor porque e que e invertido

    if(state==GLUT_DOWN){
        printf("O botão %i do rato clicou em x=%i e y=%i \n",button, x, inv_y);
        if(button == GLUT_LEFT_BUTTON){
                if(inv_y >= wY - TOOLBAR_HEIGHT){
                clickstate = 0;
                if(inv_y >= wY - 35 && inv_y <= wY - 5){
                    if(x >= 97 && x <= 127) fillcolor = 1;
                    if(x >= 137 && x <= 167) fillcolor = 2;
                    if(x >= 177 && x <= 207) fillcolor = 3;
                    if(x >= 217 && x <= 247) fillcolor = 4;
                    if(x >= 257 && x <= 287) fillcolor = 5;
                    glutPostRedisplay();
                }
                // 2. Clicou na Fila de Baixo? (Contorno)
                else if(inv_y >= wY - 75 && inv_y <= wY - 45){
                    if(x >= 97 && x <= 127) linecolor = 1;
                    if(x >= 137 && x <= 167) linecolor = 2;
                    if(x >= 177 && x <= 207) linecolor = 3;
                    if(x >= 217 && x <= 247) linecolor = 4;
                    if(x >= 257 && x <= 287) linecolor = 5;
                    glutPostRedisplay();
                }
            }
            if(clickstate == 0 && inv_y < wY - TOOLBAR_HEIGHT){
                    int idx = procurafigura(arrayfigures, figurecount, x, inv_y);
                    if(idx != -1){
                        selectedfigure = idx;
                        offset_x = x - arrayfigures[idx].x;
                        offset_y = inv_y - arrayfigures[idx].y;
                        return; // Sai para não começar a desenhar uma nova figura
                    }
                }
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
    if(state == GLUT_UP){
        selectedfigure = -1;
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
        glutPostRedisplay();
        break;
    case '2':
        fillcolor = 2;

        break;
    case '3':
        fillcolor = 3;

        break;
    case '4':
        fillcolor = 4;
        break;
    case '5':
        fillcolor = 5;
        break;
    case '6':
        linecolor = 1;
        break;
    case '7':
        linecolor = 2;
        break;
    case '8':
        linecolor = 3;
        break;
    case '9':
        linecolor = 4;
        break;
    case '0':
        linecolor = 5;
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
    case 'c':
    case 'C':
        figuretype = 5;
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
    glutPostRedisplay();
}

void mypassivemotion(int x, int y){
    if(clickstate == 1){
        x_cursor = x;
        y_cursor = wY - y;
        glutPostRedisplay();
    }
}

void mymotion(int x, int y){
    int inv_y = wY - y;

    // Se temos uma figura agarrada pelo rato, atualizamos a sua posição
    if(selectedfigure != -1){
        arrayfigures[selectedfigure].x = x - offset_x;
        arrayfigures[selectedfigure].y = inv_y - offset_y;
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

    //gera numeros aleatorios para o default
    srand(time(NULL));




}
void myreshape(int w, int h) {
    // 1. Atualiza as variáveis globais com o novo tamanho da janela
    wX = w;
    wY = h;

    // 2. Ajusta a área de visualização para ocupar a janela inteira
    glViewport(0, 0, w, h);

    // 3. Atualiza o sistema de coordenadas 2D para a nova resolução
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)wX, 0.0, (GLdouble)wY);

    // 4. Volta ao modo modelview para os desenhos normais
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);        /* Freeglut needs this line!*/
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wX, wY);
	glutCreateWindow("Trabalho");

	init();

	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykeyboard);
	glutPassiveMotionFunc(mypassivemotion);
	glutMotionFunc(mymotion);
	glutReshapeFunc(myreshape);
	glutMainLoop();
	return 0;
}



