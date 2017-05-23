#include "rsakeydialog.h"
#include "ui_rsakeydialog.h"
#include <algorithm>
#include <QMessageBox>
#include <QDebug>

RSAKeyDialog::RSAKeyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RSAKeyDialog)
{
    ui->setupUi(this);    
    ui->pLine->setValidator(new QRegExpValidator(QRegExp("[\\d]{1,2}"), this));
    ui->qLine->setValidator(new QRegExpValidator(QRegExp("[\\d]{1,2}"), this));
    QObject::connect(ui->calcButton, SIGNAL(clicked()), this, SLOT(calculate()));
    QObject::connect(ui->cancelButton, &QPushButton::clicked, [=] () {
        p = q = n = phi = e = d = 0;
        this->close();
    });
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(close()));
}

RSAKeyDialog::~RSAKeyDialog()
{
    delete ui;
}

void RSAKeyDialog::getPubKeyParams(int &ee, int &nn)
{
    ee = e;
    nn = n;
}

void RSAKeyDialog::getPrivKeyParams(int &dd, int &nn)
{
    dd = d;
    nn = n;
}

bool RSAKeyDialog::isKeySet()
{
    return setKeyFlag;
}

QList<int> RSAKeyDialog::getPrimesList() const
{
    return primes;
}

void RSAKeyDialog::setPrimes(int pParam, int qParam)
{
    ui->pLine->setText(QString::number(pParam));
    ui->qLine->setText(QString::number(qParam));
    while (ui->qLine->text() == ui->pLine->text())
        ui->qLine->setText(QString::number(qParam));
    this->calculate();
}

void RSAKeyDialog::calculate()
{
    if (ui->pLine->text().isEmpty() || ui->qLine->text().isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не указано значение p или q"), QMessageBox::Ok);
        return;
    }
    if (!isPrimal(ui->pLine->text().toInt()) || !isPrimal(ui->qLine->text().toInt())) {
        QMessageBox::warning(this, tr("Ошибка"), tr("p или q не является простым числом"), QMessageBox::Ok);
        return;
    }
    n = ui->pLine->text().toInt() * ui->qLine->text().toInt();
    phi = (ui->pLine->text().toInt() - 1) * (ui->qLine->text().toInt() - 1);
    for (auto i = 2; i < 100; i++) {
        if (std::__gcd(phi, i) == 1) {
            e = i;
            break;
        }
    }
    for (auto i = phi; i > 0; i--) {
        if ((i * e) % phi == 1) {
            d = i;
            break;
        }
    }
    ui->nLabel->setText(QString::number(n));
    ui->eLabel->setText(QString::number(e));
    ui->nnLabel->setText(QString::number(n));
    ui->dLabel->setText(QString::number(d));
    setKeyFlag = true;
}

bool RSAKeyDialog::isPrimal(int n)
{
    if (primes.indexOf(n) == -1)
        return false;
    return true;
}
