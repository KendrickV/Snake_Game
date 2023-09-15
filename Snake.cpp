#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool gameover,godmode;
const int height=20;
const int width=20;
char color[10];

int x,y,fruitx,fruity,score,p;
int tailx[100],taily[100],tailn,level,L;

enum Directions { STOP = 0, UP, DOWN, LEFT, RIGHT };
Directions dir;
	
void setup()
{	
	gameover = false;
	dir=STOP;
	x=width/2;
	y=height/2;
	fruitx=rand() % (width-2) + 1;
	fruity=rand()% (height-2)+1;
	tailn=0;
	L=1;
	level=100;
	godmode = false;
	strcpy(color,"color 0F");
}

void Bcolor()
{
	system("cls");
		cout<<"\n\t\t 1 - Black";
		cout<<"\n\t\t 2 - Green(Retro)";
		cout<<"\n\t\t Your choice: "; cin>>p;
		
	switch(p)
	{
		case 1 : strcpy(color,"color 0F"); break;
		case 2 : strcpy(color,"color 20"); break;
		default : break;
	}
}

void difficulty()
{
	system("cls");
	cout<<"\n\n\t\t\tSNAKE";
	cout<<"\n\t\t 1.Beginner";
	cout<<"\n\t\t 2.Intermediate";
	cout<<"\n\t\t 3.Expert";
	cout<<"\n\t\t 4.Godmode";
	cout<<"\n\t\t Choose the level of difficulty: "; cin>>L;
	switch(L)
	{
		case 1 : level=300; break;
		case 2 : level=200; break;
		case 3 : level=100; break;
		case 4 : godmode=true; level=100; break;
		default : break;
	}
}

void info()
{
	system("cls");
		cout<<"\n\t\t W - UP";
		cout<<"\n\t\t S - DOWN";
		cout<<"\n\t\t A - LEFT";
		cout<<"\n\t\t D - RIGHT";
		cout<<"\n\t\t X - Exit to menu\n";
	system("pause");
}

void startmenu()
{
	setup();	
	bool z=true;
		do
		{	
			system("cls");
			cout<<"\n\n\t\t\tSNAKE";
			cout<<"\n\t\t 1.Start game";
			cout<<"\n\t\t 2.Level of difficulty: Current level - L: "<<L;
			cout<<"\n\t\t 3.Background Color";
			cout<<"\n\t\t 4.Instructions";
			cout<<"\n\t\t ESC.Exit\n";
			
			switch(_getch())
			{
				case 49 : z=false; break;
				case 50 : difficulty(); break;
				case 51 : Bcolor(); break;
				case 52 : info(); break;
				case 27 : gameover=true,z=false; break;
				default : z=false; break;
			}
		
		}while(z);
}


void draw()
{
	system("cls");
	
	system(color);

	for(int i=0; i<width; i++)
	{
		cout<<"#";
	}cout<<endl;
	
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(j==0 || j==width-1) cout<<"#";
			else if(i==y && j==x)
			{
				cout<<"O";
			}
			else if(i==fruity && j==fruitx)
			{
				cout<<"F";
			}
			else
			{
				bool print=false;
				
				for(int k=0; k<tailn; k++)
				{
					if(i==taily[k] && j==tailx[k])
					{
						cout<<"o";
						print=true;
					}
					
				}if(print==false){cout<<" ";}
			}
		}
		cout<<endl;
	}
	
	for(int i=0; i<width; i++)
	{
		cout<<"#";
	}cout<<endl;
	
	cout<<"SCORE:"<<score<<endl;
}

void input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'w': dir=UP; break;
			case 'a': dir=LEFT; break;
			case 's': dir=DOWN; break;
			case 'd': dir=RIGHT; break;
			case 'x': startmenu(); break;
			default: break;
		}
	}
}

void logic()
{
	int prevx=tailx[0];
	int prevy=taily[0];
	tailx[0]=x;
	taily[0]=y;
	int prev2x,prev2y;
	
	for(int i=1; i<tailn; i++)
	{
		prev2x=tailx[i];
		prev2y=taily[i];
		tailx[i]=prevx;
		taily[i]=prevy;
		prevx=prev2x;
		prevy=prev2y;
	}
	
	switch(dir)
	{
		case UP: y--; break;
		case DOWN: y++; break;
		case LEFT: x--; break;
		case RIGHT: x++; break;
		default : break;
	}
	
	if(godmode)
	{
		if(x>=width)x=0;
		else if(x<0) x=width-1;
		if(y>=height)y=0;
		else if(y<0) y=height-1;
	}
	else 
	{
		if(x<1 || x>=width-1 || y<0 || y>height-1) gameover=true;
	}
	
	for(int i=0; i<tailn; i++)
	{
		if(x==tailx[i] && y==taily[i]) gameover=true;
	}
	
	if(x==fruitx && y==fruity)
	{
		score+=10;	
		fruitx=rand() % (width-2) + 1;
		fruity=rand()% (height-2)+1;
		tailn++;
		if(level!=0)level-=5;
		Beep(300,50);
	} 
	
	if(gameover)
	{
		for(int i=5; i>1; i--)Beep(i*100, 100);
		cout<<"GAME OVER!"<<endl;
		system("pause");
	}
}

int main()
{
	srand(time(0));
	
	startmenu();
	while(!gameover)
	{	
		draw();
		input();
		logic();
		Sleep(level);
		
		if(gameover)startmenu();
	}
	
	
	return 0;
}
