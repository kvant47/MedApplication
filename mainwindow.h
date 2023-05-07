#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QPoint>
#include <QMainWindow>
#include "QFontDatabase"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_menu1_toggled(bool checked);
    void on_menu2_toggled(bool checked);
    void on_menu3_toggled(bool checked);
    void on_menu4_toggled(bool checked);

    void on_close_btn_clicked();
    void on_min_btn_clicked();
    void on_add_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_del_clicked();
    void on_edit_clicked();

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQuery *query;
    Ui::MainWindow *ui;
    int correctMenuItem;
    void createTable();
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    QPointF m_mousePoint;
    int currentRow, currentID;     //выбранная строка и ID выбранного элемента


};
#endif // MAINWINDOW_H
