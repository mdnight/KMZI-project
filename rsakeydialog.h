#ifndef RSAKEYDIALOG_H
#define RSAKEYDIALOG_H

#include <QDialog>

namespace Ui {
class RSAKeyDialog;
}

class RSAKeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RSAKeyDialog(QWidget *parent = 0);
    ~RSAKeyDialog();
    void getPubKeyParams(int &ee, int &nn);
    void getPrivKeyParams(int &dd, int &nn);
    bool isKeySet();

private:
    Ui::RSAKeyDialog *ui;
    int p, q, n, phi, e, d;
    QList<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                         31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                         73, 79, 83, 89, 97};
    bool isPrimal(int n);
    bool setKeyFlag = false;

private slots:
    void calculate();
};

#endif // RSAKEYDIALOG_H
