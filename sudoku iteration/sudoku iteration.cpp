//---------------------
// 做来玩玩 --alex
//---------------------
#include<windows.h>
#include <stdio.h>

struct Point
{
	bool title;
	int num;
};

void color(int color);
char* GetString();
void map_print(Point* sit);

int main()
{
	Point map[81]{ { false , 0 } };

	printf(" 欢迎使用数独工具\n hanks for you use the sudoku tool\n");
	while (1) {
		while (1) {
			printf("[0]输入题目\n>>>");
			int con;
			scanf_s("%d", &con);
			if (con == 0) {
				while (1) {
					map_print(map);
					//输入样式---------------
					//(1,9)->1;(0,1)->6...
					//-----------------------
					printf("请按格式填入题目提供的数\n输入样式(x:行；y:列；z:对应的数)：(x,y)->z;\n[0]退出填写\n>>>");
					int x;
					int y;
					bool xCheck = false;
					bool yCheck = false;
					bool zCheck = false;
					bool errorCheck = false;
					char error[100] = {' '};
					int errorNum = 0;
					char* input = GetString();
					for (int i = 0; i < sizeof(input) / sizeof(char); i++) {
						//printf("\n%d\n", sizeof(input) / sizeof(char));

						//格式化识别输入并提取数据
						if (input[i] == ' ' || input[i] == '-' || input[i] == ')') {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];

							continue;
						}
						else if (input[i] == '(') {
							if (errorCheck)
								errorCheck = false;
							xCheck = true;
							continue;
						}
						else if (input[i] == ',' && !errorCheck) {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];

							yCheck = true;
							continue;
						}
						else if (input[i] == '>' && !errorCheck) {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];

							yCheck = true;
							continue;
						}
						else if (input[i] == ';' && !errorCheck) {

							//错误信息处理
							if (errorCheck)
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							else
								map_print(map);

							continue;
						}
						else {
							x = 0;
							y = 0;
							xCheck = false;
							yCheck = false;
							zCheck = false;
							errorCheck = true;
							error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							continue;
						}

						//数据提取
						if (xCheck = true) {
							if (input[i] >= '0' && input[i] <= '8') {
								xCheck = false;
								x = input[i] - 48;
								continue;
							}
							else {
								x = 0;
								y = 0;
								xCheck = false;
								errorCheck = true;
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							}
						}
						else if (yCheck = true) {
							if (input[i] >= '0' && input[i] <= '8') {
								yCheck = false;
								y = input[i] - 48;
								continue;
							}
							else {
								x = 0;
								y = 0;
								yCheck = false;
								errorCheck = true;
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							}
						}
						else if (zCheck = true) {
							if (input[i] >= '1' && input[i] <= '9') {
								zCheck = false;
								//= input[i] - 48;
								continue;
							}
							else {
								x = 0;
								y = 0;
								zCheck = false;
								errorCheck = true;
								error[errorNum >= 100 ? 99 : errorNum++] = input[i];
							}
						}
					}
					free(input);
					map_print(map);
					/*if (errorNum > 0)*/
						printf("输入中有错误信息：%s\n",error);
					printf("[0]继续输入（修改）题目\n[1]结束输入并开始计算答案（计算结束后可选择性查看）\n>>>");
					int input2;
					scanf_s("%d",&input2);
					if (input2 == 0)
						continue;
					else if (input2 == 1)
						goto end;
					
				}
			}
			else
				end:
				break;
		}

		//结果计算
		
	}
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
	while ((charCon = getchar()) == '\n');
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
		黑色		0	0	#000000
		深蓝色		1	16	#000080
		深绿色		2	32	#008000
		深青色		3	48	#008080
		深红色		4	64	#800000
		深紫色		5	80	#800080
		深黄色（棕）6	96	#808000
		灰色（默认）7	112	#C0C0C0
		深灰色		8	128	#808080
		亮蓝色		9	144	#0000FF
		亮绿色		10	160	#00FF00
		亮青色		11	176	#00FFFF
		亮红色		12	192	#FF0000
		亮紫色（粉）13	208	#FF00FF
		亮黄色  	14	224	#FFFF00
		白色		15*/

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
		for (int i = 0 ; i < 3 ; i ++) {
			if((((m + 1) / 9 ) - 1) % 3 == 0)
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
		printf("\n %d ",((m + 1) / 9) - 1);
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
