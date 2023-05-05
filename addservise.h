#ifndef ADDSERVISE_H
#define ADDSERVISE_H
#include <QMouseEvent>
#include <QPoint>
#include "QFontDatabase"
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class AddServise;
}

class AddServise : public QDialog
{
    Q_OBJECT

public:
    explicit AddServise(int action, QWidget *parent = nullptr);
    explicit AddServise(int action, int currentId, QWidget *parent = nullptr);
    ~AddServise();

private slots:
    void on_close_btn_clicked();

    void on_cancel_clicked();

    void on_ok_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    QPointF m_mousePoint;
    Ui::AddServise *ui;
    QSqlQuery* query;
    int doctorId;
    int Action;        // если равно 0, позицию добавляем, если 1 - меняем
    QString CurrentId; //id изменяемого элемента
};

#endif // ADDSERVISE_H
