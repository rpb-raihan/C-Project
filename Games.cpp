#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

void playRockPaperScissors();
void playNumberGuessingGame();
void playTicTacToe();
void playGunman();
void playQuizGame();
void playSnakeGame();

int main() {
    int choice;
    do {
        cout << "\n=== Game Hub ===" << endl;
        cout << "1. Rock, Paper, Scissors" << endl;
        cout << "2. Number Guessing Game" << endl;
        cout << "3. Tic Tac Toe" << endl;
        cout << "4. Gunman Game" << endl;
        cout << "5. Quiz Game" << endl;
         cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: playRockPaperScissors(); break;
            case 2: playNumberGuessingGame(); break;
            case 3: playTicTacToe(); break;
            case 4: playGunman(); break;
            case 5: playQuizGame(); break;
            case 7: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 7);

    return 0;
}

void playRockPaperScissors() {
    string choices[] = {"Rock", "Paper", "Scissors"};
    int user, computer;
    srand(time(0));
    cout << "\n--- Rock, Paper, Scissors ---\n0. Rock\n1. Paper\n2. Scissors\nEnter your choice: ";
    cin >> user;
    computer = rand() % 3;
    cout << "You chose: " << choices[user] << "\nComputer chose: " << choices[computer] << endl;
    if (user == computer) cout << "It's a draw!\n";
    else if ((user == 0 && computer == 2) || (user == 1 && computer == 0) || (user == 2 && computer == 1)) cout << "You win!\n";
    else cout << "Computer wins!\n";
}

void playNumberGuessingGame() {
    int number, guess, tries = 0;
    srand(time(0));
    number = rand() % 100 + 1;
    cout << "\n--- Number Guessing Game ---\nGuess a number between 1 and 100\n";
    do {
        cout << "Enter guess: ";
        cin >> guess;
        tries++;
        if (guess > number) cout << "Too high!\n";
        else if (guess < number) cout << "Too low!\n";
        else cout << "Correct! Attempts: " << tries << endl;
    } while (guess != number);
}

void playTicTacToe() {
    char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    int choice;
    char turn = 'X';
    bool draw = false;

    auto display = [&]() {
        system("cls");
        cout << "\n--- Tic Tac Toe ---\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            if (i < 2) cout << "\n---------\n";
        }
        cout << endl;
    };

    auto checkWin = [&]() {
        for (int i = 0; i < 3; ++i) if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        for (int i = 0; i < 3; ++i) if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
        return false;
    };

    do {
        display();
        cout << "\n" << turn << "'s turn. Enter cell number: ";
        cin >> choice;
        int row = (choice - 1) / 3, col = (choice - 1) % 3;
        if (choice >= 1 && choice <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = turn;
            if (checkWin()) {
                display();
                cout << turn << " wins!\n";
                return;
            }
            turn = (turn == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid move!\n";
        }
        draw = true;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O')
                    draw = false;
    } while (!draw);
    display();
    cout << "Game Draw!\n";
}

void playGunman() {
    srand(time(0));
    cout << "\n--- Gunman Game ---\nPress any key when you see 'FIRE!'\n";
    Sleep((rand() % 5 + 2) * 1000);
    cout << "FIRE!\n";
    clock_t start = clock();
    _getch();
    clock_t end = clock();
    double reaction = double(end - start) / CLOCKS_PER_SEC;
    cout << "Your reaction time: " << reaction << " seconds\n";
    if (reaction < 0.3) cout << "Fastest gun in the west!\n";
    else cout << "Too slow!\n";
}

void playQuizGame() {
    struct Question {
        string q;
        string options[4];
        char correct;
    } quiz[] = {
        {"Capital of France?", {"A. Paris", "B. Rome", "C. Madrid", "D. Berlin"}, 'A'},
        {"Red planet?", {"A. Venus", "B. Mars", "C. Jupiter", "D. Saturn"}, 'B'},
        {"Who wrote Hamlet?", {"A. Dickens", "B. Twain", "C. Shakespeare", "D. Rowling"}, 'C'}
    };

    int score = 0;
    char ans;
    for (auto &q : quiz) {
        cout << "\n" << q.q << endl;
        for (auto &o : q.options) cout << o << endl;
        cout << "Your answer: "; cin >> ans; ans = toupper(ans);
        if (ans == q.correct) { cout << "Correct!\n"; score++; }
        else cout << "Wrong!\n";
    }
    cout << "Your score: " << score << "/3\n";
}


