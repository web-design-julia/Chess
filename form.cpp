#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_Ok_clicked()
{
    if ( ui->Name_Edit->text().isEmpty()
      or ui->Name_judge_Edit->text().isEmpty()
      or ui->Date_from_Edit->text().isEmpty()
      or ui->Date_to_Edit->text().isEmpty())

    {
        QMessageBox::warning(this, "Error","You have not filled in all fields");
        qDebug() << "NOSuccess!";
    }
    else
    {
        MainWindow m;
        QSqlQuery query(m.get_db());
        QString Name_tourn = ui->Name_Edit->text();
        QString Name_judge = ui->Name_judge_Edit->text();
        QString Date_from = ui->Date_from_Edit->text();
        QString Date_to = ui->Date_to_Edit->text();
        query.prepare("insert into Info_tournament(Name, Name_Judge, Date_from, Date_to) values "
                       "(:Name_tourn,:Name_judge,:Date_from,:Date_to);");
        query.bindValue(":Name_tourn",Name_tourn);
        query.bindValue(":Name_judge",Name_judge);
        query.bindValue(":Date_from",Date_from);
        query.bindValue(":Date_to",Date_to);
        Insert_player q;
        //q.setEnabled(false);
        query.exec();
        this->close();;
    }
}

void Form::on_Cancel_clicked()
{
    this->close();
}
