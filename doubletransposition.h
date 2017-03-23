#ifndef DOUBLETRANSPOSITION_H
#define DOUBLETRANSPOSITION_H

#include <QObject>
#include "singleshift.h"

class DoubleTransposition : public QObject
{
  Q_OBJECT
public:
  explicit DoubleTransposition(QObject *parent = 0);
  ~DoubleTransposition();
  QString encrypt(QString input, QChar padChar = QChar(' '));
  QString decrypt(QString input);
  void setKeys(QString k1, QString k2);

private:
  QString key1, key2;
  SingleShift* sShift;
  QString transpose(QString input);
  QString backTranspose(QString input);
};

#endif // DOUBLETRANSPOSITION_H
