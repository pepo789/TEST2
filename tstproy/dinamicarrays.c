
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
	
 PTR2NODET temp=NULL;	
 PTR2NODET pnewnode= (PTR2NODET) calloc(1,sizeof(NODET)); // Create space for node

	if( *ptop == NULL) {	// First time ?
		*ptop=pnewnode; }//

	temp=*ptop;
 
	while(temp -> next)							// find last node
  		temp = temp -> next;
	
	temp -> next= pnewnode;						// Link new node with last one
 
	pnewnode->resist=* pres;					// copy data
 
    pnewnode->next= NULL;  						// set newly created node as last node
    pnewnode->prev=temp;
 
}




void del_node(PTR2NODET * ptop,char *nomb) //aca entras con la manija y el nombre
{

 NODET * temp;
	temp=*ptop;
	while(strcmp( (temp->resist).nombre, nomb) && temp->next!=NULL )
		temp=temp->next;



	if(temp==*ptop) {
		*ptop=temp->next;
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


void add_node_wire(PTR2ARR * ptop,PTR2LINE newline)
{
    PTR2ARR temp;
    PTR2ARR pnewarr=(PTR2ARR) calloc(1,sizeof(NODETARR));
    
    if(*ptop == NULL)
        *ptop=pnewarr;
    
    temp=*ptop;
    
    while(temp->nextarr)
        temp=temp->nextarr;
    
    temp->nextarr=pnewarr;
    pnewarr->array=newline;
    pnewarr->nextarr=NULL;
    pnewarr->prevarr=temp;
}

void add_node_line (PTR2LINE * ptop , LINEA * pline) //aca entras con los datos de la linea y la manija
{
	
 NODETLINE * temp;	
 NODETLINE * pnewnode= (PTR2LINE) calloc(1,sizeof(NODETLINE)); // Create space for node

	if( *ptop == NULL) 	// First time ?
		*ptop=pnewnode; //

	temp=*ptop;
 
	while(temp -> nextli)							// find last node
  		temp = temp -> nextli;
	
	temp -> nextli= pnewnode;						// Link new node with last one
 
	pnewnode->line=* pline;					// copy data
 
    pnewnode->nextli= NULL;  						// set newly created node as last node
    pnewnode->prevli=temp;
 
}

void add_node_arr(PTR2ARR * ptop,PTR2LINE * pline)
{
    PTR2ARR temp;
    PTR2ARR pnewnode = (PTR2ARR) calloc(1,sizeof(NODETARR));
    
    if(*ptop == NULL)
        *ptop=pnewnode;
    
    temp=*ptop;
    
    while(temp->nextarr)
        temp=temp->nextarr;
    
    temp ->nextarr=pnewnode;
    
    pnewnode->array=*pline;
    pnewnode->nextarr= NULL;
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
   
   
   
   while(editev.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
   {
      al_wait_for_event(event_queue,&editev);
      
      
      if( (editev.type == ALLEGRO_EVENT_MOUSE_AXES) || (editev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) )
      {
          ((*res)->resist).x=editev.mouse.x;
          ((*res)->resist).y=editev.mouse.y;
          
          cuadric(&((*res)->resist).x,&((*res)->resist).y);
          
      }
      
      
       al_clear_to_color(al_map_rgb(255, 255, 255));
       DrawCadriq();
       PrintResists(&reslist,copadares);
      al_flip_display();
   }
   
       
}



void PrintResists(PTR2NODET * ptop, ALLEGRO_BITMAP * dibujito)
{
   FixDirectory();
   ALLEGRO_FONT * faont = al_load_ttf_font("UbuntuMono-R.ttf",15,0 );
    NODET * temp;
    
    temp = *ptop;
    
        
    
    
        do{
            if ((temp->resist).volteado==1) {
                al_draw_bitmap(dibujito,temp->resist.x,temp->resist.y,0);
                
                
                 al_draw_text(faont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y-10,ALLEGRO_ALIGN_LEFT, (temp->resist).nombre);
                 al_draw_text(faont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y+30,ALLEGRO_ALIGN_LEFT, (temp->resist).value);
                 
                 temp=temp->next;
            }
                 else if((temp->resist).volteado==0){
                 al_draw_rotated_bitmap(dibujito,0, 0,(temp->resist).x, (temp->resist).y,1.57079632679,0);
                
                
                 al_draw_text(faont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y-10,ALLEGRO_ALIGN_LEFT, (temp->resist).nombre);
                 al_draw_text(faont, al_map_rgb(10,10,10), (temp->resist).x, (temp->resist).y+30,ALLEGRO_ALIGN_LEFT, (temp->resist).value);
                 
                 temp=temp->next;
                 }
        
        }        
            while(temp);
    
}

void printlines(PTR2LINE * top)
{
    PTR2LINE temp;
    temp=*top;

    while(temp)
    {
        al_draw_line( (temp->line).x1,(temp->line).y1,(temp->line).x2,(temp->line).y2,al_map_rgb(0,0,0),3);
        temp=temp->nextli;
    }
     
    
}

void DetectClick(ALLEGRO_EVENT clic,float* x,float* y,PTR2NODET reslist)
{
    int tocaste=1;
    if( ((YBAT+50)>=clic.mouse.y && YBAT<=clic.mouse.y) && (XBAT+10>=clic.mouse.x && XBAT<=clic.mouse.x) )
    {
        tocaste=1;
        *x=XBAT;
        *y=YBAT+25;
        return;
    }
    else if(((YBAT+50)>=clic.mouse.y && YBAT<=clic.mouse.y) && (XBAT+50>=clic.mouse.x && XBAT+40<=clic.mouse.x))
    {
        tocaste=1;
        *x=XBAT+50;
        *y=YBAT+25;
    }
    while(reslist)
    {
        if((reslist->resist).volteado==1)
        {
            if( ( ((reslist->resist).y+25)>=clic.mouse.y) && (((reslist->resist).y-25))<=clic.mouse.y)
            {
                if(( ((reslist->resist).x+25)>=clic.mouse.x ) && ( ((reslist->resist).x-25)<=clic.mouse.x ))
                {
                    tocaste=1;
                    *x=(reslist->resist).x;
                    *y=(reslist->resist).y;
                    break;
                }
                else if(( ((reslist->resist).x+125)>=clic.mouse.x ) && ( ((reslist->resist).x+75)<=clic.mouse.x ))
                {
                    tocaste=1;
                    *x=((reslist->resist).x+100);
                    *y=((reslist->resist).y);
                    break;
                }
            }
            reslist=reslist->next;
        }
        
        else if((reslist->resist).volteado==0)
        {
            if(( ((reslist->resist).x+25)>=clic.mouse.x ) && ( ((reslist->resist).x-25)<=clic.mouse.x ) )
            {
                if(( ((reslist->resist).y+25)>=clic.mouse.y) && ((reslist->resist).y-25)<=clic.mouse.y)
                {
                    tocaste=1;
                    *x=(reslist->resist).x;
                    *y=(reslist->resist).y;
                    break;
                }
                else if(( ((reslist->resist).y+125)>=clic.mouse.y) && ((reslist->resist).y+75)<=clic.mouse.y)
                {
                    tocaste=1;
                    *x=((reslist->resist).x);
                    *y=((reslist->resist).y+100);
                    break;
                }
            }
            reslist=reslist->next;
        }
    }
}