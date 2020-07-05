#include "insert_player.h"
#include "ui_insert_player.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "QSqlError"
#include "QSqlQueryModel"
#include "QTableView"
Insert_player::Insert_player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insert_player)
{
    ui->setupUi(this);
}

Insert_player::~Insert_player()
{
    delete ui;
}

void Insert_player::on_Insert_clicked()
{
    QString ID,Surname,Name,Rating;
    QString q = "";
    ID=ui->ID_player_Edit->text();
    Surname=ui->Surname_Edit->text();
    Name=ui->Name_Edit->text();
    Rating=ui->Rating_Edit->text();
    MainWindow m;
    QSqlQuery* query =new QSqlQuery(m.get_db());
    q = "INSERT OR REPLACE into Player_info (ID, Number_sort, Surname, Name, Rating, score, Berger, Status)"
        " values (:id, :ns, :sname, :name, :rating, :score, :berger, :status)";
    query->prepare(q);
    query->bindValue(":id", ID);
    query->bindValue(":ns", 0);
    query->bindValue(":sname", Surname);
    query->bindValue(":name", Name);
    query->bindValue(":rating", Rating);
    query->bindValue(":score", 0);
    query->bindValue(":berger", 0);
    query->bindValue(":status", 0);
    if (query->exec())
    {
        QMessageBox::information(0, "Information", "Saved");
    }
    else
    {
        QMessageBox::information(0, "Information", "One of the fields is empty or incorrect ID === "+q);
    }
}

void Insert_player::on_Ok_clicked()
{
    this->close();
}

void Insert_player::on_Delete_clicked()
{
    QString ID;
    MainWindow m;
    QSqlQuery query(m.get_db());
    query.prepare("delete from Player_info where ID='"+ID+"'");
    if (query.exec())
    {
        QMessageBox::information(0, "Information", "Deleted");
    }
    else
    {
        QMessageBox::critical(this,tr("error"),query.lastError().text());
    }
}

void Insert_player::on_Update_data_clicked()
{
    MainWindow m;
    QSqlQuery* query=new QSqlQuery(m.get_db());
    query->prepare("select ID, Surname, Name, Rating from Player_info");
    query->exec();
    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    qDebug() << (modal->rowCount());

    delete modal;
    delete query;
}
