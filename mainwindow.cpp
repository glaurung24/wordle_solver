#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wordleGrid->setHorizontalSpacing(SETTINGS::NR_GUESSES);
    ui->wordleGrid->setVerticalSpacing(SETTINGS::WORD_LENGTH);



    for(int line_pos = 0; line_pos<SETTINGS::WORD_LENGTH; line_pos++){
        for(int row = 0; row<SETTINGS::NR_GUESSES; row++)
        {
            QLineEdit *input_box = new QLineEdit(parent);
            input_box->setMaxLength(1);
            input_box->setEnabled(false);
            wordle_inputs [row][line_pos] = input_box;
            ui->wordleGrid->addWidget(input_box, row, line_pos);
        }
    }

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

