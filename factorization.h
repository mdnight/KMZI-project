#ifndef FACTORIZATION_H
#define FACTORIZATION_H

#include <QObject>
#include <QVector>
#include "bigint/BigIntegerLibrary.hh"

class Factorization : public QObject
{
    Q_OBJECT
public:
    explicit Factorization(QObject *parent = 0);
    static QVector<BigInteger> factorize(std::__cxx11::string number);

};

#endif // FACTORIZATION_H
