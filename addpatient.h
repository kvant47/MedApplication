#ifndef ADDPATIENT_H
#define ADDPATIENT_H

#include <QMouseEvent>
#include <QPoint>
#include "QFontDatabase"
#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class AddPatient;
}

class AddPatient : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatient(int action, QWidget *parent = nullptr);
    explicit AddPatient(int action, int currentId, QWidget *parent = nullptr);
    ~AddPatient();

private slots:
    void on_close_btn_clicked();
    void on_cancel_clicked();

    void on_ok_clicked();

private:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    QPointF m_mousePoint;
    Ui::AddPatient *ui;
    QSqlQuery* query;
    int Action;        // если равно 0, позицию добавляем, если 1 - меняем
    QString CurrentId; //id изменяемого элемента
};

#endif // ADDPATIENT_H
