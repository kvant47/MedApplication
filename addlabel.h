#ifndef ADDLABEL_H
#define ADDLABEL_H

#include <QMouseEvent>
#include <QPoint>
#include "QFontDatabase"
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class AddLabel;
}

class AddLabel : public QDialog
{
    Q_OBJECT

public:
    explicit AddLabel(int action, QWidget *parent = nullptr);
    explicit AddLabel(int action, int currentId, QWidget *parent = nullptr);
    ~AddLabel();

private slots:
    void on_close_btn_clicked();
    void on_cancel_clicked();
    void on_ok_clicked();

    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);

private:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    QPointF m_mousePoint;
    Ui::AddLabel *ui;
    QSqlQuery* query;
    int patientId;      //polis
    int serviceId;
    int Action;        // если равно 0, позицию добавляем, если 1 - меняем
    QString CurrentId; //id изменяемого элемента
};

#endif // ADDLABEL_H
