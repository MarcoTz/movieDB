#include "newmovie.h"
#include "ui_newmovie.h"
#include "qdebug.h"

newmovie::newmovie(QWidget *parent, int defaultNr) :
    QDialog(parent),
    ui(new Ui::newmovie)
{
    ui->setupUi(this);
    ui->nrEdit->setText(QString::number(defaultNr));
}

newmovie::~newmovie()
{
    delete ui;
}

void newmovie::on_cancelButton_clicked()
{
    this->done(0);
}

void newmovie::on_okButton_clicked()
{
    if(ui->nameEdit->text()!=""&&ui->nrEdit->text()!=""){
        emit addMovie(ui->nameEdit->text(),ui->nrEdit->text());
    }
    done(1);
}

void newmovie::on_nrEdit_editingFinished()
{
    ui->nrEdit->setText(QString::number(ui->nrEdit->text().toInt()));
}
