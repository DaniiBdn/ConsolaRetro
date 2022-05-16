/*
 * Buscaminas.c
 *
 * Created: 28/11/2021 18:16:25
 *  Author: Usuario
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ili9341.h"
#include "general.h"

void PunteroB(unsigned char x, unsigned char y, int color);
void celda(unsigned char x, unsigned char y, int color);
void descubrircelda(unsigned char x, unsigned char y,int Estado[9][9],int Bombas[9][9]);


void buscaminas(void){
	
	int Estado[9][9];
	int Bombas[9][9];
	
	unsigned char i,j,PunteroXY[2]={0,0},bombax,bombay,HayBomba,ganar,HasGanado,Ganartotal;
	
	Ganartotal=0;
	
	ILI9341_SetPosition(10,10);
	ILI9341_DrawString("BOMBAS:", ILI9341_WHITE, X3);
	ILI9341_DrawString(" 9", ILI9341_WHITE, X3);
	
	for (i=0;i<9;i++){
		for (j=0;j<9;j++)
		{
			Bombas[i][j]=0;
			Estado[i][i]=0;
			celda(i,j,ILI9341_WHITE);
		}
	}
	
	for (i=0;i<9;i++){
		for (j=0;j<9;j++)
		{
			//Estado[i][i]=0;
			//celda(i,j,ILI9341_WHITE);
		}
		
	while(1){
		
	bombax = rand () % (8-0+1) + 0;   // Este está entre M y N
	bombay = rand () % (8-0+1) + 0;
	
	if (Bombas[bombay][bombax]	==  0)
	{
		break;
	}
	}
	Estado[bombay][bombax] = 1;
	Bombas[bombay][bombax] = 9;	
	ILI9341_DrawLineVertical ((240/9*i),50, 319, ILI9341_WHITE);
	ILI9341_DrawLineHorizontal(0, 239, 50+30*i, ILI9341_WHITE);
	
	}
	ILI9341_DrawLineVertical (239, 50, 319, ILI9341_WHITE);
	ILI9341_DrawLineHorizontal(0, 239, 319, ILI9341_WHITE);
	
	for (i=0;i<9;i++){
		for (j=0;j<9;j++)
		{
			if (Bombas[i][j]==0)
			{
				if (i==0 && j==0)
				{
					HayBomba= Bombas[i][j+1] + Bombas[i+1][j] +Bombas[i+1][j+1];
					
				}
				else if(i==0 && j!=0 && j!=8)
				{
					HayBomba= Bombas[i][j-1] +Bombas[i][j+1] + Bombas[i+1][j-1]+ Bombas[i+1][j] +Bombas[i+1][j+1];
					
				}
				else if(i==0 && j==8)
				{
					HayBomba= Bombas[i][j-1] + Bombas[i+1][j-1]+ Bombas[i+1][j];
					
				}
				else if(i!=0 && i!=8 && j==0)
				{
					HayBomba= Bombas[i-1][j]+ Bombas[i-1][j+1]  +Bombas[i][j+1] + Bombas[i+1][j] +Bombas[i+1][j+1];
					
				}
				else if(i!=0 && i!=8 && j==8)
				{
					HayBomba=Bombas[i-1][j-1]+ Bombas[i-1][j]+  Bombas[i][j-1]  + Bombas[i+1][j-1]+ Bombas[i+1][j];
					
				}
				else if(i==8 && j==0)
				{
					HayBomba=Bombas[i-1][j]+ Bombas[i-1][j+1]  +Bombas[i][j+1];
					
				}
				else if(i==8 && j!=0 && j!=8)
				{
					HayBomba=Bombas[i-1][j-1]+ Bombas[i-1][j]+ Bombas[i-1][j+1] + Bombas[i][j-1] +Bombas[i][j+1];
					
				}
				else if(i==8 && j==8)
				{
					HayBomba=Bombas[i-1][j-1]+ Bombas[i-1][j]+  Bombas[i][j-1];
					
				}
				else{
					HayBomba=Bombas[i-1][j-1]+ Bombas[i-1][j]+ Bombas[i-1][j+1] + Bombas[i][j-1] +Bombas[i][j+1] + Bombas[i+1][j-1]+ Bombas[i+1][j] +Bombas[i+1][j+1];
					
				}
				Bombas[i][j]=HayBomba/9;
			}
		}
			}
	
	
	PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_WHITE);
	
	
	while (1)
	{
			if(PIND&(1<<7) ){
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_BLACK);
				if (PunteroXY[1]==0)
				{
					PunteroXY[1]=8;
				}
				else{
					PunteroXY[1]-=1;
				}
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_WHITE);
			}
			
			//down
			else if (PIND&(1<<6)){
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_BLACK);
				if (PunteroXY[1]==8)
				{
					PunteroXY[1]=0;
				}
				else{
					PunteroXY[1]+=1;
				}
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_WHITE);
				
			}
			//left
			else if(PINC&(1<<0) ){
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_BLACK);
				if (PunteroXY[0]==0)
				{
					PunteroXY[0]=8;
				}
				else{
					PunteroXY[0]-=1;
				}
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_WHITE);
			}
			//left
			else if(PINC&(1<<1)){
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_BLACK);
				if (PunteroXY[0]==8)
				{
					PunteroXY[0]=0;
				}
				else{
					PunteroXY[0]+=1;
				}
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_WHITE);
			}
			
			//A
			if(PIND&(1<<5)){
			descubrircelda(PunteroXY[0], PunteroXY[1],Estado,Bombas);
			}
			// ------------------------------------SABER SI HAS GANADO---------------------------//
			
			/*
			unsigned char loly=0,lolx=0;
			while (loly>8)
			{
				while(lolx>8){
					if (Bombas[loly][lolx]==9)
					{
						if (loly==0 && lolx==0)
						{
							HasGanado= Estado[loly][lolx+1] + Estado[loly+1][lolx] +Estado[loly+1][lolx+1];
							ganar=3;
						}
						else if(loly==0 && lolx!=0 && lolx!=8)
						{
							HasGanado= Estado[loly][lolx-1] +Estado[loly][lolx+1] + Estado[loly+1][lolx-1]+ Estado[loly+1][lolx] +Estado[loly+1][lolx+1];
							ganar=5;
						}
						else if(loly==0 && lolx==8)
						{
							HasGanado= Estado[loly][lolx-1] + Estado[loly+1][lolx-1]+ Estado[loly+1][lolx];
							ganar=3;
						}
						else if(loly!=0 && loly!=8 && lolx==0)
						{
							HasGanado= Estado[loly-1][lolx]+ Estado[loly-1][lolx+1]  +Estado[loly][lolx+1] + Estado[loly+1][lolx] +Estado[loly+1][lolx+1];
							ganar=5;
						}
						else if(loly!=0 && loly!=8 && lolx==8)
						{
							HasGanado=Estado[loly-1][lolx-1]+ Estado[loly-1][lolx]+  Estado[loly][lolx-1]  + Estado[loly+1][lolx-1]+ Estado[loly+1][lolx];
							ganar=5;
						}
						else if(loly==8 && lolx==0)
						{
							HasGanado=Estado[loly-1][lolx]+ Estado[loly-1][lolx+1]  +Estado[loly][lolx+1];
							ganar=3;
						}
						else if(loly==8 && lolx!=0 && lolx!=8)
						{
							HasGanado=Estado[loly-1][lolx-1]+ Estado[loly-1][lolx]+ Estado[loly-1][lolx+1] + Estado[loly][lolx-1] +Estado[loly][lolx+1];
							ganar=5;
						}
						else if(loly==8 && lolx==8)
						{
							HasGanado=Estado[loly-1][lolx-1]+ Estado[loly-1][lolx]+  Estado[loly][lolx-1];
							ganar=3;
						}
						else{
							HasGanado=Estado[loly-1][lolx-1]+ Estado[loly-1][lolx]+ Estado[loly-1][lolx+1] + Estado[loly][lolx-1] +Estado[loly][lolx+1] + Estado[loly+1][lolx-1]+ Estado[loly+1][lolx] +Estado[loly+1][lolx+1];
							ganar=8;
						}
						
						if (HasGanado==ganar)
						{
							Ganartotal+=1;
						}
	
					}
					Ganartotal+=Estado[loly][lolx];
					lolx+=1;
				}
				loly+=1;
			}
			*/
			
			
			for (i=0;i<9;i++){
				for (j=0;j<9;j++)
				{
					if (Bombas[i][j]==9)
					{
						if (i==0 && j==0)
						{
							HasGanado= Estado[i][j+1] + Estado[i+1][j] +Estado[i+1][j+1];
							ganar=3;
						}
						else if(i==0 && j!=0 && j!=8)
						{
							HasGanado= Estado[i][j-1] +Estado[i][j+1] + Estado[i+1][j-1]+ Estado[i+1][j] +Estado[i+1][j+1];
							ganar=5;
						}
						else if(i==0 && j==8)
						{
							HasGanado= Estado[i][j-1] + Estado[i+1][j-1]+ Estado[i+1][j];
							ganar=3;
						}
						else if(i!=0 && i!=8 && j==0)
						{
							HasGanado= Estado[i-1][j]+ Estado[i-1][j+1]  +Estado[i][j+1] + Estado[i+1][j] +Estado[i+1][j+1];
							ganar=5;
						}
						else if(i!=0 && i!=8 && j==8)
						{
							HasGanado=Estado[i-1][j-1]+ Estado[i-1][j]+  Estado[i][j-1]  + Estado[i+1][j-1]+ Estado[i+1][j];
							ganar=5;
						}
						else if(i==8 && j==0)
						{
							HasGanado=Estado[i-1][j]+ Estado[i-1][j+1]  +Estado[i][j+1];
							ganar=3;
						}
						else if(i==8 && j!=0 && j!=8)
						{
							HasGanado=Estado[i-1][j-1]+ Estado[i-1][j]+ Estado[i-1][j+1] + Estado[i][j-1] +Estado[i][j+1];
							ganar=5;
						}
						else if(i==8 && j==8)
						{
							HasGanado=Estado[i-1][j-1]+ Estado[i-1][j]+  Estado[i][j-1];
							ganar=3;
						}
						else{
							HasGanado=Estado[i-1][j-1]+ Estado[i-1][j]+ Estado[i-1][j+1] + Estado[i][j-1] +Estado[i][j+1] + Estado[i+1][j-1]+ Estado[i+1][j] +Estado[i+1][j+1];
							ganar=8;
						}
						
						if (HasGanado==ganar)
						{
							Ganartotal+=1;
						}
						
					
					}
					
					
				}
			}
			
			
			if (Ganartotal>8)
			{
				
				for (i=0;i<9;i++){
					for (j=0;j<9;j++)
					{
						if (Estado[i][j]==0)
						{
							Estado[i][j]=1;
							celda(j,i,ILI9341_BLACK);
							ILI9341_SetPosition((240/9*j)+10, 60+30*i);
							if (Bombas[i][j]!=9)
							{
								ILI9341_DrawChar (Bombas[i][j]+48, ILI9341_WHITE, X3);
							}
						}
					}
				}
				
				ILI9341_SetPosition(10,10);
				ILI9341_DrawString("BOMBAS: 9", ILI9341_BLACK, X3);
				ILI9341_SetPosition(100,10);
				ILI9341_DrawString(":D", ILI9341_WHITE, X3);
				
				_delay_ms(5000);
				
				ILI9341_SetPosition(100,10);
				ILI9341_DrawString(":D", ILI9341_BLACK, X3);
				
				PunteroB(PunteroXY[0],PunteroXY[1],ILI9341_BLACK);
				
				
				for (i=0;i<9;i++){
					for (j=0;j<9;j++)
					{
						if (Estado[j][i]==0)
						{
							celda(i,j,ILI9341_BLACK);
						}
						else{
							ILI9341_SetPosition((240/9*i)+10, 60+30*j);
							if (Bombas[j][i]==9)
							{
								
								celda(i,j,ILI9341_BLACK);
							}
							else{
								
								ILI9341_DrawChar (Bombas[j][i]+48, ILI9341_BLACK, X3);
							}
						}
					}
					ILI9341_DrawLineVertical ((240/9*i),50, 319, ILI9341_BLACK);
					ILI9341_DrawLineHorizontal(0, 239, 50+30*i, ILI9341_BLACK);
				}
				ILI9341_DrawLineVertical (239, 50, 319, ILI9341_BLACK);
				ILI9341_DrawLineHorizontal(0, 239, 319, ILI9341_BLACK);
				Menu();
			}
			else{
				Ganartotal=0;
			}
			
			_delay_ms(200);	
	}
	
}

void descubrircelda(unsigned char x, unsigned char y,int Estado[9][9],int Bombas[9][9]){
	unsigned char i,j;
	if (Estado[y][x]==0)
	{
		Estado[y][x]=1;
		celda(x,y,ILI9341_BLACK);
		ILI9341_SetPosition((240/9*x)+10, 60+30*y);
		if (Bombas[y][x]!=9)
		{
			ILI9341_DrawChar (Bombas[y][x]+48, ILI9341_WHITE, X3);
		}
	}
	
	if (Estado[y][x]==1)
	{
		if(Bombas[y][x]==9)
		{
			
			ILI9341_SetPosition(10,10);
			ILI9341_DrawString("BOMBAS: 9", ILI9341_BLACK, X3);
			ILI9341_SetPosition(10,10);
			ILI9341_DrawString("GAME OVER :(", ILI9341_WHITE, X3);
			
			for (i=0;i<9;i++){
				for (j=0;j<9;j++)
				{
					if (Bombas[j][i]==9)
					{
						Estado[j][i]==1;
						celda(i,j,ILI9341_BLACK);
						ILI9341_SetPosition((240/9*i)+10, 60+30*j);
						ILI9341_DrawString("*", ILI9341_WHITE, X3);
					}
				}
			}
			_delay_ms(5000);
			//BORRAR
			
			PunteroB(x,y,ILI9341_BLACK);
			
			ILI9341_SetPosition(10,10);
			ILI9341_DrawString("GAME OVER :(", ILI9341_BLACK, X3);
			
			for (i=0;i<9;i++){
				for (j=0;j<9;j++)
				{
					if (Estado[j][i]==0)
					{
						celda(i,j,ILI9341_BLACK);
					}
					else{
						ILI9341_SetPosition((240/9*i)+10, 60+30*j);
						if (Bombas[j][i]==9)
						{
						
						ILI9341_DrawString("*", ILI9341_BLACK, X3);
						}
						else{
						
						ILI9341_DrawChar (Bombas[j][i]+48, ILI9341_BLACK, X3);
						}
					}
				}
				ILI9341_DrawLineVertical ((240/9*i),50, 319, ILI9341_BLACK);
				ILI9341_DrawLineHorizontal(0, 239, 50+30*i, ILI9341_BLACK);
			}
			ILI9341_DrawLineVertical (239, 50, 319, ILI9341_BLACK);
			ILI9341_DrawLineHorizontal(0, 239, 319, ILI9341_BLACK);
			Menu();
		}
	}
	
}

void PunteroB(unsigned char x, unsigned char y, int color){
	unsigned char i;
	for (i=2;i<6;i++)
	{
		ILI9341_DrawLineHorizontal( 240/9*x+2, 240/9*x+5, 50+30*y+i, color);
	}
}
void celda(unsigned char x, unsigned char y, int color){
	unsigned char i;
	if (x==8 && y!=8)
	{
		for (i=4;i<27;i++)
		{
			ILI9341_DrawLineHorizontal( 240/9*x+5, 240/9*x+26, 50+30*y+i, color);
		}
	}
	else if (x!=8 && y==8)
	{
		for (i=4;i<25;i++)
		{
			ILI9341_DrawLineHorizontal( 240/9*x+5, 240/9*x+22, 50+30*y+i, color);
		}
	}
	else if (x==8 && y==8)
	{
		for (i=4;i<25;i++)
		{
			ILI9341_DrawLineHorizontal( 240/9*x+5, 240/9*x+26, 50+30*y+i, color);
		}
	}
	else{
		for (i=4;i<27;i++)
	{
		ILI9341_DrawLineHorizontal( 240/9*x+5, 240/9*x+22, 50+30*y+i, color);
	}
	}
	
}