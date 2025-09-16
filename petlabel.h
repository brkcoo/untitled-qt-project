#pragma once
#include <QApplication>
#include <QCursor>
#include <QLabel>
#include <QMouseEvent>

class PetLabel : public QLabel {
    Q_OBJECT
public:
    PetLabel(QWidget *parent = nullptr) : QLabel(parent) {
        setMouseTracking(true);
    }
signals:
    void petPetted();

protected:
    void
    mouseMoveEvent(QMouseEvent *e) override { // mouse needs to be moving AND held
        if (e->buttons() == Qt::LeftButton) {
            emit petPetted();
        }
        QLabel::mouseMoveEvent(e); // perform default behavior
    }
    void mousePressEvent(QMouseEvent *e) override {
        if (e->button() == Qt::LeftButton) {
            setCursor(Qt::ClosedHandCursor);
        }
        QLabel::mouseReleaseEvent(e); // perform default behavior
    }
    void mouseReleaseEvent(QMouseEvent *e) override {
        if (e->button() == Qt::LeftButton) {
            setCursor(Qt::OpenHandCursor);
        }
        QLabel::mouseReleaseEvent(e); // perform default behavior
    }
};
