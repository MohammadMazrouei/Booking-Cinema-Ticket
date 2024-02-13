#include "profile.h"
#include "ui_profile.h"
#include "movies_page.h"
#include "mainwindow.h"

profile::profile(QString username, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::profile)
{
	ui->setupUi(this);
	userName = username;
	ui->label_username->setText(username);
	ui->show_movies->setReadOnly(1);
	ui->show_reserved->setReadOnly(1);
	ui->show_sans->setReadOnly(1);
	show_information();
}

profile::~profile()
{
	delete ui;
}


void profile::show_information()
{
	QFile file(address3);
	QTextStream in(&file);
	QString line;

	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	while (!in.atEnd())
	{
		line = in.readLine();
		reserved_inf.push_back(line);
	}

	int size = reserved_inf.size();
	int j = 1;
	for (int i = 0; i < size; i++)
	{
		if (userName == reserved_inf[i].split(" ")[0] && reserved_inf[i].split(" ")[3].toInt())
		{
			index_user_movies.push_back(i);
			line = reserved_inf[i];
			ui->show_movies->appendPlainText(QString::number(j++) + ". ");
			ui->show_movies->insertPlainText(line.split(" ")[1].replace("_", " "));
			ui->show_sans->appendPlainText(line.split(" ")[2].replace("_", " "));
			ui->show_reserved->appendPlainText(line.split(" ")[3].replace("_", " "));
		}
	}

	file.close();
}


void profile::show_changes()
{
	ui->show_movies->clear();
	ui->show_reserved->clear();
	ui->show_sans->clear();

	QString line;
	int size = reserved_inf.size();
	int j = 1;
	for (int i = 0; i < size; i++)
	{
		if (userName == reserved_inf[i].split(" ")[0] && reserved_inf[i].split(" ")[3].toInt())
		{
			line = reserved_inf[i];
			ui->show_movies->appendPlainText(QString::number(j++) + ". ");
			ui->show_movies->insertPlainText(line.split(" ")[1].replace("_", " "));
			ui->show_sans->appendPlainText(line.split(" ")[2].replace("_", " "));
			ui->show_reserved->appendPlainText(line.split(" ")[3].replace("_", " "));
		}
	}
}


void profile::on_btn_logout_clicked()
{
	MainWindow * mw = new MainWindow();
	mw->show();
	this->close();
}


void profile::on_btn_back_clicked()
{
	if (userName == addminName)
	{
		movies_page * mp = new movies_page(userName, true);
		mp->show();
	}
	else
	{
		movies_page * mp = new movies_page(userName, false);
		mp->show();
	}
	this->close();
}


void profile::on_btn_unreseved_clicked()
{
	QString numberStr = ui->lineedit_unreserved->text();
	int reserved_number = index_user_movies.size();

	if (numberStr.isEmpty())
	{
		QMessageBox::warning(this, "Empty Box", "Top Box Is Empty");
		return;
	}

	for (int i = 0; i < numberStr.size(); i++)
	{
		if (numberStr[i] < "0" || numberStr[i] > "9")
		{
			QMessageBox::warning(this, "Number", "Enter A Number!");
			return;
		}
	}

	int number = numberStr.toInt() - 1;
	if (number >= reserved_number || number < 0)
	{
		QMessageBox::warning(this, "Number", "Number Is Not Exist!");
		return;
	}

	QString line1 = reserved_inf[index_user_movies[number]];
	QString line2 = "";

	int reserved = line1.split(" ")[3].toInt();
	reserved--;

	line2.append(line1.split(" ")[0] + " " + line1.split(" ")[1] + " " +
				line1.split(" ")[2] + " " + QString::number(reserved));

	reserved_inf[index_user_movies[number]] = line2;


	QFile file(address3);
	QTextStream inout(&file);
	QString line;

	if (!file.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	while (!inout.atEnd())
	{
		int posation = inout.pos();
		line = inout.readLine();

		if (line == line1)
		{
			inout.seek(posation);
			inout << line2;
			break;
		}
	}
	file.close();


	QFile file2(address2);
	QTextStream inout2(&file2);

	if (!file2.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	line2 = QString();
	while (!inout2.atEnd())
	{
		int posation = inout2.pos();
		line = inout2.readLine();

		if (line.split(" ")[0] == line1.split(" ")[1] &&
			line.split(" ")[12] == line1.split(" ")[2])
		{
			int tickets = line.split(" ")[11].toInt();
			tickets ++;
			for (int i = 0; i < 11; i++)\
				line2.append(line.split(" ")[i] + " ");
			line2.append(QString::number(tickets) + " ");
			line2.append(line.split(" ")[12]);

			inout2.seek(posation);
			inout2 << line2;
			break;
		}
	}

	file2.close();

	show_changes();
}


void profile::on_btn_unresevedall_clicked()
{
	QString numberStr = ui->lineedit_unreserved->text();
	int reserved_number = index_user_movies.size();

	if (ui->lineedit_unreserved->text().isEmpty())
	{
		QMessageBox::warning(this, "Empty Box", "Top Box Is Empty");
		return;
	}

	for (int i = 0; i < numberStr.size(); i++)
	{
		if (numberStr[i] < "0" || numberStr[i] > "9")
		{
			QMessageBox::warning(this, "Number", "Enter A Number!");
			return;
		}
	}

	int number = numberStr.toInt() - 1;
	if (number >= reserved_number || number < 0)
	{
		QMessageBox::warning(this, "Number", "Number Is Not Exist!");
		return;
	}

	QString line1 = reserved_inf[index_user_movies[number]];
	QString line2 = "";

	int reserved = line1.split(" ")[3].toInt();
	int reserve = reserved;
	reserved = 0;

	line2.append(line1.split(" ")[0] + " " + line1.split(" ")[1] + " " +
				line1.split(" ")[2] + " " + QString::number(reserved));

	reserved_inf[index_user_movies[number]] = line2;


	QFile file(address3);
	QTextStream inout(&file);
	QString line;

	if (!file.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	while (!inout.atEnd())
	{
		int posation = inout.pos();
		line = inout.readLine();

		if (line == line1)
		{
			inout.seek(posation);
			inout << line2;
			break;
		}
	}
	file.close();


	QFile file2(address2);
	QTextStream inout2(&file2);

	if (!file2.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	line2 = QString();
	while (!inout2.atEnd())
	{
		int posation = inout2.pos();
		line = inout2.readLine();

		if (line.split(" ")[0] == line1.split(" ")[1] &&
			line.split(" ")[12] == line1.split(" ")[2])
		{
			int tickets = line.split(" ")[11].toInt();
			tickets += reserve;
			for (int i = 0; i < 11; i++)\
				line2.append(line.split(" ")[i] + " ");
			line2.append(QString::number(tickets) + " ");
			line2.append(line.split(" ")[12]);

			inout2.seek(posation);
			inout2 << line2;
			break;
		}
	}

	file2.close();
	show_changes();
}

