//---------------------
// 数独的迭代解密程序
// 做来玩 :> --Alex
//---------------------
#include<windows.h>
#include <stdio.h>
#include<string.h>

struct Point
{
	bool title;
	int num;
};

void color(int color);
char* GetString();
void map_print(Point* sit);
void Love(int num, int seat, Point* map);
bool RightCheck(int num, int seat, Point* map);

int main()
{
	Point map[81]{ { false , 0 } };

	printf(" 欢迎使用数独工具\n hanks for you use the sudoku tool\n");
	while (1) {

		//操作框架
		while (1) {
			printf("[0]输入题目\n>>>");
			char* con = GetString();
			if (con[0] == '0') {
				while (1) {
					map_print(map);
					//输入样式---------------
					//(1,9)->1;(0,1)->6...
					//-----------------------
					printf("请按格式填入题目提供的数\n输入样式(x:行；y:列；z:对应的数)：(x,y)->z;\n[0]退出填写\n>>>");
					int x = -1;
					int y = -1;
					bool xCheck = false;
					bool yCheck = false;
					bool zCheck = false;
					bool errorCheck = false;
					char error[100] = { };
					int errorNum = 0;
					char* input = GetString();
					for (int i = 0; i < strlen(input); i++) {
						//printf("\n%d\n", sizeof(input) / sizeof(char));

						//printf("\n%d %d %d\n",errorNum,i, strlen(input));

						//数据提取
						if (xCheck) {
							if (input[i] >= '0' && input[i] <= '8') {
								xCheck = false;
								x = input[i] - 48;
								continue;
							}
							else {
								//printf("\n%c\n",input[i]);
								x = -1;
								y = -1;
								xCheck = false;
								errorCheck = true;
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
								continue;
							}
						}
						else if (yCheck) {
							if (input[i] >= '0' && input[i] <= '8') {
								yCheck = false;
								y = input[i] - 48;
								continue;
							}
							else {
								x = -1;
								y = -1;
								yCheck = false;
								errorCheck = true;
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
								continue;
							}
						}
						else if (zCheck) {
							if (input[i] >= '0' && input[i] <= '9') {
								zCheck = false;
								if (x != -1 && y != -1) {
									map[y * 9 + x].num = input[i] - 48;
									if (input[i] != 0)
										map[y * 9 + x].title = true;
									else
										map[y * 9 + x].title = false;
								}
								continue;
							}
							else {
								x = -1;
								y = -1;
								zCheck = false;
								errorCheck = true;
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
								continue;
							}
						}

						//格式化识别输入并提取数据
						if (input[i] == ' ' || input[i] == '-' || input[i] == ')') {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];

							continue;
						}
						else if (input[i] == '(') {
							if (errorCheck) {
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
								errorCheck = false;
							}
							xCheck = true;
							continue;
						}
						else if (input[i] == ',') {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							else
								yCheck = true;
							continue;
						}
						else if (input[i] == '>') {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							else
								zCheck = true;
							continue;
						}
						else if (input[i] == ';') {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];

							continue;
						}
						else {
							x = -1;
							y = -1;
							xCheck = false;
							yCheck = false;
							zCheck = false;
							errorCheck = true;
							error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							continue;
						}

					}
					free(input);
					map_print(map);
					/*if (errorNum > 0)*/
					printf("输入中有错误信息：%s\n", error);
					printf("[0]继续输入（修改）题目\n[1]结束输入并开始计算答案（计算结束后可选择性查看）\n>>>");
					char* input2 = GetString();
					if (input2[0] == '0') {
						free(input2);
						continue;
					}
					else if (input2[0] == '1') {
						free(input2);
						goto end;
					}

				}
			}
			else {
			end:
				free(con);
				break;
			}
		}

		//结果计算
		int num = 1;
		int seat = 0;
		Love(num,seat,map);
		map_print(map);
		break;
	}
}

long long int count = 0;
//❤迭代
void Love(int num, int seat, Point* map) {
	printf("\ncounting: %lld %d %d",count++,num,seat);

	if (num > 9 || num == -1)
		Love(map[seat - 1].title ? -1 : map[seat - 1].num + 1, seat - 1, map);

	if (map[seat].title)
		seat++;

	if (RightCheck(num, seat, map)) {
		if (seat >= 80) {
			map[seat].num = num;
			return;
		}
		else
			map[seat].num = num;
			map_print(map);
			Love(1, seat + 1, map);
	}
	else {
		if (num >= 9) {
			map[seat].num = 0;
			Love(map[seat - 1].title ? -1 : map[seat - 1].num + 1,seat - 1, map);
		}
		else
			Love(num + 1,seat,map);
	}
}

bool RightCheck(int num,int seat,Point* map) {

	//横向检测
	int xT = seat / 9;
	for (int i = 0 ; i < 9 ; i++) {
		if (map[(xT * 9) + i].num == num) {
			return false;
		}
	}

	//纵向检测
	int yT = seat % 9;
	for (int i = 0; i < 9 ;i++) {
		if (map[(i * 9) + yT].num == num) {
			return false;
		}
	}

	//当前小格检测--十字检测，先检测目标十字方向上是否可行并记录，再用记录数据遍历十字对应位的值
	int xP = yT;
	int yP = xT;
	int xC[2]{ (xP % 3 ? -(xP % 3) : 1) , (xP % 3 != 2 ? 2 - (xP % 3) : -1) };
	int yC[2]{ yP + (yP % 3 ? yP % 3 : -1) , yP + (yP % 3 != 2 ? (yP % 3) - 2 : 1) };
	for (int i = 0; i < 2; i++) {
		printf("\nxC[%d]:%d", i, xC[i] + seat);
		if (map[xC[i] + seat].num == num)
			return false;
	}
	for (int i = 0; i < 2; i++) {
		printf("\nyC[%d]:%d xP:%d", i, yC[i] * 9 + xP,xP);
		if (map[yC[i] * 9 + xP].num == num)
			return false;
	}
	for (int x = 0 ; x < 2 ; x++) {
		for (int y = 0 ; y < 2 ; y++) {
			if (map[yC[y] * 9 + xC[x] + xP].num == num) {
				printf("\n(%d,%d):%d", x,y, yC[y] * 9 + xC[x] + xP);
				return false;
			}
		}
	}

	return true;
}

//文本颜色
void color(int color) {
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, color);
}

char* GetString() {
	int stringLong = 1;
	char* stringCon = (char*)malloc(stringLong * sizeof(char));
	char charCon;
	//while ((charCon = getchar()) == '\n');
	while ((charCon = getchar()) != '\n') {
		stringCon[stringLong - 1] = charCon;
		if (stringLong >= 200) {
			free(stringCon);
			printf("ERROR:too long");
			return NULL;
		}
		stringCon = (char*)realloc(stringCon, ++stringLong * sizeof(char));
		if (stringCon == NULL) {
			free(stringCon);
			printf("ERROR:No RAM");
			return NULL;
		}
	}
	stringCon[stringLong - 1] = '\0';
	return stringCon;
}

//打印
void map_print(Point* seat) {
	/*颜色名称	前景色代码	背景色代码（左移4位）	RGB 近似值
		黑色		0			0					#000000
		深蓝色		1			16					#000080
		深绿色		2			32					#008000
		深青色		3			48					#008080
		深红色		4			64					#800000
		深紫色		5			80					#800080
		深黄色（棕）6			96					#808000
		灰色（默认）7			112					#C0C0C0
		深灰色		8			128					#808080
		亮蓝色		9			144					#0000FF
		亮绿色		10			160					#00FF00
		亮青色		11			176					#00FFFF
		亮红色		12			192					#FF0000
		亮紫色（粉）13			208					#FF00FF
		亮黄色  	14			224					#FFFF00
		白色		15*/

	//自己可以调颜色
	int color1 = 6;	//边框
	int color2 = 12;//题目
	int color3 = 7; //作答

	int n = 0, m = 8;
	printf("\n     0   1   2   3   4   5   6   7   8\n");
	for (int i = 0; i < 9; i++, m += 9) {
		if ((((m + 1) / 9) - 1) % 3 != 0)
			color(color1);
		printf("\n   +");
		color(7);
		for (int i = 0; i < 3; i++) {
			if ((((m + 1) / 9) - 1) % 3 == 0)
				color(color1);
			for (int i = 0; i < 2; i++)
				printf("---+");
			printf("---");
			color(7);

			if ((((m + 1) / 9) - 1) % 3 != 0)
				color(color1);
			printf("+");
			color(7);
		}
		printf("\n %d ", ((m + 1) / 9) - 1);
		color(color1);
		printf("|");
		color(7);

		for (n; n <= m; n++) {
			printf(" ");
			if (seat[n].title)
				color(color2);
			else
				color(color3);

			if (!seat[n].num)
				printf(" ");
			else
				printf("%d", seat[n].num);
			if ((n + 1) % 3 == 0)
				color(color1);
			else
				color(7);
			printf(" |");
			color(7);
		}
	}
	if ((((m + 1) / 9) - 1) % 3 != 0)
		color(color1);
	printf("\n   +");
	color(7);

	for (int i = 0; i < 3; i++) {
		color(color1);
		for (int i = 0; i < 2; i++)
			printf("---+");
		printf("---");
		color(7);
		printf("+");
	}
	printf("\n");
	color(7);
}
