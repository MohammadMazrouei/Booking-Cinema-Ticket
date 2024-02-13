#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movies_page.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}


bool MainWindow::check_name(QString name)
{
	int size = name.size();

	if (size > 20)
		return false;
	if ((name[0] <= "9" && name[0] >= "0") || name[0] == "_")
		return false;
	for (int i = 0; i < size; i++)
	{
		if ((name[i] >= "a" && name[i] <= "z" ) || (name[i] >= "A" && name[i] <= "Z") ||
			(name[i] >= 0 && name[i] <= "9") || (name[i] == "_"))
			continue;

		return false;
	}

	return true;
}


bool MainWindow::check_password(QString password)
{
	int size = password.size();
	if (size > 20 || size < 4)
		return false;
	for (int i = 0; i < size; i++)
		if (password[i] == " ")
			return false;

	return true;
}


void MainWindow::on_btn_signup_clicked()
{
	if (ui->get_name->text().isEmpty())
	{
		QMessageBox::warning(this, "Enter Name", "Name's Field Is Empty!");
		return;
	}
	if (ui->get_password->text().isEmpty())
	{
		QMessageBox::warning(this, "Enter Password", "Passward's Field Is Empty!");
		return;
	}

	QFile file(address);
	QString name, password, line;
	QTextStream in(&file);
	QVector<QString> names;
	QVector<QString> passwords;

	name = ui->get_name->text();
	password = ui->get_password->text();

	if (!file.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	while (!in.atEnd())
	{
		line = in.readLine();
		names.push_back(line.split(" ")[0]);
		passwords.push_back((line.split(" ")[1]));
	}

	if (names.indexOf(name) != -1)
	{
		QMessageBox::warning(this, "Name", "This Name Exist!");
		return;
	}

	if (!check_name(name))
	{
		QMessageBox::warning(this, "Name", "Style Name Is Incorrect!");
		return;
	}
	if (!check_password(password))
	{
		QMessageBox::warning(this, "Password", "Style Password Is Incorrect");
		return;
	}

	in << name << " " << password << "\n";

	file.close();

	movies_page * mp = new movies_page(name, false);
	mp->show();
	this->close();
}


void MainWindow::on_btn_login_clicked()
{
	if (ui->get_name->text().isEmpty())
	{
		QMessageBox::warning(this, "Enter Name", "Name's Field Is Empty!");
		return;
	}
	if (ui->get_password->text().isEmpty())
	{
		QMessageBox::warning(this, "Enter Password", "Passward's Field Is Empty!");
		return;
	}

	QFile file(address);
	QString name, password, line;
	QTextStream in(&file);
	QVector<QString> names;
	QVector<QString> passwords;

	name = ui->get_name->text();
	password = ui->get_password->text();

	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	while (!in.atEnd())
	{
		line = in.readLine();
		names.push_back(line.split(" ")[0]);
		passwords.push_back((line.split(" ")[1]));
	}
	file.close();

	int index = names.indexOf(name);
	if (index == -1)
	{
		QMessageBox::warning(this, "Name", "This Name Not Exist!");
		return;
	}

	if (password != passwords[index])
	{
		QMessageBox::warning(this, "Passward", "Password Is Incorrect!");
		return;
	}

	if (name == addminName && password == addminPassword)
	{
		movies_page * mp = new movies_page();
		mp->show();
	}
	else
	{
		movies_page * mp = new movies_page(name, false);
		mp->show();
	}
	this->close();
}

