#include "cardano.h"
#include <QDebug>

Cardano::Cardano(int lang, QObject *parent) : QObject(parent)
{
    switch(lang) {
    case 0:
        alpha = QString(" ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        break;
    case 1:
        alpha = QString(" АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
    }
}

void Cardano::setKey(QVector<QVector<bool> > key)
{
    keyMatrix = key;
}

QString Cardano::encrypt(const QString &ptext)
{
    QVector<QVector<int> > text = {
        QVector<int>(6), QVector<int>(6), QVector<int>(6),
        QVector<int>(6), QVector<int>(6), QVector<int>(6)
    };
    int count = 0;
    for (auto round = 0; round < 4; round++) {
        for (auto i = 0; i < 6; i++)
            for (auto j = 0; j < 6; j++){
                if (keyMatrix[i][j])
                    text[i][j] = alpha.indexOf(ptext.mid(count++, 1));
            }
        rotateKeyMatrix();
    }
    qDebug() << count;
    QString result;
    for (auto i = 0; i < 6; i++)
        for (auto j = 0; j < 6; j++ )
            result += alpha.mid(text[i][j], 1);
    return result;
}

QString Cardano::decrypt(const QString &ctext)
{
    QVector<QVector<int> > text = {
        QVector<int>(6), QVector<int>(6), QVector<int>(6),
        QVector<int>(6), QVector<int>(6), QVector<int>(6)
    };
    int count = 0;
    for (auto i = 0; i < 6; i++)
        for (auto j = 0; j < 6; j++)
            text[i][j] = alpha.indexOf(ctext.mid(count++, 1));

    QString result;
    for (auto round = 0; round < 4; round++) {
        for (auto i = 0; i < 6; i++)
            for (auto j = 0; j < 6; j++) {
                if (keyMatrix[i][j])
                    result += alpha.mid(text[i][j], 1);
            }
        rotateKeyMatrix();
    }
    return result;
}

void Cardano::rotateKeyMatrix() //TODO: ПОМЕНЯТЬ НАПРАВЛЕНИЕ ПОВОРОТА. СЕЙЧАС ПОВОРАЧИВАЕТ ПО ЧАСОВОЙ СТРЕЛКЕ)
{
    QChar tmp;
    QVector<QVector<bool> > tmpMatrix = {
        QVector<bool>(6), QVector<bool>(6), QVector<bool>(6),
        QVector<bool>(6), QVector<bool>(6), QVector<bool>(6)
    };
    for (auto i = 0; i < 6; i++)
        for (auto j = 0; j < 6; j++)
            tmpMatrix[i][j] = keyMatrix[6-j-1][i];
    keyMatrix =  tmpMatrix;
}


