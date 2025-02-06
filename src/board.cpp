#include "board.h"

#include <array>
#include <cstdlib>
#include <ctime>
#ifdef DEBUG
#include <iostream>
#endif
#include <vector>


// Public member functions

void Board::init() {
    std::srand(std::time({}));
}

Board::Board() : board(), score(0), open_spaces(BOARD_SIZE - 2) {
    // Start with an empty board with two randomly generated squares

    board.fill(0);
    generate_new_square();
    generate_new_square();
}

Board::Board(const Board& other) : board(other.board), score(other.score), open_spaces(other.open_spaces) {
    
}

Board::Board(const Board&& other) : board(std::move(other.board)), score(other.score), open_spaces(other.open_spaces) {

}


#if defined(DEBUG) || defined(solver)

int Board::calculate_open_spaces(const std::array<int, BOARD_SIZE>& board) {
    int open_spaces = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i] == 0) {
            ++open_spaces;
        }
    }

    return open_spaces;
}

Board::Board(const std::array<int, BOARD_SIZE>& board) : board(board), score(0), open_spaces(calculate_open_spaces(board)) {
}

Board::Board(const std::array<int, BOARD_SIZE>&& board) : board(std::move(board)), score(0), open_spaces(calculate_open_spaces(board)) {
}

Board::Board(const std::array<int, BOARD_SIZE>& board, int score) : board(board), score(score), open_spaces(calculate_open_spaces(board)) {
}

Board::Board(const std::array<int, BOARD_SIZE>&& board, int score) : board(std::move(board)), score(score), open_spaces(calculate_open_spaces(board)) {
}

#endif

void Board::perform_up() {
    
    // Perform all actions on one column at a time
    for (int i = 0; i < 4; ++i) {
        int last_number = -1;
        int last_number_index = -1;
        int first_zero = -1;
        

        for (int j = i; j < BOARD_SIZE; j += 4) {
            if (board[j] == last_number) {
                // Combine the two numbers
                board[last_number_index] *= 2;
                board[j] = 0;
                score += board[last_number_index];
                last_number = -1;
                if (first_zero == -1) {
                    first_zero = j;
                }
                --open_spaces;
            } else if (board[j] != 0) {
                last_number = board[j];
                last_number_index = j;
                if (first_zero != -1) {
                    board[first_zero] = board[j];
                    board[j] = 0;
                    last_number = board[first_zero];
                    last_number_index = first_zero;
                    first_zero += 4;
                }
            } else if (first_zero == -1) {
                first_zero = j;
            }

        }
    }
}


void Board::perform_down() {
    
    // Perform all actions on one column at a time
    for (int i = 0; i < 4; ++i) {
        int last_number = -1;
        int last_number_index = -1;
        int first_zero = -1;
        

        for (int j = i + 12; j >= 0; j -= 4) {
            if (board[j] == last_number) {
                // Combine the two numbers
                board[last_number_index] *= 2;
                board[j] = 0;
                score += board[last_number_index];
                last_number = -1;
                if (first_zero == -1) {
                    first_zero = j;
                }
                --open_spaces;
            } else if (board[j] != 0) {
                last_number = board[j];
                last_number_index = j;
                if (first_zero != -1) {
                    board[first_zero] = board[j];
                    board[j] = 0;
                    last_number = board[first_zero];
                    last_number_index = first_zero;
                    first_zero -= 4;
                }
            } else if (first_zero == -1) {
                first_zero = j;
            }

        }
    }
}



void Board::perform_left() {
    
    // Perform all actions on one row at a time
    for (int i = 0; i < BOARD_SIZE; i += 4) {
        int last_number = -1;
        int last_number_index = -1;
        int first_zero = -1;
        

        for (int j = i; j < i + 4; ++j) {
            // Combine the two numbers
            if (board[j] == last_number) {
                board[last_number_index] *= 2;
                board[j] = 0;
                score += board[last_number_index];
                last_number = -1;
                if (first_zero == -1) {
                    first_zero = j;
                }
                --open_spaces;
            } else if (board[j] != 0) {
                last_number = board[j];
                last_number_index = j;
                if (first_zero != -1) {
                    board[first_zero] = board[j];
                    board[j] = 0;
                    last_number = board[first_zero];
                    last_number_index = first_zero;
                    ++first_zero;
                }
            } else if (first_zero == -1) {
                first_zero = j;
            }

        }
    }
}


void Board::perform_right() {
    
    // Perform all actions on one row at a time
    for (int i = 0; i < BOARD_SIZE; i += 4) {
        int last_number = -1;
        int last_number_index = -1;
        int first_zero = -1;
        

        for (int j = i + 3; j >= i; --j) {
            // Combine the two numbers
            if (board[j] == last_number) {
                board[last_number_index] *= 2;
                board[j] = 0;
                score += board[last_number_index];
                last_number = -1;
                if (first_zero == -1) {
                    first_zero = j;
                }
                --open_spaces;
            } else if (board[j] != 0) {
                last_number = board[j];
                last_number_index = j;
                if (first_zero != -1) {
                    board[first_zero] = board[j];
                    board[j] = 0;
                    last_number = board[first_zero];
                    last_number_index = first_zero;
                    --first_zero;
                }
            } else if (first_zero == -1) {
                first_zero = j;
            }

        }
    }
}

bool Board::can_perform_up() const {

    for (int i = 0; i < 4; ++i) {
        bool seen_air = false;
        int last_num = -1;

        for (int j = i; j < BOARD_SIZE; j += 4) {
            if (seen_air) {
                if (board[j] != 0) {
                    return true;
                }
            } else if (board[j] == 0) {
                seen_air = true;
            } else {
                if (board[j] == last_num) {
                    return true;
                } else {
                    last_num = board[j];
                }
            }
        }
    }

    return false;
}


bool Board::can_perform_down() const {

    for (int i = 0; i < 4; ++i) {
        bool seen_air = false;
        int last_num = -1;

        for (int j = i + 12; j >= 0; j -= 4) {
            if (seen_air) {
                if (board[j] != 0) {
                    return true;
                }
            } else if (board[j] == 0) {
                seen_air = true;
            } else {
                if (board[j] == last_num) {
                    return true;
                } else {
                    last_num = board[j];
                }
            }
        }
    }

    return false;
}


bool Board::can_perform_left() const {

    for (int i = 0; i < BOARD_SIZE; i += 4) {
        bool seen_air = false;
        int last_num = -1;

        for (int j = i; j < i + 4; ++j) {
            if (seen_air) {
                if (board[j] != 0) {
                    return true;
                }
            } else if (board[j] == 0) {
                seen_air = true;
            } else {
                if (board[j] == last_num) {
                    return true;
                } else {
                    last_num = board[j];
                }
            }
        }
    }

    return false;
}


bool Board::can_perform_right() const {

    for (int i = 0; i < BOARD_SIZE; i += 4) {
        bool seen_air = false;
        int last_num = -1;

        for (int j = i + 3; j >= i; --j) {
            if (seen_air) {
                if (board[j] != 0) {
                    return true;
                }
            } else if (board[j] == 0) {
                seen_air = true;
            } else {
                if (board[j] == last_num) {
                    return true;
                } else {
                    last_num = board[j];
                }
            }
        }
    }

    return false;
}

int Board::get_score() const {
    return score;
}

bool Board::game_over() const {

    if (open_spaces != 0) {
        return false;
    }

    // Check if any of the same numbers are adjacent

    for (int i = 0; i < BOARD_SIZE; i += 4) {
        for (int j = i; j < i + 3; ++j) {
            if (board[j] == board[j + 1]) return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = i; j < 12; j += 4) {
            if (board[j] == board[j + 4]) return false;
        }
    }

    return true;;
}

const std::array<int, Board::BOARD_SIZE>& Board::get_board() const {
    return board;
}

void Board::generate_new_square() {
    std::vector<int> open_indicies;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i] == 0) {
            open_indicies.push_back(i);
        }
    }

    board[open_indicies[std::rand() % open_indicies.size()]] = std::rand() % 100 < FOUR_PERCENTAGE ? 4 : 2;
}

#ifdef DEBUG

bool Board::operator==(const Board& other) {
    return board == other.board;
}

bool Board::operator!=(const Board& other) {
    return board != other.board;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {

    for (int i = 0; i < Board::BOARD_SIZE; i += 4) {
        for (int j = i; j < i + 4; ++j) {
            os << board.board[j] << ' ';
        }
        os << '\n';
    }

    return os;
}
#endif
