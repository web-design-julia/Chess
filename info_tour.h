#ifndef INFO_TOUR_H
#define INFO_TOUR_H
#include <QWidget>

namespace Ui {
class Info_tour;
}

class Info_tour : public QWidget
{
    Q_OBJECT

public:
    explicit Info_tour(QWidget *parent = nullptr);
    ~Info_tour();

//signals:
//    void firstWindow();  // Сигнал для первого окна на открытие

//private slots:
    // Слот-обработчик нажатия кнопки
//    void on_pushButton_clicked();

private:
    Ui::Info_tour *ui;
};
#endif // INFO_TOUR_H
