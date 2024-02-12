#include "Headers.h"

int check_length(char* ship_class) {
    if (strcmp(ship_class, "CAR") == 0) {
        return CAR_LENGTH;

    }
    if (strcmp(ship_class, "BAT") == 0) {
        return BAT_LENGTH;

    }
    if (strcmp(ship_class, "CRU") == 0) {
        return CRU_LENGTH;

    }
    if (strcmp(ship_class, "DES") == 0) {
        return DES_LENGTH;

    }
    return 0;
}

int check_length_from_int(int ship_class) {
    switch (ship_class) {
    case CAR:
        return CAR_LENGTH;
        break;
    case BAT:
        return BAT_LENGTH;
        break;
    case CRU:
        return CRU_LENGTH;
        break;
    case DES:
        return DES_LENGTH;
        break;

    }
    return 0;
}

int check_class_int(char* ship_class) {
    if (strcmp(ship_class, "CAR") == 0) {
        return CAR;

    }
    if (strcmp(ship_class, "BAT") == 0) {
        return BAT;

    }
    if (strcmp(ship_class, "CRU") == 0) {
        return CRU;

    }
    if (strcmp(ship_class, "DES") == 0) {
        return DES;

    }
    return TEST_INITIAL_VALUE;
}

void check_ship_direction(char* ship_direction) {
    if (*ship_direction == N)
        *ship_direction = 'N';
    if (*ship_direction == E)
        *ship_direction = 'E';
    if (*ship_direction == S)
        *ship_direction = 'S';
    if (*ship_direction == W)
        *ship_direction = 'W';
}

void set_additions(char ship_direction, int section_number, int* y_addition, int* x_addition) {
    switch (ship_direction) {
    case 'N':
        *y_addition = section_number;
        break;
    case 'E':
        *x_addition = -section_number;
        break;
    case 'S':
        *y_addition = -section_number;
        break;
    case 'W':
        *x_addition = section_number;
        break;

    }
}

void check_move_direction(char* move_direction) {
    if (*move_direction == L)
        *move_direction = 'L';
    if (*move_direction == F)
        *move_direction = 'F';
    if (*move_direction == R)
        *move_direction = 'R';
}

int distance(int x1, int y1, int x2, int y2) {
    float distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    int distance_int = distance;
    if (distance - distance_int > 0) {
        return distance_int + 1;

    }
    return distance_int;
}

int count_digits(int number) {
    int result = 1;
    while (number >= 10) {
        result++;
        number /= 10;

    }
    return result;
}

int opponent(char player) {
    if (player == 'A')
        return B;
    else
        return A;
}

void set_class_from_int(int ship_class_int, char* ship_class) {
    if (ship_class_int == CAR)
        strcpy(ship_class, "CAR");
    if (ship_class_int == BAT)
        strcpy(ship_class, "BAT");
    if (ship_class_int == CRU)
        strcpy(ship_class, "CRU");
    if (ship_class_int == DES)
        strcpy(ship_class, "DES");
}

void find_position(Game_data* game, Ship ship, int section_number, int* y0, int* x0) {
    for (int y = 0; y < game->board_size_y; y++) {
        for (int x = 0; x < game->board_size_x; x++) {
            int y_addition = 0;
            int x_addition = 0;

            set_additions(ship.direction, section_number, &y_addition, &x_addition);

            if (y == ship.y + y_addition && x == ship.x + x_addition) {
                *y0 = y;
                *x0 = x;
                return;

            }

        }

    }
}

char ai_match(Game_data* game) {
    if (game->ai[A] == TRUE && game->ai[B] == TRUE)
        return TRUE;
    return FALSE;
}

void change_player(Game_data* game) {
    if (game->round == 'A') {
        game->round = 'B';

    }
    else {
        game->round = 'A';

    }
}