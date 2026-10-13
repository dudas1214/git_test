#include <GL/glut.h>
#include <stdlib.h>
#include "Forma.h"

int criafigura(Forma array[], int pos_atual, int rato_x, int rato_y, int w, int h, int fill, int line, int type){

        array[pos_atual].x = rato_x;
        array[pos_atual].y = rato_y;
        array[pos_atual].w = w;
        array[pos_atual].h = h;
        switch(fill){
            case 1:
                array[pos_atual].r_fill = 255;
                array[pos_atual].g_fill = 0;
                array[pos_atual].b_fill = 0;
                break;
            case 2:
                array[pos_atual].r_fill = 0;
                array[pos_atual].g_fill = 255;
                array[pos_atual].b_fill = 255;
                break;
            case 3:
                array[pos_atual].r_fill = 0;
                array[pos_atual].g_fill = 0;
                array[pos_atual].b_fill = 255;
                break;
            default:
                array[pos_atual].r_fill = rand()%256;
                array[pos_atual].g_fill = rand()%256;
                array[pos_atual].b_fill = rand()%256;
            break;
        }
        switch(line){
            case 1:
                array[pos_atual].r_line = 255;
                array[pos_atual].g_line = 255;
                array[pos_atual].b_line = 0;
                break;
            case 2:
                array[pos_atual].r_line = 0;
                array[pos_atual].g_line = 255;
                array[pos_atual].b_line = 0;
                break;
            case 3:
                array[pos_atual].r_line = 255;
                array[pos_atual].g_line = 0;
                array[pos_atual].b_line = 255;
                break;
            default:
                array[pos_atual].r_line = rand()%256;
                array[pos_atual].g_line = rand()%256;
                array[pos_atual].b_line = rand()%256;
            break;
        }
        switch(type){
            case 1:
                array[pos_atual].tipo = RECTANGLE;
                break;
            case 2:
                array[pos_atual].tipo = TRIANGLE;
                break;
            case 3:
                array[pos_atual].tipo = LINE;
                break;
            case 4:
                array[pos_atual].tipo = SQUARE;
            break;
            default:
                array[pos_atual].tipo = rand()%4;
            break;
        }
        if(array[pos_atual].tipo==SQUARE){
            array[pos_atual].h =array[pos_atual].w;
        }
        //devolve o nº de figuras atualizado
        return pos_atual + 1;
}
void desenhafigura(Forma f){
        //percorrer array de figuras, guardar em variaveis temporarias
        float x = f.x;
        float y = f.y;
        float w = f.w;
        float h = f.h;

        //fundo (linhas nao tem fundo)
        if (f.tipo != LINE){
            glColor3ub(f.r_fill, f.g_fill, f.b_fill);
            glBegin(GL_POLYGON);
            if(f.tipo==TRIANGLE){
                glVertex2f(x, y);
                glVertex2f(x + w, y);
                glVertex2f(x + (w/2), y + h);
            }
            else if(f.tipo==RECTANGLE || f.tipo == SQUARE){
                glVertex2f(x, y);
                glVertex2f(x + w, y);
                glVertex2f(x + w, y + h);
                glVertex2f(x, y + h);
            }
        glEnd();
        }
        glColor3ub(f.r_line,f.g_line ,f.b_line );
        glBegin(GL_LINE_LOOP);
            if(f.tipo==TRIANGLE){
                glVertex2f(x, y);
                glVertex2f(x + w, y);
                glVertex2f(x + (w/2), y + h);
            }
            else if(f.tipo==RECTANGLE || f.tipo == SQUARE){
                glVertex2f(x, y);
                glVertex2f(x + w, y);
                glVertex2f(x + w, y + h);
                glVertex2f(x, y + h);
            }
        glEnd();
            //condicional diferente porque linhas utilizam GL_LINES em vez de GL_POLYGON
            if(f.tipo == LINE){
                glBegin(GL_LINES);
                glVertex2f(x,y);
                glVertex2f(x+w,y+h);
                glEnd();
            }
}
int apagafigura(Forma array[], int pos_atual, int indice){
    if(pos_atual>0 && indice>=0 && indice < pos_atual){
    int apagado = indice;
    array[apagado] = array[pos_atual-1];
    return pos_atual - 1;
    }
    else return pos_atual;
}

int procurafigura(Forma array[], int count, int rato_x, int rato_y){
    for(int i=count-1; i>=0; i--){
        if((rato_x>=array[i].x)&&(rato_x<=(array[i].x+array[i].w))&&(rato_y>=array[i].y)&&(rato_y<=(array[i].y+array[i].h))){
            return i;
            }

    }
    return -1;
}
