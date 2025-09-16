#pragma once

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <vector>

class Minigame : public QWidget {
    Q_OBJECT
public:
    Minigame(QWidget *parent = nullptr);
signals:
    void sendScore(int score);
private:
    int score;
    int loops;
    QTimer *timer;
    std::vector<QPushButton*> buttons;

    QPushButton *returnButton;
    QLabel *backgroundLabel;
    QLabel *timerLabel;
    QLabel *scoreLabel;

    void runMinigame();
    void createButton();
    void endMinigame();
private slots:
    void onReturnButtonClicked();
    void onButtonPress(QPushButton *button);
};
