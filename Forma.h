    #ifndef FORMA_H
    #define FORMA_H

        typedef enum{
        RECTANGLE,
        TRIANGLE,
        LINE,
        SQUARE,
        CIRCLE
        }Tipo;

        typedef struct{
        //posicao e dimensao
        float x,y,w,h;

        //guardam os valores do rand para a cor nao alterar
        unsigned char r_fill, g_fill, b_fill;
        unsigned char r_line, g_line, b_line;

        Tipo tipo;
        }Forma;

        int criafigura(Forma array[], int pos_atual, int rato_x, int rato_y, int w, int h, int fill, int line, int type);
        void desenhafigura(Forma f);
        int apagafigura(Forma array[], int pos_atual, int indice);
        int procurafigura(Forma array[], int count, int rato_x, int rato_y);
    #endif // FORMA_H
