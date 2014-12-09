

#ifndef TST4EADER_H
#define	TST4EADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
#define BATHEIGHT 100
#define BATWIDTH 50
#define COLUMNAS 25
#define FILAS 25
#define CLICK 1
#define REFRESH 3
#define REDRAW 24
#define XBAT WIDTH/2-BATHEIGHT/2
#define YBAT HEIGHT-BATHEIGHT
#define HALFPI 1.57079632679
#define QU 'q'

#define OFF 0
#define ON  1

#define DEBUG 1

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
                        int resnum;
			char nombre[10];
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
    PTR2NODET in;
    PTR2NODET out;
    int seen;
    NODETARR * nextarr;
    NODETARR * prevarr;
};

typedef NODETARR * PTR2ARR;



//MACROS---------------------------------------
#define round(c) ( ( (c)-((int)(c))*10 ) >=5 ?  ( ((int)(c)) +1 ) : ( ((int)(c)) ))
#define abs(c)  ( (c) >= 0 ? (c) : (-1*(c)) )


//prototipos----------------------------------------
void ListRessistances(PTR2NODET * reslist,PTR2ARR * wireslist);
PTR2NODET SearchRes(int numberres,PTR2NODET  * reslist);
char * CreateMatrix(int cantidadresistencias);
void Calculate(ALLEGRO_EVENT ev);
void EditMatrix(char * matrix,PTR2NODET * reslist,PTR2ARR * wireslist);
void CleanWireSeen(PTR2ARR * wireslist);
void PutOne(int fila,int columna,char * matrix);
double * RessistancesValues(PTR2NODET * reslist);
void SelectWire(PTR2ARR * toparr,ALLEGRO_EVENT ev);
void SelectLine(PTR2ARR wire);
void printselectedlines(PTR2LINE * top);
char * DoubletoASCII(double num);

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
void PrintAllWires(PTR2ARR linesarr);

//linea
void add_node_line (PTR2LINE * ptop , LINEA * pline);
void add_node_wire(PTR2ARR * ptop,PTR2ARR newire);

//maquina de estados----------
int maquina(ALLEGRO_EVENT ev);
void reset_FSM(void);
STATE * fsm(STATE *pstate,ALLEGRO_EVENT ev);

void insert_ressistance(ALLEGRO_EVENT ev);
void insert_ressistance_ROT(ALLEGRO_EVENT ev);
int DetectClick(ALLEGRO_EVENT clic,float* x,float* y,PTR2NODET * reslist);
PTR2NODET AssignNode(PTR2NODET * reslist,float x, float y);

void insert_line(ALLEGRO_EVENT ev);

int GetResName(ALLEGRO_EVENT ev,char * name);
int GetResValue(ALLEGRO_EVENT ev,char * value);
int string2num(char * res);
void do_nothing(ALLEGRO_EVENT ev);

void SelectRes(ALLEGRO_EVENT ev);
void DrawCadriq(void);
int ScanName(char * name,PTR2NODET * reslist);
void TouchWire(PTR2ARR * cables,PTR2NODET selres);

//ALLEGRO fallas
void FixDirectory(void);

//FUNCIONES DE CALCULO INTERNO
int unosfila(int * ptrint, int tamanio,int subtamanio, int fila);
int unoscolumna(int * ptrint, int tamanio,int subtamanio, int columna);
int queunofila(int * ptrint, int tamanio,int subtamanio, int fila);
int queunocolumna(int * ptrint, int tamanio,int subtamanio, int columna);
void moverfilas(int * ptrint, int tamanio,int filadesdedondemuevo);
void movercolumnas(int * ptrint, int tamanio,int columnadesdedondemuevo);
void moverd(double* a,int tamanio,int k);
void moverfila(int * ptrint, int tamanio,int filaadondemuevo, int filaquemuevo);
void movercolumna(int * ptrint, int tamanio,int columnaadondemuevo, int columnaquemuevo);
void sumainvertida(double * a,int i,int k);
void sumad(double * a,int i,int k);
double resistenciatotal(int * ptrmatriz,double * ptrvalores,int tamanio);


//variables globales
extern STATE estado_0[];
extern STATE estado_01[];
extern STATE estado_1[];
extern STATE estado_S[];
extern STATE estado_ROT[];
extern STATE estado_Z[];

//manijas
extern PTR2NODET reslist;
extern PTR2ARR linesarr;
//parte grafica
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *copadares;
extern ALLEGRO_BITMAP *pila;


extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_FONT * fiont;

extern cuentarresistencias;
extern cuentacables;

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TST4EADER_H */
