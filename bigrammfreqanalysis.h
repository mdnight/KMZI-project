#ifndef BIGRAMMFREQANALYSIS_H
#define BIGRAMMFREQANALYSIS_H

#include <QObject>
#include <QMap>
#include <QVector>

class BigrammFreqAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit BigrammFreqAnalysis(QObject *parent = 0);
    static QMap<QString, int> calculate(const QString &ctext, int size);
private:
};

#endif // BIGRAMMFREQANALYSIS_H
