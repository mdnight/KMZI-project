#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include "keyvaluedialog.h"
#include "rsakeydialog.h"
#include <QCheckBox>
#include <QRegExpValidator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QString loadKey();
private slots:
    void loadFile(QPlainTextEdit *pte);
    void performOperation();
    void toggleKeyInputWay(int i);
    void convertText(QCheckBox *cbox, QPlainTextEdit *pte);
private:
    Ui::MainWindow *ui;
    KeyValueDialog *kvd;
    RSAKeyDialog *rsakeyDialog;
    QList<QRegExpValidator*> *validatorList;
};

#endif // MAINWINDOW_H
