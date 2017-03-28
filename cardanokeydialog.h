#ifndef CARDANOKEYDIALOG_H
#define CARDANOKEYDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class CardanoKeyDialog;
}

class CardanoKeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CardanoKeyDialog(QWidget *parent = 0);
    ~CardanoKeyDialog();
    QVector<QVector<bool> > getMatrix();

private slots:
    void clearClose();
    void saveMatrix();
    //void toggleCells(QTableWidgetItem *item);

private:
    Ui::CardanoKeyDialog *ui;
    QVector<QVector<bool> > keyMatrix{ QVector<bool>(6), QVector<bool>(6), QVector<bool>(6), QVector<bool>(6), QVector<bool>(6), QVector<bool>(6) };
};

#endif // CARDANOKEYDIALOG_H
