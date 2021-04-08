#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qobjectdefs.h"
#include "qwidget.h"
#include "qwindowdefs.h"
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QString>
#include "snake.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum type {
        snake,
        food,
        background
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots: 
    void control();
    bool eventFilter(QObject *object, QEvent *event);

    void gameover();
private:
    void handleKeyPress(QKeyEvent *event);
    QWidget *scene;
    QLabel *asnake[16][16];
    type snakes[16][16];
    QGridLayout *game;
    void start();
    QTimer *timer;
    Snake *mysnake;
    bool hasfood;
    bool isrun;
    void createfood(); 
};
#endif // MAINWINDOW_H
