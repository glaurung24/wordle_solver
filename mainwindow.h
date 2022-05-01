#pragma once

#include <QMainWindow>
#include "qlineedit.h"
#include "settings.h"
#include <vector>
#include "game.h"
#include <memory>
#include <QPalette>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<char> getInputs();
    int startRoutine();

private slots:
    void on_submitButton_clicked();

    void on_newGameButton_clicked();

private:
    QPalette palette_correct_guess;
    QPalette palette_char_in_word;
    QPalette palette_std_backgrd;
    Ui::MainWindow *ui;
    QLineEdit* wordle_inputs [SETTINGS::NR_GUESSES][SETTINGS::WORD_LENGTH];
    unsigned active_row; // Defines which line the inputs is activated

    void activate_row(unsigned row_nr);
    void deactivate_row(unsigned row_nr);
    void reset_input_boxes();
    std::unique_ptr<Game> game;
};
