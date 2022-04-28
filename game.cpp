#include "game.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include<QDebug>
#include <QtGlobal>

Game::Game()
{
    try {
        std::ifstream file(SETTINGS::WORDLIST_FILE);
        std::string word;
        if( file.is_open())
        {
            while (std::getline(file, word)) {
                if(word.length() != SETTINGS::WORD_LENGTH){
                    throw 1;
                }

                official_words.push_back(word);
            }
            file.close();
        }
        else
        {
            throw 1;
        }

    }
    catch (...) {
        qDebug() <<"ups";
    }
}

void Game::chooseNewSecretWord()
{
    std::srand(time(NULL));
    int guess;
    guess = rand() % official_words.size();
    secret_word = official_words[guess];
}

