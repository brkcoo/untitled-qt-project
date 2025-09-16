#include "pet.h"
#include <QFile>

Pet::Pet(QString n) {
    name = n;
    power = stamina = wisdom = 10;
    happiness = hunger = 100;
    lastLogin = time(nullptr);
}

void Pet::gainPower(double pwr) {
    int randomNum = (rand() % 16) + 85; // generate number from 85 to 100
    power += (pwr) * (randomNum / 100.0);
}

void Pet::gainStamina(double sta) {
    int randomNum = (rand() % 16) + 85;
    stamina += (sta) * (randomNum / 100.0);
}

void Pet::gainWisdom(double wis) {
    int randomNum = (rand() % 16) + 85;
    wisdom += (wis) * (randomNum / 100.0);
}

void Pet::improveHappiness(double hpn) {
    happiness += hpn;
    if (happiness > 100)
        happiness = 100;
}
void Pet::satiateHunger(double hgr) {
    hunger += hgr;
    if (hunger > 100)
        hunger = 100;
}

void Pet::perpetualChange() {
    // lose 4% per hour , gain 3% stats per hour
    time_t currentLogin = time(nullptr);
    double hrs = difftime(currentLogin, lastLogin) / 3600;
    if (hrs > 24)
        hrs = 24; // cap out at 1 day
    // losses
    satiateHunger(hunger * -.04 * hrs);
    improveHappiness(happiness * -.04 * hrs);
    // gains
    gainPower(power * .03 * hrs);
    gainStamina(stamina * .03 * hrs);
    gainWisdom(wisdom * .03 * hrs);

    lastLogin = currentLogin;
}

void Pet::savePet() {
    QFile file("p.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << *this;
    }
}

void Pet::loadPet() {
    QFile file("p.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> *this;
    }
}

QDataStream &operator<<(QDataStream &out, const Pet &pet) {
    out << pet.name << pet.power << pet.stamina << pet.wisdom << pet.happiness
        << pet.hunger << pet.lastLogin;
    return out;
}
QDataStream &operator>>(QDataStream &in, Pet &pet) {
    in >> pet.name >> pet.power >> pet.stamina >> pet.wisdom >> pet.happiness >>
        pet.hunger >> pet.lastLogin;
    return in;
}
QDebug operator<<(QDebug out, const Pet &pet) {
    out << pet.name << pet.power << pet.stamina << pet.wisdom << pet.happiness
        << pet.hunger << pet.lastLogin;
    return out;
}
