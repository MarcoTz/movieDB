#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QStandardItemModel>
#include "dialog.h"
#include "newmovie.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void LoadDB();
    ~MainWindow();

private slots:
    void on_cancel_clicked();

    void on_actionBeenden_triggered();

    void on_actionLaden_triggered();

    void on_OK_clicked();

    void model_itemChanged(QStandardItem*);

    void on_search_clicked();

    void searchDB(QString, int);

    void on_pushButton_clicked();

    void movieAdded(QString,QString);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QStandardItemModel *model;
    //items in table, list[0]=ids, list[1]=names, list[2]=nrs
    QList<QStandardItem *> items [3];
    QList<QStandardItem *> changedItems;
    Dialog *searchDialog;
    newmovie *addmovie;

    void fillTable(int,QSqlQuery);

};

#endif // MAINWINDOW_H
