#ifndef CARDANO_H
#define CARDANO_H

#include <QObject>
#include <QVector>

class Cardano : public QObject
{
    Q_OBJECT
public:
    explicit Cardano(int lang, QObject *parent = 0);
    void setKey(QVector<QVector<bool> > key);
    QString encrypt(const QString &ptext);
    QString decrypt(const QString &ctext);

signals:

public slots:
private:
    QVector<QVector<bool> > keyMatrix;
    void rotateKeyMatrix();
    QString alpha;
};

#endif // CARDANO_H
