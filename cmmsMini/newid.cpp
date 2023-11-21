#include "newid.h"
#include "ui_newid.h"
//#include<fstream>
//#include<iostream>
#include<QString>
//#include<string>
#include<QMessageBox>
#include<Qfile>
#include<QTextStream>


NewID::NewID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewID)
{
    ui->setupUi(this);
}

NewID::~NewID()
{
    delete ui;
}

void NewID::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username2->text();
    QString password = ui->lineEdit_password2->text();
    QFile ufile("username.txt");
    QFile pfile("password.txt");

    if (!ufile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open the file for reading: " + ufile.errorString());
        return;
    }

    bool usernameExists = false;
    QTextStream instream(&ufile);
    while (!instream.atEnd()) {
        QString existingUsername = instream.readLine();
        if (existingUsername == username) {
            usernameExists = true;
            break;
        }
    }

    if (ufile.isOpen()) {
        ufile.close();
    }

    if (usernameExists) {
        QMessageBox::warning(this, "Error", "Username already exists. Please choose a different username.");
        return;
    }

    else if (!ufile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QMessageBox::warning(this, "Error", "Failed to open the file for writing: " + ufile.errorString());
    }
    else
    {
        QTextStream stream(&ufile);
        stream << username;
        ufile.close();

    }
    if (!pfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QMessageBox::warning(this, "Error", "Failed to open the file for writing: " + pfile.errorString());
    }

    else if(username.isEmpty())
    {
        QMessageBox::information(this,"Error","Please enter a Username");
    }


    else if (password.isEmpty())
    {
        QMessageBox::information(this,"Error","Please enter a Password");
    }

    else if (!ufile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open the file for writing: " + ufile.errorString());
    }

    else
    {
        QTextStream stream(&pfile);
        stream << password;
        pfile.close();
        QMessageBox::about(this, "Username set", "Username written to file");
        close();
    }


}
