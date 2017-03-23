#ifndef GAMMACYPHER_H
#define GAMMACYPHER_H

#include <QObject>

class GammaCypher : public QObject
{
    Q_OBJECT
public:
    explicit GammaCypher(QObject *parent = 0);
    ~GammaCypher();
    QString encrypt(const QString &ptext) const;
    QString decrypt(const QString &ctext) const;
    QString getGamma() const;
    int genNewGamma();    
    void setGamma(QString gammatext) const;
signals:

public slots:
private:
    QString *gamma;
    QString *alpha;
};

#endif // GAMMACYPHER_H
