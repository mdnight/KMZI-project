#ifndef KEYVALUEDIALOG_H
#define KEYVALUEDIALOG_H

#include <QDialog>

namespace Ui {
class KeyValueDialog;
}

class KeyValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyValueDialog(QWidget *parent = 0);
    ~KeyValueDialog();
    QMap<QString, QString> readDict() const;

private:
    Ui::KeyValueDialog *ui;
    QMap<QString, QString> *dict;

private slots:
    void moveUp();
    void moveDown();
    void slotRememberDict();
};

#endif // KEYVALUEDIALOG_H
