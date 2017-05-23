#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <QObject>

class Bruteforce : public QObject
{
    Q_OBJECT
public:
    explicit Bruteforce(QObject *parent = 0);
    static QList<std::tuple<int, int, QString> > bruteRSA(int eParam, int nParam, int lang, const QString &ctext);
    static QList<std::tuple<QString, QString> > bruteSimpleReplacement(const QString &ctext);
    static QList<std::tuple<QString, QString> > bruteDoubleTransposition(QString);
    static QList<std::tuple<int, QString> > bruteGronsfeld(int lang, int range, const QString &ctext);
};

#endif // BRUTEFORCE_H
