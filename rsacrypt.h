#ifndef RSACRYPT_H
#define RSACRYPT_H

#include <QObject>
#include "bigint/BigIntegerLibrary.hh"

class RSACrypt : public QObject
{
    Q_OBJECT
public:
    explicit RSACrypt(int alph, QObject *parent = 0);
    QString encrypt(QString ptext);
    QString decrypt(QString ctext);
    void setKeysParams(int eParam, int dParam, int nParam);

private:
    QString *alpha;
    int n, e, d;

    BigUnsigned power(BigUnsigned x, BigUnsigned y);
};

#endif // RSACRYPT_H
