#ifndef SINGLESHIFT_H
#define SINGLESHIFT_H

#include <QObject>

class SingleShift : public QObject
{
  Q_OBJECT
public:
  explicit SingleShift(QObject *parent = 0);
  QString encrypt(QString input, QChar padChar = QChar(' '));
  QString decrypt(QString input);
  ~SingleShift();
  typedef struct {
          int Key;
          QChar Value;
  } KeyValuePair;
  void setKey(QString k);

private:
  QString PadRight(QString str, int max, QChar padChar);
  int* GetShiftIndexes(QString key);
  QString key;

};

#endif // SINGLESHIFT_H
