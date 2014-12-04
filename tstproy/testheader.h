

#ifndef TST4EADER_H
#define	TST4EADER_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <string.h>
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/keyboard.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"


#define WIDTH 800
#define HEIGHT 600
#define RESWIDTH 100
#define RESHEIGHT 50
#define BATHEIGHT 50
#define BATWIDTH 50
#define COLUMNAS 25
#define FILAS 25
#define CLICK 1
#define REFRESH 3
#define REDRAW 24
#define XBAT WIDTH/2-BATHEIGHT/2
#define YBAT HEIGHT-BATHEIGHT/2

//typedef de la maquina de estados--------------------------


typedef unsigned char BYTE;
typedef struct tabla_estado STATE;
struct tabla_estado

{
	int evento;
	STATE *prx_estado;
	void (*p_rut_accion)(ALLEGRO_EVENT ev);
};
#define FIN_TABLA 00

typedef struct
{
    int xpos;
    int ypos;
}POSMEM;
 

//typedef del arreglo dinamico de las resistencias--------------------------
typedef struct
		{
			char nombre[7];
                        char value[10];
			
                        unsigned int ohm;
                        
                        float x;
                        float y;
                        
                        int volteado;
                        
                        int in;
                        int out;
		} RESISTENCIA;

typedef struct node NODET;
struct	node
		{
			RESISTENCIA resist;
			NODET * next;
			NODET * prev;

		};

typedef NODET * PTR2NODET;

//arreglo dinamico de las lineas----------

//arreglo de lineas
typedef struct
		{
			float x1;
                        float y1;
                        float x2;
                        float y2;
                        int in;
                        int out;
		} LINEA;

typedef struct node2 NODETLINE;
struct	node2
		{
			LINEA line;
			NODETLINE * nextli;
			NODETLINE * prevli;

		};

typedef NODETLINE * PTR2LINE;


typedef struct node3 NODETARR;
struct node3
{
    PTR2LINE array;
    NODETARR * nextarr;
    NODETARR * prevarr;
};

typedef NODETARR * PTR2ARR;



//MACROS---------------------------------------
#define round(c) ( ( (c)-((int)(c))*10 ) >=5 ?  ( ((int)(c)) +1 ) : ( ((int)(c)) ))
#define abs(c)  ( (c) >= 0 ? (c) : (-1*(c)) )


//prototipos----------------------------------------


//cuadricula---------
void cuadric(float *,float *);


//arrreglo dinamico-------
void create_list(PTR2NODET * ptop);
void add_node_RES (PTR2NODET * ptop , RESISTENCIA * pres);
void del_node(PTR2NODET * ptop,char *nombre);
void EditRes(PTR2NODET * res);

//MANIJAS
void GetPtr2Res(void);
void GetPtr2Line(void);


//imprimir resistencias
void PrintResists(PTR2NODET * ptop,ALLEGRO_BITMAP * dibujito);

//lineas
void printlines(PTR2LINE * top);


//linea
void add_node_line (PTR2LINE * ptop , LINEA * pline);
void add_node_wire(PTR2ARR * ptop,PTR2LINE newline);

//maquina de estados----------
int maquina(ALLEGRO_EVENT ev);
void reset_FSM(void);
STATE * fsm(STATE *pstate,ALLEGRO_EVENT ev);

void insert_ressistance(ALLEGRO_EVENT ev);
void insert_ressistance_ROT(ALLEGRO_EVENT ev);

 void insert_line(ALLEGRO_EVENT ev);

int GetResName(ALLEGRO_EVENT ev,char * name);
int GetResValue(ALLEGRO_EVENT ev,char * value);
int string2num(char * res);
void do_nothing(ALLEGRO_EVENT ev);

void SelectRes(ALLEGRO_EVENT ev);
void DrawCadriq(void);

//ALLEGRO fallas
void FixDirectory(void);



//variables globales
extern STATE estado_0[];
extern STATE estado_01[];
extern STATE estado_1[];
extern STATE estado_S[];
extern STATE estado_ROT[];

//manijas
extern PTR2NODET reslist;
extern PTR2ARR linesarr;
//parte grafica
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *copadares;


extern ALLEGRO_EVENT_QUEUE *event_queue;

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TST4EADER_H */
