/*
 * Juegodelavida.c
 *
 * Created: 24/11/2021 17:12:33
 *  Author: Usuario
 */ 
#include <avr/io.h>
#include <stdlib.h>

#include "ili9341.h"
#include "general.h"

void copiarmatriz(void);
void copiarmatriz2(void);
void borrarpuntero(void);
void dibujarpuntero(void);
void cuadro(int x, int y,int color);
void puntero(unsigned char x, unsigned char y,int color);


int matriz[8][6]={{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
int matrizcopia[8][6]={{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
unsigned char xyz[2]={0,0};
unsigned char k=0;
char i,j,negativoy,negativox,vivo;

void Juegodelavida(void){
	xyz[0]=0;
	xyz[1]=0;
	
		for (i=0;i<8;i++)
		{
			for (j=0;j<6;j++)
			{
				matrizcopia[i][j]=0;
				matriz[i][j]=0;
			}
			}
	
	for (i=0;i<6;i++){	
		ILI9341_DrawLineVertical ((240/6*i),0, 319, ILI9341_WHITE);
	}
	
	ILI9341_DrawLineVertical (239,0, 319, ILI9341_WHITE);
	
	for (i=0;i<8;i++){	
		ILI9341_DrawLineHorizontal(0, 239, 320/8*i, ILI9341_WHITE);
	}
	
	ILI9341_DrawLineHorizontal(0, 239, 319, ILI9341_WHITE);
	
	puntero(xyz[0], xyz[1],ILI9341_WHITE);
	
	
		while (1)
		{
			//up
			if(PIND&(1<<7) ){
				
				borrarpuntero();
				if (xyz[1]==0)
				{
					xyz[1]=7;
				}
				
				else {
					xyz[1]-=1;
				}
					
				dibujarpuntero();
			}
			
			//down
			else if (PIND&(1<<6)){
				borrarpuntero();
				if (xyz[1]==7)
				{
					xyz[1]=0;
				}
				else {
					xyz[1]+=1;
				}
				
				dibujarpuntero();
				
			}
			//left
			else if(PINC&(1<<0) ){
				borrarpuntero();
				if (xyz[0]==0)
				{
					xyz[0]=5;
				}
				
				else {
					xyz[0]-=1;
				}
				dibujarpuntero();
			}
			//left
			else if(PINC&(1<<1)){
				borrarpuntero();
				if (xyz[0]==5)
				{
					xyz[0]=0;
				}
				
				else {
					xyz[0]+=1;
				}
				
				dibujarpuntero();
			}
			
			//A
			if(PIND&(1<<5)){
				if (matriz[xyz[1]][xyz[0]]==0)
				{
					cuadro(xyz[0], xyz[1],ILI9341_WHITE);
					matriz[xyz[1]][xyz[0]]=1;
					puntero(xyz[0], xyz[1],ILI9341_BLACK);
				}
				else if (matriz[xyz[1]][xyz[0]]==1)
				{
					cuadro(xyz[0], xyz[1],ILI9341_BLACK);
					matriz[xyz[1]][xyz[0]]=0;
					puntero(xyz[0], xyz[1],ILI9341_WHITE);
				}
			}
			
			if (PINB&(1<<0))
			{
				break;
			}
			_delay_ms(200);
		}
		//ILI9341_ClearScreen(ILI9341_BLACK);
		
		if (matriz[xyz[1]][xyz[0]]==0)
		{
			puntero(xyz[0], xyz[1],ILI9341_BLACK);
		}
		else if (matriz[xyz[1]][xyz[0]]==1)
		{
			puntero(xyz[0], xyz[1],ILI9341_WHITE);
		}


          //////////ERROR/////////////////////////////////////////
		  
		for (i=0;i<8;i++)
		{
			for (j=0;j<6;j++)
			{
				matrizcopia[i][j]=matriz[i][j];
			}
		}
		
		while(1){
			int x=0,y=0;
			while (x<6)
			{
				while (y<8)
				{
					negativoy=y-1;
					if (y==0)
					{
						negativoy=7;
					}
					else
					{
						negativoy=y-1;
					}
					
					if (x==0)
					{
						negativox=5;
					}
					else{
						negativox=x-1;
					}
					
					vivo=matriz[negativoy % 8][negativox % 6]+matriz[y % 8][negativox % 6]+matriz[(y+1) % 8][negativox % 6]+matriz[negativoy % 8][(x) % 6]+matriz[(y+1) % 8][(x) % 6]+matriz[negativoy % 8][(x+1) % 6]+matriz[y % 8][(x+1) % 6]+matriz[(y+1) % 8][(x+1) % 6];
					
					if (matriz[y][x]==0 && vivo==3)
					{
						matrizcopia[y][x]=1;
						
					}
					else if(matriz[y][x]==1 && (vivo<2 || vivo>3))
					{
						matrizcopia[y][x]=0;
						
					}
				y+=1;
				}
				y=0;
				x+=1;
			}
				
			/*
		for (i=0;i<8;i++)
		{
			for (j=0;j<6;j++)
			{
				negativoy=y-1;
				if (y==0)
				{
					negativoy=7;
				}
				else
				{
					negativoy=y-1;
				}
				
				if (x==0)
				{
					negativox=5;
				}
				else{
					negativox=x-1;
				}
				vivo=matriz[negativoy % 8][negativox % 6]+matriz[i % 8][negativox % 6]+matriz[(i+1) % 8][negativox % 6]+matriz[negativoy % 8][(j) % 6]+matriz[(i+1) % 8][(j) % 6]+matriz[negativoy % 8][(j+1) % 6]+matriz[i % 8][(j+1) % 6]+matriz[(i+1) % 8][(j+1) % 6];
				
				if (matriz[i][j]==0 && vivo==3)
				{
					matrizcopia[i][j]=1;
					
				}
				else if(matriz[i][j]==1 && (vivo<2 || vivo>3))
				{
					matrizcopia[i][j]=0;
					
				}
			}
		}
		*/
		unsigned char mom=0,dad=0;
		while (mom<6)
		{
			while (dad<8)
			{
				if (matrizcopia[dad][mom]!=matriz[dad][mom])
				{
					if (matrizcopia[dad][mom]==1)
					{
						cuadro(mom, dad,ILI9341_WHITE);
					}
					else if(matrizcopia[dad][mom]==0){
						cuadro(mom, dad,ILI9341_BLACK);
					}
				}
				dad+=1;
			}
			dad=0;
			mom+=1;
		}
		/*
		for (i=0;i<8;i++)
		{
			for (j=0;j<6;j++)
			{
				if (matrizcopia[i][j]!=matriz[i][j])
				{
					if (matrizcopia[i][j]==1)
					{
						cuadro(j, i,ILI9341_WHITE);
					}
					else if(matrizcopia[i][j]==0){
						cuadro(j, i,ILI9341_BLACK);
					}
				}
			}
		}
		*/
		for (i=0;i<8;i++)
		{
			for (j=0;j<6;j++)
			{
				matriz[i][j]=matrizcopia[i][j];
			}
		}
		

		
		_delay_ms(1000);
		 if(PIND&(1<<5)){
			 for (i=0;i<6;i++){
				 
				 ILI9341_DrawLineVertical ((240/6*i),0, 319, ILI9341_BLACK);
			 }
			 ILI9341_DrawLineVertical (239,0, 319, ILI9341_BLACK);
			 for (i=0;i<8;i++){
				 
				 ILI9341_DrawLineHorizontal(0, 239, 320/8*i, ILI9341_BLACK);
			 }
			 ILI9341_DrawLineHorizontal(0, 239, 319, ILI9341_BLACK);
			 
			 puntero(xyz[0], xyz[1],ILI9341_BLACK);
			 
			 unsigned char mom=0,dad=0;
			 while (mom<6)
			 {
				 while (dad<8)
				 {
					
						 if (matrizcopia[dad][mom]==1)
						 {
							 cuadro(mom, dad,ILI9341_BLACK);
						 }
						 
					
					 dad+=1;
				 }
				 dad=0;
				 mom+=1;
			 }
			 break;
		 }
		}
		
		Menu();
}
void copiarmatriz(void){
	for (i=0;i<8;i++)
	{
		for (j=0;j<6;j++)
		{
			matriz[i][j]=matrizcopia[i][j];
		}
	}
	
}
void copiarmatriz2(void){
	for (i=0;i<8;i++)
	{
		for (j=0;j<6;j++)
		{
			matrizcopia[i][j]=matriz[i][j];
		}
	}
	
}
void borrarpuntero(void){
	if (matriz[xyz[1]][xyz[0]]==1)
	{
		puntero(xyz[0], xyz[1],ILI9341_WHITE);
	}
	else if (matriz[xyz[1]][xyz[0]]==0)
	{
		puntero(xyz[0], xyz[1],ILI9341_BLACK);
	}
	
}
void dibujarpuntero(void){
	if (matriz[xyz[1]][xyz[0]]==0)
	{
		puntero(xyz[0], xyz[1],ILI9341_WHITE);
	}
	else if (matriz[xyz[1]][xyz[0]]==1)
	{
		puntero(xyz[0], xyz[1],ILI9341_BLACK);
	}
	
}
void cuadro(int x, int y,int color){
	
	for (i=1;i<40;i++)
	{
		if (y!=7)
		{
			if (!(i==39 && x==5))
			{
				ILI9341_DrawLineVertical ((240/6*x+i),(320/8*y+1), (320/8*y+40), color);
			}
		}
		else if (y==7)
		{
			if (!(i==39 && x==5))
			{
				ILI9341_DrawLineVertical ((240/6*x+i),(320/8*y+1), (320/8*y+39), color);
			}
		}
		
	}
	
	
}

void puntero(unsigned char x, unsigned char y,int color){
	
	for (i=18;i<23;i++)
	{
		
		ILI9341_DrawLineVertical ((240/6*x+i),320/8*y+18, 320/8*y+22, color);
	
	}
	
	
}