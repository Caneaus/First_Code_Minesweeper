#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//This is my first dive into learning C/C++! I have books and resources, but I prefer just hopping in and learning 
// by actually writing something and getting a feel for it. I had fun with this little project.

int getchar(void);

void Minefield(int* board, int r, int c);

int Minesweeper(int* board, int r, int c, int coord);

int main() {
	//Basically create dimensions for board based on input
	int r;
	int c;
	int d;
	int coord = 0;
	printf("What size gameboard would you like? Enter y dimension:\n");
	scanf_s("%d", &r);
	printf("What size gameboard would you like? Enter x dimension:\n");
	scanf_s("%d", &c);
	printf("What difficulty would you like? Pick 1, 2, or 3 (easy, med, hard) :\n");
	scanf_s("%d", &d);
	printf("Your gameboard is %d by %d. You have chosen difficulty level %d \n", r, c, d);
	int i = 0;
	int j = 0;
	int tile = i * c + j;
	enum Flag { win, lose, play };
	int state;
	state = play;
	int x;
	int y;
	//Create an array of size r x c using dynamic memory allocation then set difficulty ratio
	int* board = (int*)malloc(c * r * sizeof(int));
	int dif = 0;
	if (d == 1) {
		dif = 56;
	}
	else if (d == 2) {
		dif = 53;
	}
	else if (d == 3) {
		dif = 50;
	}
	else {
		printf("If you slected an invalid difficulty. Every tile set to -Mine-.\n");
	}
	//Put some sort of thing here that randomly generates "mines" at a certain frequency, lets say mines are 9, and unrevealed tiles as 11. Then, as we play the game
	// tiles will be assigned 1, 2, 3, 4, 5, 6, 7, and 8 based on number of adjacent mines when revealed. 0 will be empty revealed tiles, and a 10 will be a game loss.
	//some proportion Tiles should have a mine. Semi arbitrary, booted up a browser minesweeper and it was 10/64 tiles. 
	srand(time(NULL));
	int rannum = 0;
	//Randomly assign either a 5 or a 0 to each element of the array
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			int rannum = rand() % 64;
			printf(" %d ", rannum);
			if (rannum >= dif) {
				*(board + i * c + j) = 9;
			}
			else if (rannum < dif) {
				*(board + i * c + j) = 11;
			}
		}
	}
	//changed i*c+j into a var called "tile" because i will always be checking the tile location based on the nested for loop for now
	//This next block will be a reusable piece to "render" the gameboard for the player. It will also check if its a win, loss, or whether it should keep playing

	Minefield(board, r, c);

	//end rendering, then check the state of the game
	while (state == play) {
		i = 0;
		int undisc = 0;
		printf("\n Select a Tile by inputting the x and y value of the Tile:\n ");
		scanf_s("%d %d", &x, &y);
		coord = ((r * c - 1) - (c - x) - (y - 1) * c);
		while (coord > r*c-1 || coord < 0) {
			printf("That isn't in the gameboard.\n");
			printf("\n Select a Tile by inputting the x and y value of the Tile:\n ");
			scanf_s("%d %d", &x, &y);
			coord = ((r * c - 1) - (c - x) - (y - 1) * c);
		}
		if (board[coord] == 9 || board[coord] == 10) {
			printf("You selected a mine and died.\n");
			Minesweeper(board, r, c, coord);
			Minefield(board, r, c);
			state = lose;
			
		}
		Minesweeper(board, r, c, coord);
		Minefield(board, r, c);
		for (i = 0; i < r * c - 1;i++) {
			if (board[i] == 11) {
				undisc = undisc + 1;
			}
		}
		if (undisc == 0) {
			printf("(No more undiscovered safe tiles) You won the game! you win!\n");
			state = win;
		
		}
	}

	printf("Game has concluded, press enter twice to terminate...\n ");
	char end = 'b';
	while (end = getchar() != EOF && end != '\n') {

		end = getchar();
	}
	putchar(end);
		//free up the memory to avoid any memory issues
		free(board);
		return 0;
	}



	//Function that prints the array
	void Minefield(int *board, int r, int c) {
		int i =0;
		int j =0;
		int tile = i * c + j;
		for (i = 0; i < r; i++) {
			printf("\n");
			for (j = 0; j < c; j++) {
				 tile = i * c + j;
				if (board[tile] == 9 || board[tile] == 11) {
					printf(" ? ");
				}
				else if (board[tile] >= 0 && board[tile] < 9) {
					printf(" %d ", board[tile]);
				}
				else if (board[tile] == 10) {
					printf(" X ");
				}
				else {
					printf(" e ");
				}
			}
			printf("\n");
		}
		return ;
	}
	//Function that Checks adjacent tiles for mines, then returns the number of mines on the tile Input: Array of tiles, rows, columns, and coord
	int Minesweeper(int* board, int r, int c, int coord) {
		int minecount = 0;
		//printf("The array index selected is %d \n", coord);
		//printf("Checking selected tile is number %d \n", coord + 1);
		if (board[coord] != 9 && board[coord] != 10) {
		//	printf("You did not select a mine!\n");
			//printf("Tile Value is %d \n", board[coord]);
		}
		if (board[coord] == 9 || board[coord] == 10) {
				board[coord] = 10;
				//printf("you lost the game Wait, what was the game again? you selected a mine  \n");
			return 1;
		}
		if (board[coord] >= 0 && board[coord] < 9) {
			//printf("you already selected that tile!\n");
			return 3;
		}
		if (board[coord] == 11) {
			//printf("Tile value is %d \n", board[coord]);
			if (coord % c != 0) {
				//printf("This is not a left edge tile, checking left tile... \n");
				if (board[coord - 1] == 9) {
					minecount = minecount + 1;
					//printf(" Its a mine to your left! %d mines detected so far \n", minecount);
				}
			}
				if (coord - c >= 0 && coord % c != 0) {
					//printf("This is not a top edge tile, checking top left tile...\n");
					if (board[coord - 1 - c] == 9) {
						minecount = minecount + 1;
					//	printf("Its a mine to your top left!%d mines detected so far \n", minecount);
					}
				}
				if (coord + c <= r * c - 1 && coord %c !=0) {
					//printf("This is not a bottom edge tile, checking the bot left tile...\n");
					if (board[coord - 1 + c] == 9) {
						minecount = minecount + 1;
						//printf("Its a mine to your bot left! %d mines detected so far \n", minecount);
					}
				}
			
				if (coord % c != c - 1) {
					//	printf("This is not a right edge tile, checking right tile...\n");
					if (board[coord + 1] == 9) {
						minecount = minecount + 1;
						//printf(" Its a mine to your right! %d mines detected so far \n", minecount);
					}
				}
				if (coord - c >= 0 && coord % c != c - 1) {
				//	printf("This is not a top edge tile, checking top right tile...\n");
					if (board[coord + 1 - c]==9) {
						minecount = minecount + 1;
					//	printf("Its a mine to your top right!%d mines detected so far \n", minecount);
					}
				}
				if (coord + c <= r * c - 1 && coord % c != c - 1) {
				//	printf("This is not a bottom edge tile, checking the bottom right tile...\n");
					if (board[coord + 1 + c]==9) {
						minecount = minecount + 1;
				//		printf(" Its a mine to your bottom right! %d mines detected so far \n", minecount);
					}
				}

		
			if (coord + c <= r * c - 1) {
			//	printf("This is not a bottom edge tile, checking bottom tile...\n");
					if (board[coord + c] == 9) {
						minecount = minecount + 1;
				//		printf("Its a mine to your bottom! %d mines detected so far \n",minecount);
					}
					
			}
			if (coord - c >= 0) {
				//printf("This is not a top edge tile, checking top tile...\n");
				if (board[coord - c] == 9) {
					minecount = minecount + 1;
					//printf("Its a mine to your top! %d mines detected so far \n",minecount);
				}
			}
			board[coord] = minecount;
			//if the checked tile is 0, run the detection on ALL adjacent tiles, except for ones that have already had mine detection
			if (minecount == 0) {
				int proxy = coord;
				//printf("moving to left check\n");
				if (proxy % c != 0 && board[proxy - 1] == 11) {
					//printf("This is not a left edge tile, cascading detection left... \n");
					//Minesweeper(board, r, c, proxy - 1);
					//printf("moving to top left check\n");
				}
					if (proxy - c >= 0 && proxy % c !=0 && board[proxy-1-c] == 11) {
						//printf("This is not a top edge tile, cascading direction upwards... \n");
						Minesweeper(board, r, c, proxy - 1 - c);
						}
					//printf("moving to bot left check\n");
					if (proxy + c <= r * c - 1 && proxy % c !=0 && board[proxy-1+c] == 11) {
					   //printf("This is not a bottom edge tile, cascading detection downwards...\n");
						Minesweeper(board, r, c, proxy - 1 + c);
					}
				
				//printf("moving to right check\n");
					if (proxy % c != c - 1 && board[proxy + 1] == 11) {
						//printf("This is not a right edge tile, cascading detection right... \n");
						Minesweeper(board, r, c, proxy + 1);
						//printf("moving to top right check\n");
					}
					if (proxy - c >= 0 && proxy %c != c-1 && board[proxy +1-c] == 11) {
						//printf("This is not a top edge tile, cascading direction upwards... \n");
						Minesweeper(board, r, c, proxy + 1 - c);
					}
					//printf("moving to bot right check\n");
					if (proxy + c <= r * c - 1 && proxy %c != c-1 && board[proxy+1+c]==11) {
						//printf("This is not a bottom edge tile, cascading detection downwards...\n");
						Minesweeper(board, r, c, proxy + 1 + c);
					}
				
				//printf("moving to top check\n");
				if (proxy - c >= 0 && board[proxy-c] == 11) {
					//printf("This is not a top edge tile, cascading direction upwards... \n");
					Minesweeper(board, r, c, proxy - c);
				}
				//printf("moving to bot check\n");
				if (proxy + c <= r * c - 1 && board[proxy+c]==11) {
					//printf("This is not a bottom edge tile, cascading detection downwards...\n");
					Minesweeper(board, r, c, proxy + c);
				}



			}
		}   
		//printf("There are %d mines adjacent to this tile. \n", minecount);
		return 3;
	}

