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
    vector<string> easyWords = {
        "code", "class", "float", "data", "array", "debug", "bit", "byte", "hex", "math", "null",
        "queue", "regex", "stack", "tuple", "void", "char", "enum", "list", "index", "event", "short",
        "long", "break", "case", "try", "catch", "true", "false", "else", "final", "lock", "loop",
        "print", "range", "while", "git", "java", "graph", "cpp", "merge", "tree", "bool"};

    vector<string> midWords = {
        "boolean", "integer", "function", "variable", "compiler", "comment", "library", "package", "console",
        "program", "runtime", "keyword", "pointer", "iterator", "operator", "element", "unicode", "operand", "register",
        "callback", "exception", "delegate", "string", "property", "resource", "adapter", "template", "database", "software",
        "computer", "object", "method", "binary", "module", "syntax", "github"};

    vector<string> hardWords = {
        "programming", "algorithm", "language", "developer", "structure", "condition", "attribute", "assignment",
        "reference", "namespace", "inheritance", "encapsulation", "polymorphism", "abstraction", "framework",
        "interface", "interpreter", "declaration", "initialization", "expression", "statement", "debugging", "testing"};

    vector<string> words;
    string secretWord;
    string guessedWord;
    int maxAttempts;
    int remainingAttempts;
    int hintLetters; // Number of letters to reveal as hints
    int score;

public:
    WordGuessingGame() : remainingAttempts(0), hintLetters(0), score(0)
    {
        // Seed the random number generator
        srand(time(0));
    }

    void selectLevel(int level)
    {
        switch (level)
        {
        case 1:
            words = easyWords;
            maxAttempts = 6;
            hintLetters = 2;
            break;
        case 2:
            words = midWords;
            maxAttempts = 8;
            hintLetters = 3;
            break;
        case 3:
            words = hardWords;
            maxAttempts = 12;
            hintLetters = 4;
            break;
        default:
            words = midWords; // Default to mid-level words
            maxAttempts = 8;
            hintLetters = 3;
            break;
        }

        // Choose a random word
        selectRandomWord();

        // Initialize guessedWord with hints
        guessedWord = getGuessedWordWithHints();

        remainingAttempts = maxAttempts;
    }

    void playGame()
    {
        cout << endl
             << "Welcome to Word Guessing Game!" << endl
             << "This game features words based on programming." << endl
             << endl;

        do
        {
            printGameStatus();

            char guess;
            cout << endl
                 << "Enter your guess letter: ";
            cin >> guess;

            makeGuess(guess);

        } while (!isGameOver());

        printGameStatus();

        if (guessedWord == secretWord)
        {
            cout << endl
                 << "Congratulations! You guessed the word: " << secretWord << endl;
            score++;
            cout << "Your score: " << score << endl;
            selectNextWord();
            playGame(); // Start another game
        }
        else
        {
            cout << endl
                 << "Sorry, you ran out of attempts. The word was: " << secretWord << endl;
            cout << "Your score: " << score << endl;
        }
    }

private:
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
            bool guessedCorrectly = false;
            for (size_t i = 0; i < secretWord.length(); ++i)
            {
                if (secretWord[i] == guess)
                {
                    guessedWord[i] = guess;
                    guessedCorrectly = true;
                }
            }

            if (!guessedCorrectly)
            {
                cout << endl
                     << "Incorrect guess: " << guess << endl;
                --remainingAttempts;
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

    void selectRandomWord()
    {
        secretWord = words[rand() % words.size()];
    }

    void selectNextWord()
    {
        selectRandomWord();
        guessedWord = getGuessedWordWithHints();
        remainingAttempts = maxAttempts;
    }

    string getGuessedWordWithHints()
    {
        string word = secretWord;

        // Shuffle indices to randomize hints
        vector<int> indices(word.length());
        for (size_t i = 0; i < word.length(); ++i)
            indices[i] = i;
        random_shuffle(indices.begin(), indices.end());

        // Hide some letters as underscores
        for (size_t i = hintLetters; i < word.length(); ++i)
            word[indices[i]] = '_';

        return word;
    }
};

int main()
{
    WordGuessingGame game;
    int level;

    cout << "Welcome to Word Guessing Game!" << endl;
    cout << "Choose difficulty level:" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Mid" << endl;
    cout << "3. Hard" << endl;
    cout << "Enter your choice: ";
    cin >> level;

    game.selectLevel(level);
    game.playGame();

    return 0;
}
