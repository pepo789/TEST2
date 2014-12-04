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
    while ( (pstate -> evento != ev.keyboard.keycode) && (pstate -> evento!= ev.mouse.button) && ((pstate -> evento) != ALLEGRO_KEY_ESCAPE))	//Recorre las tablas de estado
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
        {ALLEGRO_KEY_ESCAPE,estado_0,do_nothing},
};

STATE estado_ROT[]=
{
        {CLICK,estado_ROT,insert_ressistance_ROT},
        {ALLEGRO_KEY_L,estado_1,do_nothing},
  	{ALLEGRO_KEY_R,estado_01,do_nothing},
        {ALLEGRO_KEY_S,estado_S,do_nothing},
        {ALLEGRO_KEY_ESCAPE,estado_ROT,do_nothing},
};

 STATE estado_01[]=
{
  	{CLICK,estado_01,insert_ressistance},
        {ALLEGRO_KEY_L,estado_1,do_nothing},
        {ALLEGRO_KEY_R,estado_ROT,do_nothing},
        {ALLEGRO_KEY_S,estado_S,do_nothing},
        {ALLEGRO_KEY_ESCAPE,estado_01,do_nothing},
};
 
 
 STATE estado_1[]=
{
	{CLICK,estado_1,insert_line},
        {ALLEGRO_KEY_R,estado_01,do_nothing},
        {ALLEGRO_KEY_S,estado_S,do_nothing},
        {ALLEGRO_KEY_ESCAPE,estado_1,do_nothing},
};
 
 STATE estado_S[]=
{
	{CLICK,estado_1,SelectRes},
        {ALLEGRO_KEY_L,estado_1,do_nothing},
        {ALLEGRO_KEY_R,estado_01,do_nothing},
        {ALLEGRO_KEY_ESCAPE,estado_S,do_nothing},
};

 
 void insert_line(ALLEGRO_EVENT ev)
 {
     PTR2LINE * topline=(PTR2LINE *)calloc(1,sizeof(PTR2LINE)); //PUNTERO AL ARREGLO GENERAL
         

         float linexinit,lineyinit,linexend,lineyend;
         int respressed=1;
         
        
         
     if( ( (XBAT-25) <=ev.mouse.x) && ( (XBAT+25 ) >=ev.mouse.x) && ( (YBAT+25) >=ev.mouse.y) && ( (YBAT-25) <=ev.mouse.y) )
     {
         
         
         linexinit=ev.mouse.x;
         lineyinit=ev.mouse.y;
         cuadric(&linexinit,&lineyinit);
         
     
        
         while(respressed)
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
             
             else if(linev.type ==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
             {
                 
                 LINEA * templine=(LINEA *)calloc(1,sizeof(LINEA));
                 
                 templine->x1=linexinit;
                 templine->y1=lineyinit;
                 templine->x2=linexend;
                 templine->y2=lineyend;
                 
                 
                 add_node_line(topline,templine);
                 
                 linexinit=templine->x2;
                 lineyinit=templine->y2;
                 
                 
             }
             
             //dibujo
               
             al_clear_to_color(al_map_rgb(255, 255, 255));
             DrawCadriq();
             PrintResists(&reslist,copadares);
             
             printlines(topline);
             al_draw_line( linexinit,lineyinit,linexend,lineyend,al_map_rgb(0,0,0),3);
             
             al_flip_display();
             
                            
         }
          
          
      add_node_wire(&linesarr,*topline);
     } 

    
 }
 
 

 
 
 void insert_ressistance(ALLEGRO_EVENT ev)
 {
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
     
     GetResName(ev,name);   
     strcpy ( tempres->nombre, name);
     
     GetResValue(ev,resis);   
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
     RESISTENCIA *  tempres=(RESISTENCIA*)calloc(1,sizeof(RESISTENCIA));
     float resx,resy;
     char * name= (char *)calloc(10,1);
     char * resis= (char *)calloc(10,1);

     
     
     resx=ev.mouse.x;
     resy=ev.mouse.y-RESHEIGHT/2;
     
     cuadric(&resx,&resy);
     
     tempres->x=resx;
     tempres->y=resy;
     tempres->volteado=0;
     
     GetResName(ev,name);   
     strcpy ( tempres->nombre, name);
     
     GetResValue(ev,resis);   
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
     float xpos=ev.mouse.x;
     float ypos=ev.mouse.y-RESHEIGHT/2;
     
     cuadric(&xpos,&ypos);
     
     
     al_init_font_addon(); // initialize the font addon
     al_init_ttf_addon();// initialize the ttf (True Type Font) addon
     

     FixDirectory();
     ALLEGRO_FONT * fiont = al_load_ttf_font("UbuntuMono-R.ttf",20,0 );
     int respos;
     
    

     
     for(respos=0;respos<=9;)
     {
         ALLEGRO_EVENT resev;
         al_wait_for_event(event_queue,&resev);
         
         if(resev.type==ALLEGRO_EVENT_KEY_CHAR || resev.type==ALLEGRO_EVENT_KEY_DOWN)
         {
             
             if(resev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {
                 
                 break;
             }
             else if(resev.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
             {
                 if(respos>=1){
                 value[respos]=0;  
                 respos--;
                 al_set_clipping_rectangle(xpos, ypos+35, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
                 }
                 
             }
             else if((  (resev.keyboard.unichar>=48) && (resev.keyboard.unichar<=57) ) )
             {
                 value[respos]=(char)resev.keyboard.unichar;
                 respos++;
                 al_set_clipping_rectangle(xpos, ypos+35, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
             }
         
             
             al_draw_text(fiont, al_map_rgb(250,120,60), xpos, ypos+35,ALLEGRO_ALIGN_LEFT, value);
             al_flip_display();
             
         
         }
         
         
     }
     
 }
 
 
 
 
 
 int GetResName(ALLEGRO_EVENT ev,char * name)
 {
 
 
     float xpos=ev.mouse.x;
     float ypos=ev.mouse.y-RESHEIGHT/2;
     
     cuadric(&xpos,&ypos);
     
     FixDirectory();
     ALLEGRO_FONT * fuont = al_load_ttf_font("UbuntuMono-R.ttf",20,0 );

     
     
     int nampos;
     
     for(nampos=0;nampos<=9;)
     {
         ALLEGRO_EVENT namev;
         al_wait_for_event(event_queue, &namev);
         
         if(namev.type==ALLEGRO_EVENT_KEY_CHAR || namev.type==ALLEGRO_EVENT_KEY_UP)
         {
             
             if(namev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {
                 
                 break;
             }
             else if(namev.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
             {
                 if(nampos>=1){
                 name[nampos]=0;  
                 nampos--;
                 al_set_clipping_rectangle(xpos, ypos-10, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
                 }
                 
             }
             else if( ( (namev.keyboard.unichar>=65) && (namev.keyboard.unichar<=90) ) || (  (namev.keyboard.unichar>=97) && (namev.keyboard.unichar<=122) )   || (  (namev.keyboard.unichar>=48) && (namev.keyboard.unichar<=57) ) )
             {
                 name[nampos]=(char)namev.keyboard.unichar;
                 nampos++;
                 al_set_clipping_rectangle(xpos, ypos-10, 100, 20);
                 al_clear_to_color(al_map_rgb(255,255,255)) ;
                 al_flip_display();
             }
         
             
         }
     
       
             al_draw_text(fuont, al_map_rgb(0,0,0), xpos, ypos-10,ALLEGRO_ALIGN_LEFT, name );
             al_flip_display();
             
             
     
     }
     
  
     
 }
 
 void SelectRes(ALLEGRO_EVENT ev)
 {
     SeeResists(&reslist,ev);
 }

 
 void do_nothing(ALLEGRO_EVENT ev)
 {
     //holis
 } 
   
