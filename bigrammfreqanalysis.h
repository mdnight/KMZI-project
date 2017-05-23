#ifndef BIGRAMMFREQANALYSIS_H
#define BIGRAMMFREQANALYSIS_H

#include <QObject>
#include <QMap>

class BigrammFreqAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit BigrammFreqAnalysis(QObject *parent = 0);
    static QMap<QString, int> calculate(int alp, const QString &ctext);
private:
};

#endif // BIGRAMMFREQANALYSIS_H
