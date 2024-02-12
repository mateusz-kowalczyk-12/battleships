#include "Definitions.cpp"

void print_board(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int perspective, int print_parameter);

void clear_board(char** board, int board_size_y, int board_size_x);

void print_column_numbers(int board_size_x, int board_size_y);

void update_board(char** board, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

void update_board_player(char** board, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

void check_to_add_ship(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int y, int x);

void check_to_add_reef(Game_data* game, char** board, int y, int x);

void draw_ship(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board);

void delete_ship_proposed_by_ai(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void draw_ship_advanced(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board, char player);

void draw_ship_radar(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board, char player);

void draw_ship_cannon(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board);

void draw_ship_engine(int ship_y, int ship_x, char ship_direction, int length, char* section_state, char** board);

void set_default_initial_ships_numbers(int ships_init_number[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER]);

void reset_moves_shots_left(Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);


void check_ai(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void read_command_group(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char*** board);


void continue_ai(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void begin_command_for_player(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void begin_command_for_state(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char*** board);


void continue_print_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int perspective);

void continue_set_fleet_command(Game_data* game);

void continue_next_player_command(Game_data* game);

void continue_board_size_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char*** board);

void continue_init_position_command(Game_data* game);

void continue_reef_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void continue_ship_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void continue_extended_ships_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

void continue_save_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

void continue_srand_command(Game_data* game);

void continue_set_ai_player_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);


void continue_place_ship_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void ai_place_ship(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void continue_shoot_command_basic(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void ai_shoot_basic(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void ai_shoot_extended(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void continue_shoot_command_extended(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void continue_move_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void ai_move(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void continue_spy_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void continue_print_player_command(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);


char in_starting_position(int ship_y, int ship_x, char ship_direction, char* ship_class, int starting_position_NW[DIMENSIONS_NUMBER], int starting_position_SE[DIMENSIONS_NUMBER]);

char ship_already_present(int ship_number, char* ship_class, char round, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

char all_ships_of_the_class_already_set(int ship_number, char* ship_class, char round, Game_data* game);

char ship_on_reef(int ship_y, int ship_x, char ship_direction, char* ship_class, int reefs_number, int** reefs);

char ship_too_close(int ship_y, int ship_x, char ship_direction, char* ship_class, Game_data* game, char** board);

char all_ships_placed(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

char all_ships_placed_player(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

char no_possible_place(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

char no_possible_moves(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

char is_a_ship_in_range(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

char no_ship_can_shoot(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int condition);

char no_ship_can_shoot_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x);

void find_ship_that_can_shoot_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x, int* ship_class_int, int* ship_number);

char no_ships_have_OK_section_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int player, int y, int x);

char own_ship_here(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x);


char ship_placed(Ship ship);

char any_place_possible(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, char ship_direction, char* ship_class, int ship_number);

char is_a_reef(int y, int x, int reefs_number, int** reefs);

char is_a_ship_near(int y, int x, char** board, int board_size_y, int board_size_x);

char ship_has_section_here(Ship ship, int ship_length, int y, int x, int state);

char is_in_radar_range(Ship ship, int ship_length, int y, int x);

char is_in_spy_range(int spy_y, int spy_x, int checked_y, int checked_x);

char is_in_cannon_range(Game_data* game, Ship ship, int ship_length, int y, int x);

void check_victory_condition(int* remaining_parts);

void check_if_ai_can_continue(Game_data* game);

char seen_by_the_player(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int y, int x);


char place_ship_command_validation(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, char* ship_class, int ship_number, char caller);

char ai_place_ship_checking(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void place_ship_command_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, char* ship_class, int ship_number);

char shoot_command_basic_validation(int y, int x, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

char shoot_command_extended_validation(int ship_number, char* ship_class, int y, int x, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

char ai_shoot_extended_checking(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void shoot_command_basic_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int y, int x);

void shoot_command_extended_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int y, int x, char* ship_class, int ship_number);

char move_command_validation(int ship_number, char* ship_class, char move_direction, int new_ship_y, int new_ship_x, char new_ship_direction, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, char caller);

char ai_move_checking(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board);

void move_command_preset_new_data(char move_direction, int ship_class_int, int ship_number, int ship_length, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], int player_int, int* new_ship_y, int* new_ship_x, char* new_ship_direction);

void move_command_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_class_int, int ship_number, int new_ship_y, int new_ship_x, int new_ship_direction);


char ship_command_validation(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, int ship_number, char* section_state, char* ship_class, char player);

void ship_command_execution(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS], char** board, int ship_y, int ship_x, char ship_direction, int ship_number, char* section_state, char* ship_class, char player);

void save_players(Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);

void save_player_ships(char player, Game_data* game, Ship ships[PLAYERS_NUMBER][SHIPS_CLASSES_NUMBER][MAX_SHIPS_NUMBER_PER_CLASS]);


int check_length(char* ship_class);

int check_length_from_int(int ship_class);

int check_class_int(char* ship_class);

void check_ship_direction(char* ship_direction);

void set_additions(char ship_direction, int section_number, int* y_addition, int* x_addition);

void check_move_direction(char* move_direction);

int distance(int x1, int y1, int x2, int y2);

int opponent(char player);

int count_digits(int number);

void set_class_from_int(int ship_class_int, char* ship_class);

void find_position(Game_data* game, Ship ship, int section_number, int* y0, int* x0);

char ai_match(Game_data* game);

void change_player(Game_data* game);