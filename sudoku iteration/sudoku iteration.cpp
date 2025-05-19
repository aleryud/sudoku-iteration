#include <stdio.h>
#include<windows.h>

struct Point
{
	bool title;
	int num;
};

void color(int color);
void map_print(Point* sit);

int main()
{
	Point map[81]{ { true , 1 } };
	map_print(map);
}

//文本颜色
void color(int color) {
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, color);
}

void map_print(Point* seat) {
	int n = 0, m = 8;
	for (int i = 0; i <= 8; i++, m += 9) {
		printf("\n+---+---+---+---+---+---+---+---+---+\n|");
		for (n; n <= m; n++) {
			printf(" ");
			if (seat[n].title)
				color(4);
			else
				color(7);

			if (!seat[n].num)
				printf(" ");
			else
				printf("%d",seat[n].num);

			color(7);
			printf(" |");
		}
	}printf("\n+---+---+---+---+---+---+---+---+---+\n");

}

