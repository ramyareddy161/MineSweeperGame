#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<stddef.h>
#include<stdlib.h>

void print_grid(char **game_board, int size_of_board){
	int i, j;
	system("cls");
	printf("                            MineSweeper  Game\n");
	printf("                            ^^^^^^^^^^^^^^^^^\n");
	printf("           ");
	for (i = 1; i <= size_of_board; i++){
		printf("   %d  ", i);
	}	
	printf("\n          ====================================================\n");
	printf("          ----------------------------------------------------\n");
	for (i = 0; i < size_of_board; i++){
		printf("       %d  ||",i+1);
		for (j = 0; j < size_of_board; j++){		
			printf("  %c  |", game_board[i][j]);
		}
		printf("|\n");
		printf("          ----------------------------------------------------\n");
	}
	printf("          =====================================================\n");
}


void print_real_grid(int **real_board, int size_of_board){
	int i, j;
	system("cls");
	printf("                            MineSweeper  Game\n");
	printf("                            ^^^^^^^^^^^^^^^^^\n");
	printf("           ");
	for (i = 1; i <= size_of_board; i++){
		printf("   %d  ", i);
	}
	printf("\n          ====================================================\n");
	printf("          ----------------------------------------------------\n");
	for (i = 0; i < size_of_board; i++){
		printf("       %d  ||", i + 1);
		for (j = 0; j < size_of_board; j++){
			printf("  %d  |", real_board[i][j]);
		}
		printf("|\n");
		printf("          ----------------------------------------------------\n");
	}
	printf("          =====================================================\n");
}


int check_for_win(int **real_board,char **game_board, int size_of_board){
	int i, j;
	for (i = 0; i < size_of_board; i++){
		for (j = 0; j < size_of_board; j++){
			if (game_board[i][j] == ' '){
				if (real_board[i][j] != 8)
					return 0;
			}
		}
	}
	return 1;
}


void right_click(char **game_board,int *xy){
	if (game_board[xy[0]][xy[1]] == ' ')
		game_board[xy[0]][xy[1]] = '#';
	else
		game_board[xy[0]][xy[1]] = '?';
}


int is_valid(int x){
	if (x >= 0 && x <= 7)
		return 1;
	else
		return 0;
}


void assign_neighbors(int **real_board,int x,int y,int size_of_board){
	if (is_valid(x-1) && is_valid(y-1)&&real_board[x-1][y-1]!=size_of_board)
		real_board[x - 1][y - 1] += 1;
	if (is_valid(x - 1) && is_valid(y)&&real_board[x - 1][y] != size_of_board)
		real_board[x - 1][y] += 1;
	if (is_valid(x - 1) && is_valid(y + 1) && real_board[x - 1][y + 1] != size_of_board)
		real_board[x - 1][y + 1] += 1;
	if (is_valid(x) && is_valid(y - 1) && real_board[x][y - 1] != size_of_board)
		real_board[x][y - 1] += 1;
	if (is_valid(x) && is_valid(y + 1) && real_board[x][y + 1] != size_of_board)
		real_board[x][y + 1] += 1;
	if (is_valid(x + 1) && is_valid(y - 1) && real_board[x + 1][y - 1] != size_of_board)
		real_board[x + 1][y - 1] += 1;
	if (is_valid(x + 1) && is_valid(y) && real_board[x + 1][y] != size_of_board)
		real_board[x + 1][y] += 1;
	if (is_valid(x + 1) && is_valid(y + 1) && real_board[x + 1][y + 1] != size_of_board)
		real_board[x + 1][y + 1] += 1;
}


void left_click(int **real_board,char **game_board,int *xy,int size_of_board){
	int x = xy[0];
	int y = xy[1];
	if (real_board[x][y] == 0){
		game_board[x][y] = '-';
		while (is_valid(xy[0] - 1) && is_valid(xy[1] - 1) && real_board[xy[0] - 1][xy[1] - 1] == 0){
			game_board[xy[0] - 1][xy[1] - 1] = '-';
			xy[0] -= 1;
			xy[1] -= 1;
		}
		if (is_valid(xy[0] - 1) && is_valid(xy[1] - 1) && real_board[xy[0] - 1][xy[1] - 1] != size_of_board)
			game_board[xy[0] - 1][xy[1] - 1] = '0' + real_board[xy[0] - 1][xy[1] - 1];

		xy[0] = x;
		xy[1] = y;
		while (is_valid(xy[0] - 1) && is_valid(xy[1]) && real_board[xy[0] - 1][xy[1]] == 0){
			game_board[xy[0] - 1][xy[1]] = '-';
			xy[0] -= 1;
		}
		if (is_valid(xy[0] - 1) && is_valid(xy[1]) && real_board[xy[0] - 1][xy[1]] != size_of_board)
			game_board[xy[0] - 1][xy[1]] = '0' + real_board[xy[0] - 1][xy[1]];

		xy[0] = x;
		xy[1] = y;
		while (is_valid(xy[0] - 1) && is_valid(xy[1] + 1) && real_board[xy[0] - 1][xy[1] + 1] == 0){
			game_board[xy[0] - 1][xy[1] + 1] = '-';
			xy[0] -= 1;
			xy[1] += 1;
		}
		if (is_valid(xy[0] - 1) && is_valid(xy[1] + 1) && real_board[xy[0] - 1][xy[1] + 1] != size_of_board)
			game_board[xy[0] - 1][xy[1] + 1] = '0' + real_board[xy[0] - 1][xy[1] + 1];

		xy[0] = x;
		xy[1] = y;
		while (is_valid(xy[0]) && is_valid(xy[1] - 1) && real_board[xy[0]][xy[1] - 1] == 0){
			game_board[xy[0]][xy[1] - 1] = '-';
			xy[1] -= 1;
		}
		if (is_valid(xy[0]) && is_valid(xy[1] - 1) && real_board[xy[0]][xy[1] - 1] != size_of_board)
			game_board[xy[0]][xy[1] - 1] = '0' + real_board[xy[0]][xy[1] - 1];

		xy[0] = x;
		xy[1] = y;
		while (is_valid(xy[0]) && is_valid(xy[1] - 1) && real_board[xy[0]][xy[1] + 1] == 0){
			game_board[xy[0]][xy[1] + 1] = '-';
			xy[1] += 1;
		}
		if (is_valid(xy[0]) && is_valid(xy[1] + 1) && real_board[xy[0]][xy[1] + 1] != size_of_board)
			game_board[xy[0]][xy[1] + 1] = '0' + real_board[xy[0]][xy[1] + 1];

		xy[0] = x;
		xy[1] = y;
		while (is_valid(xy[0] + 1) && is_valid(xy[1] - 1) && real_board[xy[0] + 1][xy[1] - 1] == 0){
			game_board[xy[0] + 1][xy[1] - 1] = '-';
			xy[0] += 1;
			xy[1] -= 1;
		}
		if (is_valid(xy[0] + 1) && is_valid(xy[1] - 1) && real_board[xy[0] + 1][xy[1] - 1] != size_of_board)
			game_board[xy[0] + 1][xy[1] - 1] = '0' + real_board[xy[0] + 1][xy[1] - 1];

		xy[0] = x;
		xy[1] = y;
		while (is_valid(xy[0] + 1) && is_valid(xy[1]) && real_board[xy[0] + 1][xy[1]] == 0){
			game_board[xy[0] + 1][xy[1]] = '-';
			xy[0] += 1;
		}
		if (is_valid(xy[0] + 1) && is_valid(xy[1]) && real_board[xy[0] + 1][xy[1]] != size_of_board)
			game_board[xy[0] + 1][xy[1]] = '0' + real_board[xy[0] + 1][xy[1]];

		xy[0] = x;
		xy[1] = y;
		while (is_valid(xy[0] + 1) && is_valid(xy[1] + 1) && real_board[xy[0] + 1][xy[1] + 1] == 0){
			game_board[xy[0] + 1][xy[1] + 1] = '-';
			xy[0] += 1;
			xy[1] += 1;
		}
		if (is_valid(xy[0] + 1) && is_valid(xy[1] + 1) && real_board[xy[0] + 1][xy[1] + 1] != size_of_board)
			game_board[xy[0] + 1][xy[1] + 1] = '0' + real_board[xy[0] + 1][xy[1] + 1];
	}
	else
		game_board[x][y] = real_board[x][y] + '0';
}



int check_for_mine(int *xy, int **real_board,int size_of_board){
	if (real_board[xy[0]][xy[1]] == size_of_board)
		return 1;
	else
		return 0;
}


void show_all_mines(int **real_board, char **game_board, int size_of_board, int no_of_mines){
	int i, j;
	for (i = 0; i < size_of_board; i++){
		for (j = 0; j < size_of_board; j++){
			if (real_board[i][j] == size_of_board)
				game_board[i][j] = '*';
		}
	}
}


void insert_mines(int *xy,int no_of_mines,int **real_board,int size_of_board){
	int i, y, x;
	for (i = 0; i < no_of_mines; i++){
		x = rand() % 8;
		y = rand() % 8;
		if ((x == xy[0] && y == xy[1])||(real_board[x][y]==size_of_board)){
			i-=1;
		}
		else{
			assign_neighbors(real_board,x,y,size_of_board);
			real_board[x][y] = size_of_board;
		}
	}
}

void initialize_game_board(char **game_board,int size_of_board){
	int i, j;
	for (i = 0; i < size_of_board; i++){
		game_board[i] = (char *)malloc(size_of_board*sizeof(char));
		for (j = 0; j < size_of_board; j++){
			game_board[i][j] = ' ';
		}
	}
}

void initialize_real_board(int **real_board, int size_of_board){
	int i, j;
	for (i = 0; i < size_of_board; i++){
		real_board[i] = (int *)malloc(size_of_board*sizeof(int));
		for (j = 0; j < size_of_board; j++){
			real_board[i][j] = 0;
		}
	}
}

int* take_input(){
	int xy[2];
	printf("\nEnter X coordinate : ");
	scanf("%d", &xy[0]);
	printf("\nEnter Y coordinate : ");
	scanf("%d", &xy[1]);
	return xy;
}


int check_valid_input(int *xy, char **game_board){
	if (game_board[xy[0]][xy[1]] == ' ' || game_board[xy[0]][xy[1]]=='#')
		return 1;
	return 0;
}

int main(){
	int size_of_board = 8,no_of_mines=10;
	char **game_board = (char **)malloc(size_of_board*sizeof(char*));
	char **real_board = (int **)malloc(size_of_board*sizeof(int*));
	initialize_game_board(game_board, size_of_board);
	initialize_real_board(real_board, size_of_board);
	int x, y, xy[2], counter = 0, flag;
	while (check_for_win(real_board, game_board, size_of_board) == 0){
		print_grid(game_board, size_of_board);
		printf("\nEnter X coordinate : ");
		scanf("%d", &x);
		printf("\nEnter Y coordinate : ");
		scanf("%d", &y);
		xy[0] = x-1;
		xy[1] = y-1;
		if (!check_valid_input(xy, game_board)){
			continue;
		}
		if (counter == 0){
			counter += 1;
			insert_mines(xy, no_of_mines, real_board, size_of_board);
		}
		printf("Choose your option : \n 1. Open The box\t 2. Place a flag for mine\n");
		scanf("%d", &flag);
		if (flag == 1){
			if (check_for_mine(xy, real_board, size_of_board)){
				print_grid(game_board, size_of_board);
				counter = -1;
				printf("\nGame Over :/");
				break;
			}
			left_click(real_board, game_board, xy, size_of_board);
		}
		else if (flag == 2){
			right_click(game_board, xy);
		}
		else
			printf("\nInvalid Option\n");
	}
	if (counter>0)
		printf("\nCongratulations! You Won!! :D");
	//print_grid(game_board, size_of_board);
	getch();
}