#include "addlabel.h"
#include "ui_addlabel.h"

AddLabel::AddLabel(int action, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLabel)
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
    ui->comboBox_2->setFont(comforta);
    ui->label_position_4->setFont(comforta);
    ui->label_position_5->setFont(comforta);
    ui->comboBox->setFont(comforta);
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);

    query = new QSqlQuery();
    query->exec("SELECT name, surname, patronymic FROM patient");
    while(query->next()){
        QString fio = query->value(1).toString() + ' ' + QString(query->value(0).toString())[0] + ". "  + QString(query->value(2).toString())[0] + ".";
        ui->comboBox_2->addItem(fio);
    }
    query->exec("SELECT name FROM service");
    while(query->next()){
        ui->comboBox->addItem(query->value(0).toString());
    }
}


AddLabel::AddLabel(int action, int currentId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLabel)
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
    ui->comboBox_2->setFont(comforta);
    ui->label_position_4->setFont(comforta);
    ui->label_position_5->setFont(comforta);
    ui->comboBox->setFont(comforta);
    ui->ok->setFont(comforta);
    ui->cancel->setFont(comforta);

    query = new QSqlQuery();
    query->exec("SELECT name, surname, patronymic FROM patient");
    while(query->next()){
        QString fio = query->value(1).toString() + ' ' + QString(query->value(0).toString())[0] + ". "  + QString(query->value(2).toString())[0] + ".";
        ui->comboBox_2->addItem(fio);
    }
    query->exec("SELECT name FROM service");
    while(query->next()){
        ui->comboBox->addItem(query->value(0).toString());
    }

    QString select = "SELECT date, time FROM appointment WHERE id='";
    select = select + CurrentId + "'";
    query->prepare(select);
    query->bindValue(":id", currentId);
    if (query->exec()){
        query->next();
        ui->areaEdit_4->setText(query->value(0).toString());
        ui->areaEdit_5->setText(query->value(1).toString());
    }
}



AddLabel::~AddLabel()
{
    delete ui;
}



#define ПеремещениеОкна {

void AddLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePoint = event->pos();
        event->accept();
    }
}

void AddLabel::resizeEvent(QResizeEvent* event)
{
}

void AddLabel::mouseMoveEvent(QMouseEvent* event)

{
    const QPointF delta = event->globalPos() - m_mousePoint;
    move(delta.toPoint());

    event->accept();
}
#define ПеремещениеОкна }

void AddLabel::on_close_btn_clicked()
{
    this->close();
}


void AddLabel::on_cancel_clicked()
{
    this->close();
}





void AddLabel::on_ok_clicked()
{
    if(Action == 0){
        query = new QSqlQuery();
        query->prepare(QString ("INSERT INTO appointment(patient, service, date, time)"
                                "VALUES(:patient, :service, :date, :time);"));
        query->bindValue(":patient", ui->comboBox_2->itemText(patientId));
        query->bindValue(":service", ui->comboBox->itemText(serviceId));
        query->bindValue(":date", ui->areaEdit_4->text());
        query->bindValue(":time", ui->areaEdit_5->text());


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

        //query = new QSqlQuery();
        QString  select = "UPDATE appointment SET patient=:patient, service=:service, date=:date, time=:time WHERE id='" + CurrentId + "'";
        query->prepare(select);
        query->bindValue(0, ui->comboBox_2->itemText(patientId));
        query->bindValue(1, ui->comboBox->itemText(serviceId));
        query->bindValue(2, ui->areaEdit_4->text());
        query->bindValue(3, ui->areaEdit_5->text());


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





void AddLabel::on_comboBox_2_currentIndexChanged(int index)
{
    patientId = index;
}

void AddLabel::on_comboBox_currentIndexChanged(int index)
{
    serviceId = index;
}

