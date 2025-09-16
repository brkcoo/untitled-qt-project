#include <QDebug>
#include <QFont>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QTimer>

#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), pet() {
    // window
    setFixedSize(800, 600);

    // pet
    pet.loadPet();
    pet.perpetualChange();

    // window elements
    QFont font("Comic Sans MS", 14);

    stack = new QStackedWidget(this);
    home = new QWidget(this);
    stack->addWidget(home);
    stack->setCurrentWidget(home);
    setCentralWidget(stack);

    button1 = new QPushButton(home);
    button1->setText("feed him");
    button1->setFont(font);
    button1->setIconSize(QSize(64, 64));
    button1->resize(200, 125);
    button1->move(100, 450);

    button2 = new QPushButton(home);
    button2->setText("gain stuff");
    button2->setFont(font);
    button2->setIconSize(QSize(64, 64));
    button2->resize(200, 125);
    button2->move(300, 450);

    button3 = new QPushButton(home);
    button3->setText("play minigame");
    button3->setFont(font);
    button3->setIconSize(QSize(64, 64));
    button3->resize(200, 125);
    button3->move(500, 450);

    backgroundLabel = new QLabel(home);
    backgroundLabel->setPixmap(QPixmap(":/bg.jpeg"));
    backgroundLabel->lower();

    petLabel = new PetLabel(home);
    petLabel->setPixmap(QPixmap(":/fox.png"));
    petLabel->move(250, 150);
    petLabel->setCursor(Qt::OpenHandCursor);

    nameLabel = new QLabel(home);
    nameLabel->setText("jeremiah bacon");
    nameLabel->setFont(font);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->adjustSize();
    nameLabel->move((width() * .5 - nameLabel->width() * .5), 100);

    label1 = new QLabel(home);
    label1->setFont(font);
    label1->setAlignment(Qt::AlignCenter);
    label1->move(50, 50);

    connect(button1, &QPushButton::clicked, this, &GameWindow::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &GameWindow::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &GameWindow::onButton3Clicked);
    connect(petLabel, &PetLabel::petPetted, this, &GameWindow::onPetPetted);

    updateLabels();
}

void GameWindow::onExit() { pet.savePet(); }

void GameWindow::onButton1Clicked() {
    pet.satiateHunger(rand() % 10);
    updateLabels();
}
void GameWindow::onButton2Clicked() {
    int whichStat = rand() % 3;
    switch (whichStat) {
    case 0:
        pet.gainPower(5);
        break;
    case 1:
        pet.gainStamina(5);
        break;
    case 2:
        pet.gainWisdom(5);
        break;
    }
    updateLabels();
}
void GameWindow::onButton3Clicked() {
    currentMinigame = new Minigame();
    connect(currentMinigame, &Minigame::sendScore, this,
            &GameWindow::finalizeMinigame);
    stack->addWidget(currentMinigame);
    stack->setCurrentWidget(currentMinigame);
}

void GameWindow::onPetPetted() {
    pet.improveHappiness(.01);
    spawnHearts();
    updateLabels();
}

void GameWindow::spawnHearts() {
    if (rand() % 100 < 95)
        return;
    QPoint pos = mapFromGlobal(QCursor::pos());
    auto modifier = [](int n, int range) {
        return n + (rand() % (range * 2 + 1) - range);
    }; // modify a number by a random amount (-range to +range)
    int x = modifier(pos.x(), 20);
    int y = modifier(pos.y(), 20);
    int size = modifier(20, 10);

    QPixmap image = QPixmap(":/heart.png");
    image =
        image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *heart = new QLabel(this);
    heart->setPixmap(image);
    heart->resize(size, size);
    heart->hasScaledContents();
    heart->move(x, y);
    heart->show();

    QTimer *timer = new QTimer(this);
    timer->setInterval(25);
    timer->start();
    connect(timer, &QTimer::timeout, this, [heart]() {
        QPoint p = heart->pos();
        heart->move(p.x(), p.y() - rand() % 4);
    });
    QTimer::singleShot(modifier(1000, 250), this, [=]() {
        timer->stop();
        timer->deleteLater();
        heart->deleteLater();
    });
}

void GameWindow::finalizeMinigame(int score) {
    int whichStat = rand() % 3;
    switch (whichStat) {
    case 0:
        pet.gainPower(score * 5);
        break;
    case 1:
        pet.gainStamina(score * 5);
        break;
    case 2:
        pet.gainWisdom(score * 5);
        break;
    }
    updateLabels();

    stack->setCurrentWidget(home);
    stack->removeWidget(currentMinigame);
    currentMinigame->deleteLater();
    currentMinigame = nullptr;
}

void GameWindow::updateLabels() {
    label1->setText(
        QString("Power: %1\nStamina: %2\nWisdom: %3\nHappiness: %4\nHunger: %5")
            .arg((int)pet.getPower())
            .arg((int)pet.getStamina())
            .arg((int)pet.getWisdom())
            .arg((int)pet.getHappiness())
            .arg((int)pet.getHunger()));
    label1->adjustSize();
}
