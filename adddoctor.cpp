#include "adddoctor.h"
#include "ui_adddoctor.h"

addDoctor::addDoctor( int action, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDoctor)
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
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);
}

addDoctor::addDoctor(int action, int currentId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDoctor)
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
    ui->label_position_4->setFont(comforta);
    ui->label_position_5->setFont(comforta);
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);

    query = new QSqlQuery();

    QString select = "SELECT name, surname, patronymic, salary, profile FROM doctor WHERE id = '";
    select +=  CurrentId + "'";
    query->prepare(select);
    query->bindValue(":id", currentId);
    if (query->exec()){
        query->next();
        ui->areaEdit->setText(query->value(0).toString());
        ui->areaEdit_2->setText(query->value(1).toString());
        ui->areaEdit_3->setText(query->value(2).toString());
        ui->areaEdit_4->setText(QString::number(query->value(3).toInt()));
        ui->areaEdit_5->setText(query->value(4).toString());
    }
}

addDoctor::~addDoctor()
{
    delete ui;
}

void addDoctor::on_close_btn_clicked()
{
    this->close();
}
void addDoctor::on_cancel_clicked()
{
    this->close();
}


#define ПеремещениеОкна {

void addDoctor::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePoint = event->pos();
        event->accept();
    }
}

void addDoctor::resizeEvent(QResizeEvent* event)
{
}

void addDoctor::mouseMoveEvent(QMouseEvent* event)

{
    const QPointF delta = event->globalPos() - m_mousePoint;
    move(delta.toPoint());

    event->accept();
}
#define ПеремещениеОкна }


void addDoctor::on_ok_clicked()
{
    if(Action == 0) {
        query = new QSqlQuery();
        query->prepare(QString ("INSERT INTO doctor(name, surname, patronymic, salary, profile) "
                                "VALUES(:name, :surname, :patronymic, :salary, :profile);"));
        query->bindValue(":name", ui->areaEdit->text());
        query->bindValue(":surname", ui->areaEdit_2->text());
        query->bindValue(":patronymic", ui->areaEdit_3->text());
        query->bindValue(":salary", ui->areaEdit_4->text());
        query->bindValue(":profile", ui->areaEdit_5->text());

        QMessageBox* mess = new QMessageBox();

        if(!query->exec()){
            mess->setText("Что-то пошло не так!");
            mess->show();
        }
        else {
            this->close();
        }
    }
    if(Action == 1) {
        query = new QSqlQuery();

        QString  select = "UPDATE doctor SET name=:name, surname=:surname, patronymic=:patronymic, ";
        select += "salary=:salary, profile=:profile WHERE id='";
        select +=  CurrentId + "'";

        query->prepare(select);
        query->bindValue(0, ui->areaEdit->text());
        query->bindValue(1, ui->areaEdit_2->text());
        query->bindValue(2, ui->areaEdit_3->text());
        query->bindValue(3, ui->areaEdit_4->text());
        query->bindValue(4, ui->areaEdit_5->text());

        QMessageBox* mess = new QMessageBox();

        if(!query->exec()){
            mess->setText("Что-то пошло не так!");
            mess->show();
        }
        else {
            this->close();
        }

    }
}

