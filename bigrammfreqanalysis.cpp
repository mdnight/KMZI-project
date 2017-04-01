#include "bigrammfreqanalysis.h"
#include <QMap>

BigrammFreqAnalysis::BigrammFreqAnalysis(QObject *parent) : QObject(parent)
{
}

QMap<QString, int> BigrammFreqAnalysis::calculate(int alp, const QString &ctext)
{
    QString alpha;
    switch (alp) {
    case 0:
        alpha = QString(" ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        break;
    case 1:
        alpha = QString(" АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
        break;
    }
    QMap<QString, int> freq;
    for (auto i = 0; i < alpha.size(); i++)
        for (auto j = 0; j < alpha.size(); j++)
            freq[alpha.mid(i, 1) + alpha.mid(j, 1)] = 0;
    for (auto i : freq.keys())
        freq[i] = ctext.count(i);
    return freq;
}


