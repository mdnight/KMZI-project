#include "keyvaluedialog.h"
#include "ui_keyvaluedialog.h"
#include <QTableWidget>

KeyValueDialog::KeyValueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyValueDialog)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(60);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    dict = new QMap<QString, QString>({
                                      {QString(" "), QString(" ")}, {QString("A"), QString("A")},
                                      {QString("B"), QString("B")}, {QString("C"), QString("C")},
                                      {QString("D"), QString("D")}, {QString("E"), QString("E")},
                                      {QString("F"), QString("F")}, {QString("G"), QString("G")},
                                      {QString("H"), QString("H")}, {QString("I"), QString("I")},
                                      {QString("J"), QString("J")}, {QString("K"), QString("K")},
                                      {QString("L"), QString("L")}, {QString("M"), QString("M")},
                                      {QString("N"), QString("N")}, {QString("O"), QString("O")},
                                      {QString("P"), QString("P")}, {QString("Q"), QString("Q")},
                                      {QString("R"), QString("R")}, {QString("S"), QString("S")},
                                      {QString("T"), QString("T")}, {QString("U"), QString("U")},
                                      {QString("V"), QString("V")}, {QString("W"), QString("W")},
                                      {QString("X"), QString("X")}, {QString("Y"), QString("Y")},
                                      {QString("Z"), QString("Z")}, {QString("А"), QString("А")},
                                      {QString("Б"), QString("Б")}, {QString("В"), QString("В")},
                                      {QString("Г"), QString("Г")}, {QString("Д"), QString("Д")},
                                      {QString("Е"), QString("Е")}, {QString("Ж"), QString("Ж")},
                                      {QString("З"), QString("З")}, {QString("И"), QString("И")},
                                      {QString("К"), QString("К")},
                                      {QString("Л"), QString("Л")}, {QString("М"), QString("М")},
                                      {QString("Н"), QString("Н")}, {QString("О"), QString("О")},
                                      {QString("П"), QString("П")}, {QString("Р"), QString("Р")},
                                      {QString("С"), QString("С")}, {QString("Т"), QString("Т")},
                                      {QString("У"), QString("У")}, {QString("Ф"), QString("Ф")},
                                      {QString("Х"), QString("Х")}, {QString("Ц"), QString("Ц")},
                                      {QString("Ч"), QString("Ч")}, {QString("Ш"), QString("Ш")},
                                      {QString("Щ"), QString("Щ")}, {QString("Ъ"), QString("Ъ")},
                                      {QString("Ы"), QString("Ы")}, {QString("Ь"), QString("Ь")},
                                      {QString("Э"), QString("Э")}, {QString("Ю"), QString("Ю")},
                                      {QString("Я"), QString("Я")}});

    for (auto i = 0; i < dict->keys().length(); i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(dict->keys()[i]));
        ui->tableWidget->item(i,0)->setFlags(ui->tableWidget->item(i,0)->flags() ^ Qt::ItemIsEditable
                                             ^ Qt::ItemIsSelectable);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(dict->keys()[i]));
    }

    connect(ui->upButton, &QPushButton::clicked, this, &KeyValueDialog::moveUp);
    connect(ui->downButton, &QPushButton::clicked, this, &KeyValueDialog::moveDown);
    connect(ui->rememberDictButton, &QPushButton::clicked, this, &KeyValueDialog::slotRememberDict);
}

KeyValueDialog::~KeyValueDialog()
{
    delete ui;
}

QMap<QString, QString> KeyValueDialog::readDict() const
{
    return *dict;
}

void KeyValueDialog::moveUp() {
    QTableWidgetItem *tmpItem = new QTableWidgetItem(ui->tableWidget->item(0,1)->text());
    delete ui->tableWidget->item(0,1);
    QTableWidgetItem *tmp;
    for (auto i = 0; i < ui->tableWidget->rowCount() - 1; i++) {
        tmp = new QTableWidgetItem(ui->tableWidget->item((i+1) % ui->tableWidget->rowCount(), 1)->text());
        ui->tableWidget->setItem(i, 1, tmp);
        delete ui->tableWidget->item((i+1) % ui->tableWidget->rowCount(), 1);

    }
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, tmpItem);
}

void KeyValueDialog::moveDown() {
    QTableWidgetItem *tmpItem = new QTableWidgetItem(ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->text());
    delete ui->tableWidget->item(ui->tableWidget->rowCount()-1, 1);
    QTableWidgetItem *tmp;
    for (auto i = ui->tableWidget->rowCount() - 1; i > 0; i--) {
        tmp = new QTableWidgetItem(ui->tableWidget->item((i-1) % ui->tableWidget->rowCount(), 1)->text());
        ui->tableWidget->setItem(i, 1, tmp);
        delete ui->tableWidget->item((i-1) % ui->tableWidget->rowCount(), 1);

    }
    ui->tableWidget->setItem(0, 1, tmpItem);
}

void KeyValueDialog::slotRememberDict()
{
    for (auto i = 0; i < ui->tableWidget->rowCount(); i++) {
        dict->insert(ui->tableWidget->item(i,0)->text(), ui->tableWidget->item(i,1)->text());
    }
}
