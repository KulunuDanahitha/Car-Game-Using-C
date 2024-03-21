/*
Group 17

IM/2020/039 -  Kaveesha  Kumaradasa
IM/2020/057 -  Lasandi Randini
IM/2020/064 -  Kulunu Liyanage
IM/2020/075 -  Punsisi Tilani
IM/2020/112 -  Charuni Weerakoon

*/

#include <iostream>
#include <conio.h>
#include <dos.h> 
#include <windows.h>
#include <time.h>

#define  WIDTH 98
#define  HEIGHT 26
#define GAME_WIDTH 70 

using namespace std; 
 
void printWelcome();
void instructions();
void goto_position(int x, int y);
void setcursor(bool visible, DWORD size);
void drawBorder();
void drawCar();
void eraseCar();
void genEnemy(int ind);
void drawEnemy();
void eraseEnemy();
void resetEnemy(int ind);
int collision();
void gameOver();
void updateScore();
void play();

// main function
int main()

{
	int Width = 98;
	int Height = 26;
	int GameWidth = 70;
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	static CONSOLE_FONT_INFOEX  fontex;
    	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    	 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    	 GetCurrentConsoleFontEx(hOut, 0, &fontex);
    	 fontex.FontWeight = 700;
    	 fontex.dwFontSize.X = 30;
    	 fontex.dwFontSize.Y = 25;
    	 SetCurrentConsoleFontEx(hOut, 1 , &fontex);
		 printWelcome();
	     Sleep(5000); 
	 
	do{
		system("cls");
		cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl;
		
		goto_position(45,9);      cout<< "***************************"; 
		goto_position(35,10);      cout<<"       	                 ";
		goto_position(45,11);      cout<<"          Car Game         "; 
		goto_position(45,12);     cout<< "                           ";
		goto_position(45,13);     cout<< "***************************";
		goto_position(45,15);     cout<< " ---Select your option--- " ;
		goto_position(45,18);     cout<< " Start Game    -->  click 1";
		goto_position(45,19);     cout<< " Instructions  -->  clike 2";	 
		goto_position(45,20);     cout<< " Quit          -->  click 3";
		
		char op = getche();
		
		if( op=='1') 
				play();
		else if( op=='2') 
				instructions();
		else if( op=='3') 
				exit(0);
		
	}while(1);
	
	return 0;
	
}

 // Get console window handle
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] =   {' ','*','*',' ', 
					'*','*','*','*', 
					'*','*','*','*',
					' ','*','*',' ' }; 
					
int carPos = GAME_WIDTH / 2;
int score = 0; 

//This function use to display the welcome text
void printWelcome() {
cout << endl;cout << endl;
cout << endl;cout << endl;cout << endl;

 system("Color E4");


cout <<  "                8888        888 8888888888   8888            88888888      8888888      888       888 8888888888\n";
cout <<  "                 88          8   88      8    88            88       8    88     88      88       88   88      8\n";
cout <<  "                 88          8   88           88           88       88   88       88     888     888   88\n";
cout <<  "                 88    88    8   88           88           88       88   88       88     888     888   88\n";
cout <<  "                  88   88   8    88  8        88           88            88       88     888     888   88  8\n";
cout <<  "                  88   88   8    88888        88           88            88       88     8 8    8 88   88888\n";
cout <<  "                  88  8888  8    88  8        88           88            88       88     8 8    8 88   88  8\n";
cout <<  "                  88  8888 8     88           88           88            88       88     8 88   8 88   88\n";
cout <<  "                   8888  888     88           88           88            88       88     8 888888 88   88\n";
cout <<  "                   8888  888     88           88           88            88       88     8  88888 88   88\n";
cout <<  "                   88    888     88           88           88            88       88     8   888  88   88\n";
cout <<  "                   88    88      88        8  88         8  88       8    88     88      8   888  88   88         8\n";
cout <<  "                   88    88     888888888888 8888888888888   888888888     8888888      888  888 8888  888888888888\n";

cout << endl;cout << endl;cout << endl;

cout << "                                     88888  88 888   8888    8888    8888    8888   88   88    8\n"; 
cout << "                                    88   8  888     8   88  88   8  88   8  8   88 888   88   88\n";
cout << "                                    88      88     88   88   88      88    88   88  88   88  88888\n";
cout << "                                    88   8  88     88   8    8888    8888  88   8   88   88   88\n";      
cout << "                                    88  8   88     88  8        88      88 88  8    88  888 8 88  8  \n";
cout << "                                     888    88      888     88888   88888   888      888  88  8888 \n";



}


//This function give instruction to the player
void instructions(){
	system("cls");
	cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl;
	cout<<"\t\t\t\t\t\t     Instructions\n\n";
	cout<<"\n\t\t\t\t\t-----------------------------------------\n";
	cout<<"\n\t\t\t\t\t Avoid Cars by moving left or right. ";
	cout<<"\n\n\t\t\t\t\t Press 'a' or 'Left arrow key' to move left";
	cout<<"\n\t\t\t\t\t Press 'd' or 'Right arrow key' to move right";
	cout<<"\n\t\t\t\t\t Press 'escape' to exit";
	cout<<"\n\n\t\t\t\t\t Press any key to go back to menu";
	getch();
}

// Move window to required position
void goto_position(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

// set cursor to control the cursor
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 0;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

// draw the game background
void drawBorder(){  
	for(int i=0; i< HEIGHT; i++){
		for(int j=0; j<17; j++){
			goto_position(0+j,i); cout<<"*";
			goto_position( GAME_WIDTH -j , i); cout<<"*";
		}
	} 
}

// draw the car
void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			goto_position(j+carPos, i+22); cout<<car[i][j];
		}
	}
}

// This function uses to delete the position after the car moves.
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			goto_position(j+carPos, i+22); cout<<" ";
		}
	}
}

//This function use to generates enemies randomly. For that, we use the cstdlib library.
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}

//this function use to draw enemy
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		
		goto_position(enemyX[ind], enemyY[ind]);   cout<<" ** ";  
		goto_position(enemyX[ind], enemyY[ind]+1); cout<<"*--*"; 
		goto_position(enemyX[ind], enemyY[ind]+2); cout<<"*--*"; 
		goto_position(enemyX[ind], enemyY[ind]+3); cout<<" ** ";  
	} 
}

//this function use to erase the when enemy reach to the end.
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		
		goto_position(enemyX[ind], enemyY[ind]); cout<<"    ";  
		goto_position(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		goto_position(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		goto_position(enemyX[ind], enemyY[ind]+3); cout<<"    ";
		
		} 
}

//This function is used When the enemy is erasing and it generates again from the top.
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

//This function uses to identify the collision between cars and enemies.
int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 

//This function uses to display the game over the interface.
void gameOver(){

	system("cls");
	cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl;
	cout<<endl;
	system("Color E4");
	cout<<"    888888888       888      8888888   88888  8888888888888        8888888   8888888       888 8888888888888  88888888888888 \n";
	cout<<"   8888    88      88888      8888888  8888    88888     88       888   888   88888       88    88888     88   8888888  88888\n";
	cout<<"  8888      8      88888      8 88888 88888    88888      8      8888   8888  88888       88    88888      8   88888       88 \n";
	cout<<" 88888             888888     8 888888 8888    88888  8   8     88888   88888  88888      88    88888  8   8   88888       88 \n";
	cout<<" 88888 8888888    8 88888     8 888888 8888    88888  8         88888   88888  88888      88    88888  8       88888    888   \n";
	cout<<" 88888  88888    8  88888     8  88888 8888    88888888         88888   88888   88888    8      88888888       8888888888     \n";
	cout<<" 88888  88888     88888888    8  888   8888    88888  8         88888   88888   88888    8      88888  8       888888   8888  \n";
	cout<<" 88888  88888    8   88888    8  888   8888    88888  8   8     88888   88888    88888   8      88888  8   8   88888      88 \n";
    cout<<"  8888  88888   8    888888   8  888   8888    88888      8      8888   8888     88888 88       88888      8   88888       88 \n";
    cout<<"   888 88888   88     88888   8   8    8888    88888     88       888   888       8888888       88888     88   88888       88\n";
    cout<<"    888888    8888   8888888 888  8   888888  8888888888888        8888888         88888       8888888888888  8888888      888\n";
	cout<<endl;cout<<endl;
	cout<<"                                                       YOUR SCORE = "<< score ;
	cout<< endl << endl;	
	cout<<"\t\t\t\t             Press any key to go back to menu.";
	getch();
}

//This function uses to show the final score.
void updateScore(){
	goto_position(GAME_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}


//This function gives the method of the game.
void play(){
	carPos = -1 + GAME_WIDTH / 2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	  
	system("cls"); 
	cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl; cout << endl;
	cout << endl; cout << endl;
	drawBorder(); 
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	
	goto_position(GAME_WIDTH + 7, 2);cout<<"Car Game";
	goto_position(GAME_WIDTH + 6, 4);cout<<"----------";
	goto_position(GAME_WIDTH + 6, 6);cout<<"----------";
	goto_position(GAME_WIDTH + 7, 12);cout<<"Control ";
	goto_position(GAME_WIDTH + 7, 13);cout<<"-------- ";
	goto_position(GAME_WIDTH + 2, 14);cout<<" A or left Key - Left ";
	goto_position(GAME_WIDTH + 2, 15);cout<<"D or right Key - Right "; 
	
	goto_position(18, 5);cout<<"Press any key to start";
	getch();
	goto_position(18, 5);cout<<"                      ";
	
	
	
	while(1){
		if(kbhit()){
			char ch = getch();
			// by entering a or A or left key can move the car to the left.
			if( ch=='a' || ch=='A' || ch==75){
				if( carPos > 18 )
					carPos -= 4;
			}
			// by entering d or D or right key can move the car to the right.
			if( ch=='d' || ch=='D'|| ch==77 ){
				if( carPos < 50 )
					carPos += 4;
			} 
			// by clicking Esc player can exit.
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1);
		
		
		// method identify collisions 
		if( collision() == 1  ){
			gameOver();
			return;
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;    
		 
		if( enemyY[0] > HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}



