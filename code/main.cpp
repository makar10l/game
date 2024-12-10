//подключение библиотек
#include <iostream>
#include <unistd.h>
#include <string>
#include <ctime>
#include <windows.h>


//ТРОНЕШЬ ЭТИ ПЕРЕМЕННЫЕ ГЕЙ
int coordinates_x;
int coordinates_y;

std::string direction = "ПОСХАЛКО ТЫ ГЕЙ";

//ЭТУ ТРОГАТЬ МОЖНО 1000 = 1секунда
const int SPEED = 1;

char field[10][30];
//ПОСЛЕ ЭТОГО МОЖНО ТРОГАТЬ

class enemy {
public:
	int crds_x_e;
	int crds_y_e;

	void init() {
		crds_x_e = 0 + std::rand() % 10;
		crds_y_e = 1 + std::rand() % 30;
		field[crds_x_e][crds_y_e] = '#';
	}

	std::string search() {
		std::string dir_e = "";
		char symbol;
		int y = crds_y_e;
		for (int x = crds_x_e; x >= 0; x--) {
			symbol = field[x][y];
			if (symbol == '0') { dir_e = "LEFT_UP"; return dir_e; }
			y--;
		}
		y = crds_y_e;
		for (int x = crds_x_e; x >= 0; x--) {
			symbol = field[x][y];
			if (symbol == '0') { dir_e = "RIGHT_UP"; return dir_e; }
			y++;
		}
		y = crds_y_e;
		for (int x = crds_x_e; x > 9; x++) {
			symbol = field[x][y];
			if (symbol == '0') { dir_e = "RIGHT_DOWN"; return dir_e; }
			y++;
		}
		y = crds_y_e;
		for (int x = crds_x_e; x > 9; x++) {
			symbol = field[x][y];
			if (symbol == '0') { dir_e = "LEFT_DOWN"; return dir_e; }
			y--;
		}
		for (int i = crds_x_e; i >= 0; i--) {
			symbol = field[i][crds_y_e];
			if (symbol == '0') { dir_e = "UP"; return dir_e; }
		}
		for (int i = crds_x_e; i > 10; i++) {
			symbol = field[i][crds_y_e];
			if (symbol == '0') { dir_e = "DOWN"; return dir_e; }

		}
		for (int i = crds_y_e; i >= 0; i--) {
			symbol = field[crds_x_e][i];
			if (symbol == '0') { dir_e = "LEFT"; return dir_e; }
		}
		for (int i = crds_y_e; i >= 29; i++) {
			symbol = field[crds_x_e][i];
			if (symbol == '0') { dir_e = "RIGHT"; return dir_e; }
		}
		return dir_e;
	}
};


static void coordinates() {
	for (int a = 0; a < 20; a++) {
		for (int i = 0; i < 30; i++) {
			if (field[a][i] == '0') {
				coordinates_x = a;
				coordinates_y = i;
			}
		}
	}
}
static void display() {

	//system("cls");
	coordinates();
	printf(field);
}

static void clear_display() {
	for (int a = 0; a <= 9; a++) {
		for (int i = 0; i <= 29; i++) {
			field[a][i] = '1';
		}
	}

}

void attack() {
	coordinates();
	//атака вперед
	if (direction == "UP") {
		int x;
		for (int i = coordinates_x - 1; i >= 0; i--) {
			field[i][coordinates_y] = '.';
			if (i != coordinates_x - 1)
				field[i + 1][coordinates_y] = '1';
			display();
			Sleep(100);
			x = i;
		}
		field[x][coordinates_y] = '1';
	}
	//атака назад
	if (direction == "DOWN") {
		int x;
		for (int i = coordinates_x + 1; i < 10; i++) {
			field[i][coordinates_y] = '.';
			if (i != coordinates_x + 1)
				field[i - 1][coordinates_y] = '1';
			display();
			Sleep(100);
			x = i;
		}
		field[x][coordinates_y] = '1';
	}
	//атака вправо
	if (direction == "RIGHT") {
		int x;
		for (int i = coordinates_y + 1; i < 30; i++) {
			field[coordinates_x][i] = '.';
			if (i != coordinates_y + 1)
				field[coordinates_x][i - 1] = '1';
			display();
			Sleep(100);
			x = i;
		}
		field[coordinates_x][x] = '1';
	}
	//атака влево
	if (direction == "LEFT") {
		int x;
		for (int i = coordinates_y - 1; i >= 0; i--) {
			field[coordinates_x][i] = '.';
			if (i != coordinates_y - 1)
				field[coordinates_x][i + 1] = '1';
			display();
			Sleep(100);
			x = i;
		}
		field[coordinates_x][x] = '1';
	}
}

void movement() {
	char ch;
	int code;
	ch = _getch();
	code = static_cast<int>(ch);
	//атака
	if (ch == 32) {
		attack();
	}
	//движение вперед
	else if (ch == 72) {
		coordinates();

		field[coordinates_x - 1][coordinates_y] = '0';
		field[coordinates_x][coordinates_y] = '1';
		direction = "UP";

		display();
	}
	//движение назад
	else if (ch == 80) {
		coordinates();

		field[coordinates_x + 1][coordinates_y] = '0';
		field[coordinates_x][coordinates_y] = '1';
		direction = "DOWN";

		display();
	}
	//движение вправо
	else if (ch == 77) {
		coordinates();

		field[coordinates_x][coordinates_y + 1] = '0';
		field[coordinates_x][coordinates_y] = '1';
		direction = "RIGHT";

		display();
	}
	//движение влево
	else if (ch == 75) {
		coordinates();

		field[coordinates_x][coordinates_y - 1] = '0';
		field[coordinates_x][coordinates_y] = '1';
		direction = "LEFT";

		display();
	}
	else if (ch == 27) {
		clear_display();
	}
}

int main() {
	std::srand(time(0));
	clear_display();
	field[0][0] = '0';
	while (1) {
		movement();
		display();
	}


}
