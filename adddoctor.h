#ifndef ADDDOCTOR_H
#define ADDDOCTOR_H
#include <QMouseEvent>
#include <QPoint>
#include "QFontDatabase"
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class addDoctor;
}

class addDoctor : public QDialog
{
    Q_OBJECT

public:
    explicit addDoctor(int action, QWidget *parent = nullptr);
    explicit addDoctor(int action, int currentId, QWidget *parent = nullptr);

    ~addDoctor();

private slots:
    void on_close_btn_clicked();
    void on_cancel_clicked();

    void on_ok_clicked();

private:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    QPointF m_mousePoint;
    Ui::addDoctor *ui;
    QSqlQuery* query;
    int Action;        // если равно 0, позицию добавляем, если 1 - меняем
    QString CurrentId; //id изменяемого элемента
};

#endif // ADDDOCTOR_H
