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
        std::fstream fin;
        fin.open(SETTINGS::WORDLIST_FILE, std::ios::in);
        std::string word;
        while (std::getline(fin, word)) {
            if(word.length() != SETTINGS::WORD_LENGTH){
                throw 1;
            }

            official_words.push_back(word);
        }
    }
    catch (...) {
        qDebug() <<"ups";
        throw 1;
    }
    for (std::vector<std::string>::iterator it = official_words.begin() ; it != official_words.end(); ++it){
      QString s = QString::fromStdString(*it);
      qDebug() << qUtf8Printable(s);
    }
}

void Game::chooseNewSecretWord()
{
    for (std::vector<std::string>::iterator it = official_words.begin() ; it != official_words.end(); ++it){
      QString s = QString::fromStdString(*it);
      qDebug() << qUtf8Printable(s);
    }
    std::srand(time(NULL));
    int guess;
    guess = rand() % official_words.size();
//    qDebug << guess << std::endl;
    secret_word = official_words[guess];
}

