#include "addpatient.h"
#include "ui_addpatient.h"

AddPatient::AddPatient(int action, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    int id1 = QFontDatabase::addApplicationFont(":/font/Comfortaa-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id1).at(0);
    QFont comforta(family);

    Action = action;

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->label_2->setFont(comforta);
    ui->label_position->setFont(comforta);
    ui->label_position_2->setFont(comforta);
    ui->label_position_3->setFont(comforta);
    ui->label_position_4->setFont(comforta);
    ui->label_position_5->setFont(comforta);
    ui->label_position_7->setFont(comforta);
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);
}




AddPatient::AddPatient(int action, int currentId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    int id1 = QFontDatabase::addApplicationFont(":/font/Comfortaa-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id1).at(0);
    QFont comforta(family);

    Action = action;
    CurrentId = QString::number(currentId);

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->label_2->setFont(comforta);
    ui->label_position->setFont(comforta);
    ui->label_position_2->setFont(comforta);
    ui->label_position_3->setFont(comforta);
    ui->label_position_4->setFont(comforta);
    ui->label_position_5->setFont(comforta);
    ui->label_position_7->setFont(comforta);
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);


    query = new QSqlQuery();

    QString select = "SELECT polis, name, surname, patronymic, dateborn, adress FROM patient WHERE polis = '";
    select +=  CurrentId + "'";
    query->prepare(select);
    query->bindValue(":polis", currentId);
    if (query->exec()){
        query->next();
        ui->areaName->setText(query->value(1).toString());
        ui->areaSurname->setText(query->value(2).toString());
        ui->areaPatronimic->setText(query->value(3).toString());
        ui->areaEdit_4->setText(query->value(4).toString());
        ui->areaEdit_5->setText(query->value(0).toString());
        ui->areaEdit_7->setText(query->value(5).toString());
    }
}




AddPatient::~AddPatient()
{
    delete ui;
}



#define ПеремещениеОкна {

void AddPatient::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePoint = event->pos();
        event->accept();
    }
}

void AddPatient::resizeEvent(QResizeEvent* event)
{
}

void AddPatient::mouseMoveEvent(QMouseEvent* event)

{
    const QPointF delta = event->globalPos() - m_mousePoint;
    move(delta.toPoint());

    event->accept();
}
#define ПеремещениеОкна }


void AddPatient::on_close_btn_clicked()
{
    this->close();
}
void AddPatient::on_cancel_clicked()
{
    this->close();
}




void AddPatient::on_ok_clicked()
{
    if(Action == 0){
        query = new QSqlQuery();
        query->prepare(QString ("INSERT INTO patient(name, surname, patronymic, dateborn, polis, adress) "
                                "VALUES(:name, :surname, :patronymic, :dateborn, :polis, :adress);"));
        query->bindValue(":name", ui->areaName->text());
        query->bindValue(":surname", ui->areaSurname->text());
        query->bindValue(":patronymic", ui->areaPatronimic->text());
        query->bindValue(":dateborn", ui->areaEdit_4->text());
        query->bindValue(":polis", ui->areaEdit_5->text());
        query->bindValue(":adress", ui->areaEdit_7->text());

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
        query = new QSqlQuery();

        QString  select = "UPDATE patient SET name=:name, surname=:surname, patronymic=:patronymic, dateborn=:dateborn, adress=:adress, polis=:polis  WHERE polis='";
        //select += "dateborn=:dateborn, adress=:adress WHERE polis='";
        select = select +  CurrentId + "'";

        query->prepare(select);
        query->bindValue(0, ui->areaName->text());
        query->bindValue(1, ui->areaSurname->text());
        query->bindValue(2, ui->areaPatronimic->text());
        query->bindValue(3, ui->areaEdit_4->text());
        query->bindValue(5, ui->areaEdit_5->text());
        query->bindValue(4, ui->areaEdit_7->text());

        QString s = (query->value(0).toString)();
        qDebug() << s;
        s =query->value(1).toString();



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

