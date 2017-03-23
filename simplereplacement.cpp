#include "simplereplacement.h"

SimpleReplacement::SimpleReplacement(QMap<QString, QString> dictionary, QObject *parent) : QObject(parent)
{
    dict = new QMap<QString, QString>(dictionary);

}

QString SimpleReplacement::encrypt(const QString plainText)
{
    QString cryptText("");
    for (auto i : plainText) {
        cryptText.append(dict->value(i));
    }
    return cryptText;
}

QString SimpleReplacement::decrypt(const QString &cryptText) const
{
    QString plainText("");
    for (auto i : cryptText) {
        plainText.append(dict->key(i));
    }
    return plainText;
}

SimpleReplacement::~SimpleReplacement()
{
}
