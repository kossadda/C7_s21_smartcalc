#include "s21_credit_table.h"
#include "ui_s21_credit_table.h"

s21_credit_table::s21_credit_table(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::s21_credit_table)
{
    ui->setupUi(this);
}

s21_credit_table::~s21_credit_table()
{
    delete ui;
}

Ui::s21_credit_table* s21_credit_table::getUi() const
{
    return ui;
}
