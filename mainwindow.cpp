#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settings.h"
#include "game.h"
#include<QDebug>
#include <memory>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wordleGrid->setHorizontalSpacing(SETTINGS::NR_GUESSES);
    ui->wordleGrid->setVerticalSpacing(SETTINGS::WORD_LENGTH);

    palette_correct_guess.setColor(QPalette::Base,SETTINGS::CHAR_GUESS_CORRECT_COLOR);
    palette_char_in_word.setColor(QPalette::Base, SETTINGS::CHAR_GUESS_IN_WORD_COLOR);
    palette_std_backgrd.setColor(QPalette::Base, SETTINGS::INPUT_BOX_STD_BACKGRD);


    active_row = 0;
    for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++){
        for(int row = 0; row<SETTINGS::NR_GUESSES; row++)
        {
            QLineEdit *input_box = new QLineEdit(parent);
            input_box->setMaxLength(1);
            input_box->setEnabled(false);
            input_box->setAlignment(Qt::AlignHCenter);
            input_box->setPalette(palette_std_backgrd);
            wordle_inputs [row][line_pos] = input_box; //TODO Make unique pointer?
            ui->wordleGrid->addWidget(input_box, row, line_pos);
        }
    }
    game = std::make_unique<Game>();
    on_newGameButton_clicked(); // start the game

}

MainWindow::~MainWindow()
{
    //Freeing QLineEdits used for word input
    for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++){
        for(int row = 0; row<SETTINGS::NR_GUESSES; row++)
        {
             delete wordle_inputs [row][line_pos];
        }
    }
    delete ui;
}

int MainWindow::startRoutine()
{

    game->chooseNewSecretWord();
    return 0;
}


void MainWindow::on_submitButton_clicked() // read user input
{
    try
    {
        char input[SETTINGS::WORD_LENGTH];
        for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++) //Read in user input from active row
        {
            char temp_input;
            temp_input = wordle_inputs[active_row][line_pos]->displayText().toStdString()[0];
            game->convertToUpperCase(temp_input);
            wordle_inputs [active_row][line_pos]->setText(QString(temp_input));
            input[line_pos] = temp_input;
        }
        Game::Hint output_hint = game->generateHint(input);

        //TODO check win condition!!!

        for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++) //Set background of input boxes accoring to the users' guess in active row
        {
            if(output_hint.char_in_correct_place[line_pos])
            {
                wordle_inputs[active_row][line_pos]->setPalette(palette_correct_guess);
            }
            else if(output_hint.char_in_word[line_pos])
            {
                wordle_inputs[active_row][line_pos]->setPalette(palette_char_in_word);
            }


        }
        deactivate_row(active_row);
        active_row++;
        if(active_row > SETTINGS::NR_GUESSES)
        {
            game->reset();
            return; //TODO handle this case better
        }
        activate_row(active_row);

    }catch(...)
    {
        active_row--;
        qDebug() <<"wrong input after clicking submit";
    }
}


void MainWindow::on_newGameButton_clicked()
{
    active_row = 0;
    reset_input_boxes();
    activate_row(active_row);//activate the first row
}

void MainWindow::activate_row(unsigned row_nr)
{
    for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++) //activate the row
    {
        wordle_inputs [row_nr][line_pos]->setEnabled(true);
    }
}
void MainWindow::deactivate_row(unsigned row_nr)
{
    for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++) //deactivate the  row
    {
        wordle_inputs[row_nr][line_pos]->setEnabled(false);
    }
}

void MainWindow::reset_input_boxes() //resets the background of all boxes, deletes text and deactivates them
{
    for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++){
        for(int row = 0; row<SETTINGS::NR_GUESSES; row++)
        {
            wordle_inputs [row][line_pos]->setText("");
            wordle_inputs [row][line_pos]->setPalette(palette_std_backgrd);
            deactivate_row(row);
        }
    }

}

