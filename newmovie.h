#ifndef NEWMOVIE_H
#define NEWMOVIE_H

#include <QDialog>

namespace Ui {
class newmovie;
}

class newmovie : public QDialog
{
    Q_OBJECT

public:
    explicit newmovie(QWidget *parent = 0, int defaultNr = 0);
    ~newmovie();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_nrEdit_editingFinished();

signals:
    void addMovie(QString,QString);

private:
    Ui::newmovie *ui;
};

#endif // NEWMOVIE_H
