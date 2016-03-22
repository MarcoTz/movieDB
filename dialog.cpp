#include "dialog.h"
#include "ui_dialog.h"
#include <qdebug.h>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_cancel_clicked()
{
    done(1);
}

void Dialog::on_search_clicked()
{
    QString searchStr = ui->searchString->text();
    int searchRow = 0;

    if(ui->radioNr->isChecked()){
        searchRow=1;
        if(searchStr.toInt()==0){
            QMessageBox::information(this,"Keine Zahl","Nr muss eine Zahl sein(nicht 0)",QMessageBox::Ok);
            return;
        }
    }
    emit startSearch(searchStr,searchRow);
    done(1);
}
