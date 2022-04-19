#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "settings.h"

class Game
{
public:
    Game();
    void chooseNewSecretWord();

private:
    char secret_word[SETTINGS::WORD_LENGTH];
};

#endif // GAME_H
