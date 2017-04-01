#include "symbolfreqanalysis.h"

    SymbolFreqAnalysis::SymbolFreqAnalysis(int alp, QObject *parent) : QObject(parent)
    {
        switch (alp) {
        case 0:
            alpha = QString(" ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            break;
        case 1:
            alpha = QString(" АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
            break;
        }
        for (auto i = 0; i < alpha.size(); i++)
            freq.insert(alpha.mid(i, 1), 0);
    }

    QMap<QString, int> SymbolFreqAnalysis::calculate(const QString &ctext)
    {
        for (auto i = 0; i < ctext.size(); i++)
            if (alpha.contains(ctext.mid(i, 1)))
                freq[ctext.mid(i, 1)]++;
        return freq;
    }

    QMap<QString, int> SymbolFreqAnalysis::getFreqrate()
    {
        return freq;
    }



