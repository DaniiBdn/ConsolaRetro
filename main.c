/*
 * TFG.c
 *
 * Created: 02/11/2021 15:18:12
 * Author : Usuario
 */ 


#include <stdio.h>
#include <avr/io.h>

#include "ili9341.h"
#include "general.h"

void MenuPrincipal(unsigned char ON);
void Teclas(void);
void Seleccion(unsigned char Opcion, unsigned char x, int color);
unsigned char xy[1]={1,1};
//unsigned char i;



/**
 * @desc    Main function
 *
 * @param   Void
 *
 * @return  Void
 */

int main(void)
{
	xy[1]=1;
	xy[0]=1;
  // init lcd
  ILI9341_Init();
  Teclas();
  ILI9341_ClearScreen(ILI9341_BLACK);
  Menu();
  
 return 0;
}



void Teclas(void){
	DDRD&=~(1<<7);
	DDRD&=~(1<<6);
	DDRD&=~(1<<5);
	DDRC&=~(1<<0);
	DDRC&=~(1<<1);

	PORTD&=~(1<<7);
	PORTD&=~(1<<6);
	PORTD&=~(1<<5);
	PORTC&=~(1<<0);
	PORTC&=~(1<<1);
	
}

void Menu(void){
	
MenuPrincipal(1);

unsigned char Cuadrado;
Cuadrado=1;

while(1){
	//UP
	if(PIND&(1<<7)){
		xy[1]-=1;
		Cuadrado=1;
		if (xy[1]<1)
		{
			xy[1]=1;
		}
	}
	//down
	else if (PIND&(1<<6) ){
		xy[1]+=1;
		Cuadrado=1;
		if (xy[1]>3)
		{
			xy[1]=3;
		}
	}
	//left
	else if(PINC&(1<<0) && xy[1]==2){
		xy[0]-=1;
		Cuadrado=1;
		if (xy[0]<1)
		{
			xy[0]=1;
		}
	}
	//right
	else if(PINC&(1<<1) && xy[1]==2){
		xy[0]+=1;
		Cuadrado=1;
		if (xy[0]>2)
		{
			xy[0]=2;
		}
	}
	
	
	if(xy[1]==1 && Cuadrado==1 ){
		Seleccion(2,1,ILI9341_BLACK);
		Seleccion(2,2,ILI9341_BLACK);
		Seleccion(xy[1],xy[0],ILI9341_WHITE);
		Cuadrado=0;
	}
	else if (xy[0]==1 && xy[1]==2  && Cuadrado==1)
	{
		Seleccion(1,1,ILI9341_BLACK);
		Seleccion(2,2,ILI9341_BLACK);
		Seleccion(3,1,ILI9341_BLACK);
		Seleccion(xy[1],xy[0],ILI9341_WHITE);
		Cuadrado=0;
	}
	else if (xy[0]==2 && xy[1]==2  && Cuadrado==1)
	{
		Seleccion(1,1,ILI9341_BLACK);
		Seleccion(2,1,ILI9341_BLACK);
		Seleccion(3,1,ILI9341_BLACK);
		Seleccion(xy[1],xy[0],ILI9341_WHITE);
		Cuadrado=0;
	}
	if( xy[1]==3 && Cuadrado==1 ){
		Seleccion(2,1,ILI9341_BLACK);
		Seleccion(2,2,ILI9341_BLACK);
		Seleccion(xy[1],xy[0],ILI9341_WHITE);
		Cuadrado=0;
	}
	
	
	if(PIND&(1<<5) && xy[1]==1){
		Seleccion(xy[1],xy[0],ILI9341_BLACK);
		MenuPrincipal(0);
		Juegodelavida();
		
	}
	else if(PIND&(1<<5) && xy[0]==1 &&  xy[1]==2){
		Seleccion(xy[1],xy[0],ILI9341_BLACK);
		MenuPrincipal(0);
		juegonave();
		
	}
	else if(PIND&(1<<5) && xy[0]==2 &&  xy[1]==2 ){
		Seleccion(xy[1],xy[0],ILI9341_BLACK);
		MenuPrincipal(0);
		SnakeGame();
		
	}
	else if(PIND&(1<<5) && xy[1]==3 ){
		Seleccion(xy[1],xy[0],ILI9341_BLACK);
		MenuPrincipal(0);
		buscaminas();
	}
	
	_delay_ms(200);
	
}

}


	
	
void MenuPrincipal(unsigned char ON){
	int lineas,letras;
	
	if (ON==1)
	{
	lineas=ILI9341_WHITE;
	letras=ILI9341_RED;
	}
	else{
	lineas=ILI9341_BLACK;
	letras=ILI9341_BLACK;	
	}
	 // draw horizontal fast line
	 ILI9341_DrawLineHorizontal(10, ILI9341_MAX_X - 10, 12, lineas);
	 // draw horizontal fast line
	 ILI9341_DrawLineHorizontal(10, ILI9341_MAX_X - 10, 50, lineas);
	 //
	 ILI9341_DrawLineVertical (10 , 12,  ILI9341_MAX_Y - 10, lineas);
	 ILI9341_DrawLineVertical (ILI9341_MAX_X - 10, 12,  ILI9341_MAX_Y - 10, lineas);

	 ILI9341_DrawLineHorizontal(10, ILI9341_MAX_X - 10, ILI9341_MAX_Y - 10, lineas);
	 //ILI9341_DrawPixel (uint16_t, uint16_t, uint16_t);
	 // set position
	 ILI9341_SetPosition(75, 25);
	 // draw string
	 ILI9341_DrawString("CATALOGO", letras, X3);
	 
	  ILI9341_SetPosition(45, 80);
	  ILI9341_DrawString("0 Jugadores", letras, X3);
	
	  
	  ILI9341_DrawLineHorizontal(10,ILI9341_MAX_X - 10,70, lineas);
	  ILI9341_DrawLineHorizontal(10,ILI9341_MAX_X - 10,100, lineas);
	  
	  ILI9341_SetPosition(25, 110);
	  ILI9341_DrawString("Juego de la vida", letras, X3);
	  
	  ILI9341_SetPosition(75, 160);
	  ILI9341_DrawString("1 Jugador", letras, X3);
	  
	  ILI9341_DrawLineHorizontal(10,ILI9341_MAX_X - 10,150, lineas);
	  ILI9341_DrawLineHorizontal(10,ILI9341_MAX_X - 10,180, lineas);
	  
	  ILI9341_SetPosition(25, 210);
	  ILI9341_DrawString("Spaceship", letras, X3);
	  
	  ILI9341_SetPosition(160, 210);
	  ILI9341_DrawString("Snake", letras, X3);
	  
	  ILI9341_SetPosition(55, 250);
	  ILI9341_DrawString("Buscaminas", letras, X3);
	  

}

void Seleccion(unsigned char y,unsigned char x, int color){
	
	if (y==1)
	{
		ILI9341_DrawLineHorizontal(20,220,105 , color);
		ILI9341_DrawLineHorizontal(20,220,130 , color);
		
		ILI9341_DrawLineVertical (20 , 105, 130, color);
		ILI9341_DrawLineVertical (220, 105, 130, color);
	}
	else if (y==2 && x==1)
	{
		ILI9341_DrawLineHorizontal(15,140,205 , color);
		ILI9341_DrawLineHorizontal(15,140,230 , color);
		
		ILI9341_DrawLineVertical (15 , 205, 230, color);
		ILI9341_DrawLineVertical (140, 205, 230, color);
	}
	else if (y==2 && x==2)
	{
		ILI9341_DrawLineHorizontal(155,220,205 , color);
		ILI9341_DrawLineHorizontal(155,220,230 , color);
		
		ILI9341_DrawLineVertical (155, 205, 230, color);
		ILI9341_DrawLineVertical (220, 205, 230, color);
	}
	else if (y==3)
	{
		ILI9341_DrawLineHorizontal(50,180,245 , color);
		ILI9341_DrawLineHorizontal(50,180,270 , color);
		
		ILI9341_DrawLineVertical (50 , 245, 270, color);
		ILI9341_DrawLineVertical (180, 245, 270, color);
	}
	
	
}
