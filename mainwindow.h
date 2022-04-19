#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlineedit.h"
#include "settings.h"
#include <vector>

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

private:
    Ui::MainWindow *ui;
    QLineEdit* wordle_inputs [SETTINGS::NR_GUESSES][SETTINGS::WORD_LENGTH];
};
#endif // MAINWINDOW_H
