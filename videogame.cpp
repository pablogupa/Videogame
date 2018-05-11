#include <stdio.h>
#include<iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void OcultarCursor(){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize=50;
	cci.bVisible=FALSE;
	SetConsoleCursorInfo(hcon,&cci);
}

void pintar_limites(){
	for(int i=2; i<78;i++){
		gotoxy(i,3); printf("%c", 205);
		gotoxy(i,33); printf("%c", 205);
	}
	for(int i=4; i<23;i++){
		gotoxy(77, i); printf("%c", 186);
		gotoxy(2, i); printf("%c", 186);
	}
	gotoxy(2, 3); printf("%c", 201);
	gotoxy(2, 33); printf("%c", 200);
	gotoxy(77, 3); printf("%c", 187);
	gotoxy(77, 33); printf("%c", 288);
}

class NAVE{
	int x,y, corazones, vidas;
	public:
		NAVE(int _x, int _y, int _corazones,int _vidas):x(_x),y(_y),corazones(_corazones), vidas(_vidas){}
		void pintar();
		void borrar();
		void mover();
		void pintar_corazones();
		void morir();
		int X(){return x;}
		int Y(){return y;}
		void COR(){corazones--;}
		int VID(){return vidas;}
};

void NAVE::pintar(){
 gotoxy(x,y);   printf("  %c",30);
 gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
 gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);	
}
void NAVE::borrar(){
	gotoxy(x,y); printf("        ");
	gotoxy(x,y+1); printf("        ");
	gotoxy(x,y+2); printf("        ");
}
void NAVE::mover(){
	if(kbhit()){
		char tecla=getch();
		borrar();
		if(tecla==IZQUIERDA && x>3)x--;
		if(tecla==DERECHA && x+6<77)x++;
		if(tecla==ARRIBA && y>4)y--;
		if(tecla==ABAJO && y+3<33)y++;
		pintar();
		pintar_corazones();	
	}
}
void NAVE::pintar_corazones(){
	gotoxy(50,2); printf("VIDAS %d",vidas);
	gotoxy(64,2);printf("Salud");
	gotoxy(70,2);printf("     ");
	for(int i=0;i<corazones ; i++){
	gotoxy(70+1,2);printf("%c%c%c",3,3,3);
	}
}
void NAVE::morir(){
	if(corazones==0){
		borrar();
		gotoxy(x,y); printf("   **  ");
		gotoxy(x,y+1); printf("  ****  ");
		gotoxy(x,y+2); printf("   **");
		Sleep(200);
		borrar();
		gotoxy(x,y); printf(" * ** *");
		gotoxy(x,y+1); printf("  ****  ");
		gotoxy(x,y+2); printf(" * ** *");
		Sleep(200);
		borrar();
		vidas--;
		corazones=3;
		pintar_corazones();
		pintar();
	}
}

class AST{
	int x, y;
	public:
		AST(int _x, int _y):x(_x),y(_y){}
		void pintar();
		void mover();
		void choque(struct NAVE &N);
};
void AST::pintar(){
	gotoxy(x,y); printf("%c", 184);
}
void AST::mover(){
	gotoxy(x,y); printf(" ");
	y++;
	if(y>32){
		x=rand()%71+4;
		y=4;
	}
	pintar();
}
void AST::choque(struct NAVE &N){
	if(x>=N.X() && x<=N.X()+5 && y>=N.Y() && y<=N.Y()+2){
		N.COR();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x=rand()%71+4;
		y=4;
		
	}
}





int main(){
	OcultarCursor();
	NAVE N(30,30, 3,3);
	N.pintar();
	N.pintar_corazones();
	
	AST ast1(10,4), ast2(4,8), ast3(15,10), ast4(20,5), ast5(30,10), ast6(24,8), ast7(12,5);
	bool game_over=false;
	while(!game_over){
		ast1.mover(); ast1.choque(N);
		ast2.mover(); ast2.choque(N);
		ast3.mover(); ast3.choque(N);
		ast4.mover(); ast4.choque(N);
		ast5.mover(); ast5.choque(N);
		ast6.mover(); ast6.choque(N);
		ast7.mover(); ast7.choque(N);
		if(N.VID()==0) game_over=true;
		N.morir();
		N.mover();		
		Sleep(30);
	}
	system ("cls");
	printf("Pero que has perdido eso no es guay															");
	system("pause");
	return 0;
}