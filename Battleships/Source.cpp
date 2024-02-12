#include "Headers.h"

int main() {
    struct Game_data game;
    struct Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS];

    char** board = (char**)malloc(game.board_size_y * sizeof(char*));
    for (int y = 0; y < game.board_size_y; y++) {
        board[y] = (char*)malloc(game.board_size_x * sizeof(char));

    }

    set_default_initial_ships_numbers(game.ships_init_number);
    srand(time(NULL));

    clear_board(board, game.board_size_y, game.board_size_x);
    update_board(board, &game, ships);

    char victory_condition_to_be_checked = 0;

    while (true) {
        reset_moves_shots_left(ships);
        check_ai(&game, ships, board);
        read_command_group(&game, ships, &board);
        if (victory_condition_to_be_checked == 0) {
            victory_condition_to_be_checked = all_ships_placed(&game, ships);

        }
        if (victory_condition_to_be_checked == 1) {
            check_victory_condition(game.remaining_parts);

        }

    }

    return 0;
}


void set_default_initial_ships_numbers(int ships_init_number[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER]) {
    for (int player = A; player <= B; player++) {
        for (int ship_class = CAR; ship_class <= DES; ship_class++) {
            ships_init_number[player][ship_class] = ship_class + 1; //1 for CAR==0, 2 for BAT==1, ... 

        }

    }
}

void reset_moves_shots_left(Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    for (int player = A; player <= B; player++) {
        for (int ship_class = CAR; ship_class <= DES; ship_class++) {
            for (int ship_number = 0; ship_number < MAX_SHIPS_NUMBER_PER_CLASS; ship_number++) {
                switch (ship_class) {
                case CAR:
                    ships[player][ship_class][ship_number].moves_left = 2;
                    break;
                default:
                    ships[player][ship_class][ship_number].moves_left = 3;

                }
                ships[player][ship_class][ship_number].shots_left = check_length_from_int(ship_class);

            }

        }

    }
}


void check_ai(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    if (game->ai[game->round - 'A'] == TRUE) { //expected player is A.I.
        continue_ai(game, ships, board);

    }
}

void read_command_group(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char*** board) {
    char command_group[SHORT_INPUT_LENGTH] = ""; //long enough to store "[playerX]" or "[state]", some additional chars can be stored in case the input is longer

    if (!ai_match(game))
        scanf("%s", command_group);
    else
        return;

    if (strcmp(command_group, "[playerA]") == 0) {
        if (game->round == 'A') {
            begin_command_for_player(game, ships, *board);

        }
        else {
            printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED\n", command_group);
            exit(0);

        }

    }
    if (strcmp(command_group, "[playerB]") == 0) {
        if (game->round == 'B') {
            begin_command_for_player(game, ships, *board);

        }
        else {
            printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED\n", command_group);
            exit(0);

        }

    }
    if (strcmp(command_group, "[state]") == 0) {
        begin_command_for_state(game, ships, board);

    }
    if ((strcmp(command_group, "[playerA]")) * (strcmp(command_group, "[playerB]")) * (strcmp(command_group, "[state]")) != 0) {
        exit(0);

    }
}


void continue_ai(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    check_if_ai_can_continue(game);

    continue_save_command(game, ships);

    printf("\n[state]\nPRINT 0\n[state]\n", game->round);
    if (ai_match(game))
        print_board(game, ships, board, STATE, 0);

    printf("\n[player%c]\n", game->round);

    ai_place_ship(game, ships, board);

    if (game->extended_ships == FALSE)
        ai_shoot_basic(game, ships, board);
    else
        ai_shoot_extended(game, ships, board);

    if (rand() % 2 == 0) //50% chance of trying to move a ship
        ai_move(game, ships, board);

    if (!ai_match(game))
        delete_ship_proposed_by_ai(game, ships, board);

    printf("[player%c]\n\n[state]\nPRINT 0\n[state]\n", game->round);
    if (ai_match(game))
        print_board(game, ships, board, STATE, 0);

    change_player(game);
}

void begin_command_for_player(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    char command_key_word[2 * SHORT_INPUT_LENGTH] = ""; //enough to store each command keywords, i.e. "PLACE_SHIP", "SHOOT", ...

    scanf("%s", command_key_word);

    if (strcmp(command_key_word, "PLACE_SHIP") == 0) {
        continue_place_ship_command(game, ships, board);

    }
    if (strcmp(command_key_word, "SHOOT") == 0) {
        if (game->extended_ships == FALSE) {
            continue_shoot_command_basic(game, ships, board);

        }
        else {
            continue_shoot_command_extended(game, ships, board);

        }

    }
    if (strcmp(command_key_word, "MOVE") == 0) {
        continue_move_command(game, ships, board);

    }
    if (strcmp(command_key_word, "SPY") == 0) {
        continue_spy_command(game, ships, board);

    }
    if (strcmp(command_key_word, "PRINT") == 0) {
        continue_print_player_command(game, ships, board);

    }
    if (strcmp(command_key_word, "[playerA]") == 0) {
        if (game->round == 'A') {
            game->round = 'B';
            return;

        }
        else {
            printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED\n", command_key_word);
            exit(0);

        }

    }
    if (strcmp(command_key_word, "[playerB]") == 0) {
        if (game->round == 'B') {
            game->round = 'A';
            return;

        }
        else {
            printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED\n", command_key_word);
            exit(0);

        }

    }
    begin_command_for_player(game, ships, board);
}

void begin_command_for_state(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char*** board) {
    char command_key_word[30] = ""; //30 is enough to store each command keywords, i.e. "PRINT", "SET_FLEET", ...

    scanf("%s", command_key_word);
    if (strcmp(command_key_word, "PRINT") == 0) {
        continue_print_command(game, ships, *board, STATE);

    }
    if (strcmp(command_key_word, "SET_FLEET") == 0) {
        continue_set_fleet_command(game);

    }
    if (strcmp(command_key_word, "NEXT_PLAYER") == 0) {
        continue_next_player_command(game);

    }
    if (strcmp(command_key_word, "BOARD_SIZE") == 0) {
        continue_board_size_command(game, ships, board);

    }
    if (strcmp(command_key_word, "INIT_POSITION") == 0) {
        continue_init_position_command(game);

    }
    if (strcmp(command_key_word, "REEF") == 0) {
        continue_reef_command(game, ships, *board);

    }
    if (strcmp(command_key_word, "SHIP") == 0) {
        continue_ship_command(game, ships, *board);

    }
    if (strcmp(command_key_word, "EXTENDED_SHIPS") == 0) {
        continue_extended_ships_command(game, ships);

    }
    if (strcmp(command_key_word, "SAVE") == 0) {
        continue_save_command(game, ships);

    }
    if (strcmp(command_key_word, "SRAND") == 0) {
        continue_srand_command(game);

    }if (strcmp(command_key_word, "SET_AI_PLAYER") == 0) {
        continue_set_ai_player_command(game, ships);

    }
    if (strcmp(command_key_word, "[state]") == 0) {
        return;

    }
    begin_command_for_state(game, ships, board);
}


void continue_print_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int perspective) {
    int print_parameter;

    scanf("%d", &print_parameter);

    print_board(game, ships, board, perspective, print_parameter);
}

void continue_set_fleet_command(Game_data* game) {
    char player;

    scanf(" %c", &player);
    for (int ship_class = CAR; ship_class <= DES; ship_class++) {
        scanf("%d", &(game->ships_init_number[player - 'A'][ship_class]));

    }
}

void continue_next_player_command(Game_data* game) {
    char player;

    scanf(" %c", &player);

    game->round = player;
}

void continue_board_size_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char*** board) {
    for (int y = 0; y < game->board_size_y; y++) {
        free((*board)[y]);

    }
    free(*board);

    scanf("%d %d", &(game->board_size_y), &(game->board_size_x));

    char** new_board = (char**)malloc(game->board_size_y * sizeof(char*));
    for (int y = 0; y < game->board_size_y; y++) {
        new_board[y] = (char*)malloc(game->board_size_x * sizeof(char));

    }

    *board = new_board;
    clear_board(*board, game->board_size_y, game->board_size_x);
    update_board(*board, game, ships);

    if (game->default_starting_positions == TRUE) {
        game->starting_position[A][SE][Y] = game->board_size_y / 2 - 1;
        game->starting_position[A][SE][X] = game->board_size_x - 1;

        game->starting_position[B][NW][Y] = game->board_size_y / 2 + 1;
        game->starting_position[B][SE][Y] = game->board_size_y - 1;
        game->starting_position[B][SE][X] = game->board_size_x - 1;

    }
}

void continue_init_position_command(Game_data* game) {
    char player;

    scanf(" %c", &player);
    scanf("%d %d %d %d", &(game->starting_position[player - 'A'][NW][Y]), &(game->starting_position[player - 'A'][NW][X]), &(game->starting_position[player - 'A'][SE][Y]), &(game->starting_position[player - 'A'][SE][X]));

    game->default_starting_positions = FALSE;
}

void continue_reef_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int reef_y, reef_x;

    scanf("%d %d", &reef_y, &reef_x);

    /*validation*/ {
        if (reef_y < 0 || reef_y >= game->board_size_y || reef_x < 0 || reef_x >= game->board_size_x) {
            printf("INVALID OPERATION \"REEF %d %d\": REEF IS NOT PLACED ON BOARD\n", reef_y, reef_x);
            exit(0);

        }

    }

    /*execution*/ {
        game->reefs_number++;
        int** new_reefs = (int**)malloc(game->reefs_number * sizeof(int*));
        for (int i = 0; i < game->reefs_number; i++) {
            new_reefs[i] = (int*)malloc(DIMENSIONS_NUMBER * sizeof(int));

        }

        for (int i = 0; i < game->reefs_number - 1; i++) {
            new_reefs[i][Y] = game->reefs[i][Y];
            new_reefs[i][X] = game->reefs[i][X];

        }

        if (game->reefs != NULL) {
            for (int i = 0; i < game->reefs_number - 1; i++) {
                free(game->reefs[i]);

            }
            free(game->reefs);

        }

        game->reefs = new_reefs;
        game->reefs[game->reefs_number - 1][Y] = reef_y;
        game->reefs[game->reefs_number - 1][X] = reef_x;

        update_board(board, game, ships);

    }
}

void continue_ship_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    char player, ship_direction;
    int ship_y, ship_x, ship_number;
    char ship_class[4];
    char section_state[MAX_SECTIONS_NUMBER + 1] = { TEST_INITIAL_VALUE, TEST_INITIAL_VALUE, TEST_INITIAL_VALUE, TEST_INITIAL_VALUE, TEST_INITIAL_VALUE
    }; //+1 in the length value is for the '\0' to be saved by scanf scanning to a string

    scanf(" %c %d %d %c %d %s %s", &player, &ship_y, &ship_x, &ship_direction, &ship_number, ship_class, section_state);

    if (ship_command_validation(game, ships, board, ship_y, ship_x, ship_direction, ship_number, section_state, ship_class, player) == FALSE) {
        exit(0);

    }

    ship_command_execution(game, ships, board, ship_y, ship_x, ship_direction, ship_number, section_state, ship_class, player);

}

void continue_extended_ships_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    if (game->extended_ships == FALSE) {
        game->extended_ships = TRUE;

    }
    else {
        game->extended_ships = FALSE;

    }
}

void continue_save_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    printf("\n[state]\n");

    printf("BOARD_SIZE %d %d\n", game->board_size_y, game->board_size_x);

    printf("NEXT_PLAYER %c\n", game->round);

    save_players(game, ships);

    for (int reef_number = 0; reef_number < game->reefs_number; reef_number++) {
        printf("REEF %d %d\n", game->reefs[reef_number][Y], game->reefs[reef_number][X]);

    }

    if (game->extended_ships == TRUE) {
        printf("EXTENDED_SHIPS\n");

    }

    if (game->seed_rand != TEST_INITIAL_VALUE) {
        printf("SRAND %d\n", game->seed_rand + 1);

    }

    for (char player = 'A'; player <= 'B'; player++) {
        if (game->ai[player - 'A'] == TRUE)
            printf("SET_AI_PLAYER %c\n", player);

    }

    printf("[state]\n");
}

void continue_srand_command(Game_data* game) {
    scanf("%d", &game->seed_rand);

    srand(game->seed_rand);
}

void continue_set_ai_player_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    char player;

    scanf(" %c", &player);

    game->ai[player - 'A'] = TRUE;
}


void continue_place_ship_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int ship_y, ship_x, ship_number;
    char ship_direction;
    char ship_class[4];

    scanf("%d %d %c %d %s", &ship_y, &ship_x, &ship_direction, &ship_number, ship_class);

    if (place_ship_command_validation(game, ships, board, ship_y, ship_x, ship_direction, ship_class, ship_number, PLAYER) == FALSE) {
        exit(0);

    }

    place_ship_command_execution(game, ships, board, ship_y, ship_x, ship_direction, ship_class, ship_number);
}

void ai_place_ship(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int ship_y, ship_x, ship_class_int;
    int ship_number = TEST_INITIAL_VALUE;
    char ship_direction;
    char ship_class[4];

    if (ai_place_ship_checking(game, ships, board) == FALSE)
        return;

    while (TRUE) {
        ship_y = rand() % (game->board_size_y);
        ship_x = rand() % (game->board_size_x);

        ship_direction = rand() % DIRECTIONS_NUMBER;
        check_ship_direction(&ship_direction);

        ship_class_int = rand() % SHIPS_CLASSES_NUMBER;
        set_class_from_int(ship_class_int, ship_class);

        for (int i = 0; i < game->ships_init_number[game->round - 'A'][ship_class_int]; i++) {
            if (!ship_placed(ships[game->round - 'A'][ship_class_int][i])) {
                ship_number = i;
                break;

            }

        }

        if (ship_number == TEST_INITIAL_VALUE)
            continue;

        if (place_ship_command_validation(game, ships, board, ship_y, ship_x, ship_direction, ship_class, ship_number, AI) == TRUE) {
            printf("PLACE_SHIP %d %d %c %d %s\n", ship_y, ship_x, ship_direction, ship_number, ship_class);

            place_ship_command_execution(game, ships, board, ship_y, ship_x, ship_direction, ship_class, ship_number); //for the MOVE command (proposed by the A.I.) to know where the ships cannot be moved after executing proposed by the A.I. PLACE_SHIP command
            game->ship_placed_by_ai[SHIP_CLASS] = ship_class_int;
            game->ship_placed_by_ai[SHIP_NUMBER] = ship_number;
            break;

        }

    }
}

void continue_shoot_command_basic(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int y, x;

    scanf("%d %d", &y, &x);

    if (shoot_command_basic_validation(y, x, game, ships) == FALSE)
        exit(0);

    shoot_command_basic_execution(game, ships, board, y, x);
    update_board(board, game, ships);
}

void ai_shoot_basic(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int y, x, ship_class_int, ship_number, section_number;
    int opponent_number = opponent(game->round);
    char ship_class[4];

    if (!all_ships_placed(game, ships))
        return;

    while (TRUE) {
        ship_class_int = rand() % SHIPS_CLASSES_NUMBER;
        set_class_from_int(ship_class_int, ship_class);

        if (game->ships_init_number[opponent_number][ship_class_int] == 0) //there is 0 ships of this class available to be placed in this game for the opponeent 
            continue;

        ship_number = rand() % game->ships_init_number[opponent_number][ship_class_int];

        if (!ship_placed(ships[opponent_number][ship_class_int][ship_number]))
            return;

        section_number = rand() % check_length(ship_class);

        find_position(game, ships[opponent_number][ship_class_int][ship_number], section_number, &y, &x);

        printf("SHOOT %d %d\n", y, x);
        if (ai_match(game)) {
            shoot_command_basic_execution(game, ships, board, y, x);
            update_board(board, game, ships);

        }
        break;

    }
}

void ai_shoot_extended(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int y, x, ship_class_int, ship_number;
    char ship_class[4];

    if (ai_shoot_extended_checking(game, ships, board) == FALSE)
        return;

    while (TRUE) {
        y = rand() % game->board_size_y;
        x = rand() % game->board_size_x;

        if(is_a_reef(y, x, game->reefs_number, game->reefs))
            continue;

        if (game->no_ships_in_range[game->round - 'A'] == FALSE) {
            if (no_ships_have_OK_section_here(game, ships, opponent(game->round - 'A'), y, x))
                continue;
        }

        ship_class_int = TEST_INITIAL_VALUE; //to later check if any ship was found
        find_ship_that_can_shoot_here(game, ships, y, x, &ship_class_int, &ship_number);

        if (ship_class_int == TEST_INITIAL_VALUE)
            continue;

        set_class_from_int(ship_class_int, ship_class);

        printf("SHOOT %d %s %d %d\n", ship_class_int, ship_class, y, x);
        if (ai_match(game)) {
            shoot_command_extended_execution(game, ships, board, y, x, ship_class, ship_number);
            update_board(board, game, ships);

        }
        break;

    }
}

void continue_shoot_command_extended(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int ship_number, y, x;
    char ship_class[4];

    scanf("%d %s %d %d", &ship_number, ship_class, &y, &x);

    if (shoot_command_basic_validation(y, x, game, ships) == FALSE) {
        exit(0);

    }
    if (shoot_command_extended_validation(ship_number, ship_class, y, x, game, ships) == FALSE) {
        exit(0);

    }

    shoot_command_extended_execution(game, ships, board, y, x, ship_class, ship_number);
}

void continue_move_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int ship_number;
    char ship_class[4];
    char move_direction;

    int new_ship_y, new_ship_x;
    char new_ship_direction;

    scanf("%d %s %c", &ship_number, ship_class, &move_direction);

    int ship_class_int = check_class_int(ship_class);

    move_command_preset_new_data(move_direction, ship_class_int, ship_number, check_length(ship_class), ships, game->round - 'A', &new_ship_y, &new_ship_x, &new_ship_direction);

    if (move_command_validation(ship_number, ship_class, move_direction, new_ship_y, new_ship_x, new_ship_direction, game, ships, board, PLAYER) == FALSE) {
        exit(0);

    }

    move_command_execution(game, ships, board, ship_class_int, ship_number, new_ship_y, new_ship_x, new_ship_direction);
}

void ai_move(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int ship_number, ship_class_int, new_ship_y, new_ship_x;
    char ship_class[4];
    char move_direction, new_ship_direction;

    if (ai_move_checking(game, ships, board) == FALSE)
        return;

    while (TRUE) {
        ship_class_int = rand() % SHIPS_CLASSES_NUMBER;
        set_class_from_int(ship_class_int, ship_class);

        if (game->ships_init_number[game->round - 'A'][ship_class_int] == 0) {//there is 0 ships of this class available to be pleced in this game for the opponeent 
            continue;

        }

        ship_number = rand() % game->ships_init_number[game->round - 'A'][ship_class_int];
        if (ships[game->round - 'A'][ship_class_int][ship_number].direction == 0) {//has the picked ship been placed
            continue;

        }

        move_direction = rand() % MOVE_DIRECTIONS_NUMBER;
        check_move_direction(&move_direction);

        move_command_preset_new_data(move_direction, ship_class_int, ship_number, check_length(ship_class), ships, game->round - 'A', &new_ship_y, &new_ship_x, &new_ship_direction);

        if (move_command_validation(ship_number, ship_class, move_direction, new_ship_y, new_ship_x, new_ship_direction, game, ships, board, AI) == TRUE) {
            printf("MOVE %d %s %c\n", ship_number, ship_class, move_direction);
            if (ai_match(game))
                move_command_execution(game, ships, board, ship_class_int, ship_number, new_ship_y, new_ship_x, new_ship_direction);
            break;

        }

    }
}

void continue_spy_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int ship_number, spy_y, spy_x;

    scanf("%d %d %d", &ship_number, &spy_y, &spy_x);

    /*validation*/ {
        if (ships[game->round - 'A'][CAR][ship_number].section_state[CANNON] == DESTROYED) {
            printf("INVALID OPERATION \"SPY %d %d %d\": CANNOT SEND PLANE", ship_number, spy_y, spy_x);
            exit(0);

        }
        if (ships[game->round - 'A'][CAR][ship_number].shots_left == 0) {
            printf("INVALID OPERATION \"SPY %d %d %d\": ALL PLANES SENT", ship_number, spy_y, spy_x);
            exit(0);

        }

    }

    /*execution*/ {
        game->spies_sent++;
        Spy* new_spies = (Spy*)malloc(game->spies_sent * sizeof(Spy));
        for (int spy_number = 0; spy_number < game->spies_sent - 1; spy_number++) {
            new_spies[spy_number] = game->spies[spy_number];

        }
        free(game->spies);
        game->spies = new_spies;
        game->spies[game->spies_sent - 1].player = game->round;
        game->spies[game->spies_sent - 1].y = spy_y;
        game->spies[game->spies_sent - 1].x = spy_x;
        ships[game->round - 'A'][CAR][ship_number].shots_left--;

    }
}

void continue_print_player_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    int print_parameter;

    scanf("%d", &print_parameter);

    print_board(game, ships, board, PLAYER, print_parameter);
}


char in_starting_position(int ship_y, int ship_x, char ship_direction, char* ship_class, int starting_position_NW[DIMENSIONS_NUMBER], int starting_position_SE[DIMENSIONS_NUMBER]) {
    int ship_length = check_length(ship_class);

    for (int i = 0; i < ship_length; i++) { //for each section
        switch (ship_direction) {
        case 'N':
            if (ship_y + i < starting_position_NW[Y] || ship_y + i > starting_position_SE[Y] || ship_x < starting_position_NW[X] || ship_x > starting_position_SE[X]) {
                return FALSE;

            }
            break;
        case 'E':
            if (ship_y < starting_position_NW[Y] || ship_y > starting_position_SE[Y] || ship_x - i < starting_position_NW[X] || ship_x - i > starting_position_SE[X]) {
                return FALSE;

            }
            break;
        case 'S':
            if (ship_y - i < starting_position_NW[Y] || ship_y - i > starting_position_SE[Y] || ship_x < starting_position_NW[X] || ship_x > starting_position_SE[X]) {
                return FALSE;

            }
            break;
        case 'W':
            if (ship_y < starting_position_NW[Y] || ship_y > starting_position_SE[Y] || ship_x + i < starting_position_NW[X] || ship_x + i > starting_position_SE[X]) {
                return FALSE;

            }
            break;

        }

    }
    return TRUE;
}

char ship_already_present(int ship_number, char* ship_class, char round, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    int ship_class_int = check_class_int(ship_class);

    if (ship_placed(ships[round - 'A'][ship_class_int][ship_number]))
        return TRUE;

    return FALSE;
}

char all_ships_of_the_class_already_set(int ship_number, char* ship_class, char round, Game_data* game) {
    if (strcmp(ship_class, "CAR") == 0) {
        if (ship_number >= game->ships_init_number[round - 'A'][CAR]) {
            return TRUE;

        }

    }
    if (strcmp(ship_class, "BAT") == 0) {
        if (ship_number >= game->ships_init_number[round - 'A'][BAT]) {
            return TRUE;

        }

    }
    if (strcmp(ship_class, "CRU") == 0) {
        if (ship_number >= game->ships_init_number[round - 'A'][CRU]) {
            return TRUE;

        }

    }
    if (strcmp(ship_class, "DES") == 0) {
        if (ship_number >= game->ships_init_number[round - 'A'][DES]) {
            return TRUE;

        }

    }
    return FALSE;
}

char ship_on_reef(int ship_y, int ship_x, char ship_direction, char* ship_class, int reefs_number, int** reefs) {
    int ship_length = check_length(ship_class);

    for (int section_number = 0; section_number < ship_length; section_number++) { //for each section
        int y_addition = 0;
        int x_addition = 0;
        
        set_additions(ship_direction, section_number, &y_addition, &x_addition);

        if (is_a_reef(ship_y + y_addition, ship_x + x_addition, reefs_number, reefs)) {
            return TRUE;

        }

    }
    return FALSE;
}

char ship_too_close(int ship_y, int ship_x, char ship_direction, char* ship_class, Game_data* game, char** board) {
    int ship_length = check_length(ship_class);

    for (int section_number = 0; section_number < ship_length; section_number++) { //for each section of the ship
        int y_addition = 0;
        int x_addition = 0;
        
        set_additions(ship_direction, section_number, &y_addition, &x_addition);

        if (is_a_ship_near(ship_y + y_addition, ship_x + x_addition, board, game->board_size_y, game->board_size_x)) {
            return TRUE;

        }

    }
    return FALSE;
}

char all_ships_placed(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    for (int player = A; player <= B; player++) {
        for (int ship_class = CAR; ship_class <= DES; ship_class++) {
            for (int ship_number = 0; ship_number < game->ships_init_number[player][ship_class]; ship_number++) {
                if (!ship_placed(ships[player][ship_class][ship_number])) {
                    return FALSE;

                }

            }

        }

    }
    return TRUE;
}

char all_ships_placed_player(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    for (int ship_class = CAR; ship_class <= DES; ship_class++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class]; ship_number++) {
            if (!ship_placed(ships[game->round - 'A'][ship_class][ship_number])) {
                return FALSE;

            }

        }

    }
    return TRUE;
}

char no_possible_place(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    for (int ship_class_int = CAR; ship_class_int <= DES; ship_class_int++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class_int]; ship_number++) {
            if (!ship_placed(ships[game->round - 'A'][ship_class_int][ship_number])) {
                for (char ship_direction = 0; ship_direction < DIRECTIONS_NUMBER; ship_direction++) {
                    check_ship_direction(&ship_direction);

                    char ship_class[4];

                    set_class_from_int(ship_class_int, ship_class);

                    return any_place_possible(game, ships, board, ship_direction, ship_class, ship_number);


                }

            }

        }

    }

    return TRUE;
}

char no_possible_moves(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    char new_ship_direction;
    int new_ship_y, new_ship_x;
    char ship_class[4];

    for (int ship_class_int = CAR; ship_class_int <= DES; ship_class_int++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class_int]; ship_number++) {
            for (char move_direction = L; move_direction < MOVE_DIRECTIONS_NUMBER; move_direction++) {
                check_move_direction(&move_direction);
                set_class_from_int(ship_class_int, ship_class);

                move_command_preset_new_data(move_direction, ship_class_int, ship_number, check_length(ship_class), ships, game->round - 'A', &new_ship_y, &new_ship_x, &new_ship_direction);

                if (move_command_validation(ship_number, ship_class, move_direction, new_ship_y, new_ship_x, new_ship_direction, game, ships, board, AI) == TRUE) {
                    return FALSE;

                }

            }

        }

    }

    return TRUE;
}

char is_a_ship_in_range(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    int opponent_number = opponent(game->round);
    int y, x;

    for (int opponent_ship_class_int = CAR; opponent_ship_class_int <= DES; opponent_ship_class_int++) {
        for (int opponent_ship_number = 0; opponent_ship_number < game->ships_init_number[opponent_number][opponent_ship_class_int]; opponent_ship_number++) {
            for (int section_number = 0; section_number < check_length_from_int(opponent_ship_class_int); section_number++) {
                if (ship_placed(ships[opponent_number][opponent_ship_class_int][opponent_ship_number]) && ships[opponent_number][opponent_ship_class_int][opponent_ship_number].section_state[section_number] == OK) {
                    find_position(game, ships[opponent_number][opponent_ship_class_int][opponent_ship_number], section_number, &y, &x);

                    if (!no_ship_can_shoot_here(game, ships, y, x))
                        return TRUE;
                }
            }
        }
    }

    return FALSE;
}

char no_ship_can_shoot(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int condition) {
    for (int ship_class = CAR; ship_class <= DES; ship_class++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class]; ship_number++) {
            switch (condition) {
            case CANNON_DESTROYED:
                if (ship_placed(ships[game->round - 'A'][ship_class][ship_number]) && ships[game->round - 'A'][ship_class][ship_number].section_state[CANNON] == OK)
                    return FALSE;
                break;
            case ALL_SHOTS_SPECIFIED:
                if (ship_placed(ships[game->round - 'A'][ship_class][ship_number]) && ships[game->round - 'A'][ship_class][ship_number].shots_left > 0)
                    return FALSE;
                break;

            }
        }
    }
    return TRUE;
}

char no_ship_can_shoot_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x) {
    for (int ship_class_int = CAR; ship_class_int <= DES; ship_class_int++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class_int]; ship_number++) {
            if (ship_placed(ships[game->round - 'A'][ship_class_int][ship_number])) {
                char ship_class[4];

                set_class_from_int(ship_class_int, ship_class);

                if (is_in_cannon_range(game, ships[game->round - 'A'][ship_class_int][ship_number], check_length(ship_class), y, x) && is_in_radar_range(ships[game->round - 'A'][ship_class_int][ship_number], check_length(ship_class), y, x)
                   && ships[game->round - 'A'][ship_class_int][ship_number].section_state[CANNON] == OK && ships[game->round - 'A'][ship_class_int][ship_number].shots_left > 0)
                    return FALSE;

            }

        }

    }

    return TRUE;
}

void find_ship_that_can_shoot_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x, int* ship_class_int, int* ship_number) {
    if (no_ship_can_shoot_here(game, ships, y, x))
        return;

    int ship_class_int_candidate, ship_number_candidate;
    int ship_length_candidate;

    while (true) {
        ship_class_int_candidate = rand() % SHIPS_CLASSES_NUMBER;
        char ship_class_candidate[4];

        if (game->ships_init_number[game->round - 'A'][ship_class_int_candidate] == 0)
            continue;

        set_class_from_int(ship_class_int_candidate, ship_class_candidate);
        ship_number_candidate = rand() % game->ships_init_number[game->round - 'A'][ship_class_int_candidate];
        ship_length_candidate = check_length(ship_class_candidate);

        if (is_in_cannon_range(game, ships[game->round - 'A'][ship_class_int_candidate][ship_number_candidate], ship_length_candidate, y, x) && is_in_radar_range(ships[game->round - 'A'][ship_class_int_candidate][ship_number_candidate], ship_length_candidate, y, x)
            && ships[game->round - 'A'][ship_class_int_candidate][ship_number_candidate].section_state[CANNON] == OK && ships[game->round - 'A'][ship_class_int_candidate][ship_number_candidate].shots_left > 0) {
            *ship_class_int = ship_class_int_candidate;
            *ship_number = ship_number_candidate;
            return;

        }

    }
}

char no_ships_have_OK_section_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int player, int y, int x) {
    for (int ship_class = CAR; ship_class <= DES; ship_class++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[player][ship_class]; ship_number++) {
            if (ship_has_section_here(ships[player][ship_class][ship_number], check_length_from_int(ship_class), y, x, OK))
                return FALSE;

        }

    }

    return TRUE;
}

char own_ship_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x) {
    for (int ship_class = CAR; ship_class <= DES; ship_class++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class]; ship_number++) {
            if (ship_has_section_here(ships[game->round - 'A'][ship_class][ship_number], check_length_from_int(ship_class), y, x, ANY))
                return TRUE;
        }
    }
    return FALSE;
}


char ship_placed(Ship ship) {
    if (ship.direction != 0)
        return TRUE;

    return FALSE;
}

char any_place_possible(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, char ship_direction, char* ship_class, int ship_number) {
    for (int y = 0; y < game->board_size_y; y++) {
        for (int x = 0; x < game->board_size_x; x++) {
            if (place_ship_command_validation(game, ships, board, y, x, ship_direction, ship_class, ship_number, AI))
                return FALSE;

        }

    }

    return TRUE;
}

char is_a_reef(int y, int x, int reefs_number, int** reefs) {
    for (int reef_number = 0; reef_number < reefs_number; reef_number++) {
        if (reefs[reef_number][Y] == y && reefs[reef_number][X] == x) {
            return TRUE;

        }

    }
    return FALSE;
}

char is_a_ship_near(int y, int x, char** board, int board_size_y, int board_size_x) {
    for (int checked_y = y - 1; checked_y <= y + 1; checked_y++) {
        for (int checked_x = x - 1; checked_x <= x + 1; checked_x++) {
            if (checked_y >= 0 && checked_y < board_size_y && checked_x >= 0 && checked_x < board_size_x) { //if a place (checked_y, checked_x) exists on the board
                if (board[checked_y][checked_x] != ' ' && board[checked_y][checked_x] != '#')
                    return TRUE;

            }

        }

    }

    return FALSE;
}

char ship_has_section_here(Ship ship, int ship_length, int y, int x, int state) {
    for (int section_number = 0; section_number < ship_length; section_number++) { //for each section
        if (state == OK) {
            if (ship.section_state[section_number] == DESTROYED)
                continue;

        }

        int y_addition = 0;
        int x_addition = 0;

        set_additions(ship.direction, section_number, &y_addition, &x_addition);

        if (ship.y + y_addition == y && ship.x + x_addition == x) {
            return TRUE;

        }

    }
    return FALSE;
}

char is_in_radar_range(Ship ship, int ship_length, int y, int x) {
    int radar_range;

    if (ship.section_state[RADAR] == DESTROYED) {
        radar_range = 1;

    }
    else {
        radar_range = ship_length;

    }

    if (distance(ship.x, ship.y, x, y) <= radar_range) {
        return TRUE;

    }
    return FALSE;
}

char is_in_spy_range(int spy_y, int spy_x, int checked_y, int checked_x) {
    for (int y = spy_y - 1; y <= spy_y + 1; y++) {
        for (int x = spy_x - 1; x <= spy_x + 1; x++) {
            if (y == checked_y && x == checked_x) {
                return TRUE;

            }

        }

    }
    return FALSE;
}

char is_in_cannon_range(Game_data* game, Ship ship, int ship_length, int y, int x) {
    int range = ship_length;
    int cannon_y, cannon_x;

    int y_addition = 0;
    int x_addition = 0;

    set_additions(ship.direction, CANNON, &y_addition, &x_addition);

    cannon_y = ship.y + y_addition;
    cannon_x = ship.x + x_addition;

    if (ship_length != CAR_LENGTH) { //if the ship is not a carrier
        if (distance(cannon_x, cannon_y, x, y) > range) {
            return FALSE;

        }

    }

    return TRUE;
}

void check_victory_condition(int* remaining_parts) {
    if (remaining_parts[A] == 0) {
        printf("B won");
        exit(0);

    }
    if (remaining_parts[B] == 0) {
        printf("A won");
        exit(0);

    }
}

void check_if_ai_can_continue(Game_data* game) {
    if (game->all_cannons_destroyed[A] && game->all_cannons_destroyed[B]) {
        printf("ALL CANNOS DESTROYED\n");
        exit(0);

    }
    if (game->no_ships_in_range[A] && game->no_ships_in_range[B] && game->no_possible_moves[A] && game->no_possible_moves[B]) {
        printf("NO MOVES NOR SHOTS POSSIBLE\n");
        exit(0);

    }
    if ((game->all_cannons_destroyed[A] && game->no_ships_in_range[B] && game->no_possible_moves[B]) || (game->all_cannons_destroyed[B] && game->no_ships_in_range[A] && game->no_possible_moves[A])) {
        printf("ONE PLAYER HAS ALL CANNONS DESTOYED, THE OTHER ONE CANNOT MOVE NOR SHOOT\n");
        exit(0);

    }
    if ((game->no_possible_place[A] && game->no_possible_moves[A]) || (game->no_possible_place[B] && game->no_possible_moves[B])) {
        printf("NO POSSIBILITY TO PLACE A SHIP NOR TO MOVE");
        exit(0);

    }
}

char seen_by_the_player(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x) {
    for (int ship_class = CAR; ship_class <= DES; ship_class++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class]; ship_number++) {
            if (ship_placed(ships[game->round - 'A'][ship_class][ship_number])) {
                if (ship_has_section_here(ships[game->round - 'A'][ship_class][ship_number], check_length_from_int(ship_class), y, x, ANY)) {
                    return TRUE;

                }
                if (is_in_radar_range(ships[game->round - 'A'][ship_class][ship_number], check_length_from_int(ship_class), y, x)) {
                    return TRUE;

                }

            }

        }

    }
    if (is_a_reef(y, x, game->reefs_number, game->reefs)) {
        return TRUE;

    }
    for (int spy_number = 0; spy_number < game->spies_sent; spy_number++) {
        if (game->spies[spy_number].player == game->round) {
            if (is_in_spy_range(game->spies[spy_number].y, game->spies[spy_number].x, y, x)) {
                return TRUE;

            }

        }

    }

    return FALSE;
}


char place_ship_command_validation(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, char* ship_class, int ship_number, char caller) {
    if (!in_starting_position(ship_y, ship_x, ship_direction, ship_class, game->starting_position[game->round - 'A'][NW], game->starting_position[game->round - 'A'][SE])) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": NOT IN STARTING POSITION\n", ship_y, ship_x, ship_direction, ship_number, ship_class);
        return FALSE;

    }
    if (ship_already_present(ship_number, ship_class, game->round, ships)) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": SHIP ALREADY PRESENT\n", ship_y, ship_x, ship_direction, ship_number, ship_class);
        return FALSE;

    }
    if (all_ships_of_the_class_already_set(ship_number, ship_class, game->round, game)) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": ALL SHIPS OF THE CLASS ALREADY SET\n", ship_y, ship_x, ship_direction, ship_number, ship_class);
        return FALSE;

    }
    if (ship_on_reef(ship_y, ship_x, ship_direction, ship_class, game->reefs_number, game->reefs)) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": PLACING SHIP ON REEF\n", ship_y, ship_x, ship_direction, ship_number, ship_class);
        return FALSE;

    }
    if (ship_too_close(ship_y, ship_x, ship_direction, ship_class, game, board)) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": PLACING SHIP TOO CLOSE TO OTHER SHIP\n", ship_y, ship_x, ship_direction, ship_number, ship_class);
        return FALSE;

    }
    return TRUE;
}

char ai_place_ship_checking(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    if (all_ships_placed_player(game, ships))
        return FALSE;

    if (no_possible_place(game, ships, board)) {
        game->no_possible_place[game->round - 'A'] = TRUE;
        return FALSE;

    }
    else {
        game->no_possible_place[game->round - 'A'] = FALSE;

    }

    return TRUE;
}

void place_ship_command_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, char* ship_class, int ship_number) {
    int ship_class_int = check_class_int(ship_class);

    ships[game->round - 'A'][ship_class_int][ship_number].y = ship_y;
    ships[game->round - 'A'][ship_class_int][ship_number].x = ship_x;
    ships[game->round - 'A'][ship_class_int][ship_number].direction = ship_direction;
    game->remaining_parts[game->round - 'A'] += check_length(ship_class);

    update_board(board, game, ships);
}

char shoot_command_basic_validation(int y, int x, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    if (y < 0 || y >= game->board_size_y || x < 0 || x >= game->board_size_x) {
        printf("INVALID OPERATION \"SHOOT %d %d\": FIELD DOES NOT EXIST", y, x);
        return FALSE;

    }
    if (!all_ships_placed(game, ships)) {
        printf("INVALID OPERATION \"SHOOT %d %d\": NOT ALL SHIPS PLACED", y, x);
        return FALSE;

    }

    return TRUE;
}

char shoot_command_extended_validation(int ship_number, char* ship_class, int y, int x, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    int ship_class_int = check_class_int(ship_class);

    if (ships[game->round - 'A'][ship_class_int][ship_number].section_state[CANNON] == DESTROYED) {
        printf("INVALID OPERATION \"SHOOT %d %s %d %d\": SHIP CANNOT SHOOT", ship_number, ship_class, y, x);
        return FALSE;

    }
    if (ships[game->round - 'A'][ship_class_int][ship_number].shots_left == 0) {
        printf("INVALID OPERATION \"SHOOT %d %s %d %d\": TOO MANY SHOOTS", ship_number, ship_class, y, x);
        return FALSE;

    }

    if (!is_in_cannon_range(game, ships[game->round - 'A'][ship_class_int][ship_number], check_length(ship_class), y, x)) {
        printf("INVALID OPERATION \"SHOOT %d %s %d %d\": SHOOTING TOO FAR", ship_number, ship_class, y, x);
        return FALSE;

    }
    return TRUE;
}

void shoot_command_basic_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int y, int x) {
    int y_addition = 0;
    int x_addition = 0;
    
    for (int player = A; player <= B; player++) {
        for (int ship_class = CAR; ship_class <= DES; ship_class++) {
            for (int ship_number = 0; ship_number < game->ships_init_number[player][ship_class]; ship_number++) {
                for (int section_number = 0; section_number < check_length_from_int(ship_class); section_number++) { //for each section checking if it was shot
                    int y_addition = 0;
                    int x_addition = 0;
                    
                    set_additions(ships[player][ship_class][ship_number].direction, section_number, &y_addition, &x_addition);
                    
                    if (ships[player][ship_class][ship_number].y + y_addition == y && ships[player][ship_class][ship_number].x + x_addition == x) {
                        if (ships[player][ship_class][ship_number].section_state[section_number] != DESTROYED) {
                            ships[player][ship_class][ship_number].section_state[section_number] = DESTROYED;
                            game->remaining_parts[player]--;

                        }
                    }
                }
            }
        }
    }
}

void shoot_command_extended_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int y, int x, char* ship_class, int ship_number) {
    shoot_command_basic_execution(game, ships, board, y, x);
    ships[game->round - 'A'][check_class_int(ship_class)][ship_number].shots_left--;
    update_board(board, game, ships);
}

char ai_shoot_extended_checking(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    if (!all_ships_placed(game, ships))
        return FALSE;

    if (no_ship_can_shoot(game, ships, ALL_SHOTS_SPECIFIED))
        return FALSE;

    if (no_ship_can_shoot(game, ships, CANNON_DESTROYED)) {
        game->all_cannons_destroyed[game->round - 'A'] = TRUE;
        return FALSE;

    }

    if (!is_a_ship_in_range(game, ships))
        game->no_ships_in_range[game->round - 'A'] = TRUE;
    else
        game->no_ships_in_range[game->round - 'A'] = FALSE;

    return TRUE;
}

char move_command_validation(int ship_number, char* ship_class, char move_direction, int new_ship_y, int new_ship_x, char new_ship_direction, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, char caller) {
    int ship_class_int = check_class_int(ship_class);

    if (ships[game->round - 'A'][ship_class_int][ship_number].moves_left == 0) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP MOVED ALREADY\n", ship_number, ship_class, move_direction);
        return FALSE;

    }
    if (ship_on_reef(new_ship_y, new_ship_x, new_ship_direction, ship_class, game->reefs_number, game->reefs)) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"MOVE %d %s %c\": PLACING SHIP ON REEF\n", ship_number, ship_class, move_direction);
        return FALSE;

    }
    if (new_ship_y < 0 || new_ship_y >= game->board_size_y || new_ship_x < 0 || new_ship_x >= game->board_size_x) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD\n", ship_number, ship_class, move_direction);
        return FALSE;

    }

    char temp_ship_direction = ships[game->round - 'A'][ship_class_int][ship_number].direction;
    ships[game->round - 'A'][ship_class_int][ship_number].direction = 0;
    clear_board(board, game->board_size_y, game->board_size_x);
    update_board(board, game, ships);

    char too_close = FALSE;

    if (ship_too_close(new_ship_y, new_ship_x, new_ship_direction, ship_class, game, board)) {
        if (caller == PLAYER)
            printf("INVALID OPERATION \"MOVE %d %s %c\": PLACING SHIP TOO CLOSE TO OTHER SHIP\n", ship_number, ship_class, move_direction);
        too_close = TRUE;

    }
    ships[game->round - 'A'][ship_class_int][ship_number].direction = temp_ship_direction;
    update_board(board, game, ships);

    if (too_close == TRUE)
        return FALSE;

    if (game->extended_ships == TRUE) {
        if (ships[game->round - 'A'][ship_class_int][ship_number].section_state[check_length(ship_class) - 1] == DESTROYED) {
            if (caller == PLAYER)
                printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP CANNOT MOVE\n", ship_number, ship_class, move_direction);
            return FALSE;

        }

    }

    return TRUE;
}

char ai_move_checking(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board) {
    char any_ship_placed = FALSE;

    for (int ship_class_int = CAR; ship_class_int <= DES; ship_class_int++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[game->round - 'A'][ship_class_int]; ship_number++) {
            if (ship_placed(ships[game->round - 'A'][ship_class_int][ship_number])) {
                any_ship_placed = TRUE;

            }

        }

    }
    if (any_ship_placed == FALSE) {
        game->no_possible_moves[game->round - 'A'] = TRUE;
        return FALSE;

    }
    else {
        game->no_possible_moves[game->round - 'A'] = FALSE;

    }

    if (no_possible_moves(game, ships, board) == TRUE) {
        game->no_possible_moves[game->round - 'A'] = TRUE;
        return FALSE;

    }
    else {
        game->no_possible_moves[game->round - 'A'] = FALSE;

    }

    return TRUE;
}

void move_command_preset_new_data(char move_direction, int ship_class_int, int ship_number, int ship_length, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int player_int, int* new_ship_y, int* new_ship_x, char* new_ship_direction) {
    int y_addition = 0;
    int x_addition = 0;
    
    set_additions(ships[player_int][ship_class_int][ship_number].direction, 1, &y_addition, &x_addition);
    y_addition = -y_addition;
    x_addition = -x_addition;

    *new_ship_y = ships[player_int][ship_class_int][ship_number].y + y_addition;
    *new_ship_x = ships[player_int][ship_class_int][ship_number].x + x_addition;

    switch (move_direction) {
    case 'F':
        *new_ship_direction = ships[player_int][ship_class_int][ship_number].direction;
        break;
    case 'L':
        switch (ships[player_int][ship_class_int][ship_number].direction) {
        case 'N':
            *new_ship_x -= (ship_length - 1);
            *new_ship_direction = 'W';
            break;
        case 'E':
            *new_ship_y -= (ship_length - 1);
            *new_ship_direction = 'N';
            break;
        case 'S':
            *new_ship_x += (ship_length - 1);
            *new_ship_direction = 'E';
            break;
        case 'W':
            *new_ship_y += (ship_length - 1);
            *new_ship_direction = 'S';
            break;

        }
        break;
    case 'R':
        switch (ships[player_int][ship_class_int][ship_number].direction) {
        case 'N':
            *new_ship_x += (ship_length - 1);
            *new_ship_direction = 'E';
            break;
        case 'E':
            *new_ship_y += (ship_length - 1);
            *new_ship_direction = 'S';
            break;
        case 'S':
            *new_ship_x -= (ship_length - 1);
            *new_ship_direction = 'W';
            break;
        case 'W':
            *new_ship_y -= (ship_length - 1);
            *new_ship_direction = 'N';
            break;

        }

    }
}

void move_command_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_class_int, int ship_number, int new_ship_y, int new_ship_x, int new_ship_direction) {
    clear_board(board, game->board_size_y, game->board_size_x);

    ships[game->round - 'A'][ship_class_int][ship_number].y = new_ship_y;
    ships[game->round - 'A'][ship_class_int][ship_number].x = new_ship_x;
    ships[game->round - 'A'][ship_class_int][ship_number].direction = new_ship_direction;
    ships[game->round - 'A'][ship_class_int][ship_number].moves_left--;

    update_board(board, game, ships);
}


char ship_command_validation(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, int ship_number, char* section_state, char* ship_class, char player) {
    if (ship_on_reef(ship_y, ship_x, ship_direction, ship_class, game->reefs_number, game->reefs)) {
        printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": PLACING SHIP ON REEF\n", player, ship_y, ship_x, ship_direction, ship_number, ship_class, section_state);
        return FALSE;

    }
    if (ship_too_close(ship_y, ship_x, ship_direction, ship_class, game, board)) {
        printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": PLACING SHIP TOO CLOSE TO OTHER SHIP\n", player, ship_y, ship_x, ship_direction, ship_number, ship_class, section_state);
        return FALSE;

    }
    if (ship_already_present(ship_number, ship_class, player, ships)) {
        printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": SHIP ALREADY PRESENT\n", player, ship_y, ship_x, ship_direction, ship_number, ship_class, section_state);
        return FALSE;

    }
    if (all_ships_of_the_class_already_set(ship_number, ship_class, player, game)) {
        printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": ALL SHIPS OF THE CLASS ALREADY SET\n", player, ship_y, ship_x, ship_direction, ship_number, ship_class, section_state);
        return FALSE;

    }

    return TRUE;
}

void ship_command_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, int ship_number, char* section_state, char* ship_class, char player) {
    int ship_class_int = check_class_int(ship_class);

    ships[player - 'A'][ship_class_int][ship_number].y = ship_y;
    ships[player - 'A'][ship_class_int][ship_number].x = ship_x;
    ships[player - 'A'][ship_class_int][ship_number].direction = ship_direction;

    for (int section_number = 0; section_number < check_length(ship_class); section_number++) {
        ships[player - 'A'][ship_class_int][ship_number].section_state[section_number] = section_state[section_number] - '0';
        game->remaining_parts[player - 'A'] += (section_state[section_number] - '0');

    }
    update_board(board, game, ships);
}

void save_players(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    for (char player = 'A'; player <= 'B'; player++) {
        //saving initial positions:
        printf("INIT_POSITION %c ", player);
        for (int position = NW; position <= SE; position++) {
            for (int dimension = Y; dimension <= X; dimension++) {
                printf("%d ", game->starting_position[player - 'A'][position][dimension]);

            }

        }
        putchar('\n');

        //saving fleet size:
        printf("SET_FLEET %c ", player);
        for (int ship_class = CAR; ship_class <= DES; ship_class++) {
            printf("%d ", game->ships_init_number[player - 'A'][ship_class]);

        }
        putchar('\n');

        save_player_ships(player, game, ships);

    }
}

void save_player_ships(char player, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]) {
    for (int ship_class_int = CAR; ship_class_int <= DES; ship_class_int++) {
        for (int ship_number = 0; ship_number < game->ships_init_number[player - 'A'][ship_class_int]; ship_number++) {
            if (ship_placed(ships[player - 'A'][ship_class_int][ship_number])) {
                char ship_class[4];

                set_class_from_int(ship_class_int, ship_class);

                printf("SHIP %c %d %d %c %d %s ", player, ships[player - 'A'][ship_class_int][ship_number].y, ships[player - 'A'][ship_class_int][ship_number].x, ships[player - 'A'][ship_class_int][ship_number].direction, ship_number, ship_class);

                for (int section_number = 0; section_number < check_length(ship_class); section_number++) {
                    printf("%d", ships[player - 'A'][ship_class_int][ship_number].section_state[section_number]);

                }
                putchar('\n');

            }

        }

    }
}