#include "s21_credit.h"
#include "s21_deposit.h"
#include "s21_smartcalc.h"
#include "ui_s21_credit.h"

s21_credit::s21_credit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::s21_credit)
{
    ui->setupUi(this);
    ui->setupUi(this);
    ui->creditBox->addItem("Кредитный");
    ui->creditBox->addItem("Инженерный");
    ui->creditBox->addItem("Депозитный");

    connect(ui->creditBox, SIGNAL(activated(int)), this, SLOT(change_credit(int)));
}

s21_credit::~s21_credit()
{
    delete ui;
}

void s21_credit::change_credit(int index)
{
    QPoint currentPosGlobal = this->mapToGlobal(QPoint(0, 0));
    QSize currentSize = this->size();
    if(index == 1) {
        this->close();
        s21_smartcalc *depositWindow = new s21_smartcalc();
        depositWindow->setGeometry(currentPosGlobal.x(), currentPosGlobal.y(), currentSize.width(), currentSize.height());
        depositWindow->show();
    } else if(index == 2) {
        this->close();
        s21_deposit *depositWindow = new s21_deposit();
        depositWindow->setGeometry(currentPosGlobal.x(), currentPosGlobal.y(), currentSize.width(), currentSize.height());
        depositWindow->show();
    }
}
