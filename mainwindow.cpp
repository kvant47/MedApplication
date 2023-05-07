#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addservise.h"
#include "adddoctor.h"
#include "addpatient.h"
#include "addlabel.h"
#include "QDebug"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);


    int id1 = QFontDatabase::addApplicationFont(":/font/Comfortaa-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id1).at(0);
    QFont comforta(family);


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./DB/AppMedDB.db");
    if (db.open()){
        qDebug() << "Успешное подключение к базе данных " + db.databaseName();
        model = new QSqlTableModel(this, db);
        createTable();
    }
    else
    {
        qDebug() << "База данных не открыта!";
        qDebug() << db.lastError();
    }

    ui->menu1->setChecked(true);
    ui->menu2->setIcon(QIcon(":/image/doctor.png"));
    ui->menu3->setChecked(true);
    ui->menu4->setIcon(QIcon(":/image/medical-history.png"));
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //выравниваение столбцов по содержимому
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);                     //Выделение всей строки
    ui->tableView->setSortingEnabled(true);                                                 //Сорировка по столбцам
    ui->tableView->verticalHeader()->setVisible(false);
}

void MainWindow::createTable()
{
    query = new QSqlQuery(db);

    query->exec("CREATE TABLE IF NOT EXISTS \"Appointment\" ( \n\t"
                    "\"Id\"	INTEGER,\n\t"
                    "\"Patient\"	TEXT,\n\t"
                    "\"Service\"	TEXT,\n\t"
                    "\"Date\"	TEXT,\n\t"
                    "\"Time\"	TEXT,\n\t"
                    "PRIMARY KEY(\"Id\"));");

    query->exec("CREATE TABLE IF NOT EXISTS \"Doctor\" ( \n\t"
                    "\"Id\"	INTEGER,\n\t"
                    "\"Name\"	TEXT,\n\t"
                    "\"Surname\"	TEXT,\n\t"
                    "\"Patronymic\"	TEXT,\n\t"
                    "\"Salary\"	INTEGER,\n\t"
                   "\"Profile\"	TEXT,\n\t"
                    "PRIMARY KEY(\"Id\"));");

    query->exec("CREATE TABLE IF NOT EXISTS \"Patient\" ( \n\t"
                    "\"Polis\"	INTEGER,\n\t"
                    "\"Name\"	TEXT,\n\t"
                    "\"Surname\"	TEXT,\n\t"
                    "\"Patronymic\"	TEXT,\n\t"
                    "\"DateBorn\"	TEXT,\n\t"
                   "\"Adress\"	TEXT,\n\t"
                    "PRIMARY KEY(\"Polis\"));");

    query->exec("CREATE TABLE IF NOT EXISTS \"Service\" ( \n\t"
                    "\"Id\"	INTEGER,\n\t"
                    "\"Name\"	TEXT,\n\t"
                    "\"Doctor\"	TEXT,\n\t"
                    "\"Price\"	INTEGER,\n\t"
                    "PRIMARY KEY(\"Id\"));");
}


MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}


void MainWindow::on_close_btn_clicked()
{
    this->close();
}
void MainWindow::on_min_btn_clicked()
{
    this->showMinimized();
}


#define РаботаМеню {
void MainWindow::on_menu1_toggled(bool checked)
{
    if(checked){
        ui->menu1->setStyleSheet( "#menu1 { border-left: 5px solid #00d4ff; color: #00d4ff;} "
                                  "#menu1:hover {color: white; }");

        ui->menu1->setIcon(QIcon(":/image/healthcare_act.png"));

        model->setTable("Service");
        model->select();
        model->setHeaderData(0, Qt::Horizontal, "Код услуги", Qt::DisplayRole);
        model->setHeaderData(1, Qt::Horizontal, "Название услуги", Qt::DisplayRole);
        model->setHeaderData(2, Qt::Horizontal, "Врач", Qt::DisplayRole);
        model->setHeaderData(3, Qt::Horizontal, "Цена", Qt::DisplayRole);

        ui->tableView->setModel(model);
        ui->tableView->setColumnHidden(0, true); //Сокрытие столбца с ID

        //ui->tableView->setColumnWidth(0, 100);
        ui->tableView->setColumnWidth(1, 260);
        ui->tableView->setColumnWidth(2, 264);
        ui->tableView->setColumnWidth(3, 180);
        qDebug() <<" Выбрана 1";
        currentID = -1;
        correctMenuItem = 1;
    }
    else{
        ui->menu1->setStyleSheet( "#menu1 { border-left: 5px solid transparent; color: #5c6266;"
                                  "QRadioButton:hover {color: white;}");
        ui->menu1->setIcon(QIcon(":/image/healthcare.png"));
    }
}
void MainWindow::on_menu2_toggled(bool checked)
{
    if(checked){
         ui->menu2->setIcon(QIcon(":/image/doctor_act.png"));
         ui->menu2->setStyleSheet( "#menu2 { border-left: 5px solid #00d4ff; color: #00d4ff;} "
                                   "#menu2:hover {color: white; }");

        correctMenuItem = 2;


        model->setTable("Doctor");
        model->select();
        model->setHeaderData(0, Qt::Horizontal, "№", Qt::DisplayRole);
        model->setHeaderData(1, Qt::Horizontal, "Имя", Qt::DisplayRole);
        model->setHeaderData(2, Qt::Horizontal, "Фамилия", Qt::DisplayRole);
        model->setHeaderData(3, Qt::Horizontal, "Отчество", Qt::DisplayRole);
        model->setHeaderData(4, Qt::Horizontal, "Зарплата", Qt::DisplayRole);
        model->setHeaderData(5, Qt::Horizontal, "Профиль", Qt::DisplayRole);
        ui->tableView->setModel(model);


        ui->tableView->setColumnHidden(0, true); //Сокрытие столбца с ID
        //ui->tableView->setColumnWidth(0, 10);
        ui->tableView->setColumnWidth(1, 138);
        ui->tableView->setColumnWidth(2, 157);
        ui->tableView->setColumnWidth(3, 157);
        ui->tableView->setColumnWidth(4, 107);
        ui->tableView->setColumnWidth(5, 145);
        currentRow = -1;
        currentID = -1;

        qDebug() <<"Выбрана 2";
    }
    else{
     ui->menu2->setStyleSheet( "#menu2 { border-left: 5px solid transparent; color: #5c6266;"
                                  "QRadioButton:hover {color: white;}");
     ui->menu2->setIcon(QIcon(":/image/doctor.png"));
    }
}
void MainWindow::on_menu3_toggled(bool checked)
{
    if(checked){
         ui->menu3->setIcon(QIcon(":/image/patient_act.png"));
         ui->menu3->setStyleSheet( "#menu3 { border-left: 5px solid #00d4ff; color: #00d4ff;} "
                                   "#menu3:hover {color: white; }");
        correctMenuItem = 3;

        model->setTable("Patient");
        model->select();
        model->setHeaderData(0, Qt::Horizontal, "Полис", Qt::DisplayRole);
        model->setHeaderData(1, Qt::Horizontal, "Имя", Qt::DisplayRole);
        model->setHeaderData(2, Qt::Horizontal, "Фамилия", Qt::DisplayRole);
        model->setHeaderData(3, Qt::Horizontal, "Отчество", Qt::DisplayRole);
        model->setHeaderData(4, Qt::Horizontal, "Д. рожд.", Qt::DisplayRole);
        model->setHeaderData(5, Qt::Horizontal, "Адрес", Qt::DisplayRole);

        ui->tableView->setColumnWidth(0, 97);
        ui->tableView->setColumnWidth(1, 116);
        ui->tableView->setColumnWidth(2, 116);
        ui->tableView->setColumnWidth(3, 133);
        ui->tableView->setColumnWidth(4, 80);
        ui->tableView->setColumnWidth(5, 162);
        ui->tableView->setModel(model);
        currentRow = -1;
        currentID = -1;

        qDebug() <<"Выбрана 3";
    }
    else{
        ui->menu3->setIcon(QIcon(":/image/patient.png"));
        ui->menu3->setStyleSheet( "#menu3 { border-left: 5px solid transparent; color: #5c6266;"
                                  "QRadioButton:hover {color: white;}");
    }
}
void MainWindow::on_menu4_toggled(bool checked)
{
    if(checked){
         ui->menu4->setIcon(QIcon(":/image/medical-history_act.png"));
         ui->menu4->setStyleSheet( "#menu4 { border-left: 5px solid #00d4ff; color: #00d4ff;} "
                                   "#menu4:hover {color: white; }");
         correctMenuItem = 4;

         model->setTable("Appointment");
         model->select();
         model->setHeaderData(0, Qt::Horizontal, "№ записи", Qt::DisplayRole);
         model->setHeaderData(1, Qt::Horizontal, "Пациент", Qt::DisplayRole);
         model->setHeaderData(2, Qt::Horizontal, "Услуга", Qt::DisplayRole);
         model->setHeaderData(3, Qt::Horizontal, "Дата", Qt::DisplayRole);
         model->setHeaderData(4, Qt::Horizontal, "Время", Qt::DisplayRole);

         ui->tableView->setColumnWidth(0, 90.25);
         ui->tableView->setColumnWidth(1, 174.25);
         ui->tableView->setColumnWidth(2, 198.25);
         ui->tableView->setColumnWidth(3, 121.25);
         ui->tableView->setColumnWidth(4, 121.25);
         ui->tableView->setModel(model);
         currentRow = -1;
         currentID = -1;

         qDebug() <<"Выбрана 4";
    }
    else{
        ui->menu4->setIcon(QIcon(":/image/medical-history.png"));
        ui->menu4->setStyleSheet( "#menu4 { border-left: 5px solid transparent; color: #5c6266;"
                                  "QRadioButton:hover {color: white;}");
    }
}
#define РаботаМеню }


#define ПеремещениеОкна {

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePoint = event->pos();
        event->accept();
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)

{
    const QPointF delta = event->globalPos() - m_mousePoint;
    move(delta.toPoint());

    event->accept();
}
#define ПеремещениеОкна }


void MainWindow::on_add_clicked()
{
    switch(correctMenuItem){
        case 1:{
            AddServise ServiseWnd(0);
            ServiseWnd.setModal(true);
            ServiseWnd.exec();
            model->select();
            break;
        }
        case 2:{
            addDoctor DoctorWnd(0);
            DoctorWnd.setModal(true);
            DoctorWnd.exec();
            model->select();
            break;
        }
        case 3:{
            AddPatient PatientWnd(0);
            PatientWnd.setModal(true);
            PatientWnd.exec();
            model->select();
            break;
        }
        case 4:{
            AddLabel LabelWnd(0);
            LabelWnd.setModal(true);
            LabelWnd.exec();
            model->select();
            break;
        }
    }
}

void MainWindow::on_edit_clicked()
{
    switch(correctMenuItem){
    case 1:{
        if(currentID >= 0){    //если выбрана запись
            AddServise ServiseWnd(1, currentID);;
            ServiseWnd.setModal(true);
            ServiseWnd.exec();
            model->select();
            currentID = -1;
        }
        break;
    }
    case 2:{
        if(currentID >= 0){
            addDoctor DoctorWnd(1, currentID);
            DoctorWnd.setModal(true);
            DoctorWnd.exec();
            model->select();
            currentID = -1;
        }
        break;
    }
    case 3:{
        if(currentID >= 0){
            AddPatient PatientWnd(1, currentID);
            PatientWnd.setModal(true);
            PatientWnd.exec();
            model->select();
            currentID = -1;
        }
        break;
    }
    case 4:{
        if(currentID >= 0){
            AddLabel LabelWnd(1, currentID);
            LabelWnd.setModal(true);
            LabelWnd.exec();
            model->select();
            currentID = -1;
        }
        break;
    }
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
    currentID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
}

void MainWindow::on_del_clicked()
{
    model->removeRow(currentRow);
    model->select();
}




