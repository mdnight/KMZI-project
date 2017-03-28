#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractButton>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "simplereplacement.h"
#include "singleshift.h"
#include "doubletransposition.h"
#include "gronspheld.h"
#include "cardano.h"
#include "rsacrypt.h"
#include <QCheckBox>
#include <gammacypher.h>
#include <QRadioButton>
#include <QLineEdit>
#include <QDebug>
#include <QComboBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Karavai-project");
    ui->handmadeKey->setChecked(true);
    ui->keyLine->setVisible(false);
    ui->encrypt->setChecked(true);
    ui->genKey->setVisible(false);
    ui->key2Line->setVisible(false);
    ui->rsaKeyButton->setVisible(false);
    ui->cardanButton->setVisible(false);
    validatorList = new QList<QRegExpValidator*>();
    validatorList->append(new QRegExpValidator(QRegExp(QString("[А-ЕЖ-ИК-Я\\s]+")))); //gamma
    validatorList->append(new QRegExpValidator(QRegExp(QString("[A-ZА-ЕЖ-ИК-Я]+")))); //transpos
    validatorList->append(new QRegExpValidator(QRegExp(QString("[\\d]+")))); //grons
    kvd = new KeyValueDialog();
    rsakeyDialog = new RSAKeyDialog(this);
    cardKeyDialog = new CardanoKeyDialog(this);
    QObject::connect(ui->genKey, &QAbstractButton::clicked, [=] () {
        ui->keyLine->setEnabled(true);
    });
    QObject::connect(ui->fromFile, &QAbstractButton::clicked, [=] () {
        ui->keyLine->setEnabled(false);
    });
    QObject::connect(ui->handmadeKey, &QAbstractButton::clicked, [=] () {
        ui->keyLine->setEnabled(true);
        switch (ui->cyphersBox->currentIndex()) {
        case 0:
            ui->keyLine->setVisible(false);
            ui->keyPair->setVisible(true);
            break;
        case 1:
            ui->keyLine->setVisible(false);
            ui->keyPair->setVisible(true);
            break;
        case 2:
            ui->keyLine->setVisible(true);
            ui->keyPair->setVisible(false);
            break;
        }
    });
    QObject::connect(ui->clearPlainTextButton, &QPushButton::clicked, ui->plainText, &QPlainTextEdit::clear);
    QObject::connect(ui->clearCyphTextButton, &QPushButton::clicked, ui->cypherText, &QPlainTextEdit::clear);
    QObject::connect(ui->openPlainText, &QPushButton::clicked, [=] () {this->loadFile(ui->plainText);});
    QObject::connect(ui->openCyphText, &QPushButton::clicked, [=] () {this->loadFile(ui->cypherText);});
    QObject::connect(ui->keyPair, &QPushButton::clicked, kvd, &KeyValueDialog::show);
    QObject::connect(ui->doButton, &QPushButton::clicked, this, &MainWindow::performOperation);
    QObject::connect(ui->cyphersBox, SIGNAL(currentIndexChanged(int)), this, SLOT(toggleKeyInputWay(int)));
    QObject::connect(ui->plainHex, &QCheckBox::stateChanged, [=] () {this->convertText(ui->plainHex, ui->plainText);});
    QObject::connect(ui->cryptHex, &QCheckBox::stateChanged, [=] () {this->convertText(ui->cryptHex, ui->cypherText);});
    QObject::connect(ui->rsaKeyButton, &QPushButton::clicked, rsakeyDialog, &RSAKeyDialog::show);
    QObject::connect(ui->cardanButton, &QPushButton::clicked, cardKeyDialog, &CardanoKeyDialog::show);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete kvd;
    delete rsakeyDialog;
}

void MainWindow::loadFile(QPlainTextEdit *pte) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите файл"),
                                                    "/home",
                                                    tr("Any files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удается открыть файл"), QMessageBox::Ok);
    else {
        QString *text = new QString();
        QTextStream in(&file);
        while (!in.atEnd())
            text->append(in.readLine());
        file.close();

        if (text->length() > 5000)
            text->truncate(5000);
        *text = text->toUpper();
        text->remove(QRegExp(QString::fromUtf8("[^A-ZА-ЕЖ-ИК-Я\\s]")));
        pte->clear();
        pte->document()->setPlainText(*text);
        delete text;
    }
}

void MainWindow::performOperation()
{
    if (ui->encrypt->isChecked()) {
        switch (ui->cyphersBox->currentIndex()) {
        case 0: {
            if (ui->genKey->isChecked()) {

            }
            else if (ui->fromFile->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                SimpleReplacement *srepl = new SimpleReplacement(kvd->readDict());
                if (ui->plainText->document()->toPlainText().isEmpty()) {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Не введен открытый текст"));
                    break;
                }
                ui->cypherText->setPlainText(srepl->encrypt(ui->plainText->document()->toPlainText()));
                delete srepl;
                break;
            }

        }
        case 1: {
            if (ui->genKey->isChecked()) {

            }
            else if (ui->fromFile->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                SimpleReplacement *srepl = new SimpleReplacement(kvd->readDict());
                if (ui->plainText->document()->toPlainText().isEmpty()) {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Не введен открытый текст"));
                    break;
                }
                ui->cypherText->setPlainText(srepl->encrypt(ui->plainText->document()->toPlainText()));
                delete srepl;
                break;
            }

        }
        case 2: {
            GammaCypher gcyph(this);
            ui->plainText->setPlainText(ui->plainText->toPlainText().remove(QRegExp(QString::fromUtf8("[^А-ЕЖ-ИК-Я\\s]"))));
            if (ui->genKey->isChecked()) {
                gcyph.genNewGamma();
                ui->keyLine->setText(gcyph.getGamma());
                ui->cypherText->clear();
                ui->cypherText->setPlainText(gcyph.encrypt(ui->plainText->toPlainText()));
            }
            else if (ui->fromFile->isChecked()) {
                //gcyph.setGamma((*this->loadKey());
                ui->keyLine->clear();
                ui->keyLine->setText(gcyph.getGamma());
                QString cryptText = gcyph.encrypt(ui->plainText->toPlainText());
                ui->cypherText->setPlainText(cryptText);
            }
            else if (ui->handmadeKey->isChecked()) {
                gcyph.setGamma(ui->keyLine->text());
                QString cryptText = gcyph.encrypt(ui->plainText->toPlainText());
                ui->cypherText->document()->setPlainText(cryptText);
            }
            break;
        }
        case 3: {
            SingleShift sShift(this);
            ui->plainText->setPlainText(ui->plainText->toPlainText().remove(QRegExp(QString::fromUtf8("[^A-ZА-ЕЖ-ИК-Я\\s]"))));
            if (ui->genKey->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                sShift.setKey(ui->keyLine->text());
                ui->cypherText->clear();
                ui->cypherText->setPlainText(sShift.encrypt(ui->plainText->toPlainText()));
            }
            break;
        }
        case 4: {
            DoubleTransposition doubleTrans(this);
            if (ui->genKey->isChecked()){

            }
            else if (ui->handmadeKey->isChecked()) {
                doubleTrans.setKeys(ui->keyLine->text(), ui->key2Line->text());
                ui->cypherText->clear();
                ui->cypherText->setPlainText(doubleTrans.encrypt(ui->plainText->toPlainText()));
            }
            break;
        }
        case 5: {
            RSACrypt rsacrypt(ui->alphBox->currentIndex(), this);
            ui->plainText->setPlainText(ui->plainText->toPlainText().remove(QRegExp(QString::fromUtf8("[^A-ZА-ЕЖ-ИК-Я\\s]"))));
            if (ui->genKey->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                int e, d, n;
                rsakeyDialog->getPubKeyParams(e, n);
                rsakeyDialog->getPrivKeyParams(d, n);
                rsacrypt.setKeysParams(e, d, n);

                if (rsakeyDialog->isKeySet()) {
                    ui->cypherText->clear();
                    ui->cypherText->setPlainText(rsacrypt.encrypt(ui->plainText->toPlainText()));
                }
            }
            break;
        }
        case 6: {
            Cardano cardano(ui->alphBox->currentIndex(), this);
            ui->plainText->setPlainText(ui->plainText->toPlainText().remove(QRegExp(QString::fromUtf8("[^A-ZА-Я\\s]"))));
            if (ui->fromFile->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                cardano.setKey(cardKeyDialog->getMatrix());
                ui->cypherText->clear();
                ui->cypherText->setPlainText(cardano.encrypt(ui->plainText->toPlainText()));
            }
            break;
        }
        case 7: {
            Gronspheld grons(ui->alphBox->currentIndex(), this);
            if (ui->genKey->isChecked()) {
                QString newKey = grons.genNewKey();
                ui->keyLine->setText(newKey);
                ui->cypherText->clear();
                ui->cypherText->setPlainText(grons.encrypt(ui->plainText->toPlainText()));
            }
            else if (ui->handmadeKey->isChecked()) {
                grons.setKey(ui->keyLine->text());
                ui->cypherText->clear();
                ui->cypherText->setPlainText(grons.encrypt(ui->plainText->toPlainText()));
            }
        }
        }
    }
    else if (ui->decrypt->isChecked()) {
        switch (ui->cyphersBox->currentIndex()) {
        case 0: {
            if (ui->genKey->isChecked()) {

            }
            else if (ui->fromFile->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                SimpleReplacement *srepl = new SimpleReplacement(kvd->readDict());
                if (ui->cypherText->document()->toPlainText().isEmpty()) {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Не введен закрытый текст"));
                    break;
                }
                ui->plainText->setPlainText(srepl->decrypt(ui->cypherText->document()->toPlainText()));
                delete srepl;
                break;
            }

        }
        case 1: {
            if (ui->genKey->isChecked()) {

            }
            else if (ui->fromFile->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                SimpleReplacement *srepl = new SimpleReplacement(kvd->readDict());
                if (ui->cypherText->document()->toPlainText().isEmpty()) {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Не введен закрытый текст"));
                    break;
                }
                ui->plainText->setPlainText(srepl->decrypt(ui->cypherText->document()->toPlainText()));
                delete srepl;
                break;
            }
        }
        case 2: {
            GammaCypher gcyph(this);
            if (ui->genKey->isChecked()) {
                ui->keyLine->setText(gcyph.getGamma());
                ui->plainText->clear();
                ui->plainText->setPlainText(gcyph.decrypt(ui->cypherText->toPlainText()));
            }
            else if (ui->fromFile->isChecked()) {
                gcyph.setGamma(this->loadKey());
                ui->keyLine->clear();
                ui->keyLine->setText(gcyph.getGamma());
                QString cryptText = gcyph.encrypt(ui->plainText->document()->toPlainText());
                ui->cypherText->setPlainText(cryptText);
            }
            else if (ui->handmadeKey->isChecked()) {
                gcyph.setGamma(ui->keyLine->text());
                qDebug() << "HERE";
                QString plainText = gcyph.decrypt(ui->cypherText->document()->toPlainText());
                ui->plainText->document()->setPlainText(plainText);
            }
            break;
        }
        case 3:{
            SingleShift sShift(this);
            if (ui->genKey->isChecked()) {
            }
            else if (ui->handmadeKey->isChecked()) {
                sShift.setKey(ui->keyLine->text());
                ui->plainText->clear();
                ui->plainText->setPlainText(sShift.decrypt(ui->cypherText->toPlainText()));
            }
            break;
        }
        case 4: {
            DoubleTransposition doubleTrans(this);
            if (ui->genKey->isChecked()){

            }
            else if (ui->handmadeKey->isChecked()) {
                doubleTrans.setKeys(ui->keyLine->text(), ui->key2Line->text());
                ui->plainText->clear();
                ui->plainText->setPlainText(doubleTrans.decrypt(ui->cypherText->toPlainText()));
            }
            break;
        }
        case 5: {
            RSACrypt rsacrypt(ui->alphBox->currentIndex(), this);
            if (ui->genKey->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                int e, d, n;
                rsakeyDialog->getPubKeyParams(e, n);
                rsakeyDialog->getPrivKeyParams(d, n);
                rsacrypt.setKeysParams(e, d, n);

                if (rsakeyDialog->isKeySet()) {
                    ui->plainText->clear();
                    ui->plainText->setPlainText(rsacrypt.decrypt(ui->cypherText->toPlainText()));
                }
            }
            break;
        }
        case 6: {
            Cardano cardano(ui->alphBox->currentIndex(), this);
            ui->plainText->setPlainText(ui->plainText->toPlainText().remove(QRegExp(QString::fromUtf8("[^A-ZА-Я\\s]"))));
            if (ui->fromFile->isChecked()) {

            }
            else if (ui->handmadeKey->isChecked()) {
                qDebug() << cardKeyDialog->getMatrix();
                cardano.setKey(cardKeyDialog->getMatrix());
                ui->plainText->clear();
                ui->plainText->setPlainText(cardano.decrypt(ui->cypherText->toPlainText()));
            }
            break;
        }
        case 7:{
            Gronspheld grons(ui->alphBox->currentIndex(), this);
            if (ui->genKey->isChecked()) {
                QString newKey = grons.genNewKey();
                ui->keyLine->setText(newKey);
                ui->plainText->clear();
                ui->plainText->setPlainText(grons.decrypt(ui->cypherText->toPlainText()));
            }
            else if (ui->handmadeKey->isChecked()) {
                grons.setKey(ui->keyLine->text());
                ui->plainText->clear();
                ui->plainText->setPlainText(grons.decrypt(ui->cypherText->toPlainText()));
            }
            break;
        }
        }
    }
}

void MainWindow::toggleKeyInputWay(int i) {
    switch (i) {
    case 0:
        ui->genKey->setVisible(false);
        ui->keyLine->setVisible(false);
        ui->keyPair->setVisible(true);
        ui->fromFile->setVisible(true);
        ui->key2Line->setVisible(false);
        ui->alphBox->setVisible(false);
        ui->rsaKeyButton->setVisible(false);
        ui->cardanButton->setVisible(false);
        break;
    case 1:
        ui->genKey->setVisible(false);
        ui->keyLine->setVisible(false);
        ui->keyPair->setVisible(true);
        ui->fromFile->setVisible(true);
        ui->key2Line->setVisible(false);
        ui->alphBox->setVisible(false);
        ui->rsaKeyButton->setVisible(false);
        ui->cardanButton->setVisible(false);
        break;
    case 2:
        ui->genKey->setVisible(true);
        ui->keyLine->setVisible(true);
        ui->keyPair->setVisible(false);
        ui->fromFile->setVisible(true);
        ui->key2Line->setVisible(false);
        ui->alphBox->setVisible(false);
        ui->keyLine->setValidator(validatorList->at(0));
        ui->rsaKeyButton->setVisible(false);
        ui->cardanButton->setVisible(false);
        break;
    case 3:
        ui->genKey->setEnabled(true);
        ui->keyPair->setVisible(false);
        ui->keyLine->setVisible(true);
        ui->fromFile->setVisible(false);
        ui->key2Line->setVisible(false);
        ui->alphBox->setVisible(false);
        ui->keyLine->setValidator(validatorList->at(1));
        ui->rsaKeyButton->setVisible(false);
        ui->cardanButton->setVisible(false);
        break;
    case 4:
        ui->genKey->setVisible(true);
        ui->keyLine->setVisible(true);
        ui->key2Line->setVisible(true);
        ui->fromFile->setVisible(false);
        ui->alphBox->setVisible(false);
        ui->rsaKeyButton->setVisible(false);
        ui->cardanButton->setVisible(false);
        break;
    case 5:
        ui->rsaKeyButton->setVisible(true);
        ui->keyLine->setVisible(false);
        ui->key2Line->setVisible(false);
        ui->keyPair->setVisible(false);
        ui->cardanButton->setVisible(false);
        break;
    case 6:
        ui->keyLine->setVisible(false);
        ui->alphBox->setVisible(true);
        ui->genKey->setVisible(false);
        ui->rsaKeyButton->setVisible(false);
        ui->cardanButton->setVisible(true);
        ui->keyPair->setVisible(false);
        break;
    case 7:
        ui->alphBox->setVisible(true);
        ui->keyLine->setValidator(validatorList->at(2));
        ui->key2Line->setVisible(false);
        ui->fromFile->setVisible(false);
        ui->keyPair->setVisible(false);
        ui->keyLine->setVisible(true);
        ui->genKey->setVisible(true);
        ui->rsaKeyButton->setVisible(false);
        ui->cardanButton->setVisible(false);
        break;
    }
}

void MainWindow::convertText(QCheckBox *cbox, QPlainTextEdit *pte)
{
    if (cbox->isChecked()) {
        QByteArray array;
        array.append(pte->document()->toPlainText());
        pte->clear();
        pte->setPlainText(QString(array.toHex()));
        ui->doButton->setEnabled(false);
    }
    else {
        QByteArray array;
        array.append(pte->document()->toPlainText());
        pte->clear();
        pte->setPlainText(QString(QByteArray::fromHex(array)));
        ui->doButton->setEnabled(true);
    }
}

QString MainWindow::loadKey() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите файл"),
                                                    "/home",
                                                    tr("Text (*.txt);; Any files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удается открыть файл"), QMessageBox::Ok);
        return QString("");
    }
    else {
        QString text;
        QTextStream in(&file);
        while (!in.atEnd())
            text.append(in.readLine());
        file.close();

        if (text.length() > 5000)
            text.truncate(5000);
        text = text.toUpper();
        text.remove(QRegExp(QString::fromUtf8("[^A-ZА-Я\\s]")));
        return text;
    }
}
