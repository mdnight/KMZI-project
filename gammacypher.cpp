#include "gammacypher.h"
#include <random>
#include <QDebug>
#include <QTextCodec>

GammaCypher::GammaCypher(QObject *parent) : QObject(parent)
{
  gamma = new QString();
  alpha = new QString(" АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
}

GammaCypher::~GammaCypher()
{
  delete gamma;
  delete alpha;
}

QString GammaCypher::encrypt(const QString &ptext) const
{
  QString arr;
  int tmpAlp = 0, tmpGam = 0;
  for (auto i = 0; i<ptext.size(); i++) {
      tmpAlp = alpha->indexOf(ptext[i]);
      tmpGam = alpha->indexOf(gamma->at(i % gamma->size()));
      arr.append(alpha->at(tmpAlp ^ tmpGam)); //Ссаный английский алфавит не кратен степени 2, так что липила, иди нахуй
    }
  return arr;
}

QString GammaCypher::decrypt(const QString &ctext) const
{
  QString arr;
  int Ci = 0, Gi = 0;
  for (auto i = 0; i<ctext.size(); i++) {
      Ci = alpha->indexOf(ctext[i]);
      Gi = alpha->indexOf(gamma->at(i % gamma->size()));
      arr.append(alpha->at(Ci ^ Gi)); //Ссаный английский алфавит не кратен степени 2, так что липила, иди нахуй
    }
  return arr;
}

int GammaCypher::genNewGamma()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, alpha->size()-1);
    gamma->clear();

    for (int i=0; i<32; ++i)
        this->gamma->append(alpha->at(dist(mt)));
    return 0;
}

QString GammaCypher::getGamma() const {
    return QString(this->gamma->data());
}

void GammaCypher::setGamma(QString gammatext) const{
  gamma->clear();
  gamma->append(gammatext);
}
