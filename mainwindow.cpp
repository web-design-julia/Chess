#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mix_par.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedWidth(1024);
    this->setFixedHeight(768);
    //connect(i_t_dialog,&Info_tournament::firstWindow,this,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QSqlDatabase MainWindow:: get_filename()
{
    return db;
}

void MainWindow::on_action_2_triggered() //Открывает базу
{
    QString filter = "Sqlite (*.sqlite)";
    QString Filename = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath(),filter);
    if (!Filename.isEmpty())
    {
        qDebug() << QSqlDatabase::drivers();
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(Filename);
        db.open();

        if(db.open()==false)
        {
            QMessageBox::warning(this, "...","Not can");
        }
        else
        {
          qDebug() << "Success!";
        }
    }
}

void MainWindow::on_action_triggered() //создает базу
{
    QString Filename=QFileDialog::getSaveFileName(this,"Save a file",QDir::homePath(),"*.sqlite");
    if (!Filename.isEmpty()) // если имя файла задано

        db = QSqlDatabase::addDatabase("QSQLITE"); // Создаем файл

        db.setDatabaseName(Filename);
        db.open();
        if(db.open()==false)
        {
            QMessageBox::warning(this, "...","Not cany");
        }
        else
        {
            qDebug() << "Success!";

            QSqlQuery query(db);
            query.exec("CREATE TABLE Info_tournament (Name varchar(30),Name_Judge varchar(15),Date_from date,Date_to date)");
            query.exec("CREATE TABLE Player_info (ID integer primary key, Number_sort integer Null,Surname VARCHAR(15), Name VARCHAR(15),"
                     " Rating integer, score integer,Berger float Null, Status integer Null);");
            query.exec("CREATE TABLE Tours (Number_Tours integer, Player_write INTEGER NOT NULL,Player_black INTEGER NOT NULL,"
                     "Result_write integer, Result_black integer, FOREIGN KEY (Player_black) REFERENCES Player_info(ID), FOREIGN KEY (Player_black) REFERENCES Player_info(ID))");

            query.exec("CREATE TABLE Current_position (Number_position integer NOT NULL, ID_player INTEGER NOT NULL, FOREIGN KEY (ID_player) REFERENCES Player_info(ID))");
            query.exec();
            Form *info_t = new Form();
            info_t->show();
        }
}

void MainWindow::on_action_3_triggered()
{
    QApplication::exit();
}

void MainWindow::on_action_7_triggered()
{
    Insert_player* insert_pl=new Insert_player();
    insert_pl->show();
}

void MainWindow::on_action_8_triggered()
{
    MainWindow m;
    QSqlQuery* query=new QSqlQuery(m.get_db());
    query->prepare("select ID, Surname, Name, Rating from Player_info Order by Rating DESC, Surname");
    query->exec();
    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());

    delete modal;
    delete query;
}

void MainWindow::on_action_5_triggered() // Составить пары
{
    MainWindow m;
    QSqlQuery* query=new QSqlQuery(m.get_db());
    query->prepare("select * from Player_info");
    query->exec();
    int num_teams{0};
    while (query->next())
        num_teams++;

    delete query;
    m.connClose();
    Mix_Par w;
    w.Sort_pairs(num_teams);
}
