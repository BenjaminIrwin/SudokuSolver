void load_board(const char* filename, char board[9][9]);

void display_board(const char board[9][9]);

bool solve_board(char board [][9]);

bool recursive_search (char board[][9], int& counter, bool backwards, int row, int column);

bool is_complete(char board [][9]); 

bool make_move(const char position [], const char digit, char board [][9]);

bool change_value(char board[][9], const char digit, int row, int column);

bool check_rc(char board[][9], const char digit, int row, int column);

bool check_square(char board[][9], const char digit, int row, int column);

bool save_board(const char filename[], char board[][9]);

void solve_mystery_board(const char* filename);

