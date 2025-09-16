#pragma once

#include "minigame.h"
#include "pet.h"
#include "petlabel.h"

#include <QPushButton>
#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>

class GameWindow : public QMainWindow {
    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr);
    void onExit();

private:
    Pet pet;

    Minigame *currentMinigame;

    QStackedWidget *stack;
    QWidget *home;

    QLabel *backgroundLabel;
    PetLabel *petLabel;
    QLabel *nameLabel;
    QLabel *label1;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;

    void updateLabels();
    void spawnHearts();
private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onPetPetted();
    void finalizeMinigame(int score);
};
