#include "widget.h"
#include "ui_widget.h"
#include <Qfile>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tableWidget-> setColumnCount(4);
    QStringList ColTotle;
    ColTotle<<"學號"<<"班級"<<"姓名"<<"電話";
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QTableWidgetItem *col1,*col2,*col3,*col4;
    col1= new QTableWidgetItem(ui->lineEdit->text());
    col2= new QTableWidgetItem(ui->lineEdit_2->text());
    col3= new QTableWidgetItem(ui->lineEdit_3->text());
    col4= new QTableWidgetItem(ui->lineEdit_4->text());
    int row = ui->tableWidget->rowCount();
    qDebug()<<row;
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row,0,col1);
    ui->tableWidget->setItem(row,1,col2);
    ui->tableWidget->setItem(row,2,col3);
    ui->tableWidget->setItem(row,3,col4);
}
void CbWrite(QString fileName,QString str)
{
    QFile outFile(fileName);
    if(!outFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug()<<"Open File failed";
        return;
    }
    QTextStream out(&outFile);
    out.setEncoding(QStringConverter::System);
    out<<str;
    outFile.flush();
    outFile.close();
}


void Widget::on_pushButton_2_clicked()
{
    QString fileName;
    QString saveStr;
    fileName = QFileDialog::getSaveFileName(this,"匯出通訊錄",".",
                                            "csv(*.csv);;text(*.txt)");
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            saveStr += ui->tableWidget->item(i,j)->text()+",";
        }
    saveStr +="\n";}
    CbWrite(fileName,saveStr);
}


void Widget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "匯入通訊錄", ".",
                                                    "csv(*.csv);;text(*.txt)");
    QFile inFile(fileName);
    if (!inFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open File failed:" << inFile.errorString();
        return;
    }
    QTextStream in(&inFile);
    in.setEncoding(QStringConverter::System);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }
        QStringList fields = line.split(',');
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < 4 && col < fields.size(); ++col)
        {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(fields[col]));
        }
    }
    inFile.close();
}

