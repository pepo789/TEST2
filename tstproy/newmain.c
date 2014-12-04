/* 
 * File:   newmain.c
 * Author: pepo
 *
 * Created on November 27, 2014, 9:21 PM
 */

#include "testheader.h"


const float FPS = 120;
PTR2NODET reslist=NULL;
PTR2ARR linesarr=NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *copadares = NULL;
/*
 * 
 */
int main(int argc, char** argv) {
    

     
     ALLEGRO_TIMER *timer = NULL;
 
     
     
     float copadares_x = 0;
     float copadares_y = 0;
     
     bool dibujar=true;
     

     static int genericevent;
 

     
     
     
     //empiezo las inicializaciones
     if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
     
     al_init_font_addon(); // initialize the font addon
     al_init_ttf_addon();// initialize the ttf (True Type Font) addon
     
     if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
     

     
     if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
     
     if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
     
   
     
     //ACA INCIALIZO ELEMENTOS DE PUNTERO
     timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
     
     
 
   display = al_create_display(WIDTH, HEIGHT);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }
   
   copadares = al_load_bitmap("copada2.png");
 
   if(!copadares) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   
   al_set_target_bitmap(al_get_backbuffer(display));
   

   
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      return -1;
   }
  
   
   
   
   //registro los eventos  
   
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_mouse_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_start_timer(timer);

 
 
   
   //inicializo los arreglos
   GetPtr2Res();
   GetPtr2Line();
  
   //ARRANCO EL PROGRAMA
   
   while(1)
   {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
           
       
       //RECEPTORES DE EVENTOS
        if(ev.type == ALLEGRO_EVENT_TIMER) {
         dibujar = true;
        }  
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
        } 
        
         else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            // al_destroy_event_queue(event_queue);
             genericevent=maquina(ev);
            // event_queue = al_create_event_queue();
         }
        
            else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
           //al_destroy_event_queue(event_queue);
           maquina(ev);   
          // event_queue = al_create_event_queue();
           
      }
        
        
         //actualizo las coordenadas del mouse
         else if( ((genericevent==7)||(genericevent==2)) && ( ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) ) {           
         
         copadares_x = ev.mouse.x;
         copadares_y = (ev.mouse.y-RESHEIGHT/2);
        //-RESHEIGHT/2
         cuadric(&copadares_x,&copadares_y);
        
         }
        
        
        
    
       
        
        
        
        
        
        
        
        //ESTO DIBUJA. VA AL FINAL--
        
        if(dibujar && al_is_event_queue_empty(event_queue)) {
         dibujar = false;     
        //pinto todo de blanco para dibujar arriba de nuevo
            al_clear_to_color(al_map_rgb(255, 255, 255));
            
            
            
            
            DrawCadriq();
            if(reslist)
            PrintResists(&reslist,copadares);
            
            
            
            //dibujo las resistencias que siguen al mouse
            if(genericevent==7)
            al_draw_bitmap(copadares, copadares_x, copadares_y, 0);
            
            else if(genericevent==2)
            al_draw_rotated_bitmap(copadares,0, 0,copadares_x+50,copadares_y+25,1.57079632679,0);
           
           
            
            
            
            
            
            
            
            
            al_flip_display();
                
        }
    
   }
   return (EXIT_SUCCESS);
}

