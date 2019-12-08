// SAFE & ZONE


#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESPACIO 32

void menu();
void ocultarCursor();
void gotoxy();
void funcionPrincipal();
void dibujarPersonaje(int,int);
void moverPersonaje();
void borrarPersonaje(int,int);
void pintarBordes();
void pintarCorazones();
void perderCorazones();
void zonaSegura();
void pintarZona();
void borrarZona();
void opciones();
void creditos();



struct personaje
{
	int x,y;
	int vidas,puntos;
}player;

struct zonaSegura
{
	int x,y;
}zona;
clock_t reloj1=0,reloj2=0;
int Bool = 0;
int TIEMPO=5 ;
int puntos=0;

void pintarCorazones()
{
	gotoxy(46,1);
	printf("Vidas ");
	
	int i;
	for(i=0;i < player.vidas; i++)
	{
		printf("%c",3);
	}
}


void perderCorazones()
{
	gotoxy(52,1);
	printf("   ");
	player.vidas-=1;
	pintarCorazones();
}


void dibujarPersonaje(int x, int y)
{
	gotoxy(x,y);
	printf("%c", 79);
}

void borrarPersonaje(int x,int y)
{
	gotoxy(x,y);
	printf(" ");
}

void moverPersonaje()
{
	if(kbhit()){
		char tecla = getch();
	
		borrarPersonaje(player.x,player.y);
		
		if(tecla == IZQUIERDA && player.x > 3){player.x--;}
		if(tecla == DERECHA && player.x < 56){player.x++;}
		if(tecla == ARRIBA && player.y > 3){player.y--;}
		if(tecla == ABAJO && player.y < 36){player.y++;}
        
        dibujarPersonaje(player.x,player.y);
	}
}

void ocultarCursor()
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 50;
	cci.bVisible = FALSE;
	
	
	SetConsoleCursorInfo(hCon,&cci);
}

void gotoxy(int x, int y)
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos .Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
}

void pintarBordes()
{
	int i;
	for(i=2; i<57; i++){
		gotoxy(i,2);   printf("%c",205);
		gotoxy(i, 37); printf("%c",205);
	}
	
	for(i=2; i<37; i++){
		gotoxy(2,i);   printf("%c",186);
		gotoxy(57,i);   printf("%c",186);
	}
	
	gotoxy(2,2);   printf("%c",201);
	gotoxy(2,37);  printf("%c",200);
	gotoxy(57,2);  printf("%c",187);
	gotoxy(57,37); printf("%c",188);
	gotoxy(15,1);printf("Puntos: 0");
}

void zonaSegura()
{
	if(Bool == 0){
		reloj1 = clock();
		
		if(zona.x != 0){ pintarZona(); }	//pintar la zona segura
		
		gotoxy(2,1);
		printf("Tiempo: %i  ", TIEMPO-((reloj1 - reloj2) / CLOCKS_PER_SEC)); //Cronometro
				
		if( ((reloj1 - reloj2) / CLOCKS_PER_SEC >= TIEMPO) || (Bool==1) )
		{
			
			if(zona.x != 0)
			{
				if(player.x < zona.x || player.x > zona.x+2 || player.y < zona.y || player.y > zona.y+2){perderCorazones();}
				else{ puntos=puntos+1; gotoxy(15,1); printf("Puntos: %i",puntos); }
			} 		//si las coordenadas de player no estan en la zona segura quitar vida
			
			if(zona.x != 0){ borrarZona(); }	//borrar la zona
			zona.x = 4 + rand() % (54 + 1 - 4);	//Hacer dos numeros aleatorios e igualarlos a x,y 
			zona.y = 4 + rand() % (34 + 1 - 4);
		
			Bool = 1;
		}
	}
	else{
		reloj2 = clock();
		
		if(zona.x != 0){ pintarZona(); }	//pintar la zona segura
		
		gotoxy(2,1);
		printf("Tiempo: %i  ", TIEMPO-((reloj2 - reloj1) / CLOCKS_PER_SEC)); //Cronometro
		
		if((reloj2 - reloj1) / CLOCKS_PER_SEC >= TIEMPO)
		{
			
			if(zona.x != 0)
			{
				if(player.x < zona.x || player.x > zona.x+2 || player.y < zona.y || player.y > zona.y+2){perderCorazones();}
				else{ puntos=puntos+1; gotoxy(15,1); printf("Puntos: %i",puntos); }
			} 		//si las coordenadas de player no estan en la zona segura quitar vida
			
			borrarZona();	//borrar la zona
			zona.x = 4 + rand() % (54 + 1 - 4);	//Hacer dos numeros aleatorios e igualarlos a x,y 
			zona.y = 4 + rand() % (34 + 1 - 4 );
			
			Bool = 0;
		}
		
	}
	    
}

void pintarZona()
{
	gotoxy(zona.x,zona.y);		printf("%c",201);
	gotoxy(zona.x+2,zona.y);	printf("%c",187);
	gotoxy(zona.x,zona.y+2);	printf("%c",200);
	gotoxy(zona.x+2,zona.y+2);	printf("%c",188);
}

void borrarZona()
{
	gotoxy(zona.x,zona.y);		printf(" ");
	gotoxy(zona.x+2,zona.y);	printf(" ");
	gotoxy(zona.x,zona.y+2);	printf(" ");
	gotoxy(zona.x+2,zona.y+2);	printf(" ");
}

void opciones()
{
	system("cls");
	int cont=1;
	int opcion;
	char tecla;
	gotoxy(20,15);printf("Elija la dificultad");
	gotoxy(22,17); printf(">");     
	        
	while(opcion!=4){
		
		ocultarCursor();
		
		gotoxy(27,17); printf("Facil");
		gotoxy(27,19); printf("Normal");
		gotoxy(27,21); printf("Dificil");
		gotoxy(27,23); printf("Atras");
		
		tecla = getch();
			
		if(tecla==ESPACIO){
			
			opcion = cont; //segun contador ejecutar la funcion que vaya
				
			if(opcion==1){ //ejecutar juego 
				TIEMPO=7;	
				opcion=4;	
			}
			else if(opcion==2){ //mostrar menu de opciones
				TIEMPO=5;
				opcion=4;
				
			}
			else if(opcion==3){ //mostrar los creditos
					TIEMPO=3;
					opcion=4;
					
			}
			else if(opcion==4){ 
			  
			}
				
		}
		else if(tecla==ABAJO){
				
			gotoxy(22,17 + cont*2-2); printf(" ");
				
			if(cont<4){
				cont++;
			}
			else{
				cont=1;
			}
				
			gotoxy(22,17 + cont*2-2); printf(">");
				
		}
		else if(tecla==ARRIBA){
				
			gotoxy(22,17 + cont*2-2); printf(" ");
				
			if(cont>1){
				cont--;
			}
			else{
				cont=4;
			}
				
			gotoxy(22,17 + cont*2-2); printf(">");
				
		}
	}	
	
	
	
}

void creditos()
{	
	system("cls");
	ocultarCursor();
	int x=20,y=40;
	
	while(y+36>3)
	{
		if(kbhit())
		{
			return;
		}
		
		if(y+4 > 3 && y+4<40){
			gotoxy(x+1,y+4); printf("Abrahan Bracho");
		}
	
    	if(y+8 > 3 && y+8<40){
    		gotoxy(x+1,y+8); printf("Sofia Bracho");
    	}    
		
		if(y+12 > 3 && y+12<40){
    		gotoxy(x+1,y+12); printf("Diego Padron");
    	} 
    	
    	if(y+16 > 3 && y+16<40){
    		gotoxy(x+1,y+16); printf("Diego Anez");
    	} 
    	
    	if(y+20 > 3 && y+20<40){
    		gotoxy(x+1,y+20); printf("Gabriel Hernandez");
    	} 
    	
    	if(y+24 > 3 && y+24<40){
    		gotoxy(x+1,y+24); printf("Jose Larez");
    	} 
		
		if(y+28 > 3 && y+28<40){
    		gotoxy(x+1,y+28); printf("juan Rivas");
    	} 
    	
    	if(y+32 > 3 && y+32<40){
    		gotoxy(x+1,y+32); printf("Moises Rojas");
    	} 
		
		if(y+36 > 3 && y+36<40){
			gotoxy(x+1,y+36); printf("Jose Cordones");	
		}
		
		if(y+40 > 3 && y+40<40){
    		gotoxy(x-10,y+40); printf(" Pr.2:6 Porque Jehova da la sabiduria,\n   y de su boca viene el conocimiento y la inteligencia.");
    	}
    	               
		zona.x=0; zona.y=0;
    	
    	y--;
    	Sleep(100);
    	
    	system("cls");
    	
	}
	Sleep(200);
}
	
	


void funcionPrincipal()
{
	system("cls");
    player.x = 29;
	player.y = 20;
	player.vidas = 3;    	
	ocultarCursor();
	pintarBordes();
	
	while(player.vidas != 0)
	{
		
		dibujarPersonaje(player.x,player.y);
		zonaSegura();
		pintarCorazones();
		moverPersonaje(player.x,player.y);
		
	}
	
	zona.x=0; zona.y=0;
	Sleep(1000);
	system("cls");
	gotoxy(25,20);
	printf("GAME OVER");
	gotoxy(23,24);
	printf("Puntaje: %i",puntos);
	Sleep(1000);
	getch();
	system("cls");
}

void menu()
{
	system("cls");
	int cont=1;
	int opcion;
	char tecla;
	gotoxy(22,17); printf(">");
	
	while(opcion!=4){
		
		ocultarCursor();
		gotoxy(20,15);printf("                   ");
		gotoxy(24,17); printf("Nuevo  juego");
		gotoxy(26,19); printf("Opciones");
		gotoxy(26,21); printf("Creditos");
		gotoxy(27,23); printf("Cerrar");
		
		tecla = getch();
			
		if(tecla==ESPACIO){
			
			opcion = cont; //segun contador ejecutar la funcion que vaya
				
			if(opcion==1){ //ejecutar juego 
				funcionPrincipal();
				gotoxy(22,17); printf(">");
			}
			else if(opcion==2){ //mostrar menu de opciones
				opciones();
				cont=1;
				gotoxy(22,17); printf(">");
				gotoxy(22,19); printf(" ");
				gotoxy(22,21); printf(" ");
				gotoxy(22,23); printf(" ");
			}
			else if(opcion==3){ //mostrar los creditos
					creditos();
					getch();
					cont = 1;
					gotoxy(22,17); printf(">");
			}
			else if(opcion==4){ 
				
			  	return;
			  
			}
				
		}
		else if(tecla==ABAJO){
				
			gotoxy(22,17 + cont*2-2); printf(" ");
				
			if(cont<4){
				cont++;
			}
			else{
				cont=1;
			}
				
			gotoxy(22,17 + cont*2-2); printf(">");
		}
		else if(tecla==ARRIBA){
				
			gotoxy(22,17 + cont*2-2); printf(" ");
				
			if(cont>1){
				cont--;
			}
			else{
				cont=4;
			}
				
			gotoxy(22,17 + cont*2-2); printf(">");
				
		}
		
	}	
	
}


int main()
{
	menu();
	
	getch();
	
}
