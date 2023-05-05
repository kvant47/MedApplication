#include "addservise.h"
#include "mainwindow.h"
#include "QFont"
#include <QFile>
#include "QDebug"
#include "QString"
#include "ui_addservise.h"

AddServise::AddServise(int action, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddServise)
{
    int id1 = QFontDatabase::addApplicationFont(":/font/Comfortaa-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id1).at(0);
    QFont comforta(family);

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    Action = action;

    ui->label_2->setFont(comforta);
    ui->label_position->setFont(comforta);
    ui->label_position_2->setFont(comforta);
    ui->label_position_3->setFont(comforta);
    ui->comboBox->setFont(comforta);
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);

    query = new QSqlQuery();
    query->exec("SELECT name, surname, patronymic FROM doctor");
    while(query->next()){
        QString fio = query->value(1).toString() + ' ' + query->value(0).toString() + ' ' + query->value(2).toString();
        ui->comboBox->addItem(fio);
    }

}



AddServise::AddServise(int action, int currentId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddServise)
{
    int id1 = QFontDatabase::addApplicationFont(":/font/Comfortaa-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id1).at(0);
    QFont comforta(family);

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    Action = action;
    CurrentId = QString::number(currentId);

    ui->label_2->setFont(comforta);
    ui->label_position->setFont(comforta);
    ui->label_position_2->setFont(comforta);
    ui->label_position_3->setFont(comforta);
    ui->comboBox->setFont(comforta);
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);

    query = new QSqlQuery();
    query->exec("SELECT name, surname, patronymic FROM doctor");
    while(query->next()){
        QString fio = query->value(1).toString() + ' ' + query->value(0).toString() + ' ' + query->value(2).toString();
        ui->comboBox->addItem(fio);
    }


    query = new QSqlQuery();

    QString select = "SELECT name, price FROM service WHERE id = '";
    select +=  CurrentId + "'";
    query->prepare(select);
    query->bindValue(":id", currentId);
    if (query->exec()){
        query->next();
        ui->areaEdit->setText(query->value(0).toString());
        ui->areaEdit_3->setText(QString::number(query->value(1).toInt()));
    }
}


AddServise::~AddServise()
{
    delete ui;
}


#define ПеремещениеОкна {

void AddServise::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePoint = event->pos();
        event->accept();
    }
}

void AddServise::resizeEvent(QResizeEvent* event)
{
}

void AddServise::mouseMoveEvent(QMouseEvent* event)

{
    const QPointF delta = event->globalPos() - m_mousePoint;
    move(delta.toPoint());

    event->accept();
}
#define ПеремещениеОкна }


void AddServise::on_close_btn_clicked()
{
    this->close();
}
void AddServise::on_cancel_clicked()
{
    this->close();
}


void AddServise::on_ok_clicked()
{
    if(Action == 0){
        query->prepare(QString ("INSERT INTO service(name, doctor, price) VALUES(:name, :doctor, :price);"));
        query->bindValue(":name", ui->areaEdit->text());
        query->bindValue(":doctor", ui->comboBox->itemText(doctorId));
        query->bindValue(":price", ui->areaEdit_3->text());

        QMessageBox* mess = new QMessageBox();

        if(!query->exec()){
            mess->setText("Что-то пошло не так! Проверьте номер полиса!");
            mess->show();
        }
        else {
            this->close();
        }
    }

    if(Action == 1){
        QString  select = "UPDATE service SET name=:name, doctor=:doctor, price=:price WHERE id='" + CurrentId + "'";
        query->prepare(select);
        query->bindValue(0, ui->areaEdit->text());
        query->bindValue(1, ui->comboBox->itemText(doctorId));
        query->bindValue(2, ui->areaEdit_3->text());

        QMessageBox* mess = new QMessageBox();

        if(!query->exec()){
            mess->setText("Что-то пошло не так! Проверьте номер полиса!");
            mess->show();
        }
        else {
            this->close();
        }
    }
}


void AddServise::on_comboBox_currentIndexChanged(int index)
{
    doctorId = index;
}

