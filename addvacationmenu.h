
#ifndef ADDVACATIONMENU_H
#define ADDVACATIONMENU_H

#include <QLabel>
#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QComboBox>
#include <QCheckBox>
#include <QDateTimeEdit>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include "database_files/database.h"


class AddVacationMenu : public QLabel
{
    Q_OBJECT
public:
    AddVacationMenu(DataBase* refer,QMainWindow* parent = nullptr);

    void setDefault();
    void resize(QRect parent);

private:
    QFont SFProDisplay;

    DataBase* localBase;

    void paintEvent(QPaintEvent *event);
    void doPainting(QPainter* drawer);

    QComboBox* m_employee;
    QDateTimeEdit* m_beginDate;
    QDateTimeEdit* m_endDate;
    QCheckBox* currentDate;

    QPushButton* m_enter;
    QPushButton* m_cancel;

    QLabel* addVacationChapter;

    int panelsShift =10;

    void on_checkBox_stateChanged(int arg1);
    void addToBase();
    void hideMenu();

    Vacation* referVac = new Vacation();

public slots:
    void showMenu();

signals:
    void baseChanged();
};

#endif // ADDVACATIONMENU_H
