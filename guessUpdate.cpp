#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class WordGuessingGame
{
private:
    vector<string> words;
    string secretWord;
    string guessedWord;
    int maxAttempts;
    int remainingAttempts;

public:/* (1-5) Easy {"Code","Class","Float","Data","Array","Debug","Bit" ,"Byte","Hex",
     "Math","Null","Queue","Regex","Stack","Tuple","Void","Char","Enum","List","Index","Event",
     "Short","Long","Break","Case","Try","Catch","True","False","Else","Final","Lock","Loop",
     "Print","Range","While ","Git","Java","Graph,"Cpp","Merge","Tree","bool"},*/

    /* (6-8) Mid{"Boolean","Integer","Function","Variable","Compiler","Comment","Library","Package","Console",
    "Program","Runtime","Keyword","Pointer","Iterator","Operator","Element","Unicode","Operand","Register",
    "Callback","Exception","Delegate","string","Property","Resource","Adapter","Template","Database","software",
    "computer","object","method",  "binary", "module","syntax","github"}*/


    WordGuessingGame() : words{"programming", "computer", "algorithm", "language", "developer",
                               "code", "debug", "software", "database", "structure", "binary"},
                         maxAttempts(6), remainingAttempts(maxAttempts)
    {
        // Seed the random number generator
        srand(time(0));

        // Choose a random word
        secretWord = words[rand() % words.size()];

        // Initialize guessedWord with underscores
        guessedWord = string(secretWord.length(), '_');
    }

    void printGameStatus() const
    {
        cout << endl
                  << "Secret Word: " << guessedWord << endl;
        cout << "Number of Letters: " << secretWord.length() << endl;
        cout << "Remaining Attempts: " << remainingAttempts << "/" << maxAttempts << endl;
    }

    void makeGuess(char guess)
    {
        if (isalpha(guess))
        {
            guess = tolower(guess); // Convert to lowercase
            if (count(guessedWord.begin(), guessedWord.end(), guess) == 0)
            {
                if (secretWord.find(guess) != string::npos)
                {
                    // Correct guess, update guessedWord
                    for (size_t i = 0; i < secretWord.length(); ++i)
                    {
                        if (secretWord[i] == guess)
                        {
                            guessedWord[i] = guess;
                        }
                    }
                }
                else
                {
                    // Incorrect guess, decrement remaining attempts
                    cout << endl
                              << "Incorrect guess: " << guess << endl;
                    --remainingAttempts;
                }
            }
            else
            {
                cout << "You already guessed the letter " << guess << ". Try again." << endl;
            }
        }
        else
        {
            cout << "Invalid input. Please enter a letter." << endl;
        }
    }

    bool isGameOver() const
    {
        return remainingAttempts == 0 || guessedWord == secretWord;
    }

    void playGame()
    {
        cout << endl
                  << "Welcome to Word Guessing Game!" << endl
                  << "This Guesses Words are Based on Programming!" << endl
                  << endl;

        do
        {
            printGameStatus();

            char guess;
            cout << endl
                      << "Enter your guess: ";
            cin >> guess;

            makeGuess(guess);

        } while (!isGameOver());

        printGameStatus();

        if (guessedWord == secretWord)
        {
            cout << endl
                      << "Congratulations! You guessed the word: " << secretWord << endl;
        }
        else
        {
            cout << endl
                      << "Sorry, you ran out of attempts. The word was: " << secretWord << endl;
        }
    }
};

int main()
{
    WordGuessingGame game;
    game.playGame();

    return 0;
}


