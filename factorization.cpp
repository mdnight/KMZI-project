#include "factorization.h"
#include "bigint/BigIntegerLibrary.hh"
#include <QDebug>

Factorization::Factorization(QObject *parent) : QObject(parent)
{

}

QVector<BigInteger> Factorization::factorize(std::string number)
{
    QVector<BigInteger> result;
    BigInteger n = stringToBigInteger(number);
    BigInteger i = 2;
    while (n > i * i)
        if ((n % i).isZero()) {
            result.append(i);
            n /= i;
        }
        else
            i++;
    if (n > 1)
        result.append(n);
    return result;
}
