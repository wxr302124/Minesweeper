#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;
int minefield[20][35], minefield_check[20][35];
int order1,order2;
int sum_lin, sum_col, sum_mines;
int result = 0;
int emoticon = 1;
void print_menu()
{
	system("cls");
	cout << "    扫雷" << endl<<endl;
	cout << "1、新游戏" << endl;
	cout << "2、帮助" << endl;
	cout << "3、退出" << endl;
	cout << "请输入选项前的序号：";
	cin >> order1;
	if (order1 == 1)
	{
		system("cls");
		cout << "1、初级    2、中级    3、高级" << endl;
		cout << "请输入选项前的序号：";
		cin >> order2;
		switch (order2)
		{
		case 1:sum_lin = 9, sum_col = 9, sum_mines = 10; break;
		case 2:sum_lin = 16, sum_col = 16, sum_mines = 40; break;
		case 3:sum_lin = 16; sum_col = 30, sum_mines = 99; break;
		default:
			break;
		}
	}
	//if (order1==2)返回重新调用函数
	if (order1 == 2)
	{
		system("cls");
		cout << "《扫雷》是一款大众类的益智小游戏。\n游戏目标是在最短的时间内根据点击格子出现的数字找出所有非雷格子，同时避免踩雷。\n游戏区包括雷区、地雷计数器（记录剩余地雷数）。\n矩形雷区中随机布置一定数量的地雷（初级为9 * 9个方块10个雷，中级为16 * 16个方块40个雷，高级为16 * 30个方块99个雷），玩家需要找出雷区中的所有不是地雷的方块，而不许踩到地雷。\n游戏的基本操作为键盘输入，玩家每次需输入三个数字，数字与数字之间用空格隔开。第一、二个数字分别代表玩家想打开的格子的行数、列数，第三个数字代表指令。指令1相当于左键单击，用于打开安全的格子，推进游戏进度；指令2相当于右键单击，用于标记地雷，以辅助判断，或为接下来的双击做准备；指令3相当于双击，在一个数字周围的地雷标记完时，即对数字周围未打开的方块均进行一次左键单击操作。\n左键单击（指令1）：在判断出不是雷的方块上按下左键，可以打开该方块。如果方块上出现数字，则该数字表示其周围3×3区域中的地雷数（一般为8个格子，对于边块为5个格子，对于角块为3个格子。所以扫雷中最大的数字为8）；如果方块上为0，则可以递归地打开与空相邻的方块；如果不幸触雷，则游戏结束。\n右键单击（指令2）：在判断为地雷的方块上按下右键，可以标记地雷（显示为△）。重复一次操作可取消标记。\n双击（指令3）：同时按下左键和右键完成双击。当双击位置周围已标记雷数等于该位置数字时操作有效，相当于对该数字周围未打开的方块均进行一次左键单击操作。地雷未标记完全时使用双击无效。若数字周围有标错的地雷，则游戏结束，标错的地雷上会显示一个“ ×”。\n";
		system("pause");
		print_menu();
	}
	if (order1 == 3)    exit(1);
}
int count_remain()//未判断出的地雷的个数
{
	int sum = 0, remain;
	for (int i = 1; i <= sum_lin; i++)
		for (int j = 1; j <= sum_col; j++)
		{
			if (minefield_check[i][j] == -2)    sum += 1;
		}
	remain = sum_mines - sum;
	return remain;
}
void print_screen()
{
	system("cls");
	int remain = count_remain();
	cout << "    剩余雷数：" << remain << "    ";
	switch (emoticon)
	{
	case 1:cout << "(＾－＾)" << endl; break;
	case 2:cout << "<(￣︶￣)>" << endl; emoticon = 1; break;
	case 3:cout << "(ㄒoㄒ)" << endl; break;
	case 4:cout << "(＾－＾)V" << endl; break;
	default:
		break;
	}
	cout << "   ";
	for (int i = 1; i <= sum_col; i++)
	{
		cout << setw(4) << setiosflags(ios::right) << setfill(' ') << i;
	}
	cout << endl;
	for (int i = 1; i <= sum_col; i++)
	{
		if (i == 1)    cout << "   ┌─";
		else    cout << "┬─";
	}
	cout << "┐" << endl;
	for (int i = 1; i <= sum_lin; i++)
	{
		cout << setw(3) << setiosflags(ios::left) << setfill(' ') << i; 
		cout << "│";
		for (int j = 1; j <= sum_col; j++)
		{
			switch (minefield_check[i][j])
			{
			case 0:cout << "  "; break;//没有雷，安全
			case -1:cout << "●"; break;//雷
			case -2:cout << "△"; break;//小旗子
			case -3:cout << "×"; break;//判断错误
			case 9:cout << "０"; break;//已经点开过但周围没有地雷
			case 1:cout << "１"; break;//改成全角
			case 2:cout << "２"; break;
			case 3:cout << "３"; break;
			case 4:cout << "４"; break;
			case 5:cout << "５"; break;
			case 6:cout << "６"; break;
			case 7:cout << "７"; break;
			case 8:cout << "８"; break;
			default:
				break;
			}
			cout << "│";
		}
		if (i == 1)    cout << "   温馨提示：";
		if (i == 2)    cout << "   指令1：左键单击，打开安全的格子";
		if (i == 3)    cout << "   指令3：双击，对数字周围未打开的方块均进行一次左键单击操作";
		cout << endl;
		if (i == sum_lin)
		{
			for (int j = 1; j <= sum_col; j++)
			{
				if (j == 1)    cout << "   └─";
				else    cout << "┴─";
			}
			cout << "┘";
		}
		else
		{
			for (int j = 1; j <= sum_col; j++)
			{
				if (j == 1)    cout << "   ├─";
				else    cout << "┼─";
			}
			cout << "┤";
			if (i == 1)    cout << "   输入三个数字，分别代表行、列、指令，例如：1 3 2";
			if (i == 2)    cout << "   指令2：右键单击，标记地雷";
			cout << endl;
		}
	}
	
}
bool order_3(int x, int y)
{
	int flag = 0;
	if (minefield_check[x - 1][y - 1] == -2)    flag += 1;
	if (minefield_check[x][y - 1] == -2)    flag += 1;
	if (minefield_check[x + 1][y - 1] == -2)    flag += 1;
	if (minefield_check[x + 1][y] == -2)    flag += 1;
	if (minefield_check[x + 1][y + 1] == -2)    flag += 1;
	if (minefield_check[x][y + 1] == -2)    flag += 1;
	if (minefield_check[x - 1][y + 1] == -2)    flag += 1;
	if (minefield_check[x - 1][y] == -2)    flag += 1;
	if ((minefield_check[x][y] >= 1) && (minefield_check[x][y] <= 8) && (flag == minefield_check[x][y]))    return true;
	else if (minefield_check[x][y] == 9 && flag == 0)    return true;
	return false;
}
void count_surr(int x, int y)
{
	if (x >= 1 && x <= sum_lin && y >= 1 && y <= sum_col && minefield_check[x][y] == 0)
	{
		if (minefield[x - 1][y - 1] == -1)    minefield_check[x][y] += 1;
		if (minefield[x][y - 1] == -1)    minefield_check[x][y] += 1;
		if (minefield[x + 1][y - 1] == -1)    minefield_check[x][y] += 1;
		if (minefield[x + 1][y] == -1)    minefield_check[x][y] += 1;
		if (minefield[x + 1][y + 1] == -1)    minefield_check[x][y] += 1;
		if (minefield[x][y + 1] == -1)    minefield_check[x][y] += 1;
		if (minefield[x - 1][y + 1] == -1)    minefield_check[x][y] += 1;
		if (minefield[x - 1][y] == -1)    minefield_check[x][y] += 1;
		if (minefield_check[x][y] == 0)    minefield_check[x][y] = 9;
	}
}
void put_mines()//随机放置地雷
{
	int cur_mines = 0;
	srand((unsigned)time(NULL));
	while (1)
	{
		int x, y;
		x = 1 + rand() % sum_lin;
		y = 1 + rand() % sum_col;
		if (minefield[x][y] == 0)
		{
			minefield[x][y] = -1;
			cur_mines += 1;
		}
		if (cur_mines == sum_mines)    break;
	}
}
int count_result2()//没有被点开的格子数
{
	int cur = 0;
	for (int i = 1; i <= sum_lin; i++)
		for (int j = 1; j <= sum_col; j++)
		{
			if (minefield_check[i][j] == 0)    cur += 1;
		}
	return cur;
}
void result1()
{
	for (int i = 1; i <= sum_lin; i++)
		for (int j = 1; j <= sum_col; j++)
		{
			if (minefield[i][j] != -1 && minefield_check[i][j] == -2)    minefield_check[i][j] = -3;
			else if (minefield[i][j] == -1 && minefield_check[i][j] != -2)    minefield_check[i][j] = -1;
		}
	emoticon = 3;
	print_screen();
	cout << "没关系，下次再来！" << endl;
}
void result2()
{
	emoticon = 4;
	print_screen();
	cout << "恭喜！你赢了！" << endl;
}
int main()
{
	memset(minefield, 0, sizeof(minefield));
	memset(minefield_check, 0, sizeof(minefield_check));
	print_menu();//进入游戏
	put_mines();//系统随机放置地雷
	print_screen();
	while (1)
	{
		int x, y, order;
		cin >> x >> y >> order;
 		if (order == 1)
		{
			if (minefield_check[x][y] == 0)
			{
				if (minefield[x][y] == 0)    count_surr(x, y);
				if (minefield[x][y] == -1)
				{
					result = 1;
					break;
				}
			}
		}
		else if (order == 2)
		{
			emoticon = 2;
			if (minefield_check[x][y] == 0)    minefield_check[x][y] = -2;
			else if (minefield_check[x][y] == -2)    minefield_check[x][y] = 0;
		}
		else if (order == 3)
		{
			if ((minefield_check[x][y] >= 1) && (minefield_check[x][y] <= 9) && order_3(x, y))
			{
				for (int i = 0; i < 9; i++)
				{
					if (i == 4)    continue;
					int newx = x + 1 - i / 3;
					int newy = y + 1 - i % 3;
					if (newx >= 1 && newx <= sum_lin && newy >= 1 && newy <= sum_col)
					{
						if (minefield_check[newx][newy] == 0)
						{
							if (minefield[newx][newy] == -1)
							{
								result = 1;
								break;
							}
							else	count_surr(newx, newy);
						}
					}
				}
				if (result == 1)    break;
			}
		}
		if (count_result2() == 0)
		{
			result = 2;
			break;
		}
		print_screen();
	}
	if (result == 1)    result1();
	else if (result == 2)    result2();
	system("pause");
	return 0;
}