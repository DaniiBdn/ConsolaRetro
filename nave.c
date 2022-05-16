/*
 * nave.c
 *
 * Created: 08/11/2021 18:50:09
 *  Author: Usuario
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include "ili9341.h"
#include "general.h"

void juegonave(void){
int navex,navey,balax,balay;
unsigned char bala=0,vidas=3;
unsigned char i,k,l,j;
char nivel=0,nivel1=0,Puntuacion=0,Puntuacion1=0,Puntuacion2=0;
int listaenemigos[3][5]={{20,80,120,200},{100,50,80,10},{0,0,0,0}}; //x,y,vida
int numero=240/5;
//int Puntuacion;
//numero = 240/5;
//numero2 = rand () % (100-50+1) + 50;   // Este está entre M y N
ILI9341_SetPosition(50, 5);
ILI9341_DrawString("Ronda", ILI9341_RED, X2);
ILI9341_SetPosition(200, 5);
ILI9341_DrawChar (nivel+48, ILI9341_RED, X2);
ILI9341_SetPosition(190, 5);
ILI9341_DrawChar (nivel1+48, ILI9341_RED, X2);

ILI9341_SetPosition(50, 25);
ILI9341_DrawString("Puntuacion", ILI9341_RED, X2);
ILI9341_SetPosition(180, 25);
ILI9341_DrawChar (Puntuacion+48, ILI9341_RED, X2);
ILI9341_SetPosition(190, 25);
ILI9341_DrawChar (Puntuacion1+48, ILI9341_RED, X2);
ILI9341_SetPosition(200, 25);
ILI9341_DrawChar (Puntuacion2+48, ILI9341_RED, X2);

ILI9341_SetPosition(50, 45);
ILI9341_DrawString("Vidas:", ILI9341_RED, X2);
ILI9341_SetPosition(200, 45);
ILI9341_DrawChar (vidas+48, ILI9341_RED, X2);

//listaenemigos[0][0]=numero;
//listaenemigos[1][0]=numero2;
navex=200;
navey=250;	

//numero = rand () % (N-M+1) + M;   // Este está entre M y N
nave(navex, navey, ILI9341_RED);
while(1){
if (listaenemigos[2][0]+listaenemigos[2][1]+listaenemigos[2][2]+listaenemigos[2][3]==0)
{
	ILI9341_SetPosition(200, 5);
	ILI9341_DrawChar (nivel+48, ILI9341_BLACK, X2);
	nivel+=1;
	if (nivel>9)
	{
	ILI9341_SetPosition(190, 5);
	ILI9341_DrawChar (nivel1+48, ILI9341_BLACK, X2);	
		nivel=0;
		nivel1+=1;
	if (nivel1>9)
	{
		nivel=0;
		nivel1=0;
	}
	ILI9341_SetPosition(190, 5);
	ILI9341_DrawChar (nivel1+48, ILI9341_RED, X2);
	}
	ILI9341_SetPosition(200, 5);
	ILI9341_DrawChar (nivel+48, ILI9341_RED, X2);
	for(i=0;i<4;++i){
		listaenemigos[2][i]=1;
		listaenemigos[0][i]=rand () % (numero*(i+2)-numero*(i+1)+1) + numero*(i+1);
		listaenemigos[1][i]=60;
	}
}

//nave(navex, navey, ILI9341_RED);

//-----------------BOTONES--------------------//
//up
 if(PIND&(1<<7) && navey>60){
	 nave(navex, navey, ILI9341_BLACK);
	 //_delay_ms(100);
	 //nave(navex, navey, ILI9341_BLACK);
	 navey-=15;
	nave(navex, navey, ILI9341_RED);
 }
 //down
 else if (PIND&(1<<6) && navey<280){
	//_delay_ms(100);
	//nave(navex, navey, ILI9341_BLACK);
	nave(navex, navey, ILI9341_BLACK);
	 navey+=15;
	nave(navex, navey, ILI9341_RED);
 }
 //left
 else if(PINC&(1<<0)){
	 //_delay_ms(100);
	 //nave(navex, navey, ILI9341_BLACK);
	 nave(navex, navey, ILI9341_BLACK);
	 navex-=15;
	 nave(navex, navey, ILI9341_RED);
 }
 //righ
 else if(PINC&(1<<1)){
	 //_delay_ms(100);
	 //nave(navex, navey, ILI9341_BLACK);
	 nave(navex, navey, ILI9341_BLACK);
	 navex+=15;
	 nave(navex, navey, ILI9341_RED);
 }
 //A
 if(PIND&(1<<5) && bala==0){
	 bala=1;
	 balax=navex;
	 balay=navey;
 }
 //-------------------------------------------------//
 if (bala==1){
	balay-=20;
	if(balay<60){
		bala=0;
		balax=0;
		balay=0;
	}
 }

 //------------------cargar------------------//
//nave(navex, navey, ILI9341_RED); 
 if (bala==1){
	 disparo(balax, balay, ILI9341_RED);
 }
 
  for(j=0;j<4;++j){
listaenemigos[1][j]=listaenemigos[1][j]+5;
if (listaenemigos[1][j]>300)
{
	listaenemigos[2][j]=0;
}
 if (listaenemigos[2][j]==1){
	 
	 enemigo(listaenemigos[0][j],listaenemigos[1][j], ILI9341_RED);
 }
  }
 
 _delay_ms(150);
 
 //nave(navex, navey, ILI9341_BLACK);
 
 if (bala==1){
	 disparo(balax, balay, ILI9341_BLACK);
 }
 
 for(k=0;k<4;++k)
 {
	 if (listaenemigos[2][k]==1){
		 enemigo(listaenemigos[0][k],listaenemigos[1][k], ILI9341_BLACK);
	 }
 }
  //-----------------HITBOX------------------//
  for(j=0;j<4;++j){
 if (listaenemigos[2][j]==1 && (balay-5)<=(listaenemigos[1][j]+20) && (balay-5)>=(listaenemigos[1][j]) && ( ((balax+15)>=(listaenemigos[0][j]) && (balax+15)<=(listaenemigos[0][j]+20)) || ((balax+10)<=listaenemigos[0][j] && (balax+15)>=listaenemigos[0][j]) || ((balax+15)>=(listaenemigos[0][j]+20) && (balax+10)<=(listaenemigos[0][j]+20)) ))
 {
	 listaenemigos[2][j]=0;
	 bala=0;
	 balax=0;
	 balay=0;
	 
	 
	 ILI9341_SetPosition(200, 25);
	 ILI9341_DrawChar (Puntuacion2+48, ILI9341_BLACK, X2);
	 Puntuacion2+=1;
	 if (Puntuacion2>9)
	 {
		 Puntuacion2=0;
		 ILI9341_SetPosition(190, 25);
		 ILI9341_DrawChar (Puntuacion1+48, ILI9341_BLACK, X2);
		 Puntuacion1+=1;
		 if (Puntuacion1>9)
		 {
			 Puntuacion1=0;
			 ILI9341_SetPosition(180, 25);
			 ILI9341_DrawChar (Puntuacion+48, ILI9341_BLACK, X2);
			 Puntuacion+=0;
			 if (Puntuacion>9)
			 {
				 Puntuacion=0;
			 }
			 ILI9341_SetPosition(180, 25);
			 ILI9341_DrawChar (Puntuacion+48, ILI9341_RED, X2);
		 }
		 ILI9341_SetPosition(190, 25);
		 ILI9341_DrawChar (Puntuacion1+48, ILI9341_RED, X2);
	 }
	 ILI9341_SetPosition(200, 25);
	 ILI9341_DrawChar (Puntuacion2+48, ILI9341_RED, X2); 
	 
 }
 if (listaenemigos[2][j]==1 && (navey+2)<=(listaenemigos[1][j]+20) && (navey+2)>=(listaenemigos[1][j]) && ( ((navex+24)>=(listaenemigos[0][j]) && (navex+24)<=(listaenemigos[0][j]+20)) || ((navex)<=listaenemigos[0][j] && (navex+24)>=listaenemigos[0][j]) || ((navex+24)>=(listaenemigos[0][j]+20) && (navex)<=(listaenemigos[0][j]+20)) ))
 {
	listaenemigos[2][j]=0;
	ILI9341_SetPosition(180, 25);
	ILI9341_DrawChar (Puntuacion+48, ILI9341_BLACK, X2);
	ILI9341_SetPosition(190, 25);
	ILI9341_DrawChar (Puntuacion1+48, ILI9341_BLACK, X2);
	ILI9341_SetPosition(200, 25);
	ILI9341_DrawChar (Puntuacion2+48, ILI9341_BLACK, X2);
	
	if (Puntuacion2==0 && Puntuacion1==0 && Puntuacion!=0)
	{
		Puntuacion2=9;
		Puntuacion1=9;
		Puntuacion-=1;
	}
	else if (Puntuacion2==0 && Puntuacion1!=0)
	{
		Puntuacion2=9;
		Puntuacion1-=1;	
	}
	else if (Puntuacion2!=0)
	{
		Puntuacion2-=1;
	}
	ILI9341_SetPosition(180, 25);
	ILI9341_DrawChar (Puntuacion+48, ILI9341_RED, X2);
	ILI9341_SetPosition(190, 25);
	ILI9341_DrawChar (Puntuacion1+48, ILI9341_RED, X2);
	ILI9341_SetPosition(200, 25);
	ILI9341_DrawChar (Puntuacion2+48, ILI9341_RED, X2);
	
	
	ILI9341_SetPosition(200, 45);
	ILI9341_DrawChar (vidas+48, ILI9341_BLACK, X2);
	vidas-=1;
	ILI9341_SetPosition(200, 45);
	ILI9341_DrawChar (vidas+48, ILI9341_RED, X2);
	
	if (vidas==0)
	{
		nave(navex, navey, ILI9341_BLACK);
		for(i=0;i<100;i++){
		ILI9341_DrawLineVertical ((240/2-50)+i , 320/2-50,  320/2+50, ILI9341_WHITE);
		}
		ILI9341_SetPosition(240/2-25, 320/2-20);
		ILI9341_DrawString("GAME", ILI9341_BLACK, X3);
		ILI9341_SetPosition(240/2-25, 320/2);
		ILI9341_DrawString("OVER", ILI9341_BLACK, X3);
		_delay_ms(5000);
		
		for(i=0;i<100;i++){
			ILI9341_DrawLineVertical ((240/2-50)+i , 320/2-50,  320/2+50, ILI9341_BLACK);
		}
		
		//nave(navex, navey, ILI9341_BLACK);
		
		ILI9341_SetPosition(50, 5);
		ILI9341_DrawString("Ronda", ILI9341_BLACK, X2);
		ILI9341_SetPosition(200, 5);
		ILI9341_DrawChar (nivel+48, ILI9341_BLACK, X2);
		ILI9341_SetPosition(190, 5);
		ILI9341_DrawChar (nivel1+48, ILI9341_BLACK, X2);

		ILI9341_SetPosition(50, 25);
		ILI9341_DrawString("Puntuacion", ILI9341_BLACK, X2);
		ILI9341_SetPosition(180, 25);
		ILI9341_DrawChar (Puntuacion+48, ILI9341_BLACK, X2);
		ILI9341_SetPosition(190, 25);
		ILI9341_DrawChar (Puntuacion1+48, ILI9341_BLACK, X2);
		ILI9341_SetPosition(200, 25);
		ILI9341_DrawChar (Puntuacion2+48, ILI9341_BLACK, X2);

		ILI9341_SetPosition(50, 45);
		ILI9341_DrawString("Vidas:", ILI9341_BLACK, X2);
		ILI9341_SetPosition(200, 45);
		ILI9341_DrawChar (vidas+48, ILI9341_BLACK, X2);
		
		Menu();
	}
 }
}

}
//-------------------------------------------------//	
}

void disparo(int x, int y, int color) {
	unsigned char i;
for (i=10;i<16;i++){	
 ILI9341_DrawLineVertical (x+i , y-5,  y, color);
}
}


void enemigo(int x, int y, int color){
	unsigned char i;
	for (i=0;i<20;i++){
	ILI9341_DrawLineVertical (x+i , y,  y+20, color);
	}

}



void nave(int x, int y, int color) {
	/*
	ILI9341_DrawPixel(120, 200, ILI9341_RED);
	ILI9341_DrawPixel(120, 201, ILI9341_RED);
	ILI9341_DrawPixel(70, 202, ILI9341_RED);
	ILI9341_DrawPixel(68, 202, ILI9341_RED);
	ILI9341_DrawPixel(72, 202, ILI9341_RED);
	*/
	ILI9341_DrawLineVertical (x+13 , y+2,  y+20, color);
	ILI9341_DrawLineVertical (x+11 , y+2,  y+20, color);
	ILI9341_DrawLineVertical (x+12 , y+2,  y+20,color);
	ILI9341_DrawLineVertical (x , y+10,  y+20, color);
	ILI9341_DrawLineVertical (x+1 , y+8,  y+20, color);
	ILI9341_DrawLineVertical (x+2 , y+10,  y+20, color);
	ILI9341_DrawLineVertical (x+24 , y+10,  y+20, color);
	ILI9341_DrawLineVertical (x+23 , y+8,  y+20,color);
	ILI9341_DrawLineVertical (x+22 , y+10,  y+20, color);
	ILI9341_DrawLineHorizontal(x, x+24, y+20, color);
	ILI9341_DrawLineHorizontal(x, x+24, y+19, color);
	ILI9341_DrawLineHorizontal(x, x+24, y+18, color);
}

void vida(int x, int y, int color){
	unsigned char i;
	for (i=0;i<20;i++){
		ILI9341_DrawLineVertical (x+i , y,  y+20, color);
	}

}