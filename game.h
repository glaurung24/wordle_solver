#pragma once
#include <QMainWindow>
#include "settings.h"
#include <vector>
#include <string>


class Game
{
public:
    typedef struct hint {
        bool char_in_word[SETTINGS::WORD_LENGTH];
        bool char_in_correct_place[SETTINGS::WORD_LENGTH];
    } Hint;

    Game();
    void chooseNewSecretWord();
    void setUserGuess(std::string input_user_guess);
    void reset(); //TODO implement
    Hint generateHint(std::string guess);
    void convertToUpperCase(char& char_input);
    void convertToUpperCase(std::string& str_input);

private:
    std::vector<std::string> official_words;
    std::string secret_word;
};

