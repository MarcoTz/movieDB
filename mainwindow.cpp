#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QTextStream>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("movies");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();

    if(!ok){
        qApp->exit(1);
    }

    MainWindow::LoadDB();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cancel_clicked()
{
    LoadDB();
}

void MainWindow::LoadDB(){

    changedItems.clear();

    searchDialog = new Dialog(this);
    connect(searchDialog,SIGNAL(startSearch(QString,int)),this,SLOT(searchDB(QString,int)));

    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM movie");
    query.next();
    int rows = query.value(0).toInt();

    query.exec("SELECT * FROM movie ORDER BY nr");
    fillTable(rows,query);

    connect(model,SIGNAL(itemChanged(QStandardItem*)),this, SLOT(model_itemChanged(QStandardItem*)));
}

void MainWindow::on_actionBeenden_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionLaden_triggered()
{
    LoadDB();
}

void MainWindow::on_OK_clicked()
{
    QSqlQuery query;
    for(int i=0;i<changedItems.length();i++){
        int index = items[1].indexOf(changedItems.at(i));

        if(index!=-1){
            query.exec("UPDATE movie SET name=\""+items[1].at(index)->text()+"\" WHERE id="+items[0].at(index)->text());
        }else {
            query.exec("UPDATE movie SET nr=\""+items[2].at(index)->text()+"\" WHERE id="+items[0].at(index)->text());
        }
    }
}

void MainWindow::model_itemChanged(QStandardItem *item)
{
    changedItems << item;
}

void MainWindow::on_search_clicked()
{
    searchDialog->show();
}

void MainWindow::searchDB(QString searchTerm, int searchRow)
{
    QSqlQuery query;
    int rows;

    if(searchRow==0){
        query.exec("SELECT COUNT(*) FROM movie WHERE name LIKE \"%"+searchTerm+"%\"");
        query.next();
        rows = query.value(0).toInt();
        query.exec("SELECT * FROM movie WHERE name LIKE \"%"+searchTerm+"%\"");
    }else if(searchRow==1){
        query.exec("SELECT COUNT(*) FROM movie WHERE nr="+searchTerm);
        query.next();
        rows = query.value(0).toInt();
        query.exec("SELECT * FROM movie WHERE nr="+searchTerm);
    }

    fillTable(rows,query);

}

void MainWindow::fillTable(int rows,QSqlQuery query)
{
    model = new QStandardItemModel(rows,3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QString("name")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QString("nr")));

    ui->tableView->setModel(model);

    items[0].clear();
    items[1].clear();
    items[2].clear();

    int count = 0;
    while(query.next()){
        items[0] << new QStandardItem(QString(query.value(0).toString()));
        items[0].last()->setFlags(items[0].last()->flags() ^ (Qt::ItemIsEditable | Qt::ItemIsSelectable));
        items[1] << new QStandardItem(QString(query.value(1).toString()));
        items[2] << new QStandardItem(QString(query.value(2).toString()));
        model->setItem(count,0,items[0].last());
        model->setItem(count,1,items[1].last());
        model->setItem(count,2,items[2].last());
        count++;
    }
}
