#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "settings.h"
#include <vector>
#include <string>


class Game
{
public:
    Game();
    void chooseNewSecretWord();

private:
    std::vector<std::string> official_words;
    std::string secret_word;
};

#endif // GAME_H
