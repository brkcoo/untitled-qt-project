#pragma once

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <cstdlib>
#include <ctime>

class Pet {
private:
    QString name;
    // stats
    double power;
    double stamina;
    double wisdom;
    // conditions
    double happiness;
    double hunger;

    time_t lastLogin;

public:
    Pet(QString name = "James");
    void setName(QString n) { name = n; }

    QString getName() { return name; }
    double getPower() { return power; }
    double getStamina() { return stamina; }
    double getWisdom() { return wisdom; }
    double getHappiness() { return happiness; }
    double getHunger() { return hunger; }

    void gainPower(double pwr);
    void gainStamina(double sta);
    void gainWisdom(double wis);
    void improveHappiness(double hpn);
    void satiateHunger(double hgr);
    void perpetualChange();

    void savePet();
    void loadPet();

    friend QDataStream &operator<<(QDataStream &out, const Pet &pet);
    friend QDataStream &operator>>(QDataStream &in, Pet &pet);
    friend QDebug operator<<(QDebug out, const Pet &pet);
};
