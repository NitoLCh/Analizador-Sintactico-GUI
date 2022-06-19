#include "dialog.h"
#include "ui_dialog.h"

// PRUNEDA NO HAGAS PUSH SIN AUTORIZACION DE JORGE D:<

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

}

void Dialog::on_pushButton_2_clicked()
{

}

void Dialog::on_pushButton_3_clicked()
{
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
    ui->textEdit_3->setText("");
}

void Dialog::on_pushButton_5_clicked()
{
    exit(-1);
}

