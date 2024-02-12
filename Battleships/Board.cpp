#include "Headers.h"

void print_board(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int perspective, int print_parameter) {
    if (print_parameter == 1 && game->advanced_printing == FALSE) {
        game->advanced_printing = TRUE;
        update_board(board, game, ships);

    }
    if (print_parameter == 0 && game->advanced_printing == TRUE) {
        game->advanced_printing = FALSE;
        update_board(board, game, ships);

    }

    if (perspective == PLAYER) {
        update_board_player(board, game, ships);

    }

    if (print_parameter == 1) {
        print_column_numbers(game->board_size_x, game->board_size_y);

    }
    for (int y = 0; y < game->board_size_y; y++) {
        if (print_parameter == 1) {
            printf("%0*d", count_digits(game->board_size_y - 1), y);

        }
        for (int x = 0; x < game->board_size_x; x++) {
            printf("%c", board[y][x]);

        }
        putchar('\n');

    }
    if (perspective == STATE) {
        printf("PARTS REMAINING:: A : %d B : %d\n", game->remaining_parts[A], game->remaining_parts[B]);

    }

    if (perspective == PLAYER) {
        clear_board(board, game->board_size_y, game->board_size_x);
        update_board(board, game, ships);

    }
}

void clear_board(char** board, int board_size_y, int board_size_x) {
    for (int y = 0; y < board_size_y; y++) {
        for (int x = 0; x < board_size_x; x++) {
            board[y][x] = ' ';

        }

    }
}

void print_column_numbers(int board_size_x, int board_size_y) {
    int digits_number = count_digits(board_size_x - 1);

    for (int digit_number = 0; digit_number < digits_number; digit_number++) {
        for (int i = 0; i < count_digits(board_size_y - 1); i++) {
            putchar(' ');

        }
        for (int x = 0; x < board_size_x; x++) {
            int digit = (x % (int)pow(10, digits_number - digit_number)) / (int)pow(10, digits_number - 1 - digit_number);

            printf("%d", digit);

        }
        putchar('\n');

    }
}

void update_board(char** board, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    for (int y = 0; y < game->board_size_y; y++) {
        for (int x = 0; x < game->board_size_x; x++) {
            check_to_add_ship(game, ships, board, y, x);
            check_to_add_reef(game, board, y, x);

        }

    }
}

void update_board_player(char** board, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    char seen;

    for (int y = 0; y < game->board_size_y; y++) {
        for (int x = 0; x < game->board_size_x; x++) {
            seen = seen_by_the_player(game, ships, y, x);

            if (seen == FALSE) {
                board[y][x] = '?';

            }

        }

    }
}

void check_to_add_ship(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int y, int x) {
    for (int player = A; player <= B; player++) {
        for (int ship_class = CAR; ship_class <= DES; ship_class++) {
            for (int ship_number = 0; ship_number < game->ships_init_number[player][ship_class]; ship_number++) {
                if (ships[player][ship_class][ship_number].x == x && ships[player][ship_class][ship_number].y == y && ship_placed(ships[player][ship_class][ship_number])) {
                    draw_ship(y, x, ships[player][ship_class][ship_number].direction, CAR_LENGTH - ship_class, ships[player][ship_class][ship_number].section_state, board);
                    if (game->advanced_printing == TRUE) {
                        draw_ship_advanced(y, x, ships[player][ship_class][ship_number].direction, CAR_LENGTH - ship_class, ships[player][ship_class][ship_number].section_state, board, player);

                    }

                }

            }

        }

    }
}

void check_to_add_reef(Game_data* game, char** board, int y, int x) {
    for (int reef_number = 0; reef_number < game->reefs_number; reef_number++) {
        if (game->reefs[reef_number][Y] == y && game->reefs[reef_number][X] == x) {
            board[y][x] = '#';

        }

    }
}

void draw_ship(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board) {
    for (int i = 0; i < length; i++) { //for each section
        switch (ship_direction) {
        case 'N':
            if (section_state[i] == OK) {
                board[ship_y + i][ship_x] = '+';

            }
            if (section_state[i] == DESTROYED) {
                board[ship_y + i][ship_x] = 'x';

            }
            break;
        case 'E':
            if (section_state[i] == OK) {
                board[ship_y][ship_x - i] = '+';

            }
            if (section_state[i] == DESTROYED) {
                board[ship_y][ship_x - i] = 'x';

            }
            break;
        case 'S':
            if (section_state[i] == OK) {
                board[ship_y - i][ship_x] = '+';

            }
            if (section_state[i] == DESTROYED) {
                board[ship_y - i][ship_x] = 'x';

            }
            break;
        case 'W':
            if (section_state[i] == OK) {
                board[ship_y][ship_x + i] = '+';

            }
            if (section_state[i] == DESTROYED) {
                board[ship_y][ship_x + i] = 'x';

            }
            break;

        }

    }
}

void delete_ship_proposed_by_ai(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    if (game->ship_placed_by_ai[SHIP_CLASS] != TEST_INITIAL_VALUE) { //if the A.I. has proposed to place a ship
        ships[game->round - 'A'][game->ship_placed_by_ai[SHIP_CLASS]][game->ship_placed_by_ai[SHIP_NUMBER]].direction = 0; //the program can now delete the ship proposed by the A.I. to be placed because A.I. is not supposed to change the board
        clear_board(board, game->board_size_y, game->board_size_x);
        update_board(board, game, ships);

        game->ship_placed_by_ai[SHIP_CLASS] = TEST_INITIAL_VALUE;

    }
}

void draw_ship_advanced(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board, char player) {
    draw_ship_radar(ship_y, ship_x, ship_direction, length, section_state, board, player);
    draw_ship_cannon(ship_y, ship_x, ship_direction, length, section_state, board);
    draw_ship_engine(ship_y, ship_x, ship_direction, length, section_state, board);

}

void draw_ship_radar(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board, char player) {
    if (section_state[RADAR] == OK)
        board[ship_y][ship_x] = '@';
}

void draw_ship_cannon(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board) {
    if (section_state[CANNON] == OK) {
        switch (ship_direction) {
        case 'N':
            board[ship_y + 1][ship_x] = '!';
            break;
        case 'E':
            board[ship_y][ship_x - 1] = '!';
            break;
        case 'S':
            board[ship_y - 1][ship_x] = '!';
            break;
        case 'W':
            board[ship_y][ship_x + 1] = '!';
            break;

        }

    }
}

void draw_ship_engine(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board) {
    if (section_state[length - 1] == OK) {
        switch (ship_direction) {
        case 'N':
            board[ship_y + (length - 1)][ship_x] = '%';
            break;
        case 'E':
            board[ship_y][ship_x - (length - 1)] = '%';
            break;
        case 'S':
            board[ship_y - (length - 1)][ship_x] = '%';
            break;
        case 'W':
            board[ship_y][ship_x + (length - 1)] = '%';
            break;

        }

    }
}
