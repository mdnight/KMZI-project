#include "cardanokeydialog.h"
#include "ui_cardanokeydialog.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QDebug>

CardanoKeyDialog::CardanoKeyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardanoKeyDialog)
{
    ui->setupUi(this);

    ui->keyTable->setColumnCount(6);
    ui->keyTable->setRowCount(6);
    ui->keyTable->horizontalHeader()->hide();
    ui->keyTable->verticalHeader()->hide();
    ui->keyTable->resizeColumnsToContents();

    for (auto i = 0; i < ui->keyTable->rowCount(); i++)
        for (auto j = 0; j < ui->keyTable->columnCount(); j++) {
            ui->keyTable->setItem(i, j, new QTableWidgetItem());
            ui->keyTable->item(i, j)->setCheckState(Qt::Unchecked);
        }
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &CardanoKeyDialog::clearClose);
    QObject::connect(ui->okButton, &QPushButton::clicked, this, &CardanoKeyDialog::saveMatrix);
    //QObject::connect(ui->keyTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(toggleCells(QTableWidgetItem*)));

}

CardanoKeyDialog::~CardanoKeyDialog()
{
    delete ui;
}

QVector<QVector<bool> > CardanoKeyDialog::getMatrix()
{
    return keyMatrix;
}

void CardanoKeyDialog::clearClose()
{
    for (auto i = 0; i < ui->keyTable->rowCount(); i++)
        for (auto j = 0; j < ui->keyTable->columnCount(); j++) {
            ui->keyTable->item(i,j)->setCheckState(Qt::Unchecked);
            keyMatrix[i][j] = false;
    }
    close();
}

void CardanoKeyDialog::saveMatrix()
{
    for (auto i = 0; i < ui->keyTable->rowCount(); i++)
        for (auto j = 0; j < ui->keyTable->columnCount(); j++) {
            if (ui->keyTable->item(i, j)->checkState() == Qt::Checked) {
                keyMatrix[i][j] = true;
            }
        }
    close();
}

//void CardanoKeyDialog::toggleCells(QTableWidgetItem *item)
//{
//    for (auto i = 0; i < ui->keyTable->rowCount(); i++) {
//        if (i == item->row())
//            continue;
//        if (ui->keyTable->item(i, item->column())->checkState() == Qt::Checked)
//            ui->keyTable->item(i, item->column())->setFlags(ui->keyTable->item(i, item->column())->flags() ^ Qt::ItemIsEnabled);
////        else
////            ui->keyTable->cellWidget(i, item->column())->setEnabled(true);
//    }
//}
