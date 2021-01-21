#include "pomoku.h"

#define ROW_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define COL_LENGTH(arr) (sizeof(arr[0]) / sizeof(arr[0][0]))

#define TRUE (1)
#define FALSE (0)

color_t player1 = COLOR_BLACK;
color_t player2 = COLOR_WHITE;
size_t g_player1_score;
size_t g_player2_score;

int board[20][20];
size_t g_row_count = 15;
size_t g_col_count = 15;


void init_game(void)
{
     size_t i;
     size_t j;
     for (i = 0; i < g_row_count; ++i) {
         for (j = 0; j < COL_LENGTH(board); ++j) {
             if (j < g_col_count) {
             board[i][j] = 1;
             } else {
             board[i][j] = 0;
             }
         }     
     }
     
     for (i = g_row_count; i < ROW_LENGTH(board); ++i) {
         for (j = 0; j < COL_LENGTH(board); ++j) {
             board[i][j] = 0;
         }
     }
     g_player1_score = 0;
     g_player2_score = 0;
     g_row_count = 15;
     g_col_count = 15;      
}

size_t get_row_count(void)
{
       size_t i;
       g_row_count = 0;

       for (i = 0; i < ROW_LENGTH(board); ++i) {
           if (board[i][0] != 0) {
               g_row_count += 1;
           } else if (board[i][0] == 0) {
               break;
           }
       }
       return g_row_count; 
}

size_t get_column_count(void)
{
       size_t i;
       g_col_count = 0;

       for (i = 0; i < COL_LENGTH(board); ++i) {
           if (board[0][i] != 0) {
               g_col_count += 1;
           } else if (board[0][i] == 0) {
               break;
           }
       }
       return g_col_count; 
}

int get_score(const color_t color)
{
    if (color == player1) {
        return g_player1_score;
    } else if (color == player2) {
        return g_player2_score;
    } else {
        return -1;
    }
}

int get_color(const size_t row, const size_t col)
{
    if (board[row][col] == 'B') {
        return 0;
    } else if (board[row][col] == 'W') {
        return 1;
    } else {
        return -1;
    }         
}

int is_placeable(const size_t row, const size_t col)
{
    if (board[row][col] == 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (is_placeable(row, col) == FALSE) {
        return FALSE;
    }
    
    if (color == player1) {
        board[row][col] = 'B';
    }
    if (color == player2) {
        board[row][col] = 'W';
    }
    check_score(color, row, col);
    return TRUE;
}

/* special moves */
int insert_row(const color_t color, const size_t row)
{
    size_t i;
    size_t j;
    size_t* player_score;

    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);
    
    if (g_row_count == 20 || row > 20) {
        return FALSE;
    }
    if (*player_score < 3) {
        return FALSE;
    } else {
        *player_score -= 3;
    }
   
    for (i = g_row_count; i > row; --i) {
        for (j = 0; j < g_col_count; ++j) {
            board[i][j] = board[i - 1][j];
        }
    }
    for (i = 0; i < COL_LENGTH(board); ++i) {
        board[row][i] = 0;
    }
    g_row_count += 1;
    
    return TRUE;  
}

int insert_column(const color_t color, const size_t col)
{
    size_t i;
    size_t j;
    size_t* player_score;
    
    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);

    if (g_col_count == 20 || col > 20) {
        return FALSE;
    }
    
    if (*player_score < 3) {
        return FALSE;
    } else {
        *player_score -= 3;
    }
 
    for (i = 0; i < g_row_count; ++i) {
        for (j = g_col_count; j >= col; --j) {
            board[i][j] = board[i][j - 1];
        }
        board[i][col - 1] = 0;
    }
    
    g_col_count += 1;
    return TRUE;  
}

int remove_row(const color_t color, const size_t row)
{
    size_t i;
    size_t j;
    size_t* player_score;
    
    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);

    if (g_row_count == 10) {
        return FALSE;
    }
    
    if (*player_score < 3) {
        return FALSE;
    } else {
        *player_score -= 3;
    }

    for (i = row; i < g_row_count; ++i) {
        for (j = 0; j < g_col_count; ++j) {
            board[i - 1][j] = board[i][j];
        }
    }
    
    for (i = 0; i < COL_LENGTH(board); ++i) {
        board[row][i] = 0;
    }
    g_row_count -= 1;
    return TRUE;
}

int remove_column(const color_t color, const size_t col)
{
    size_t i;
    size_t j;
    size_t* player_score;
    
    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);

    if (g_col_count == 10) {
        return FALSE;
    }
    
    if (*player_score < 3) {
        return FALSE;
    } else {
        *player_score -= 3;
    }
    
    for (i = 0; i < g_row_count; ++i) {
        for (j = col; j < g_col_count; ++j) {
            board[i][j - 1] = board[i][j];
        }
        board[i][g_col_count - 1] = 0;
    }
    
    g_col_count -= 1;
    return TRUE; 
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    size_t i;
    size_t* player_score;
    int temp_arr[COL_LENGTH(board)] = { 0, }; 
   
    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);

    
    if (row0 > g_row_count || row1 > g_row_count) {
        return FALSE;
    }

    if (*player_score < 2) {
        return FALSE;
    } else {
        *player_score -= 2;
    }

    for (i = 0; i < g_col_count; ++i) {
        temp_arr[i] = board[row0][i];
        board[row0][i] = board[row1][i];
        board[row0][i] = temp_arr[i];
    }
    
    return TRUE;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    size_t i;
    size_t* player_score;
    int temp_arr[COL_LENGTH(board)] = { 0, }; 
   
    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);

    
    if (col0 > g_col_count || col1 > g_col_count) {
        return FALSE;
    }

    if (*player_score < 2) {
        return FALSE;
    } else {
        *player_score -= 2;
    }

    for (i = 0; i < g_row_count; ++i) {
        temp_arr[i] = board[i][col0];
        board[i][col0] = board[i][col1];
        board[i][col1] = temp_arr[i];
    }
    
    return TRUE;
}

int copy_row(const color_t color, const size_t src, const size_t dst)
{
    size_t i;
    size_t* player_score;
   
    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);

    
    if (src > g_row_count || dst > g_row_count) {
        return FALSE;
    }

    if (*player_score < 4) {
        return FALSE;
    } else {
        *player_score -= 4;
    }

    for (i = 0; i < g_col_count; ++i) {
        board[dst][i] = board[src][i];
    }
    
    return TRUE;
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
    size_t i;
    size_t* player_score;
   
    color == player1 ? (player_score = &g_player1_score) : (player_score = &g_player2_score);

    
    if (src > g_col_count || dst > g_col_count) {
        return FALSE;
    }

    if (*player_score < 4) {
        return FALSE;
    } else {
        *player_score -= 4;
    }

    for (i = 0; i < g_row_count; ++i) {
        board[i][dst] = board[i][src];
    }
    
    return TRUE;
}

void check_score(const color_t color, const size_t row, const size_t col)
{
    check_score_row(color, row, col);
    check_score_col(color, row, col);
    check_score_NE(color, row, col);
    check_score_NW(color, row, col);
}

void increase_score(size_t same_color, size_t* player_score)
{
     if (same_color >= 5) {
        *player_score += 1;
     }
     if (same_color >= 6) {
        *player_score += 2;
     }
     if (same_color >= 7) {
        *player_score += 3;
     }   
}

void check_score_row(const color_t color, const size_t row, const size_t col)
{
    size_t i = 0;
    int stone_color = 'B';
    size_t* player_score = &g_player1_score;
    size_t same_color = 0;
    
    if (color == player2) {
        stone_color = 'W';
        player_score = &g_player2_score;
    }

    for (i = row; i < g_row_count; ++i) {
        if (board[i + 1][col] == stone_color) {
            same_color += 1;
        } 
        if (board[i + 1][col] != stone_color) {
            break;
        }
    }
    for (i = row; i > 0; --i) {
        if (board[row - 1][col] == stone_color) {
            same_color += 1;
        }
        if (board[row - 1][col] != stone_color) {
            break;
        }
    }
    
    increase_score(same_color, player_score); 
}

void check_score_col(const color_t color, const size_t row, const size_t col)
{
    size_t i = 0;
    int stone_color = 'B';
    size_t* player_score = &g_player1_score;
    size_t same_color = 0;
    
    if (color == player2) {
        stone_color = 'W';
        player_score = &g_player2_score;
    }
   
    for (i = col; i < g_col_count; ++i) {
        if (board[row][i + 1] == stone_color) {
            same_color += 1;
        }
        if (board[row][i + 1] != stone_color) {
            break;
        }
    }
    for (i = col; i > 0; --i) {
        if (board[row][i - 1] == stone_color) {
            same_color += 1;
        }
        if (board[row][i - 1] != stone_color) {
            break;
        }
    }
    
    increase_score(same_color, player_score); 
}

void check_score_NE(const color_t color, const size_t row, const size_t col)
{
    size_t i = 0;
    int stone_color = 'B';
    size_t* player_score = &g_player1_score;
    size_t same_color = 0;
    
    if (color == player2) {
        stone_color = 'W';
        player_score = &g_player2_score;
    }


    for (i = 1; i <= row && i < (g_col_count - col); ++i) {
        if (board[row - i][col + i] == stone_color) {
            same_color += 1;
        }
        if (board[row - i][col + i] != stone_color) {
            break;
        }
    }
    for (i = 1; i < (g_row_count - row) && i <= col; ++i) {
        if (board[row + i][col - i] == stone_color) {
            same_color += 1;
        }
        if (board[row + i][col - i] != stone_color) {
            break;
        }
    }

    increase_score(same_color, player_score); 
}

void check_score_NW(const color_t color, const size_t row, const size_t col)
{
    size_t i = 0;
    int stone_color = 'B';
    size_t* player_score = &g_player1_score;
    size_t same_color = 0;
    
    if (color == player2) {
        stone_color = 'W';
        player_score = &g_player2_score;
    }


    for (i = 1; i <= row && i <= col; ++i) {
        if (board[row - i][col - i] == stone_color) {
            same_color += 1;
        }
        if (board[row - i][col - i] != stone_color) {
            break;
        }
    }
    for (i = 1; i < (g_row_count - row) && i < (g_col_count = col); ++i) {
        if (board[row + i][col + i] == stone_color) {
            same_color += 1;
        }
        if (board[row + i][col + i] != stone_color) {
            break;
        }
    }

    increase_score(same_color, player_score);   
}
