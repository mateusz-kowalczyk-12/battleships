#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SHORT_INPUT_LENGTH 15
#define TEST_INITIAL_VALUE -1

#define PLAYERS_NUMBER 2
//those players are:
#define A 0
#define B 1

#define MAX_SHIPS_NUMBER_PER_CLASS 10
#define SHIPS_CLASSES_NUMBER 4
//those classes are:
#define CAR 0
#define BAT 1
#define CRU 2
#define DES 3

#define SHIP_PLACED_BY_AI_DATA_TYPES_NUMBER 2
//those types are:
#define SHIP_CLASS 0
#define SHIP_NUMBER 1

//ship lengths:
#define CAR_LENGTH 5
#define BAT_LENGTH 4
#define CRU_LENGTH 3
#define DES_LENGTH 2

#define BORDER_POINTS_NUMBER 2
//those points are:
#define NW 0
#define SE 1

#define DIRECTIONS_NUMBER 4
//those directions are:
#define N 0
#define E 1
#define S 2
#define W 3

#define MOVE_DIRECTIONS_NUMBER 3
//those directions are:
#define L 0
#define F 1
#define R 2

#define DIMENSIONS_NUMBER 2 //y and x
//those dimensions are:
#define Y 0
#define X 1

#define MAX_SECTIONS_NUMBER 5
//sections states:
#define DESTROYED 0
#define OK 1
#define ANY 2
//sections functions:
#define RADAR 0
#define CANNON 1

//logic:
#define TRUE 1
#define FALSE 0

//perspective/callers:
#define STATE 0
#define PLAYER 1
#define AI 2

//setbacks:
#define CANNON_DESTROYED 0
#define ALL_SHOTS_SPECIFIED 1


typedef struct Spy {
    char player;
    int y;
    int x;
} Spy;

typedef struct Game_data {
    char round = 'A';
    char ai[PLAYERS_NUMBER] = { FALSE, FALSE };

    int remaining_parts[PLAYERS_NUMBER] = { 0, 0 };
    int ships_init_number[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER];
    int ship_placed_by_ai[SHIP_PLACED_BY_AI_DATA_TYPES_NUMBER] = { TEST_INITIAL_VALUE, TEST_INITIAL_VALUE };

    char no_possible_moves[PLAYERS_NUMBER] = { FALSE, FALSE };
    char no_possible_place[PLAYERS_NUMBER] = { FALSE, FALSE };
    char all_cannons_destroyed[PLAYERS_NUMBER] = { FALSE, FALSE };
    char no_ships_in_range[PLAYERS_NUMBER] = { FALSE, FALSE };

    int board_size_y = 21;
    int board_size_x = 10;
    char advanced_printing = FALSE;

    int starting_position[PLAYERS_NUMBER][BORDER_POINTS_NUMBER][DIMENSIONS_NUMBER] = { { {0, 0}, {9, 9} }, { {11, 0 }, { 20, 9 } } };
    char default_starting_positions = TRUE;

    int reefs_number = 0;
    int** reefs = NULL;

    int spies_sent = 0;
    Spy* spies = NULL;

    char extended_ships = FALSE;

    int seed_rand = TEST_INITIAL_VALUE;
} Game_data;

typedef struct Ship {
    int y = TEST_INITIAL_VALUE;
    int x = TEST_INITIAL_VALUE;
    char direction = 0;

    char section_state[MAX_SECTIONS_NUMBER] = { OK, OK, OK, OK, OK };
    int moves_left;
    int shots_left;
} Ship;