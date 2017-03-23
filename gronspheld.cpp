#include "gronspheld.h"
#include <random>
#include <QDebug>

Gronspheld::Gronspheld(int lang, QObject *parent) : QObject(parent)
{
    key = new QString();
    switch (lang) {
    case 0:
        alpha = new QString(" ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        break;
    case 1:
        alpha = new QString(" АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
    }

}

Gronspheld::~Gronspheld()
{

}

void Gronspheld::setKey(QString k)
{
    key->clear();
    key->append(k);
}

QString Gronspheld::encrypt(QString ptext)
{
    int offset = 0, indexOf = 0;
    QString ctext;
    QString newKey = key->repeated((ptext.size() / key->size()) + 1);
    if (newKey.size() > ptext.size())
        newKey.truncate(ptext.size());
    for (auto i = 0; i < ptext.size(); i++) {
        indexOf = alpha->indexOf(ptext.at(i));
        if ((indexOf + newKey.at(i).digitValue()) >= alpha->size()) {
            offset = (indexOf + newKey.at(i).digitValue()) % alpha->size();
        }
        else
            offset = indexOf + newKey.at(i).digitValue();
        qDebug() << offset;
        ctext.append(alpha->at(offset));
    }
    return ctext;
}

QString Gronspheld::decrypt(QString ctext)
{
    int offset = 0, indexOf = 0;
    QString ptext;
    QString newKey = key->repeated((ctext.size() / key->size()) + 1);
    if (newKey.size() > ctext.size())
        newKey.truncate(ctext.size());
    for (auto i = 0; i < ctext.size(); i++) {
        indexOf = alpha->indexOf(ctext.at(i));
        if ((indexOf - newKey.at(i).digitValue()) < 0)
            offset = indexOf - newKey.at(i).digitValue() + alpha->size();
        else
            offset = indexOf - newKey.at(i).digitValue();
        ptext.append(alpha->at(offset));
    }
    return ptext;
}

QString Gronspheld::genNewKey()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned int> dist(0, (unsigned int) -2);
    key->clear();
    key->append(QString::number(dist(mt)));
    return *key;
}
