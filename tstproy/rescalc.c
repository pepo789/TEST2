#include "testheader.h"
int cuentarresistencias=0;
int cuentacables=0;

char * CreateMatrix(int cantidadresistencias)
{
    char * matrix;
    matrix=(char*)calloc(sizeof(int)*cantidadresistencias,sizeof(int)*cantidadresistencias);
    return matrix;
    
}


void ListRessistances(PTR2NODET * reslist,PTR2ARR * wireslist)
{
    PTR2ARR tempwire=NULL;
    PTR2NODET tempres=NULL;
    char * resmatrix;
    double * resvaltab;
    
    double loshuevosenelcuello;
    
    tempwire=*wireslist;
    tempres=*reslist;
    
    
    int wirereader,secondwirereader,ressistancenumber=1,seenressistances=1;
   
    while(tempwire)
    {
       if(tempwire->in==5)
       {
           ((tempwire->out)->resist).resnum=ressistancenumber;
           
           tempwire->seen=0;
       
           ressistancenumber++;
                
       }
       else if(tempwire->out==5)
       {
          ((tempwire->in)->resist).resnum=ressistancenumber;
          
          tempwire->seen=0;
          
          ressistancenumber++;
          
       }
        tempwire=tempwire->nextarr;
       
    }
    
   // ressistancenumber--;
    
    
    tempres=SearchRes(seenressistances,reslist);
    tempwire=*wireslist;
    
    
    while(ressistancenumber<=cuentarresistencias)
    {
        if(tempwire->seen)
        {
            if(tempwire->in!=7 && tempwire->out!=7)
            {
                if(tempwire->in==tempres && ((tempwire->out)->resist).resnum==0)
                {
                    ((tempwire->out)->resist).resnum=ressistancenumber;
                    ressistancenumber++;
                    tempwire->seen=0;
                }
                else if(tempwire->out==tempres && ((tempwire->in)->resist).resnum==0)
                {
                    ((tempwire->in)->resist).resnum=ressistancenumber;
                    ressistancenumber++;
                    tempwire->seen=0;
                }
            }
            
        }
        if(tempwire->nextarr)
            tempwire=tempwire->nextarr;
        else if(tempwire->nextarr==0)
        {
            tempwire=*wireslist;
            seenressistances++;
            //ressistancenumber++;
            tempres=SearchRes(seenressistances,reslist);
            
        }
    }
    
    tempres=*reslist;
    
    if(DEBUG){/**/
    while(tempres)
    {
        printf("%s:%d\n",(tempres->resist).nombre,(tempres->resist).resnum);
        tempres=tempres->next;
    }
    /**/}
    
    resmatrix=CreateMatrix(cuentarresistencias);
    
    resvaltab=RessistancesValues(reslist);
    
    EditMatrix(resmatrix,reslist,wireslist);
    
    if(DEBUG){/**/
        int f,c,k;
        for(f=0;f<=(cuentarresistencias-1);f++)
        {
            for(c=0;c<=(cuentarresistencias-1);c++)
            printf("%d\t",*(resmatrix+sizeof(int)*cuentarresistencias*f+sizeof(int)*c));
            printf("\n");
            
                }
        for(k=0;k<=(cuentarresistencias-1);k++){
            printf(" %f ",resvaltab[k]);
        }
    /**/}
    
    
    char * printfinal;
    loshuevosenelcuello=resistenciatotal((int *)resmatrix,resvaltab,cuentarresistencias);
    //printfinal=DoubletoASCII(loshuevosenelcuello);
 
    printfinal=DoubletoASCII(loshuevosenelcuello);
    
     al_show_native_message_box(al_get_current_display(), 
                                 "CALCULO DE RESISTENCIA", 
                                 "Resistencia total", 
                                 printfinal,
                                NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
    
}

void EditMatrix(char * matrix,PTR2NODET * reslist,PTR2ARR * wireslist)
{
    PTR2ARR tempwire=NULL;
    PTR2NODET tempres=NULL;
    char * resmatrix;
    int resseen=1;
    
    tempres=SearchRes(1,reslist);
    
    CleanWireSeen(wireslist);
    
    tempwire=*wireslist;
    
    while(resseen<=cuentarresistencias)
        
    {
        if(tempwire->seen)
        {
        
                if((tempwire->in!=5 && tempwire->out!=5) && (tempwire->in!=7 && tempwire->out!=7))
                {
                    if(tempwire->in==tempres)
                    {
                     tempwire->seen=0;
                     PutOne((tempres->resist).resnum,((tempwire->out)->resist).resnum,matrix);
                    }
                    else if(tempwire->out==tempres)
                    {
                        tempwire->seen=0;
                        PutOne((tempres->resist).resnum,((tempwire->in)->resist).resnum,matrix);
                    }
                }
                
        }   
        if(tempwire->nextarr)
            tempwire=tempwire->nextarr;
        
        else if(tempwire->nextarr==NULL){
            tempwire=*wireslist;
            resseen++;
            tempres=SearchRes(resseen,reslist);
    
        }
    }
}

void PutOne(int fila,int columna,char * matrix)
{
    *(matrix+sizeof(int)*(cuentarresistencias)*(fila-1)+sizeof(int)*(columna-1))=1;
    return;
}

void CleanWireSeen(PTR2ARR * wireslist)
{
    PTR2ARR temp;
    temp=*wireslist;
    
    while(temp){
        temp->seen=1;
        temp=temp->nextarr;
    }
}

double * RessistancesValues(PTR2NODET * reslist)
{
    PTR2NODET res;
    double * table;
    int counter=1;
    
    res=SearchRes(counter,reslist);
    
    table=(double*)calloc(cuentarresistencias,sizeof(double));
    
    for(counter=1;counter<=cuentarresistencias;)
    {
        table[counter-1]=(double)(res->resist).ohm;
        counter++;
        res=SearchRes(counter,reslist);
    }
    
    return table;
}


PTR2NODET SearchRes(int numberres,PTR2NODET  * reslist)
{
    PTR2NODET temp;
    temp=*reslist;
    
    while(temp)
    {
    if((temp->resist).resnum==numberres)
        return temp;
    else
        temp=temp->next;
    }
}


double resistenciatotal(int * ptrmatriz,double * ptrvalores,int tamanio)
{
    
    int subtamanio=tamanio;
    int i,k;
    int fila, salida, entrada,filaactual ;
    static int flag=OFF;
    
    for(k=0;k<tamanio;k++)
    {
        printf("%f\t",ptrvalores[k]);
    }
    printf("\n");
    for(k=0;k<tamanio;k++)
    {
        for(i=0;i<tamanio;i++)
        {
//        printf("%d\t",matriz4[k][i]);
        }
        printf("\n");
    }
    printf("\n");
    
    while(subtamanio>1)
    {
    
    for(fila=0;fila<tamanio;fila++)
    {
        if((unosfila(ptrmatriz,tamanio,subtamanio,fila)==1)&&(unoscolumna(ptrmatriz,tamanio,subtamanio,fila)<=1))
        {
            salida=queunofila(ptrmatriz,tamanio,subtamanio,fila);
            entrada=queunocolumna(ptrmatriz,tamanio,subtamanio,fila);
            if(unoscolumna(ptrmatriz,tamanio,subtamanio,salida)==1)
            {
                sumad(ptrvalores,salida,fila);
                moverd(ptrvalores,tamanio,fila);
                movercolumna(ptrmatriz,tamanio,salida,fila);
                moverfilas(ptrmatriz,tamanio,fila);
                movercolumnas(ptrmatriz,tamanio,fila);
                subtamanio--;
                  for(k=0;k<tamanio;k++)
                    {
                        for(i=0;i<tamanio;i++)
                        {
                        //printf("%d\t",matriz4[k][i]);
                        }
                        printf("\n");
                    }
                      for(k=0;k<tamanio;k++)
                           {
                        printf("%f\t",ptrvalores[k]);
                            }
                    printf("\n");
                    break;
            }
        }
    }
        
      for(fila=0;fila<tamanio;fila++)
      {
          for(filaactual=fila+1;filaactual<subtamanio;filaactual++)
          {
              if((unosfila(ptrmatriz,tamanio,subtamanio,filaactual)==1)&&(unosfila(ptrmatriz,tamanio,subtamanio,fila)==1)&&(unoscolumna(ptrmatriz,tamanio,subtamanio,filaactual)<=1)&&(unoscolumna(ptrmatriz,tamanio,subtamanio,fila)<=1))
              {
                  if((queunofila(ptrmatriz,tamanio,subtamanio,filaactual)==queunofila(ptrmatriz,tamanio,subtamanio,fila))&&(queunocolumna(ptrmatriz,tamanio,subtamanio,filaactual)==queunocolumna(ptrmatriz,tamanio,subtamanio,fila)))
                  {
                      sumainvertida(ptrvalores,filaactual,fila);
                      moverd(ptrvalores,tamanio,fila);
                      moverfilas(ptrmatriz,tamanio,fila);
                      movercolumnas(ptrmatriz,tamanio,fila);
                      subtamanio--;
                      flag=ON;
                        
                      for(k=0;k<tamanio;k++)
                    {
                        for(i=0;i<tamanio;i++)
                        {
                       // printf("%d\t",matriz4[k][i]);
                        }
                        printf("\n");
                    }
                     for(k=0;k<tamanio;k++)
                           {
                        printf("%f\t",ptrvalores[k]);
                            }
                    printf("\n");
                    break;
                  }
              }     
              if((unosfila(ptrmatriz,tamanio,subtamanio,filaactual)==0)&&(unosfila(ptrmatriz,tamanio,subtamanio,fila)==0)&&(unoscolumna(ptrmatriz,tamanio,subtamanio,filaactual)==0)&&(unoscolumna(ptrmatriz,tamanio,subtamanio,fila)==0))
              {
                      sumainvertida(ptrvalores,filaactual,fila);
                      moverd(ptrvalores,tamanio,fila);
                      moverfilas(ptrmatriz,tamanio,fila);
                      movercolumnas(ptrmatriz,tamanio,fila);
                      subtamanio--;
                      flag=ON;
                      for(k=0;k<tamanio;k++)
                    {
                        for(i=0;i<tamanio;i++)
                        {
                       // printf("%d\t",matriz4[k][i]);
                        }
                        printf("\n");
                    }
                     for(k=0;k<tamanio;k++)
                           {
                        printf("%f\t",ptrvalores[k]);
                            }
                    printf("\n");
                      break;   
                  
              }
 
          }
           if(flag==ON)
            {
             flag=OFF;
             break;
            }
      }
        
        
        
        
    
    }
    
    
    
    for(k=0;k<tamanio;k++)
    {
        for(i=0;i<tamanio;i++)
        {
//        printf("%d\t",matriz4[k][i]);
        }
        printf("\n");
    }
     for(k=0;k<tamanio;k++)
    {
        printf("%f\t",ptrvalores[k]);
    }
    printf("\n");
    
    return *ptrvalores;
}





void sumainvertida(double * a,int hacia,int desde)	//suma los dos valores de laa resistencias que se encuentran en paralelo
 
 {
     a[hacia]=1/(1/a[hacia]+1/a[desde]);
     a[desde]=0;

}


void sumad(double * a,int hacia,int desde)		//suma los dos valores de laa resistencias que se encuentran en serie
 
 {
     a[hacia]=a[hacia]+a[desde];
     a[desde]=0;
 }





void moverfilas(int * ptrint, int tamanio,int filadesdedondemuevo)//mueve las filas hacia arriba a partir de cierta fila
{
    int i;
    for(i=filadesdedondemuevo;i<(tamanio-1);i++)
    {
        moverfila(ptrint,tamanio,i,i+1);
    }
      
}




void movercolumnas(int * ptrint, int tamanio,int columnadesdedondemuevo)//mueve las columnas hacia la izquierda a partir de cierta columna
{
    int i;
    for(i=columnadesdedondemuevo;i<(tamanio-1);i++)
    {
        movercolumna(ptrint,tamanio,i,i+1);
    }
      
}


void moverd(double* a,int tamanio,int k)       //funcion que mueve un arreglo de double en una posicion a partir de un elemento
 {
     int p;
     for(p=k;p<(tamanio-1);p++)
     {
         *(a+p)=*(a+p+1);
         *(a+p+1)=0;
     }
     
 }


int unosfila(int * ptrint, int tamanio,int subtamanio, int fila) //calcula la cantidad de salidas de un resistencia
{
	int i,cantidad=0 ;
	for(i=0;i<subtamanio;i++)
	{
		if(*(ptrint+tamanio*fila+i)==1)
		{
		cantidad++;
		}
	}
	return cantidad;
}

int unoscolumna(int * ptrint, int tamanio,int subtamanio, int columna)//calcula la cantidad de entradas de un resistencia
{
	int i,cantidad=0 ;
	for(i=0;i<subtamanio;i++)
	{
		if(*(ptrint+columna+i*tamanio)==1)
		{
		cantidad++;
		}
	}
	return cantidad;
}

int queunofila(int * ptrint, int tamanio,int subtamanio, int fila)//calcula la salida de un resistencia
{
	int i,columna=0 ;
	for(i=0;i<subtamanio;i++)
	{
		if(*(ptrint+tamanio*fila+i)==1)
		{
		return columna;
		}
		else
		{
		columna++;
		}
	}
}	

int queunocolumna(int * ptrint, int tamanio,int subtamanio, int columna)//calcula la entrada de un resistencia
{
	int i,fila=0 ;
	for(i=0;i<subtamanio;i++)
	{
		if(*(ptrint+tamanio*i+columna)==1)
		{
		return fila;
		}
		else
		{
		fila++;
		}
	}
}	

void moverfila(int * ptrint, int tamanio,int filaadondemuevo, int filaquemuevo) //mueve una fila a la posicion de otra
{
	int i;
	for(i=0;i<tamanio;i++)
	{
	*(ptrint+tamanio*filaadondemuevo+i)=*(ptrint+tamanio*filaquemuevo+i);
        *(ptrint+tamanio*filaquemuevo+i)=0;
	}
}

void movercolumna(int * ptrint, int tamanio,int columnaadondemuevo, int columnaquemuevo)//mueve una columna a la posicion de otra
{
	int i;
	for(i=0;i<tamanio;i++)
	{
	*(ptrint+tamanio*i+columnaadondemuevo)=*(ptrint+tamanio*i+columnaquemuevo);
        *(ptrint+tamanio*i+columnaquemuevo)=0;
	}
}
