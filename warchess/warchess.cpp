#include <iostream>
#include "graphics.h"
#include <string>
#include <random>
using namespace std;

#define MAXCITY 80
#define MAXWATER 10
#define WATERINCREASE 3

string city_name[72] = { "Liverpool" , "Dunkerque", "Manchester", "Cambridge", "Hamburg", "Lille", "Birmingham", "Oxford", "Munich","Cherbourg",
	"Nottingham","Leeds","Frankfurt","Rouen","Newcastle", "Loughborough","Dusseldorf","Nancy","Plymouth","Glasgow","Bremen","Brest",
	"Edinburgh","Aberdeen","Nuremberg","Strasbourg","Bournemouth","Cardiff","Orleans","Leicester","Nantes","Sheffield","Lyon",
	"Marseille","Grenoble","Toulouse","Bordeaux","Nice","Valence","Krakow","Hague","SanPaulo","Sydney","Melbourne","Rotterdam","Manaus",
	"DenHelder","Eindhoven","Malaga","Toronto","Basilicata","Montreal","Calabria","Barcelona","Vancouver","Campania","Sevilla","Quebec",
	"Sardegna","Vitoria","Calgary","Sicilia","Veneto","Winnipeg","Milan","Firenze","Torino","Napoli","Genova","Venezia","Alghero","Bergen" };
string capital_name[14] = { "Paris","London","Berlin","Warsaw","Brasilia","Canberra","Amsterdam","Ottawa","Roma","Singapore","Manila","Athen",
	"Brussel","Oslo" };
int city_name_occupy[72] = { 0 };
int capital_name_occupy[14] = { 0 };
color_t color_water = EGERGB(187, 255, 255);

class Cell {
public:
	int id;//0~219
	int party;//0~4，0为无主
	int x;
	int y;
	int i;
	int j;
	int water;
	int city;
	int harbor;
	int capital;
	int neighbor[6] = { -1 };

	Cell() {
		id = 0;
		x = 0;
		y = 0;
		i = 0;
		j = 0;
		party = 0;
		water = 0;
		city = 0;
		harbor = 0;
		capital = 0;
	}

	void draw() {
		int polypoint1[14] = { i - 20, j, i - 10,j - 17,i + 10,j - 17,i + 20,j,i + 10,j + 17, i - 10,j + 17, i - 20, j };
		int polypoint2[12] = { i - 20, j, i - 10,j - 17,i + 10,j - 17,i + 20,j,i + 10,j + 17, i - 10,j + 17 };
		setcolor(BLACK);
		setfillcolor(WHITE);
		drawpoly(7, polypoint1);
		fillpoly(6, polypoint2);
		//xyprintf(i - 10, j - 10, "%d", id);
		if (water == 1) {
			setcolor(BLACK);
			setfillcolor(color_water);
			fillpoly(6, polypoint2);
		}
		else if (city == 1) {
			//setcolor(BLUE);
			setfillcolor(BLACK);
			fillellipse(i + 4, j - 11, 4, 4);
		}
		else if (capital == 1) {
			if (party == 1) {
				setcolor(RED);
				setfillcolor(RED);
			}
			else if (party == 2) {
				setcolor(MAGENTA);
				setfillcolor(MAGENTA);
			}
			else if (party == 3) {
				setcolor(BLUE);
				setfillcolor(BLUE);
			}
			else if (party == 4) {
				setcolor(GREEN);
				setfillcolor(GREEN);
			}
			int pt[]{ i + 4,j - 11,
				i + 4 + 3,j - 11,
				i + 4 + 4,j - 11 - 3,
				i + 4 + 5,j - 11,
				i + 4 + 8,j - 11,
				i + 4 + 5,j - 11 + 2,
				i + 4 + 7,j - 11 + 5,
				i + 4 + 4,j - 11 + 4,
				i + 4 + 2,j - 11 + 5,
				i + 4 + 2,j - 11 + 2,
				i + 4,j - 11 };
			fillpoly(10, pt);
		}
		else if (harbor == 1) {
			setcolor(BLACK);
			setfillcolor(WHITE);
			line(i + 10, j - 11, i + 10, j - 5);
			line(i + 9, j - 10, i + 11, j - 10);
			arc(i + 10, j - 8, 90, 270, 3);
		}
		setcolor(BLACK);
		setfillcolor(WHITE);
	}

	void produce() {
		if (party != 0) {
			if (city == 1) {
				int num = random(6);
				if (cell_occupy[id] == 0) {

					Troop(party, num + 10, id);
				}
				else {
					troop[id].number = num + 10;
				}
			}
			else if (capital == 1) {
				int num = random(11);
				if (cell_occupy[id] == 0) {

					Troop(party, num + 15, id);
				}
				else {
					troop[id].number = num + 15;
				}
			}
		}
	}
};

class Troop {
public:
	int party;
	int number;
	int position;

	Troop(){
		party = 0;
		number = 0;
		position = -1;
	}

	Troop(int party_, int number_, int position_) {
		party = party_;
		number = number_;
		position = position_;
	}

	void move(int i1,int i2) {
		if (cell_occupy[i2] = 0) {
			cell_occupy[i2] = 1;
			cell_occupy[i1] = 0;
			troop
		}
	}

	void draw() {

	}
};

Cell cell[220] = {};
bool cell_occupy[220] = {};
Troop troop[220] = {};

int random(int x) {//产生0~x-1之间的x个随机整数
	std::random_device rd;
	std::mt19937 mt(rd());
	int y = mt() % x;
	return y;
}

void initialize() {
	initgraph(650, 412);
	setcolor(BLACK);
	setbkcolor(WHITE);
	setfillcolor(WHITE);
	int p = 0;
	for (int i = 0; i < 220; i++) {
		cell[i].id = i;
		cell[i].x = i / 11;
		cell[i].y = i % 11;
		if (cell[i].x % 2 == 0) {//偶
			cell[i].i = 20 + cell[i].x * 32;
			cell[i].j = 17 + cell[i].y * 36;
		}
		if (cell[i].x % 2 == 1) {//奇
			cell[i].i = 20 + cell[i].x * 32;
			cell[i].j = 34 + cell[i].y * 36;
		}

		//计算neighbor
		if (cell[i].x % 2 == 0) {//偶
			cell[i].neighbor[0] = i - 12;//左上
			cell[i].neighbor[1] = i - 11;//左下
			cell[i].neighbor[2] = i - 1;//上
			cell[i].neighbor[3] = i + 1;//下
			cell[i].neighbor[4] = i + 10;//右上
			cell[i].neighbor[5] = i + 11;//右下
		}
		if (cell[i].x % 2 == 1) {//奇
			cell[i].neighbor[0] = i - 11;//左上
			cell[i].neighbor[1] = i - 10;//左下
			cell[i].neighbor[2] = i - 1;//上
			cell[i].neighbor[3] = i + 1;//下
			cell[i].neighbor[4] = i + 11;//右上
			cell[i].neighbor[5] = i + 12;//右下
		}
		if (cell[i].x % 2 == 0) {//偶
			if ((cell[i].neighbor[0] / 11) != (cell[i].x - 1) || (cell[i].neighbor[0] % 11) != cell[i].y - 1) {
				cell[i].neighbor[0] = -1;
			}
			if ((cell[i].neighbor[1] / 11) != (cell[i].x - 1) || (cell[i].neighbor[1] % 11) != cell[i].y) {
				cell[i].neighbor[1] = -1;
			}
			if ((cell[i].neighbor[2] / 11) != cell[i].x || (cell[i].neighbor[2] % 11) != cell[i].y - 1) {
				cell[i].neighbor[2] = -1;
			}
			if ((cell[i].neighbor[3] / 11) != cell[i].x || (cell[i].neighbor[3] % 11) != cell[i].y + 1) {
				cell[i].neighbor[3] = -1;
			}
			if ((cell[i].neighbor[4] / 11) != (cell[i].x + 1) || (cell[i].neighbor[4] % 11) != cell[i].y - 1) {
				cell[i].neighbor[4] = -1;
			}
			if ((cell[i].neighbor[5] / 11) != (cell[i].x + 1) || (cell[i].neighbor[5] % 11) != cell[i].y) {
				cell[i].neighbor[5] = -1;
			}
		}
		if (cell[i].x % 2 == 1) {//奇
			if ((cell[i].neighbor[0] / 11) != (cell[i].x - 1) || (cell[i].neighbor[0] % 11) != cell[i].y) {
				cell[i].neighbor[0] = -1;
			}
			if ((cell[i].neighbor[1] / 11) != (cell[i].x - 1) || (cell[i].neighbor[1] % 11) != cell[i].y + 1) {
				cell[i].neighbor[1] = -1;
			}
			if ((cell[i].neighbor[2] / 11) != cell[i].x || (cell[i].neighbor[2] % 11) != cell[i].y - 1) {
				cell[i].neighbor[2] = -1;
			}
			if ((cell[i].neighbor[3] / 11) != cell[i].x || (cell[i].neighbor[3] % 11) != cell[i].y + 1) {
				cell[i].neighbor[3] = -1;
			}
			if ((cell[i].neighbor[4] / 11) != (cell[i].x + 1) || (cell[i].neighbor[4] % 11) != cell[i].y) {
				cell[i].neighbor[4] = -1;
			}
			if ((cell[i].neighbor[5] / 11) != (cell[i].x + 1) || (cell[i].neighbor[5] % 11) != cell[i].y + 1) {
				cell[i].neighbor[5] = -1;
			}
		}
		for (int j = 0; j < 6; j++) {
			if (cell[i].neighbor[j] < 0 || cell[i].neighbor[j]>219) {
				cell[i].neighbor[j] = -1;
			}
		}
	}
	//构建地形
	cell[12].capital = 1;
	cell[12].party = 1;
	cell[20].capital = 1;
	cell[20].party = 2;
	cell[199].capital = 1;
	cell[199].party = 3;
	cell[207].capital = 1;
	cell[207].party = 4;

	//水尽可能聚在一起，城市尽可能分散
	int water_increase;
	int max_city;
	int max_water;
	int water_neighbor;
	int city_neighbor;
	for (int j = 0; j < 11; j += 2) {
		for (int k = 0; k < 220; k += 22) {
			if (j + k != 2 && j + k != 10 && j + k != 24 && j + k != 32 && j + k != 198 && j + k != 200 && j + k != 206 && j + k != 208) {
				water_increase = WATERINCREASE;
				max_city = MAXCITY;
				max_water = MAXWATER;
				water_neighbor = 0;
				city_neighbor = 0;
				p = random(100);
				for (int l = 0; l < 6; l++) {
					int temp = cell[j + k].neighbor[l];
					if (temp != -1) {
						if (cell[temp].water == 1) {
							water_neighbor++;
						}
						if (cell[temp].city == 1) {
							city_neighbor++;
						}
					}
				}
				if (water_neighbor > 2) {
					cell[j + k].water = 1;
				}
				else if (0 <= p && p < max_water) {
					cell[j + k].water = 1;
				}
				else if (max_city <= p && p < 100) {
					if (water_neighbor > 0) {
						cell[j + k].harbor = 1;
					}
					else if (city_neighbor == 0) {
						cell[j + k].city = 1;
					}
				}
			}
		}
	}
	for (int j = 1; j < 11; j += 2) {
		for (int k = 0; k < 220; k += 22) {
			if (j + k != 1 && j + k != 9 && j + k != 23 && j + k != 31 && j + k != 199 && j + k != 207) {
				water_increase = WATERINCREASE;
				max_city = MAXCITY;
				max_water = MAXWATER;
				water_neighbor = 0;
				city_neighbor = 0;
				p = random(100);
				for (int l = 0; l < 6; l++) {
					int temp = cell[j + k].neighbor[l];
					if (temp != -1) {
						if (cell[temp].water == 1) {
							water_neighbor++;
						}
						if (cell[temp].city == 1) {
							city_neighbor++;
						}
					}
				}
				if (water_neighbor > 2) {
					cell[j + k].water = 1;
				}
				else if (0 <= p && p < max_water) {
					cell[j + k].water = 1;
				}
				else if (max_city <= p && p < 100) {
					if (water_neighbor > 0) {
						cell[j + k].harbor = 1;
					}
					else if (city_neighbor == 0) {
						cell[j + k].city = 1;
					}
				}
			}
		}
	}
	for (int j = 0; j < 11; j += 2) {
		for (int k = 11; k < 220; k += 22) {
			if (j + k != 11 && j + k != 13 && j + k != 19 && j + k != 21 && j + k != 187 && j + k != 195 && j + k != 209 && j + k != 217) {
				water_increase = WATERINCREASE;
				max_city = MAXCITY;
				max_water = MAXWATER;
				water_neighbor = 0;
				city_neighbor = 0;
				p = random(100);
				for (int l = 0; l < 6; l++) {
					int temp = cell[j + k].neighbor[l];
					if (temp != -1) {
						if (cell[temp].water == 1) {
							water_neighbor++;
						}
						if (cell[temp].city == 1) {
							city_neighbor++;
						}
					}
				}
				if (water_neighbor > 2) {
					cell[j + k].water = 1;
				}
				else if (0 <= p && p < max_water) {
					cell[j + k].water = 1;
				}
				else if (max_city <= p && p < 100) {
					if (water_neighbor > 0) {
						cell[j + k].harbor = 1;
					}
					else if (city_neighbor == 0) {
						cell[j + k].city = 1;
					}
				}
			}
		}
	}
	for (int j = 1; j < 11; j += 2) {
		for (int k = 11; k < 220; k += 22) {
			if (j + k != 12 && j + k != 20 && j + k != 188 && j + k != 196 && j + k != 210 && j + k != 218) {
				water_increase = WATERINCREASE;
				max_city = MAXCITY;
				max_water = MAXWATER;
				water_neighbor = 0;
				city_neighbor = 0;
				p = random(100);
				for (int l = 0; l < 6; l++) {
					int temp = cell[j + k].neighbor[l];
					if (temp != -1) {
						if (cell[temp].water == 1) {
							water_neighbor++;
						}
						if (cell[temp].city == 1) {
							city_neighbor++;
						}
					}
				}
				if (water_neighbor > 2) {
					cell[j + k].water = 1;
				}
				else if (0 <= p && p < max_water) {
					cell[j + k].water = 1;
				}
				else if (max_city <= p && p < 100) {
					if (water_neighbor > 0) {
						cell[j + k].harbor = 1;
					}
					else if (city_neighbor == 0) {
						cell[j + k].city = 1;
					}
				}
			}
		}
	}


	for (int i = 0; i < 220; i++) {
		cell[i].draw();
	}
}

int main() {
	initialize();

	while (1) {

	}
}
