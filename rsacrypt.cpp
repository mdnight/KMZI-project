#include "rsacrypt.h"
#include <QDebug>

RSACrypt::RSACrypt(int alph, QObject *parent) : QObject(parent)
{
    switch (alph) {
    case 0:
        alpha = new QString(" ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        break;
    case 1:
        alpha = new QString(" АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
        break;
    }
}

QString RSACrypt::encrypt(QString ptext)
{
    QString ctext;
    for (auto i : ptext){
        ctext += QString::number((power(alpha->indexOf(i), e) % n).toUnsignedInt());
        ctext += " ";
    }
    ctext.truncate(ctext.size()-1);
    return ctext;
}

QString RSACrypt::decrypt(QString ctext)
{
    QString ptext;
    QStringList ctextList = ctext.split(' ', QString::SkipEmptyParts);
    for (auto i : ctextList) {
        ptext += alpha->at((power(i.toInt(), d) % n).toUnsignedInt());
    }
    return ptext;
}

void RSACrypt::setKeysParams(int eParam, int dParam, int nParam)
{
    e = eParam;
    d = dParam;
    n = nParam;
}

BigUnsigned RSACrypt::power(BigUnsigned x, BigUnsigned y)
{
    BigUnsigned temp;
    if (y == 0)
        return 1;

    temp = power(x, y / 2);
    if ((y % 2) == 0)
        return temp * temp;
    else
        return x * temp * temp;
}

