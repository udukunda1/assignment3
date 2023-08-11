#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cctype>

using namespace std;

vector<string> wordList = {"apple", "banana", "cherry", "orange", "grape", "kiwi", "melon"};

string selectWord() {
    srand(time(0));
    int randomIndex = rand() % wordList.size();
    return wordList[randomIndex];
}

int main() {
    string selectedWord = selectWord();
    int guessesRemaining = 6;
    int warningsRemaining = 3;
    string guessedLetters;

    cout << "Welcome to Hangman!" << endl;
    cout << "Try to guess the word by entering one character at a time." << endl;

    while (guessesRemaining > 0) {
        cout << "----------------------------------------------------------" << endl;
        cout << "Guesses remaining: " << guessesRemaining << endl;
        cout << "Warnings remaining: " << warningsRemaining << endl;
        cout << "Letters not yet used: ";
        for (char c = 'a'; c <= 'z'; ++c) {
            if (guessedLetters.find(c) == string::npos) {
                cout << c << " ";
            }
        }
        cout << endl;

        cout << "Guess a letter: ";
        char guess;
        cin >> guess;
        guess = tolower(guess);

        if (!isalpha(guess)) {
            cout << "Invalid input. Please enter a letter." << endl;
            if (warningsRemaining > 0) {
                warningsRemaining--;
            } else {
                guessesRemaining--;
            }
            continue;
        }

        if (guessedLetters.find(guess) != string::npos) {
            cout << "You've already guessed that letter." << endl;
            if (warningsRemaining > 0) {
                warningsRemaining--;
            } else {
                guessesRemaining--;
            }
            continue;
        }

        guessedLetters += guess;

        if (selectedWord.find(guess) != string::npos) {
            cout << "Good guess: ";
            for (char c : selectedWord) {
                if (guessedLetters.find(c) != string::npos) {
                    cout << c;
                } else {
                    cout << "-";
                }
            }
            cout << endl;

            if (selectedWord.find_first_not_of(guessedLetters) == string::npos) {
                int score = guessesRemaining * (int)(selectedWord.size() - guessedLetters.size());
                cout << "Congratulations! You've won with a score of " << score << "." << endl;
                break;
            }
        } else {
            if (string("aeiou").find(guess) != string::npos) {
                guessesRemaining -= 2;
            } else {
                guessesRemaining--;
            }

            cout << "Oops! Incorrect guess." << endl;
        }
    }

    if (guessesRemaining <= 0) {
        cout << "Sorry, you've run out of guesses. The word was '" << selectedWord << "'." << endl;
    }

    return 0;
}
