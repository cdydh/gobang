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
//��¼��ǰ����λ���Ƿ������ӡ�
char q[20][20];
//��¼��ǰ����λ�����ӵ����࣬��/�ס�
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
			printf("ʮ"); 
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
	//��ʾһ���ַ��ڿ���̨��Ļ�ϵĺ������ꡣ
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	//GetStdHandle(STD_OUTPUT_HANDLE)��������Ļ�����������
	//SetConsoleCursorPosition���ÿ���̨������꣬�������������c���ơ�
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
			printf("��");
			build_coordinate(2*position.x,position.y);
			//ʹ���ָ��ǰ�������·���
			q[position.x][position.y]=press;
			p[position.x][position.y]=1;
			flag=1;
		}
	}
	if(press==player2_laozi)
	{
		if(flag==1 && p[position.x][position.y]==0)
		{
			printf("��");
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
			//�Ե�ǰλ��Ϊԭ�����������Լ���������ж��ĸ�������
			switch(i)
			{
			case 0:
				temp.x=position.x-count1;
				temp.y=position.y;
				break;
				//���������ж��Ƿ�������������һֱ���ϡ�
			case 1:
				temp.x=position.x;
				temp.y=position.y+count1;
				break;
				//���������ж��Ƿ�������������һֱ���ϡ�
			case 2:
				temp.x=position.x-count1;
				temp.y=position.y+count1;
				break;
				//�������������ж��Ƿ�������������һֱ���ϡ�
			case 3:
				temp.x=position.x-count1;
				temp.y=position.y-count1;
				break;
				//�������������ж��Ƿ�������������һֱ���ϡ�
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
			printf("the side of �� wins\n");
			break;
		}
		else
		{
			count2=0;
		}
		if(count3 >=5)
		{
			build_coordinate(20,20);
			printf("the side of �� wins\n");
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
    printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");

    printf("\t�U                                                               �U\n");

    printf("\t�U      ��ӭʹ���������ս����     ף����������ս�޼���       �U\n");

    printf("\t�U                                                              �U\n");

    printf("\t�U                 ._______________________.                    �U\n"); 

    printf("\t�U                 | _____________________ |                    �U\n");

    printf("\t�U                 | I                   I |                    �U\n");

    printf("\t�U                 | I                   I |                    �U\n");

    printf("\t�U                 | I     �� �� ��      I |                    �U\n");

    printf("\t�U                 | I                   I |                    �U\n");

    printf("\t�U                 | I___________________I |                    �U\n");

    printf("\t�U                 !_______________________!                    �U\n");

    printf("\t�U                     ._[__________]_.                         �U\n");

    printf("\t�U                 .___|_______________|___.                    �U\n");

    printf("\t�U                  |::: ____             |                     �U\n"); 

    printf("\t�U                  |    ~~~~ [CD-ROM]    |                     �U\n");

    printf("\t�U                  !_____________________!                     �U\n");

    printf("\t�U                                                              �U\n");

    printf("\t�U                                                              �U\n");

    printf("\t�U         �� �� Ϫ �� �� �� �ף��� �� �� �� �� �� ����         �U\n");

    printf("\t�U         �� �� �� �� ׷ �� ���� �� �� �� �� ɽ �ȡ�         �U\n");

    printf("\t�U         �� �� �� Ͽ �� ˮ ������ �� �� �� �� �� ᰡ�         �U\n");

    printf("\t�U         �� �� �� �� �� �� �ǣ�б �� �� �� �� �� ��         �U\n");

    printf("\t�U         �� ʮ �� �� �� �� ����ֱ ָ �� �� б �� �ǡ�         �U\n");

    printf("\t�U                                                              �U\n");

    printf("\t�U                                                              �U\n");

    printf("\t�U          1.�˻���ս                 2.���˶�ս               �U\n");

    printf("\t�U                                                              �U\n");

    printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
    printf("\t\t\t������1��2��");
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

