#include "doubletransposition.h"
#include <list>
#include <cmath>
#include <QDebug>
using namespace std;

DoubleTransposition::DoubleTransposition(QObject *parent) : QObject(parent)
{
  sShift = new SingleShift(this);
}

DoubleTransposition::~DoubleTransposition()
{

}

QString DoubleTransposition::encrypt(QString input, QChar padChar)
{
    input += QString(" ").repeated(key1.size()*key2.size() - input.size());
    sShift->setKey(key1);
    input = sShift->encrypt(input, padChar);
    sShift->setKey(key2);
    input = sShift->encrypt(input, padChar);
    input = transpose(input);
    return input;
}

QString DoubleTransposition::decrypt(QString input)
{
    sShift->setKey(key2);
    input = backTranspose(input);
    input = sShift->decrypt(input);
    sShift->setKey(key1);
    input = sShift->decrypt(input);
    return input;
}

void DoubleTransposition::setKeys(QString k1, QString k2)
{
    key1 = k1;
    key2 = k2;
}

QString DoubleTransposition::transpose(QString input)
{
    QString result;
    for (auto i = 0; i < key1.size(); i++)
        for (auto j = 0; j < key2.size(); j++)
            result += input[key1.size()*j+i];
    return result;
}

QString DoubleTransposition::backTranspose(QString input)
{
    QString result;
    result.resize(input.size());
    int cnt = 0;
    for (auto j = 0; j < key1.size(); j++)
        for (auto i = 0; i < key2.size(); i++)
            result[key1.size()*i+j] = input[cnt++]; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return result;
}
