#include <iostream>
#include <fstream>
#include <string>

const int WIDTH = 33;
const int HEIGHT = 11;

char game_screen[HEIGHT][WIDTH] = {{'+', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '+'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                                   {'+', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '+'}};

char guess();
void update_game_screen(int wrong_counter);         
void print_game_screen(void);

int main(void) {
    // Program randomly selects a 7 letter word
    std::ifstream word_file("top_100_7_letter_words.txt");

    if (!word_file.is_open()) {
        std::cout << "Word file could not be opened. \n";
        return 1;
    }

    std::string word;

    srand(time(0));
    int chosen_line = (rand() % 100) + 1;
    int current_line = 0;

    while(std::getline(word_file, word)) {
        if (current_line ==  chosen_line) break;
        current_line++;
    }

    word_file.close();

    // Initialising some variables
    std::string answer = "       ";
    int wrong_counter = 0;


    // Game loop
    while (true) {
        // Prints the screen
        update_game_screen(wrong_counter);
        print_game_screen();

        // User loses if hangman is completely drawn
        if (wrong_counter >= 6) {
            std::cout << "You lost. \n";
            std::cout << "Correct word: " << word << '\n';
            break;
        }

        // User win if they guess the word correctly
        if (word == answer) {
            std::cout << "You win! \n";
            break;
        }

        // Let user guess a letter
        char guessed_letter = guess();

        // Check if the letter user guess is one of the letter(s) in the word chosen
        bool correct_guess = false;
        for (int i = 0; i < word.size(); i++) {
            if (guessed_letter == word[i]) {
                game_screen[8][(WIDTH / 2) - 6 + (i * 2)] = word[i];
                answer[i] = word[i];
                correct_guess = true;
            }
        }

        if (!correct_guess) {
            wrong_counter++;
        }
    }

    return 0;
}

char guess() {
    std::string guessed_letter;

    std::cout << "Pick a letter to guess. (a-z) \n";
    
    do {
        std::cin >> guessed_letter;
    } while (guessed_letter[0] < 65 || guessed_letter[0] > 122 || (guessed_letter[0] >= 91 && guessed_letter[0] <= 96) || guessed_letter.size() != 1);

    if (guessed_letter[0] >= 65 && guessed_letter[0] <= 90) {
        guessed_letter = guessed_letter[0] + 32;
    }

    return guessed_letter[0];
}

void update_game_screen(int wrong_counter) {
    switch(wrong_counter) {
        case 0:
            for (int i = (WIDTH / 2) - 6; i <= (WIDTH / 2) + 6; i+=2) {
                game_screen[9][i] = '-';
            }

            break;

        case 1:
            game_screen[0][WIDTH / 2] = '+';
            game_screen[1][WIDTH / 2] = '|';
            
            game_screen[2][(WIDTH / 2) - 2] = '+';
            game_screen[2][(WIDTH / 2) + 2] = '+';
            
            for (int i = (WIDTH / 2) - 1; i <= (WIDTH / 2) + 1; i++) {
                game_screen[2][i] = '-';
            }

            game_screen[3][(WIDTH / 2) - 2] = '|';
            game_screen[3][(WIDTH / 2) + 2] = '|';

            game_screen[4][(WIDTH / 2) - 2] = '+';
            game_screen[4][(WIDTH / 2) + 2] = '+';
            
            for (int i = (WIDTH / 2) - 1; i <= (WIDTH / 2) + 1; i++) {
                game_screen[4][i] = '-';
            }

            
            break;

        case 2:
            game_screen[5][WIDTH / 2] = '|';
            game_screen[6][WIDTH / 2] = '|';
            break;

        case 3:
            game_screen[5][(WIDTH / 2) - 1] = '-';
            game_screen[5][(WIDTH / 2) - 2] = '-';
            game_screen[5][(WIDTH / 2) - 3] = '\\';
            break;

        case 4:
            game_screen[5][(WIDTH / 2) + 1] = '-';
            game_screen[5][(WIDTH / 2) + 2] = '-';
            game_screen[5][(WIDTH / 2) + 3] = '/';
            break;
        
        case 5:
            game_screen[7][(WIDTH / 2) - 1] = '/';
            break;

        case 6:
            game_screen[7][(WIDTH / 2) + 1] = '\\';

            game_screen[3][(WIDTH / 2) - 1] = 'x';
            game_screen[3][(WIDTH / 2) + 1] = 'x';
            break;       
    }
}


void print_game_screen(void) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << game_screen[i][j];
        }

        std::cout << '\n';
    }
}