#include "rightpanel.h"

RightPanel::RightPanel(DataBase* refer,int number, QMainWindow *parent):
    QLabel(parent)
{
    parentSize = parent->geometry();
    this->setGeometry(parent->width()-parent->width()/6,80,parent->width()/6-12,parent->height()-130);
    this->setMouseTracking(true);
    selectedEm = refer->employee(number);
    referBase = refer;

    for(int c=0;c<15;c++)
    {
        taskPanels.push_back(new PTtab("",0,this));
        taskPanels[c]->hide();
    }

}

void RightPanel::updateSelectedEmployee(int refer)
{
    if(refer == -1)
    {
        return;
    }

    selectedEm = referBase->employee(refer);
    updateTaskPanel(refer);
}

void RightPanel::updateTaskPanel(int number)
{
    for(int c=0;c<15;c++)
    {
        taskPanels[c]->hide();
    }

    for(int c=0;c<selectedEm->tasksAmount();c++)
    {
        taskPanels[c]->setPicture(0);
        QString taskName = selectedEm->task(c)->name();
        if(taskName.length()>20)
        {
            taskName.truncate(20);
            taskName += " ...";
        }
        taskPanels[c]->setPText(QString(taskName),1);
        taskPanels[c]->move(0,0+80*c);
        taskPanels[c]->show();
    }
}

void RightPanel::mousePressEvent(QMouseEvent* event)
{
    if(isOnField(event->pos(),QRect(0,0,width(),this->height())))
    {
        for(int c=0;c<selectedEm->tasksAmount();c++)
        {
            if(isOnField(event->pos(),taskPanels[c]->geometry()))
            {
                taskPanels[c]->setSelected(true);
                emit changedSelected(c);

            }
            else
            {
                taskPanels[c]->setSelected(false);
            }
            taskPanels[c]->update();
        }
    }
}

bool RightPanel::isOnField(const QPointF &point, const QRectF &rect)
{
    return (rect.topLeft().x()<point.x() && rect.topLeft().y()<point.y() &&
            rect.bottomRight().x()>point.x() && rect.bottomRight().y()>point.y());
}

