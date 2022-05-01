#pragma once

#include <QPalette>
#include <QColor>

namespace SETTINGS{

static const unsigned int WORD_LENGTH = 5;
static const unsigned int NR_GUESSES = 5;

static const char* WORDLIST_FILE = "wordlist.csv";

static const Qt::GlobalColor CHAR_GUESS_CORRECT_COLOR = Qt::green;
static const Qt::GlobalColor CHAR_GUESS_IN_WORD_COLOR = Qt::yellow;
static const Qt::GlobalColor INPUT_BOX_STD_BACKGRD = Qt::white;


}
