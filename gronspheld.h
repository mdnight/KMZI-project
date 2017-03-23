#ifndef GRONSPHELD_H
#define GRONSPHELD_H

#include <QObject>

class Gronspheld : public QObject
{
  Q_OBJECT
public:
  explicit Gronspheld(int lang, QObject *parent = 0);
  ~Gronspheld();
  void setKey(QString k);
  QString encrypt(QString ptext);
  QString decrypt(QString ctext);
  QString genNewKey();

private:
  QString *key;
  QString *alpha;
};

#endif // GRONSPHELD_H
