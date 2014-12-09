
#include "testheader.h"





void cuadric(float *coord_x,float *coord_y)
{
    *coord_x=(round((*coord_x)/(FILAS)))*(FILAS);
    *coord_y=(round((*coord_y)/(COLUMNAS)))*(COLUMNAS);
}

//int printtext(ALLEGRO_EVENT ev)

int string2num(char * name)
{
    int stringreader,num=0,state=0;
    for(stringreader=0;name[stringreader]!=0 && stringreader<=10;stringreader++)
    {
        if((name[stringreader]=='k')||(name[stringreader]=='K')){
            num=num*1000;
            state=1;
        continue;    
        }
        else if(state){
            num=num+((name[stringreader]-48)*100);
            continue;
        }
        num=num*10+(name[stringreader]-48);
    }

    return num;
}


void FixDirectory(void) 
{ 
    ALLEGRO_PATH* path = al_get_standard_path(ALLEGRO_EXENAME_PATH); 
    al_set_path_filename(path , "UbuntuMono-R"); 
    al_set_path_extension(path , ".ttf"); 
    const char* cstr = al_path_cstr(path , ALLEGRO_NATIVE_PATH_SEP); 
    al_change_directory(cstr); 
    al_destroy_path(path); 
} 

void DrawCadriq(void)
{
         int verline,horline;
            for(verline=0;verline<=WIDTH;verline+=COLUMNAS){
            al_draw_line(verline,0,verline,HEIGHT, al_map_rgb(90,90,90), 1);
            }
            for(horline=0;horline<=HEIGHT;horline+=FILAS){
            al_draw_line(0,horline,WIDTH,horline, al_map_rgb(90,90,90), 1);
            }
         al_draw_bitmap(pila, XBAT, YBAT, 0);
}



void GetPtr2Res(void)
{
    reslist=NULL;
}

void GetPtr2Line(void)
{
    linesarr=NULL;
}


char * DoubletoASCII(double num)
{
    unsigned char * number;
    int strpos,decpart;
    number=(unsigned char*)calloc(15,1);
    
    int entero=(int)num;
    int numlength=(int)(log10(entero));
    
    double decimal=num-(int)num;
    
    for(strpos=0;numlength+1;strpos++,numlength--){
        number[strpos]= ((int)(entero/pow(10,numlength))-(int)(entero/pow(10,numlength+1))*10)+48;
       // printf("strpos: %d\tnum: %d\tentero: %d\tresta: %d\tnumlength:%d\n",strpos,number[strpos],(int)(entero/pow(10,numlength)),(int)(entero/pow(10,numlength+1))*10,numlength);
    }
        //printf("%s\n",*(number+1)); 
        
    number[strpos]=',';
    strpos++;
    
    for(decpart=1;decpart<=5;decpart++,strpos++){
        number[strpos]=( (int)(decimal*pow(10,decpart))- ((int)(decimal*pow(10,decpart-1)))*10  )+48;
    
     //printf("decpart:%d\tnumber:%d\tentero:%d\tresta:%d\n",decpart,number[strpos],(int)(decimal*pow(10,decpart)),((int)(decimal*pow(10,decpart-1)))*10);   
    }
    
   // printf("%s",number);
    return number;
}