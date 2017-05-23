#ifndef SYMBOLFREQANALYSIS_H
#define SYMBOLFREQANALYSIS_H

#include <QObject>
#include <QMap>


class SymbolFreqAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit SymbolFreqAnalysis(int alpha, QObject *parent = 0);
    QMap<QString, int> calculate(const QString &ctext);
    QMap<QString, int> getFreqrate();
private:
    QMap<QString, int> freq;
    QString alpha;
};

#endif // SYMBOLFREQANALYSIS_H
