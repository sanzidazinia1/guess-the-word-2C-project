#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class WordGuessingGame
{
private:
    std::vector<std::string> words;
    std::string secretWord;
    std::string guessedWord;
    int maxAttempts;
    int remainingAttempts;

public:
    WordGuessingGame() : words{"programming", "computer", "algorithm", "language", "developer",
                               "code", "debug", "software", "database", "structure", "binary"},
                         maxAttempts(6), remainingAttempts(maxAttempts)
    {
        // Seed the random number generator
        std::srand(std::time(0));

        // Choose a random word
        secretWord = words[rand() % words.size()];

        // Initialize guessedWord with underscores
        guessedWord = std::string(secretWord.length(), '_');
    }

    void printGameStatus() const
    {
        std::cout << std::endl
                  << "Secret Word: " << guessedWord << std::endl;
        std::cout << "Number of Letters: " << secretWord.length() << std::endl;
        std::cout << "Remaining Attempts: " << remainingAttempts << "/" << maxAttempts << std::endl;
    }

    void makeGuess(char guess)
    {
        if (std::isalpha(guess))
        {
            guess = std::tolower(guess); // Convert to lowercase
            if (std::count(guessedWord.begin(), guessedWord.end(), guess) == 0)
            {
                if (secretWord.find(guess) != std::string::npos)
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
                    std::cout << std::endl
                              << "Incorrect guess: " << guess << std::endl;
                    --remainingAttempts;
                }
            }
            else
            {
                std::cout << "You already guessed the letter " << guess << ". Try again." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter a letter." << std::endl;
        }
    }

    bool isGameOver() const
    {
        return remainingAttempts == 0 || guessedWord == secretWord;
    }

    void playGame()
    {
        std::cout << std::endl
                  << "Welcome to Word Guessing Game!" << std::endl
                  << "This Guesses Words are Based on Programming!" << std::endl
                  << std::endl;

        do
        {
            printGameStatus();

            char guess;
            std::cout << std::endl
                      << "Enter your guess: ";
            std::cin >> guess;

            makeGuess(guess);

        } while (!isGameOver());

        printGameStatus();

        if (guessedWord == secretWord)
        {
            std::cout << std::endl
                      << "Congratulations! You guessed the word: " << secretWord << std::endl;
        }
        else
        {
            std::cout << std::endl
                      << "Sorry, you ran out of attempts. The word was: " << secretWord << std::endl;
        }
    }
};

int main()
{
    WordGuessingGame game;
    game.playGame();

    return 0;
}
