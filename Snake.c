/*
 * Snake.c
 *
 * Created: 11/12/2021 13:13:35
 *  Author: Usuario
 */ 
#include <avr/io.h>
#include <stdlib.h>

#include "ili9341.h"
#include "general.h"


typedef struct{

	int x,y;
	int Modx,Mody;

}snk;

	
typedef struct{
		int x,y;
}frt;
		
snk snake[100];
frt fruta;

void Cabeza(int x,int y, int color);
void Cuerpo(int x,int y, int color);
void Fruta(int x, int y , int color);

void SnakeGame(void){
	unsigned char muerto;
	int i;
	char tamanyo,tamanyoChar,tamanyoChar1;
	muerto=0;
	
	tamanyoChar=3;
	tamanyoChar1=0;
	snake[0].x=120;
	snake[0].y=200;
	tamanyo=3;
	
	fruta.x= rand () % (240-1);
	//numero = rand () % (N-M+1) + M;   // Este está entre M y N
	
	fruta.y= rand () % (310-65+1) + 65;
	
	while (fruta.x==0)
	{
		fruta.x= rand () % (240-1);
	}
	while (fruta.y==0)
	{
		fruta.y= rand () % (320-1);
	}
	
	for (i=0; i<tamanyo; i++)
	{
		snake[i].Modx=15;
		snake[i].Mody=0;
	}
	
	//////////////////////////////////////////////////////////////////////////DIBUJAR ESCENARIO////////////////////////////
	ILI9341_SetPosition(10,10);
	ILI9341_DrawString("Tamanyo: ", ILI9341_WHITE, X3);
	
	ILI9341_SetPosition(120,10);
	ILI9341_DrawChar (tamanyoChar1+48, ILI9341_WHITE, X3);
	ILI9341_SetPosition(135,10);
	ILI9341_DrawChar (tamanyoChar+48, ILI9341_WHITE, X3);
	
	ILI9341_DrawLineHorizontal(0, 239, 60, ILI9341_WHITE);
	ILI9341_DrawLineHorizontal(0, 239, 319, ILI9341_WHITE);
	
	ILI9341_DrawLineVertical (0 ,60, 319, ILI9341_WHITE);
	ILI9341_DrawLineVertical (239,60, 319, ILI9341_WHITE);
	//////////////////////////////////////////////////datos///////////////////////////////////
	for (i=1;i<tamanyo;i++)
	{
		snake[i].x = snake[i-1].x -15;
		snake[i].y = snake[i-1].y;

	}
	//DIBUJAR CABEZA SNAKE//
	Cabeza(snake[0].x,snake[0].y, ILI9341_WHITE);
	
	for (i=0;i<tamanyo;i++)
	{
		Cuerpo(snake[i].x, snake[i].y, ILI9341_WHITE);
		
	}
	Fruta(fruta.x,fruta.y,ILI9341_WHITE);
	
	//////////////////////////////////////////////fin datos///////////////////////////////
	while(muerto==0){
		
		//UP
		if(PIND&(1<<7) && snake[0].Mody!=15){
		
				snake[0].Modx=0;
				snake[0].Mody=-15;
		}
		
		//down
		else if (PIND&(1<<6) && snake[0].Mody!=-15){
				
				snake[0].Modx=0;
				snake[0].Mody=15;
		}
		
		//left
		else if(PINC&(1<<0) && snake[0].Modx!=15){
				snake[0].Modx=-15;
				snake[0].Mody=0;
				
		}
		
		//right
		else if(PINC&(1<<1) && snake[0].Modx!=-15){
			
				snake[0].Modx=15;
				snake[0].Mody=0;
		}
		
		//A
		if(PIND&(1<<5)){
			
		}
		
		//morir
		if (snake[0].x<0 || snake[0].x>230 || snake[0].y<=60 || snake[0].y>310)
		{
			muerto=1;
		}
		
		for (i=1;i<tamanyo;i++)
		{
			if (snake[0].x==snake[i].x && snake[0].y==snake[i].y)
			{
				muerto=1;
			}
		}
		
		//comer fruta//
		if (fruta.x>snake[0].x+10)
		{
		}
		
		else if (fruta.x+20<snake[0].x)
		{
		}
		
		else if (fruta.y>snake[0].y+10)
		{
		}
		
		else if (fruta.y+20<snake[0].y)
		{
		}
		
		else{
			
			Fruta(fruta.x,fruta.y,ILI9341_BLACK);
			
			ILI9341_SetPosition(135,10);
			ILI9341_DrawChar (tamanyoChar+48, ILI9341_BLACK, X3);
			
			tamanyo+=1;
			tamanyoChar+=1;
			if (tamanyoChar>9)
			{
				ILI9341_SetPosition(120,10);
				ILI9341_DrawChar (tamanyoChar1+48, ILI9341_BLACK, X3);
				tamanyoChar=0;
				tamanyoChar1+=1;
				
				if (tamanyoChar1>9)
				{
					tamanyoChar1=0;
				}
				ILI9341_SetPosition(120,10);
				ILI9341_DrawChar (tamanyoChar1+48, ILI9341_WHITE, X3);
			}
			
			fruta.x= rand () % (240-1);
			fruta.y= rand () % (310-65+1) + 65;
			
			ILI9341_SetPosition(135,10);
			ILI9341_DrawChar (tamanyoChar+48, ILI9341_WHITE, X3);
			
			while (fruta.x==0)
			{
				fruta.x= rand () % (240-10);
			}
			while (fruta.y>65)
			{
				fruta.y= rand () % (310-65+1) + 65;
			}
			
			Fruta(fruta.x,fruta.y,ILI9341_WHITE);
			
		}
		
		/*
		if (snake[0].x==fruta.x && snake[0].y==fruta.y)
		{
		Fruta(fruta.x,fruta.y,ILI9341_BLACK);
		//AÑADIR UN CUERPO
		tamanyo+=1;
			
		fruta.x= rand () % (240-1);
		fruta.y= rand () % (320-1);
			
			
			while (fruta.x==0)
			{
				fruta.x= rand () % (240-10);
			}
			while (fruta.y==0)
			{
				fruta.y= rand () % (320-10);
			}
			
			Fruta(fruta.x,fruta.y,ILI9341_WHITE);
		}
		*/
		
		//update
		Cabeza(snake[0].x,snake[0].y, ILI9341_BLACK);
		
		for (i=0;i<tamanyo;i++)
		{
			Cuerpo(snake[i].x, snake[i].y, ILI9341_BLACK);
		}
		
	
		
		for (i=(tamanyo-1);i>0;i--)
		{
			snake[i].x = snake[i-1].x;
			snake[i].y = snake[i-1].y;

		}
		
			snake[0].x+=snake[0].Modx;
			snake[0].y+=snake[0].Mody;
			
		Cabeza(snake[0].x,snake[0].y, ILI9341_WHITE);
		
		for (i=0;i<tamanyo;i++)
		{
			Cuerpo(snake[i].x, snake[i].y, ILI9341_WHITE);
		}
		
		_delay_ms(200);	
		
	}
	//MORIR
	
	ILI9341_SetPosition(10,10);
ILI9341_DrawString("Tamanyo:", ILI9341_BLACK, X3);
	ILI9341_SetPosition(120,10);
	ILI9341_DrawChar (tamanyoChar1+48, ILI9341_BLACK, X3);
	ILI9341_SetPosition(135,10);
	ILI9341_DrawChar (tamanyoChar+48, ILI9341_BLACK, X3);
	
	ILI9341_DrawLineHorizontal(0, 239, 60, ILI9341_BLACK);
	ILI9341_DrawLineHorizontal(0, 239, 319, ILI9341_BLACK);
	
	ILI9341_DrawLineVertical (0 ,60, 319, ILI9341_BLACK);
	ILI9341_DrawLineVertical (239,60, 319, ILI9341_BLACK);
	
	Cabeza(snake[0].x,snake[0].y, ILI9341_BLACK);
	
	for (i=0;i<tamanyo;i++)
	{
		Cuerpo(snake[i].x, snake[i].y, ILI9341_BLACK);
	}
	Fruta(fruta.x,fruta.y,ILI9341_BLACK);
	
	Menu();
}

void Cabeza(int x,int y, int color){
	unsigned char i;
	
	for (i=0;i<10;i++)
	{
		ILI9341_DrawLineHorizontal(x,x+10 ,y+i , color);
	}
	
}
	
void Cuerpo(int x,int y, int color){
	unsigned char i;
	
	for (i=0;i<10;i++)
	{
		ILI9341_DrawLineHorizontal(x,x+10 ,y+i , color);
	}
	
}

void Fruta(int x, int y , int color){
	
	ILI9341_SetPosition(x, y);
	
	ILI9341_DrawString("%", color, X3);
}
