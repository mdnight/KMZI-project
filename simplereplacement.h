#ifndef SIMPLEREPLACEMENT_H
#define SIMPLEREPLACEMENT_H

#include <QObject>
#include <QMap>

class SimpleReplacement : public QObject
{
    Q_OBJECT
public:
    explicit SimpleReplacement(QMap<QString, QString> dictionary, QObject *parent = 0);
    QString encrypt(const QString plainText);
    QString decrypt(const QString &cryptText) const;
    ~SimpleReplacement();

signals:

public slots:

private:
    QMap<QString, QString> *dict;
};

#endif // SIMPLEREPLACEMENT_H
