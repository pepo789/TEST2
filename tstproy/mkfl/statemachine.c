#include "testheader.h"
//declaroestados como extern, dado que si no los estados recursivos tiran error
//declaro el puntero que indica el estado actual como global para no tener que pasarlo como parametro
STATE *p2state=estado_0;//apunto al primer estado

int maquina(ALLEGRO_EVENT ev)
{
    static int keypressed;
    
    p2state=fsm(p2state,ev);
    
   
    switch(ev.keyboard.keycode){
   
        case ALLEGRO_KEY_R:
        
                if(keypressed==7){
                    keypressed=2;
                    break;
                }

                keypressed=7;
        break; /* optional */
   
       
        case ALLEGRO_KEY_L:
        keypressed=1;
         break; /* optional */
       
        case ALLEGRO_KEY_S:
        keypressed=3;
         break;
    
    }
      
    return keypressed;
}

STATE * fsm(STATE *pstate,ALLEGRO_EVENT ev)
{
    while ( (pstate -> evento != ev.keyboard.keycode) && (pstate -> evento!= ev.mouse.button) && ((pstate -> evento) != QU))	//Recorre las tablas de estado
        ++pstate;
    (pstate->p_rut_accion)(ev);
    pstate=pstate->prx_estado;
    return pstate;
}

    

STATE estado_0[]=
{
  	{ALLEGRO_KEY_L,estado_1,do_nothing},
  	{ALLEGRO_KEY_R,estado_01,do_nothing},
        {ALLEGRO_KEY_S,estado_S,do_nothing},
        {ALLEGRO_KEY_C,estado_Z,do_nothing},
        {QU,estado_0,do_nothing},
};

STATE estado_ROT[]=
{
        {CLICK,estado_ROT,insert_ressistance_ROT},
        {ALLEGRO_KEY_L,estado_1,do_nothing},
  	{ALLEGRO_KEY_R,estado_01,do_nothing},
        {ALLEGRO_KEY_S,estado_S,do_nothing},
        {QU,estado_ROT,do_nothing},
};

 STATE estado_01[]=
{
  	{CLICK,estado_01,insert_ressistance},
        {ALLEGRO_KEY_L,estado_1,do_nothing},
        {ALLEGRO_KEY_R,estado_ROT,do_nothing},
        {ALLEGRO_KEY_S,estado_S,do_nothing},
        {QU,estado_01,do_nothing},
};
 
 
 STATE estado_1[]=
{
	{CLICK,estado_1,insert_line},
        {ALLEGRO_KEY_R,estado_01,do_nothing},
        {ALLEGRO_KEY_S,estado_S,do_nothing},
        {ALLEGRO_KEY_C,estado_Z,do_nothing},
        {QU,estado_1,do_nothing},
};
 
 STATE estado_S[]=
{
	{CLICK,estado_S,SelectRes},
        {ALLEGRO_KEY_L,estado_1,do_nothing},
        {ALLEGRO_KEY_R,estado_01,do_nothing},
        {QU,estado_S,do_nothing},
};

 STATE estado_Z[]=
{
        {ALLEGRO_KEY_C,estado_Z,Calculate},
        {QU,estado_Z,do_nothing},
 };
 
 
 void insert_line(ALLEGRO_EVENT ev)
 {
     PTR2ARR temp;
     temp=(PTR2ARR)calloc(1,sizeof(NODETARR));
     PTR2LINE * topline=(PTR2LINE *)calloc(1,sizeof(PTR2LINE)); //PUNTERO AL ARREGLO GENERAL
         
        
         float linexinit,lineyinit,linexend,lineyend,mousex,mousey;
         int respressed;
         respressed=DetectClick(ev,&linexinit,&lineyinit,&reslist);
         
         temp->in=AssignNode(&reslist,linexinit,lineyinit);
        
         
     if(respressed)
     {
         
         
         //linexinit=ev.mouse.x;
         //lineyinit=ev.mouse.y;
         cuadric(&linexinit,&lineyinit);
         respressed=0;
     
        
         while(respressed==0)
         {
             
             
             ALLEGRO_EVENT linev;
             al_wait_for_event(event_queue,&linev);
             
             
             
             if(( linev.type == ALLEGRO_EVENT_MOUSE_AXES || linev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY))
             {
                 if( (abs(linev.mouse.x-linexinit)) >= (abs(linev.mouse.y-lineyinit)) )
                 {
                     linexend=linev.mouse.x;
                     lineyend=lineyinit;
                     cuadric(&linexend,&lineyend);
                 }
                 else if((abs(linev.mouse.y-lineyinit)) >= (abs(linev.mouse.x-linexinit)))
                 {
                     lineyend=linev.mouse.y;
                     linexend=linexinit;
                     cuadric(&linexend,&lineyend);
                 }
                 
             }
             
             else if(linev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
             {
                 
                 
                 LINEA * templine=(LINEA *)calloc(1,sizeof(LINEA));
                 
                 mousex=linev.mouse.x;
                 mousey=linev.mouse.y;
                 //respressed=DetectClick(linev,&mousex,&mousey,&reslist);
                 respressed=DetectClick(linev,&linexend,&lineyend,&reslist);
                 if(respressed){
                     temp->out=AssignNode(&reslist,linexend,lineyend);
                     if((temp->out == temp->in) || (temp->out==5 && temp->in==7) || (temp->out==7 && temp->in==5))
                     {
                          al_show_native_message_box(al_get_current_display(), 
                                 "error", 
                                 "UNISTE MAL", 
                                 "uni de nuevo.",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
                         
                         free(temp);
                         free(*topline);
                         return;
                     }
                 }
                        templine->x1=linexinit;
                        templine->y1=lineyinit;
                        templine->x2=linexend;
                        templine->y2=lineyend;
                 
                 
                 add_node_line(topline,templine);
                 
                 linexinit=templine->x2;
                 lineyinit=templine->y2;
       
             }
             else if(linev.type == ALLEGRO_EVENT_KEY_UP)
             {
                 if(linev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                 {
                     free(temp);
                     free(*topline);
                     return;
                 }
             }
             
             //dibujo
               
             al_clear_to_color(al_map_rgb(255, 255, 255));
             DrawCadriq();
             PrintResists(&reslist,copadares);
             
             PrintAllWires(linesarr);
             printlines(topline);
             al_draw_line( linexinit,lineyinit,linexend,lineyend,al_map_rgb(0,0,0),3);
             
             al_flip_display();
             
                            
         }
          
      temp->array=*topline; 
      add_node_wire(&linesarr,temp);
     } 

         free(temp);
      
 }
 
 

 
 
 void insert_ressistance(ALLEGRO_EVENT ev)
 {
     int cancelled=0,repeatedname=1;
     RESISTENCIA *  tempres=(RESISTENCIA*)calloc(1,sizeof(RESISTENCIA));
     float resx,resy;
     char * name= (char *)calloc(10,1);
     char * resis= (char *)calloc(10,1);

     
     
     resx=ev.mouse.x;
     resy=ev.mouse.y-RESHEIGHT/2;
     
     cuadric(&resx,&resy);
     
     tempres->x=resx;
     tempres->y=resy;
     tempres->volteado=1;
     
     while(repeatedname)
     {
         
    cancelled = GetResName(ev,name);   
     
                if(cancelled)
                {
                    free(name);
                    free(resis);
                    free(tempres);
                         al_set_clipping_rectangle(0, 0, WIDTH, HEIGHT);
                    return;
                }
    
        repeatedname=ScanName(name,&reslist);
     }
    
    
    strcpy ( tempres->nombre, name);
     
    
    cancelled = GetResValue(ev,resis);
    
                if(cancelled)
                {
                    free(name);
                    free(resis);
                    free(tempres);
                         al_set_clipping_rectangle(0, 0, WIDTH, HEIGHT);
                    return;
                }
    
    
    strcpy ( tempres->value,resis);
     tempres->ohm = string2num(resis);
     

     
     add_node_RES(&reslist,tempres);
     
     free(tempres);
     free(name);
     free(resis);
     
     al_set_clipping_rectangle(0, 0, WIDTH, HEIGHT);
     
     return;
 }
 
 
 void insert_ressistance_ROT(ALLEGRO_EVENT ev)
 {
     int cancelled=0,repeatedname=1;
     RESISTENCIA *  tempres=(RESISTENCIA*)calloc(1,sizeof(RESISTENCIA));
     float resx,resy;
     char * name= (char *)calloc(10,1);
     char * resis= (char *)calloc(10,1);

     
     
     resx=ev.mouse.x+50;
     resy=ev.mouse.y;
     
     cuadric(&resx,&resy);
     
     tempres->x=resx;
     tempres->y=resy;
     tempres->volteado=0;
     
     while(repeatedname)
     {
         
    cancelled = GetResName(ev,name);   
     
                if(cancelled)
                {
                    free(name);
                    free(resis);
                    free(tempres);
                         al_set_clipping_rectangle(0, 0, WIDTH, HEIGHT);
                    return;
                }
    
        repeatedname=ScanName(name,&reslist);
     }
     
     strcpy ( tempres->nombre, name);
     
     cancelled=GetResValue(ev,resis);  
                if(cancelled)
                {
                    free(name);
                    free(resis);
                    free(tempres);
                         al_set_clipping_rectangle(0, 0, WIDTH, HEIGHT);
                    return;
                }
     
     
     strcpy ( tempres->value,resis);
     tempres->ohm = string2num(resis);
     
     
     
     add_node_RES(&reslist,tempres);
     
     free(tempres);
     free(name);
     free(resis);
     
     al_set_clipping_rectangle(0, 0, WIDTH, HEIGHT);
     
     return;
 }
 
 
 int GetResValue(ALLEGRO_EVENT ev,char * value)
 {
     int cancelled=0;
     float xpos=ev.mouse.x;
     float ypos=ev.mouse.y-RESHEIGHT/2;
     
     cuadric(&xpos,&ypos);
     
     int respos=0;
     
    

     
     while(respos<=9)
     {
         ALLEGRO_EVENT resev;
         al_wait_for_event(event_queue,&resev);
          //if(resev.type==ALLEGRO_EVENT_KEY_CHAR || resev.type==ALLEGRO_EVENT_KEY_UP)
         if(resev.type==ALLEGRO_EVENT_KEY_CHAR)
         {
             
             if(resev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {   
                 break;
             }
             else if(resev.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
             {
                 
                 if(respos>=1)
                     respos--; 
            
                 value[respos]=0;    
                 al_set_clipping_rectangle(xpos, ypos+35, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
                 
                 
             }
             else if((  ((resev.keyboard.unichar>=48) && (resev.keyboard.unichar<=57) ) || (resev.keyboard.unichar==75 || resev.keyboard.unichar==107)) &&(respos<=8) )
             {
                 value[respos]=(char)resev.keyboard.unichar;
                 respos++;
                 
                 al_set_clipping_rectangle(xpos, ypos+35, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
             }
             else if(resev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                 cancelled=1;
                 break;
             }
                 
             
         
             
             al_draw_text(fiont, al_map_rgb(250,120,60), xpos, ypos+35,ALLEGRO_ALIGN_LEFT, value);
             al_flip_display();
             
         
         }
         
         
     }
     
     return cancelled;
     
 }
 
 
 
 
 
 int GetResName(ALLEGRO_EVENT ev,char * name)
 {
 
     int cancelled=0;
     float xpos=ev.mouse.x;
     float ypos=ev.mouse.y-RESHEIGHT/2;
     
     cuadric(&xpos,&ypos);
     
     //FixDirectory();
     //ALLEGRO_FONT * faont = al_load_ttf_font("UbuntuMono-R.ttf",15,0 );

     
     
     int nampos=0;
     
     while(nampos<=9)
     {
         ALLEGRO_EVENT namev;
         al_wait_for_event(event_queue, &namev);
         
         if(namev.type==ALLEGRO_EVENT_KEY_CHAR)
         {
             
             if(namev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {
                 
                 break;
             }
             else if(namev.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
             {
                 if(nampos>=1)
                     nampos--;
                 
                 name[nampos]=0;  
                 al_set_clipping_rectangle(xpos, ypos-10, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
                 
                 
             }
             else if( ( ( (namev.keyboard.unichar>=65) && (namev.keyboard.unichar<=90) ) || (  (namev.keyboard.unichar>=97) && (namev.keyboard.unichar<=122) )   || (  (namev.keyboard.unichar>=48) && (namev.keyboard.unichar<=57) ) ) && (nampos<=8) )
             {
                 name[nampos]=(char)namev.keyboard.unichar;
                 nampos++;
                 al_set_clipping_rectangle(xpos, ypos-10, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
             }
             else if(namev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                 cancelled=1;
                 break;
             }
         
             
         }
     
       
             al_draw_text(fiont, al_map_rgb(0,0,0), xpos, ypos-10,ALLEGRO_ALIGN_LEFT, name );
             al_flip_display();
             
             
     
     }
     return cancelled;
  
     
 }
 
 void SelectRes(ALLEGRO_EVENT ev)
 {
     SeeResists(&reslist,ev);
     SelectWire(&linesarr,ev);
 }
 
 void Calculate(ALLEGRO_EVENT ev)
 {
    ListRessistances(&reslist,&linesarr);
 }

 
 void do_nothing(ALLEGRO_EVENT ev)
 {
     //holis
 } 
   
