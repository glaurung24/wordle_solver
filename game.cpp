#include "game.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include<QDebug>
#include <QtGlobal>
#include <iostream> //TODO remove after debugging

Game::Game()
{
    try {
        std::ifstream file(SETTINGS::WORDLIST_FILE);
        std::string word;
        if( file.is_open())
        {
            while (std::getline(file, word)) {
                if(word.length() != SETTINGS::WORD_LENGTH){
                    throw 1; //TODO get exceptions done
                }

                official_words.push_back(word);
            }
            file.close();
        }
        else
        {
            throw 1; //TODO get exceptions done
        }

    }
    catch (...) {
        qDebug() <<"ups";
    }
}

void Game::chooseNewSecretWord() //Uncomment for release
{
//    std::srand(time(NULL));
//    int guess;
//    guess = rand() % official_words.size();
//    secret_word = official_words[guess];
    secret_word = std::string("waard");//TODO only for testing
    this->convertToUpperCase(secret_word);
}

Game::hint Game::generateHint(std::string guess)
{
    Game::Hint solution_hint = {.char_in_word={0}, .char_in_correct_place={0}};
    std::vector<std::size_t> unmatched_chars;
    for(auto char_pos = 0; char_pos < SETTINGS::WORD_LENGTH; char_pos++)
    {
        std::size_t pos_found = secret_word.find(guess[char_pos], char_pos);
        if (pos_found != std::string::npos and pos_found == char_pos)
        {
            solution_hint.char_in_correct_place[char_pos] = true;
        }
        else
        {
            unmatched_chars.push_back(char_pos);
        }
    }
    for(auto it = unmatched_chars.begin(); it < unmatched_chars.end();it++)
    {
        std::size_t pos_found = secret_word.find(guess[*it]);
        if(pos_found != std::string::npos)
        {
            solution_hint.char_in_word[*it] = true;
        }
    }
    return solution_hint;
}

void Game::convertToUpperCase(char& char_input)
{
    if(char_input >= 97 and char_input <= 122) // check if input is valid character and make sure it is upper case
    {
        char_input -= 32;
    }
    else if(char_input <= 65 and char_input >= 90)
    {
        throw 1; //handle this exception better (incvalid char or something)
    }
}

void Game::convertToUpperCase(std::string& str_input)
{
    for (size_t char_pos = 0; char_pos < str_input.size(); char_pos++)
    {
        if(str_input[char_pos] >= 97 and str_input[char_pos] <= 122) // check if input is valid character and make sure it is upper case
        {
            str_input[char_pos] -= 32;
        }
        else if(str_input[char_pos] <= 65 and str_input[char_pos] >= 90)
        {
            throw 1; //handle this exception better (incvalid char or something)
        }
    }
}



void Game::reset()
{
    chooseNewSecretWord();
}

