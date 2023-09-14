#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool gameover;
const int height=20;
const int width=20;

int x,y,fruitx,fruity,score;
int tailx[100],taily[100],tailn=0;

enum eDirections { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirections dir;

void setup()
{
	gameover = false;
	dir=STOP;
	x=width/2;
	y=height/2;
	fruitx=rand()%width;
	fruity=rand()%height;
	
}

void draw()
{
	system("cls");

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
			}else if(i==fruity && j==fruitx)
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
	if(x<0 || x>width || y<0 || y>height) gameover=true;
	
	for(int i=0; i<tailn; i++)
	{
		if(x==tailx[i] && y==taily[i]) gameover=true;
	}
	
	if(x==fruitx && y==fruity)
	{
		score+=10;	
		fruitx=rand()%width;
		fruity=rand()%height;
		tailn++;
	} 
	
	if(gameover)
	{
		cout<<"GAME OVER!"<<endl;
		system("pause");
	}
	
}

int main()
{
	srand(time(0));
	setup();
	while(!gameover)
	{
		draw();
		input();
		logic();
		Sleep(300);
	}
	
	
	
	return 0;
}
