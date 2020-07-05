#ifndef INSERT_PLAYER_H
#define INSERT_PLAYER_H
#include <QSqlDatabase>
#include <QDialog>

namespace Ui {
    class Insert_player;
}

class Insert_player : public QDialog
{
    Q_OBJECT

public:
    explicit Insert_player(QWidget *parent = nullptr);
    ~Insert_player();

private slots:
    void on_Insert_clicked();
    void on_Ok_clicked();
    void on_Delete_clicked();
    void on_Update_data_clicked();

private:
    Ui::Insert_player *ui;
    QSqlDatabase *db;
};

#endif // INSERT_PLAYER_H
