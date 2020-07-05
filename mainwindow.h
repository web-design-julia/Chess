#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "form.h"
#include "insert_player.h"
#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QSqlDatabase get_filename();

    QSqlDatabase db;
    QString Filename;
    ~MainWindow();
    QSqlDatabase get_db()
    {
        return db;
    }
    void connClose()
    {
        db.close();
        //db.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        //db=QSqlDatabase::addDatabase("QSQLITE","SQLITE");
        //db.setDatabaseName(Filename);
        if (!db.open())
        {
            qDebug() <<"Not can";
            return false;
        }
        else {
            qDebug() << "Success db!";
            return true;
        }
    }

private slots:
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_5_triggered();
    void on_action_7_triggered();
    void on_action_8_triggered();

private:
    Ui::MainWindow *ui;
    Form *info_t;
    //QString Filename="C:/";
};

#endif // MAINWINDOW_H
