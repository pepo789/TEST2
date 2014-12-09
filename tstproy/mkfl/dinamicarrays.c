
#include "testheader.h"
//arreglo de las resistencias
/*
void create_list(PTR2NODET * ptop) //aca entras con un puntero valija
{
	*ptop=NULL;
}
*/


void add_node_RES (PTR2NODET * ptop , RESISTENCIA * pres) //aca entras con los datos de la resistencia y la manija
{
int prev=1;	
 PTR2NODET temp=NULL;	
 PTR2NODET pnewnode= (PTR2NODET) calloc(1,sizeof(NODET)); // Create space for node

	if( *ptop == NULL) {	// First time ?
		*ptop=pnewnode;
        prev=0;}//

	temp=*ptop;
 
	while(temp -> next)							// find last node
  		temp = temp -> next;
	
	temp -> next= pnewnode;						// Link new node with last one
 
	pnewnode->resist=* pres;					// copy data
 
    pnewnode->next= NULL;  // set newly created node as last node
    if(prev)
    pnewnode->prev=temp;
    
    cuentarresistencias++;
 
}




void del_node(PTR2NODET * ptop,char *nomb) //aca entras con la manija y el nombre
{
 NODET * temp;
	temp=*ptop;
	while(strcmp( (temp->resist).nombre, nomb) && temp->next!=NULL )
		temp=temp->next;



	if(temp==*ptop) {
		*ptop=temp->next;
                free(temp);
	}
	else if(temp->next==NULL)
	{
		(temp->prev)->next=NULL;
		free(temp);
	}

	else{
		(temp->prev)->next=temp->next;
		(temp->next)->prev=temp->prev;
	free(temp);
	}

}


//arreglo de lineaaaaaaaaaaaaaaaaaaaaaaaaaaas


void add_node_wire(PTR2ARR * ptop,PTR2ARR newire)
{
    int prev=1;
    PTR2ARR temp;
    PTR2ARR pnewarr=(PTR2ARR) calloc(1,sizeof(NODETARR));
    
    if(*ptop == NULL){
        *ptop=pnewarr;
    prev=0;}
    
    temp=*ptop;
    
    while(temp->nextarr)
        temp=temp->nextarr;
    
    temp->nextarr=pnewarr;
    
    pnewarr->array=newire->array;
    pnewarr->in=newire->in;
    pnewarr->out=newire->out;
    pnewarr->seen=1;
    
    pnewarr->nextarr=NULL;
    
    if(prev)
    pnewarr->prevarr=temp;
    
    cuentacables++;
}

void del_wire(PTR2ARR * ptop, PTR2LINE wire)
{
    PTR2ARR temparr;
    temparr=*ptop;
    
    while((temparr->array)!=wire && (temparr->nextarr)!=NULL)
        temparr=temparr->nextarr;
    
    if(temparr==*ptop)
    {
        *ptop=temparr->nextarr;
        free(temparr);
    }
    else if(temparr->nextarr==NULL)
    {
        (temparr->prevarr)->nextarr=NULL;
        free(temparr);
    }
    else{
        (temparr->prevarr)->nextarr=temparr->nextarr;
        (temparr->nextarr)->prevarr=temparr->prevarr;
        free(temparr);      
    }
        
    
}

void add_node_line (PTR2LINE * ptop , LINEA * pline) //aca entras con los datos de la linea y la manija
{
    int prev=1;
 NODETLINE * temp;	
 NODETLINE * pnewnode= (PTR2LINE) calloc(1,sizeof(NODETLINE)); // Create space for node

	if( *ptop == NULL) {	// First time ?
	prev=0;	
            *ptop=pnewnode; }//

	temp=*ptop;
 
	while(temp -> nextli)							// find last node
  		temp = temp -> nextli;
	
	temp -> nextli= pnewnode;						// Link new node with last one
 
	pnewnode->line=* pline;					// copy data
 
    pnewnode->nextli= NULL;
if(prev)    // set newly created node as last node
    pnewnode->prevli=temp;
 
}

void add_node_arr(PTR2ARR * ptop,PTR2LINE * pline)
{
    int prev=1;
    PTR2ARR temp;
    PTR2ARR pnewnode = (PTR2ARR) calloc(1,sizeof(NODETARR));
    
    if(*ptop == NULL){
        prev=0;
        *ptop=pnewnode;}
    
    temp=*ptop;
    
    while(temp->nextarr)
        temp=temp->nextarr;
    
    temp ->nextarr=pnewnode;
    
    pnewnode->array=*pline;
    pnewnode->nextarr= NULL;
    if(prev)
    pnewnode->prevarr=temp;
                
                
}



void SeeResists(PTR2NODET * ptop,ALLEGRO_EVENT ev)
{
    float clicx,clicy;
    PTR2NODET temp;
    temp=*ptop;
    
    clicx=ev.mouse.x;
    clicy=ev.mouse.y;
    
    cuadric(&clicx,&clicy);
   
    while(temp)
    {
        if((temp->resist).volteado==1)
        {
            if( ( ((temp->resist).y+25)>=clicy ) && ( (temp->resist).y-25<=clicy ) && ( (temp->resist).x<=clicx ) && ( (temp->resist).x+100>=clicx ) )
            {
                EditRes(&temp);
            }
        }
        else if((temp->resist).volteado==0)
        {
            if( ( ((temp->resist).x+25)>=clicx ) && ( (temp->resist).x-25<=clicx ) && ( (temp->resist).y<=clicy ) && ( (temp->resist).y+100>=clicy ) )
            {
                EditRes(&temp);
            }
        }
        temp=temp->next;
    }
    
    
}


 /*void SelectRes(ALLEGRO_EVENT ev)
 {
     
 }*/
 
 
void EditRes(PTR2NODET * res)
{
    ALLEGRO_TIMER * refresh;
    ALLEGRO_EVENT editev;
    
    
    refresh = al_create_timer(1.0 / REDRAW);
            if(!refresh) {
               fprintf(stderr, "failed to create timer!\n");
               return;
            }
    
   
    
    
   al_register_event_source(event_queue, al_get_timer_event_source(refresh));
   al_start_timer(refresh);
   
   
   
   while(editev.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
   {
      al_wait_for_event(event_queue,&editev);
      
      
      if( (editev.type == ALLEGRO_EVENT_MOUSE_AXES) || (editev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) )
      {
          ((*res)->resist).x=editev.mouse.x;
          ((*res)->resist).y=editev.mouse.y;
          TouchWire(&linesarr,(*res));
          
          cuadric(&((*res)->resist).x,&((*res)->resist).y);
          
      }
      else if(editev.type == ALLEGRO_EVENT_KEY_UP)
      {
          if(editev.keyboard.keycode == ALLEGRO_KEY_DELETE)
          {
              del_node(&reslist,((*res)->resist).nombre);
              return;
          }
      }
      
      
       al_clear_to_color(al_map_rgb(255, 255, 255));
       DrawCadriq();
       PrintResists(&reslist,copadares);
       PrintAllWires(linesarr);
       
      al_flip_display();
   }
   
       
}

int ScanName(char * name,PTR2NODET * reslist)
{
    int coincidence,stringreturn=0,eraser;
    PTR2NODET temp;
    
    temp=*reslist;
    
    while(temp)
    {
        coincidence = strcmp(name,(temp->resist).nombre);
        if(coincidence == 0)
        {
            stringreturn=1;
             al_show_native_message_box(al_get_current_display(),  "error",  "cuidado", "le estás poniendo \n el mismo nombre a dos resistencias.",NULL, ALLEGRO_MESSAGEBOX_ERROR);
                        
                            for(eraser=0;eraser<=9;eraser++)
                                name[eraser]=0;
                     
        }
       
            temp=temp->next;
    }
    
    return stringreturn;
}



void PrintResists(PTR2NODET * ptop, ALLEGRO_BITMAP * dibujito)
{
   
    NODET * temp;
    
    temp = *ptop;
    
        
    
    
       while(temp) {
            if ((temp->resist).volteado==1) {
                al_draw_bitmap(dibujito,temp->resist.x,temp->resist.y,0);
                
                
                 al_draw_text(fiont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y-10,ALLEGRO_ALIGN_LEFT, (temp->resist).nombre);
                 al_draw_text(fiont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y+30,ALLEGRO_ALIGN_LEFT, (temp->resist).value);
                     
                 
                 temp=temp->next;
            }
                 else if((temp->resist).volteado==0){
                 al_draw_rotated_bitmap(dibujito,0, 0,(temp->resist).x, (temp->resist).y,1.57079632679,0);
                
                
                 al_draw_text(fiont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y-10,ALLEGRO_ALIGN_LEFT, (temp->resist).nombre);
                 al_draw_text(fiont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y+30,ALLEGRO_ALIGN_LEFT, (temp->resist).value);
                 
                 temp=temp->next;
                 }
        
        }        
            
    
}

void TouchWire(PTR2ARR * cables,PTR2NODET selres)
{
    PTR2ARR temp;
    temp=*cables;
    
    while(temp)
    {
        if(temp->in == selres || temp->out == selres)
        {
            del_wire(cables,temp->array);
        }
        temp=temp->nextarr;
    }
}
void PrintAllWires(PTR2ARR linesarr)
{
    PTR2ARR temp;
    temp=linesarr;
    

    while(temp){
    printlines(&(temp->array));
    temp=temp->nextarr;
    }
}


void printlines(PTR2LINE * top)
{
    PTR2LINE temp;
    temp=*top;

    while(temp)
    {
        al_draw_line( (temp->line).x1,(temp->line).y1,(temp->line).x2,(temp->line).y2,al_map_rgb(0,0,0),2);
        temp=temp->nextli;
    }
     
    
}

int DetectClick(ALLEGRO_EVENT clic,float* x,float* y,PTR2NODET * reslist)
{
    int tocaste=0;
    PTR2NODET temp;
    temp=*reslist;
    
    
    if( ((YBAT+BATHEIGHT)>=clic.mouse.y && YBAT<=clic.mouse.y) && ((XBAT+BATWIDTH/2)>=clic.mouse.x && (XBAT-BATWIDTH)<=clic.mouse.x) )
    {
        tocaste=1;
        *x=XBAT;
        *y=YBAT+BATHEIGHT/2;
        
        
        return tocaste;
    }
    else if(((YBAT+BATHEIGHT)>=clic.mouse.y && YBAT<=clic.mouse.y) && ((XBAT+2*BATWIDTH)>=clic.mouse.x && (XBAT+BATWIDTH/2)<=clic.mouse.x))
    {
        tocaste=1;
        *x=XBAT+BATWIDTH;
        *y=YBAT+BATHEIGHT/2;
        return tocaste;
    }
    
    else
    { 
            while(temp)
            {
                if((temp->resist).volteado==1)
                {
                    if( ( ((temp->resist).y+RESHEIGHT)>=clic.mouse.y) && (((temp->resist).y))<=clic.mouse.y)
                    {
                        if(( ((temp->resist).x+50)>=clic.mouse.x ) && ( ((temp->resist).x-10)<=clic.mouse.x ))
                        {
                            tocaste=1;
                            *x=(temp->resist).x;
                            *y=(temp->resist).y+RESHEIGHT/2;
                            break;
                        }
                        else if(( ((temp->resist).x+RESWIDTH+10)>=clic.mouse.x ) && ( ((temp->resist).x+50)<=clic.mouse.x ))
                        {
                            tocaste=1;
                            *x=((temp->resist).x+100);
                            *y=((temp->resist).y+RESHEIGHT/2);
                            break;
                        }
                    }
                    temp=temp->next;
                }

                else if((temp->resist).volteado==0)
                {
                    if(( ((temp->resist).x)>=clic.mouse.x ) && ( ((temp->resist).x)-RESHEIGHT<=clic.mouse.x ) )
                    {
                        if(( ((temp->resist).y+50)>=clic.mouse.y) && ((temp->resist).y-10)<=clic.mouse.y)
                        {
                            tocaste=1;
                            *x=(temp->resist).x-25;
                            *y=(temp->resist).y;
                            break;
                        }
                        else if(( ((temp->resist).y+RESWIDTH+10)>=clic.mouse.y) && ((temp->resist).y+50)<=clic.mouse.y)
                        {
                            tocaste=1;
                            *x=((temp->resist).x-25);
                            *y=((temp->resist).y+100);
                            break;
                        }
                    }
                    temp=temp->next;
                }
            }
    
    }
    return tocaste;
}



PTR2NODET AssignNode(PTR2NODET * reslist,float x, float y)
{
    PTR2NODET temp=*reslist;
    int returndir;
    
   
    if(x==XBAT && y==(YBAT+BATHEIGHT/2))
    {
        returndir=5;
        return returndir;
    }
    else if(x==(XBAT+BATWIDTH) && y==(YBAT+BATHEIGHT/2))
    {
        returndir=7;
        return returndir;
    }
    
    
    else
        while(temp)
        {
            if((temp->resist).volteado==1) {
                if( (x==(temp->resist).x || x==((temp->resist).x+100)) && y==((temp->resist).y+RESHEIGHT/2))
                    return temp;  }
            
            
            else if((temp->resist).volteado==0){
                if( (y==((temp->resist).y+100) ||  y==((temp->resist).y)) && x==((temp->resist).x-25))
                    return temp;}
          
            temp=temp->next;
        }
}

void SelectWire(PTR2ARR * toparr,ALLEGRO_EVENT ev)
{
    PTR2ARR temp,correctedarr;
    temp=*toparr;
    int advancedlines=0,advancedarrs=0;
    
    while(temp)
    {
        while(temp->array)
        {
            if((temp->array)->line.y1 == (temp->array)->line.y2)
            {
                        if( ( ( ((ev.mouse.x) >= ( (temp->array)->line).x1) && ((temp->array)->line.x2) >= ev.mouse.x )  || ( ((ev.mouse.x) <= ( (temp->array)->line).x1) && ((temp->array)->line.x2) <= ev.mouse.x ) ) && ( ( ev.mouse.y <= ((temp->array)->line.y2 + 5) ) &&   ( ev.mouse.y >= ((temp->array)->line.y2 - 5) )) )                            
                        {
                                
                            
                                for(;advancedlines;advancedlines--)
                                temp->array=temp->array->prevli;
                            
                                correctedarr=temp;
                                for(;advancedarrs;advancedarrs--)
                                    temp=temp->prevarr;
                                
                                SelectLine(correctedarr);
                                return;
                        }
            }
            else if((temp->array)->line.x1 == (temp->array)->line.x2)
            {
                if( ( ((ev.mouse.y) >= ( (temp->array)->line).y1) && ((temp->array)->line.y2) >= ev.mouse.y )  || ( ((ev.mouse.y) <= ( (temp->array)->line).y1) && ((temp->array)->line.y2) <= ev.mouse.y ) && ( ( ev.mouse.x <= ((temp->array)->line.x2 + 5) ) &&   ( ev.mouse.x >= ((temp->array)->line.x2 - 5) )) )
                        {
                                for(;advancedlines;advancedlines--)
                                temp->array=temp->array->prevli;
                                
                                correctedarr=temp;
                                for(;advancedarrs;advancedarrs--)
                                    temp=temp->prevarr;
                                
                                SelectLine(correctedarr);
                                return;
                        }
                
            }
           
            if(temp->array->nextli)
            temp->array=temp->array->nextli;
            else
                break;
            
            advancedlines++;
        }
        //advancedlines--;
                    
                    for(;advancedlines;advancedlines--)
                    temp->array=temp->array->prevli;

        
        temp=temp->nextarr;
        advancedarrs++;
      
        
    }
}

void SelectLine(PTR2ARR wire)
{
    PTR2LINE top;
    
     al_clear_to_color(al_map_rgb(255, 255, 255));
     DrawCadriq();
     PrintResists(&reslist,copadares);         
     PrintAllWires(linesarr);
     
     printselectedlines(&(wire->array));
     
    al_flip_display();
    
    while(1){
    ALLEGRO_EVENT wiredit;
    al_wait_for_event(event_queue,&wiredit);
    
            if(wiredit.type == ALLEGRO_EVENT_KEY_UP)
            {
                if(wiredit.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    DrawCadriq();
                    PrintResists(&reslist,copadares);         
                    PrintAllWires(linesarr);
                    al_flip_display();
                    break;
                }
                else if(wiredit.keyboard.keycode == ALLEGRO_KEY_DELETE)
                {
                    del_wire(&linesarr,wire->array);
                    break;
                }
            }
    
    
    
    }
    
}



void printselectedlines(PTR2LINE * top)
{
    PTR2LINE temp;
    temp=*top;

    while(temp)
    {
        al_draw_line( (temp->line).x1,(temp->line).y1,(temp->line).x2,(temp->line).y2,al_map_rgb(255,0,0),3);
        temp=temp->nextli;
    }
     
    
}