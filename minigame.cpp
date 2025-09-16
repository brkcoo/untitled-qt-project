#include "minigame.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFont>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QTimer>

Minigame::Minigame(QWidget *parent) : QWidget(parent) {
    // window
    setFixedSize(800, 600);

    // window elements
    QFont font("Comic Sans MS", 14);
    QFont font2("Comic Sans MS", 50);

    returnButton = new QPushButton(this);
    returnButton->hide();
    returnButton->setText("return to home");
    returnButton->setFont(font);
    returnButton->resize(200, 125);
    returnButton->move(width() * .5 - returnButton->width() * .5,
                       height() * .5 - returnButton->height() * .5);
    returnButton->raise();

    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/bg.jpeg"));
    backgroundLabel->lower();

    timerLabel = new QLabel(this);
    timerLabel->setText("30");
    timerLabel->setFont(font2);
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->adjustSize();
    timerLabel->move((width() * .5 - timerLabel->width() * .5), 0);

    scoreLabel = new QLabel(this);
    scoreLabel->setText("Score: 0");
    scoreLabel->setFont(font);
    scoreLabel->setAlignment(Qt::AlignCenter);

    connect(returnButton, &QPushButton::clicked, this,
            &Minigame::onReturnButtonClicked);

    runMinigame();
}

void Minigame::runMinigame() {
    // initialize
    score = 0;
    loops = 0;
    timer = new QTimer(this);
    buttons = {};
    connect(timer, &QTimer::timeout, this, [this]() {
        timerLabel->setText(QString("%1").arg(30 - (loops / 2)));
        createButton();
        loops++;
        if (loops > 60) {
            timer->stop();
            endMinigame();
        }
    });
    timer->start(500);
}

void Minigame::createButton() {
    QPushButton *button = new QPushButton(this);
    button->setText("click!");
    button->resize(50, 50);
    int randX = rand() % 600 + 100; // 100 to 700
    int randY = rand() % 400 + 100; // 100 to 500
    button->move(randX, randY);
    button->raise();
    button->show();
    buttons.push_back(button);
    connect(button, &QPushButton::clicked, this,
            [this, button]() { this->onButtonPress(button); });
}

void Minigame::endMinigame() {
    returnButton->show();
    // clear leftover buttons
    for (auto it : buttons) {
        if (it) {
            it->hide();
        }
    }
};

void Minigame::onReturnButtonClicked() {
    // return to gamewindow
    emit sendScore(score);
};

void Minigame::onButtonPress(QPushButton *button) {
    score += 1;
    scoreLabel->setText(QString("Score: %1").arg(score));
    scoreLabel->adjustSize();
    button->hide();
};
