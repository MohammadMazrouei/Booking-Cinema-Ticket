#include "control.h"
#include "ui_control.h"
#include "movies_page.h"

control::control(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::control)
{
	ui->setupUi(this);
	ui->show_movies->setReadOnly(1);
	ui->show_names->setReadOnly(1);
	ui->show_reserved->setReadOnly(1);
	ui->show_sans->setReadOnly(1);
	show_information();
}

control::~control()
{
	delete ui;
}


void control::on_btn_back_clicked()
{
	movies_page * mp = new movies_page();
	mp->show();
	this->close();
}


void control::show_information()
{
	QFile file(address3);
	QTextStream in(&file);
	QString name, movie, sans, reserved;
	int j = 1;

	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Exist!");
		return;
	}

	while (!in.atEnd())
	{
		in >> name >> movie >> sans >> reserved;
		if (reserved.toInt() != 0)
		{
			ui->show_names->appendPlainText(QString::number(j++) + ". ");
			ui->show_names->insertPlainText(name);
			ui->show_movies->appendPlainText(movie.replace("_", " "));
			ui->show_sans->appendPlainText(sans.replace("_", " "));
			ui->show_reserved->appendPlainText(reserved.replace("_", " "));
		}
	}
	file.close();
}

