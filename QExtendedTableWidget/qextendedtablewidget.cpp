#include "qextendedtablewidget.h"

#include <QToolButton>
#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QWidgetAction>
#include <QDebug>


QExtendedTableWidget::QExtendedTableWidget(QWidget *parent) :
    QTableWidget(parent),
    mSelectColumnBtn(new QToolButton(this)),
    mButtonMenu(new QMenu(this))
{

    mSelectColumnBtn->setText("+/-");
    mSelectColumnBtn->setMenu(mButtonMenu);
    mSelectColumnBtn->setPopupMode(QToolButton::InstantPopup);
    mSelectColumnBtn->setStyleSheet("QToolButton::menu-indicator{  image: none;  }");
    mButtonMenu->setStyleSheet("QMenu {"
                               "    border: 1px solid gray;"
                               "}"
                               "QMenu::item{"
                               "   padding: 2px 20px 2px 20px;"
                               "   border: 1px solid transparent;"
                               "   spacing: 20px;"
                               "}");

    QAction* a = mButtonMenu->addAction("test");
    a->setCheckable(true);
    a = mButtonMenu->addAction("test2");
    a->setCheckable(true);

    updateSelectableColumns();
}

void QExtendedTableWidget::disableColumnForSelection(const int columnCount){
    mColumnsDisabledForSelection.append(columnCount);
    updateSelectableColumns();
}

void QExtendedTableWidget::setHorizontalHeaderItem(int column, QTableWidgetItem *item){
    QTableWidget::setHorizontalHeaderItem(column, item);
    updateSelectableColumns();
}

bool QExtendedTableWidget::setColumnHidden(int column, bool hide){
    if(column > mButtonMenu->actions().count())
        return false;

    mButtonMenu->actions().at(column)->setChecked(!hide);
    return true;
}

QList<int> QExtendedTableWidget::getCurrentVisibleColumns(){

    QList<int> columnList;

    for (int i = 0; i < this->columnCount(); ++i) {
        QTableWidgetItem *item = this->horizontalHeaderItem(i);
        if(item){
            if(!this->horizontalHeader()->isSectionHidden(i))
                columnList.append(i);
        }
    }

    return columnList;
}


void QExtendedTableWidget::resizeEvent(QResizeEvent *){
    const int headerSize = this->horizontalHeader()->size().height();
    mSelectColumnBtn->setGeometry(this->rect().topRight().x() - headerSize * 1.5,
                                  this->rect().topRight().y() + headerSize * 0.1,
                                  headerSize * 1.5,
                                  headerSize * 0.9);
}

void QExtendedTableWidget::updateSelectableColumns(){
    mButtonMenu->clear();

    //headline
    QLabel *headlineLabel = new QLabel("Spalten anzeigen");

    headlineLabel->setStyleSheet("padding: 2px 20px 2px 20px;"
                                 "border: 1px solid transparent;"
                                 "spacing: 20px;"
                                 "background-color: #1A9DDE;"
                                 "color: white;"
                                 "font: bold;");

    QWidgetAction *headlineAction = new QWidgetAction(this);
    headlineAction->setDefaultWidget(headlineLabel);
    mButtonMenu->addAction(headlineAction);

    for (int i = 0; i < this->columnCount(); ++i) {
        QTableWidgetItem *item = this->horizontalHeaderItem(i);
        if(item){
            QAction *newAction = new QAction(item->text());
            newAction->setCheckable(true);
            newAction->setChecked(true);

            connect(newAction, &QAction::toggled, newAction, [=](bool checked){
                if(checked)
                    this->horizontalHeader()->showSection(i);
                else
                    this->horizontalHeader()->hideSection(i);

                emit visibleColumnsChanged();
            });

            if(!mColumnsDisabledForSelection.contains(i))
                mButtonMenu->addAction(newAction);
        }
    }
}
