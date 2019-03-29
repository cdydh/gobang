#include<stdio.h>
#include<windows.h>
#include<conio.h>

#define player1up 'w'
#define player1down 's'
#define player1left 'a'
#define player1right 'd'
#define player2up 'o'
#define player2down 'l'
#define player2left 'i'
#define player2right 'p'
#define player1_laozi 'z'
#define player2_laozi ' '
#define replay 'q'
#define exit 'e'
int m=1;
int p[20][20];
//记录当前坐标位置是否有棋子。
char q[20][20];
//记录当前坐标位置棋子的种类，黑/白。
struct Coordinate
{
	int x;
	int y;
}position;

void draw_chessboard();
void build_coordinate(int x,int y);
void move_cursor(char press);
void laozi(char press);
void judge_win(char press);
int login_interface();
void AI(int *x,int *y);
int main()
{
	char press;
	int choice;
	int C_x,C_y;
	system("COLOR 8f");
	choice=login_interface();
	system("cls");
	draw_chessboard();
	build_coordinate(0,0);
	if(choice==1)
	{
			while(m)
			{
				press=getch();
				move_cursor(press);
				switch(press)
				{
				case player1_laozi:
					laozi(press);
					judge_win(press);
					AI(&C_x,&C_y);
					position.x=C_x;
					position.y=C_y;
					build_coordinate(2*C_x,C_y);
					laozi(player2_laozi);
					judge_win(player2_laozi);
					break;
				case replay:
					system("cls");
					draw_chessboard();
					build_coordinate(0,0);
					break;
				case exit:
					m=0;
					build_coordinate(20,20);
					break;
				default:
					break;
				}
			}
	}
	if(choice==2)
	{
		while(m)
		{
			press=getch();
			move_cursor(press);
			switch(press)
			{
			case player1_laozi:
			case player2_laozi:
				laozi(press);
				judge_win(press);
				break;
			case replay:
				system("cls");
				draw_chessboard();
				build_coordinate(0,0);
				break;
			case exit:
				m=0;
				build_coordinate(20,20);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

void draw_chessboard()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{ 
			p[i][j]=0;
			q[i][j]='o';
			printf("十"); 
		}
		printf("\n");
	}
}

void build_coordinate(int x,int y)
{
	//typedef struct _COORD
	//{
	//	short X;
	//	short Y;
	//}COORD;
	//表示一个字符在控制台屏幕上的横纵坐标。
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	//GetStdHandle(STD_OUTPUT_HANDLE)获得输出屏幕缓冲区句柄。
	//SetConsoleCursorPosition设置控制台光标坐标，横纵坐标参数由c控制。
}

void move_cursor(char press)
{
	switch(press)
	{
	case player1up:	
		if(position.y > -1)
			position.y--;
		if(position.y <0)
			position.y=19;
		break;
	case player1down:
		if(position.y < 20)
			position.y++;
		if(position.y > 19)
			position.y=0;
		break;
	case player1left:
		if(position.x > -1)
			position.x--;
		if(position.x < 0)
			position.x=19;
		break;
	case player1right:
		if(position.x < 20)
			position.x++;
		if(position.x < 0)
			position.x=19;
		break;
	case player2up:
		if(position.y > -1)
			position.y--;
		if(position.y <0)
			position.y=19;
		break;
	case player2down:
		if(position.y < 20)
			position.y++;
		if(position.y > 19)
			position.y=0;
		break;
	case player2left:
		if(position.x > -1)
			position.x--;
		if(position.x < 0)
			position.x=19;
		break;
	case player2right:
		if(position.x < 20)
			position.x++;
		if(position.x < 0)
			position.x=19;
		break;
	default:
		break;
	}
	build_coordinate(2*position.x,position.y);
}

void laozi(char press)
{
	static int flag=0;
	if(press==player1_laozi)
	{
		if(flag==0 && p[position.x][position.y]==0)
		{
			printf("●");
			build_coordinate(2*position.x,position.y);
			//使光标指向当前棋子正下方。
			q[position.x][position.y]=press;
			p[position.x][position.y]=1;
			flag=1;
		}
	}
	if(press==player2_laozi)
	{
		if(flag==1 && p[position.x][position.y]==0)
		{
			printf("○");
			build_coordinate(2*position.x,position.y);
			q[position.x][position.y]=press;
			p[position.x][position.y]=1;
			flag=0;
		}
	}
}

void judge_win(char press)
{
	int i,count1=0,count2=0,count3=0;
	struct Coordinate temp;
	for(i=0;i<4;i++)
	{
		for(count1=4;count1>=-4;count1--)
		{
			//以当前位置为原点向正方向以及负方向各判断四个步长。
			switch(i)
			{
			case 0:
				temp.x=position.x-count1;
				temp.y=position.y;
				break;
				//从左往右判断是否有五子连续在一直线上。
			case 1:
				temp.x=position.x;
				temp.y=position.y+count1;
				break;
				//从上往下判断是否有五子连续在一直线上。
			case 2:
				temp.x=position.x-count1;
				temp.y=position.y+count1;
				break;
				//从左上往右下判断是否有五子连续在一直线上。
			case 3:
				temp.x=position.x-count1;
				temp.y=position.y-count1;
				break;
				//从左下往右上判断是否有五子连续在一直线上。
			}
			if(temp.x>=0 && temp.y>=0)
			{
				if(q[temp.x][temp.y]==player1_laozi)
				{
					count2++;
					count3=0;
				}
				if(q[temp.x][temp.y]==player2_laozi)
				{
					count3++;
					count2=0;
				}
			}
		}
		if(count2 >=5)
		{
			build_coordinate(20,20);
			printf("the side of ● wins\n");
			break;
		}
		else
		{
			count2=0;
		}
		if(count3 >=5)
		{
			build_coordinate(20,20);
			printf("the side of ○ wins\n");
			break;
		}
		else
		{
			count3=0;
		}
	}
}

int login_interface()
{
	int choice;
    printf("\t╔═══════════════════════════════╗\n");

    printf("\t║                                                               ║\n");

    printf("\t║      欢迎使用五子棋对战程序     祝您玩的愉快挑战无极限       ║\n");

    printf("\t║                                                              ║\n");

    printf("\t║                 ._______________________.                    ║\n"); 

    printf("\t║                 | _____________________ |                    ║\n");

    printf("\t║                 | I                   I |                    ║\n");

    printf("\t║                 | I                   I |                    ║\n");

    printf("\t║                 | I     五 子 棋      I |                    ║\n");

    printf("\t║                 | I                   I |                    ║\n");

    printf("\t║                 | I___________________I |                    ║\n");

    printf("\t║                 !_______________________!                    ║\n");

    printf("\t║                     ._[__________]_.                         ║\n");

    printf("\t║                 .___|_______________|___.                    ║\n");

    printf("\t║                  |::: ____             |                     ║\n"); 

    printf("\t║                  |    ~~~~ [CD-ROM]    |                     ║\n");

    printf("\t║                  !_____________________!                     ║\n");

    printf("\t║                                                              ║\n");

    printf("\t║                                                              ║\n");

    printf("\t║         寒 星 溪 月 疏 星 首，花 残 二 月 并 白 莲。         ║\n");

    printf("\t║         雨 月 金 星 追 黑 玉，松 丘 新 宵 瑞 山 腥。         ║\n");

    printf("\t║         星 月 长 峡 恒 水 流，白 莲 垂 俏 云 浦 岚。         ║\n");

    printf("\t║         黑 玉 银 月 倚 明 星，斜 月 明 月 堪 称 朋。         ║\n");

    printf("\t║         二 十 六 局 先 弃 二，直 指 游 星 斜 彗 星。         ║\n");

    printf("\t║                                                              ║\n");

    printf("\t║                                                              ║\n");

    printf("\t║          1.人机对战                 2.人人对战               ║\n");

    printf("\t║                                                              ║\n");

    printf("\t╚═══════════════════════════════╝\n");
    printf("\t\t\t请输入1或2：");
	scanf("%d",&choice);
	return choice;
}

void AI(int *x,int *y)
{
	int i,j,max=0,X,Y;     
    for(i=0;i<20;i++)
	{
        for(j=0;j<20;j++)
		{
            if(q[i][j]!=player1_laozi && q[i][j]!=player2_laozi)
			{      
					X=i; 
					Y=j; 
            }
		}
	}
    *x=X; *y=Y;
}

