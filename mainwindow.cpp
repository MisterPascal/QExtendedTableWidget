#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QExtendedTableWidget/qextendedtablewidget.h"

#include <QDebug>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QExtendedTableWidgetExample");

    tableWid = new QExtendedTableWidget(this);

    tableWid->setColumnCount(5);
    tableWid->setRowCount(10);


    tableWid->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWid->setHorizontalHeaderItem(0, new QTableWidgetItem(QStringLiteral("One")));
    tableWid->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    tableWid->setHorizontalHeaderItem(1, new QTableWidgetItem(QStringLiteral("Two")));
    tableWid->setHorizontalHeaderItem(2, new QTableWidgetItem(QStringLiteral("Three")));
    tableWid->setHorizontalHeaderItem(3, new QTableWidgetItem(QStringLiteral("Four")));
    tableWid->setHorizontalHeaderItem(4, new QTableWidgetItem(QStringLiteral("Five")));
    tableWid->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);


    tableWid->disableColumnForSelection(2);
    tableWid->disableColumnForSelection(3);

    ui->centralwidget->layout()->addWidget(tableWid);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_clicked(){
    tableWid->setColumnHidden(1, false);
}


void MainWindow::on_pushButton_2_clicked(){
    tableWid->setColumnHidden(1, true);
}

