#include "movies_page.h"
#include "ui_movies_page.h"
#include "addnewmovie.h"
#include "profile.h"
#include "control.h"

movies_page::movies_page(QString username, bool addmin, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::movies_page)
{
	ui->setupUi(this);
	access = addmin;
	add_infmovies_to_vector();
	show_movies();
	ui->show_movie1->setReadOnly(1);
	ui->show_movie2->setReadOnly(1);
	ui->show_movie3->setReadOnly(1);
	userName = username;
	if (userName.isEmpty())
		userName = addminName;
}

movies_page::~movies_page()
{
	delete ui;
}


void movies_page::show_movies()
{
	int number_movie = (recent_page - 1 ) * 3;
	int all_movies;
	QPlainTextEdit * boxs[3] = {ui->show_movie1, ui->show_movie2, ui->show_movie3};
	ui->show_movie1->clear();
	ui->show_movie2->clear();
	ui->show_movie3->clear();

	if (search)
	{
		all_movies = line_information_search.size();
		last_page = ((line_information_search.size()-1) / 3 ) + 1;

		for (int i = 0; i < 3; i++)
		{
			if (all_movies <= (number_movie + i))
				break;

			boxs[i]->appendPlainText(line_information_search[number_movie + i].split(" ")[0].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Director : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[1].replace("_", " "));

			boxs[i]->appendPlainText("Producer : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[2].replace("_", " "));

			boxs[i]->appendPlainText("Writer : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[3].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Cast : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[4].replace("_", " "));

			boxs[i]->appendPlainText("            ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[5].replace("_", " "));

			boxs[i]->appendPlainText("            ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[6].replace("_", " "));
			boxs[i]->appendPlainText("");


			boxs[i]->appendPlainText("Musician : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[7].replace("_", " "));

			boxs[i]->appendPlainText("Countries : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[8].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Genres : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[9].replace("_", " "));

			boxs[i]->appendPlainText("Release Year : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[10].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Tickets : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[11].replace("_", " "));

			boxs[i]->appendPlainText("Sans : ");
			boxs[i]->insertPlainText(line_information_search[number_movie + i].split(" ")[12].replace("_", " "));
		}
	}
	else
	{
		all_movies = line_information.size();
		last_page = ((line_information.size()-1) / 3 ) + 1;

		for (int i = 0; i < 3; i++)
		{
			if (all_movies <= (number_movie + i))
				break;

			boxs[i]->appendPlainText(line_information[number_movie + i].split(" ")[0].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Director : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[1].replace("_", " "));

			boxs[i]->appendPlainText("Producer : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[2].replace("_", " "));

			boxs[i]->appendPlainText("Writer : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[3].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Cast : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[4].replace("_", " "));

			boxs[i]->appendPlainText("            ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[5].replace("_", " "));

			boxs[i]->appendPlainText("            ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[6].replace("_", " "));
			boxs[i]->appendPlainText("");


			boxs[i]->appendPlainText("Musician : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[7].replace("_", " "));

			boxs[i]->appendPlainText("Countries : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[8].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Genres : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[9].replace("_", " "));

			boxs[i]->appendPlainText("Release Year : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[10].replace("_", " "));
			boxs[i]->appendPlainText("");

			boxs[i]->appendPlainText("Tickets : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[11].replace("_", " "));

			boxs[i]->appendPlainText("Sans : ");
			boxs[i]->insertPlainText(line_information[number_movie + i].split(" ")[12].replace("_", " "));
		}
	}

	ui->label_counter->setText(QString::number(recent_page) + " / " + QString::number(last_page));
}


void movies_page::add_infmovies_to_vector()
{
	QFile file(address2);
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
		line_information.push_back(line);
	}

	file.close();
}


int movies_page::what_box()
{
	QMessageBox * quiz = new QMessageBox(QMessageBox::Information,
										tr("Question"),
										tr("What is Boxs ?"),
										QMessageBox::Yes | QMessageBox::No |
										QMessageBox::Close | QMessageBox::Cancel);

	quiz->button(QMessageBox::Close)->setText(tr("Box1"));
	quiz->button(QMessageBox::No)->setText(tr("Box2"));
	quiz->button(QMessageBox::Yes)->setText(tr("Box3"));

	int result = quiz->exec();
	delete quiz;

	return result;
}


void movies_page::on_btn_addnew_clicked()
{
	if (access)
	{
		addnewmovie * add = new addnewmovie();
		add->show();
		this->close();
	}
	else
	{
		QMessageBox::warning(this, "No Access", "You Are Not Addmin!");
		return;
	}
}


void movies_page::on_btn_nextpage_clicked()
{
	if (recent_page == last_page)
		return;

	recent_page ++;
	show_movies();
}


void movies_page::on_btn_perviouspage_clicked()
{
	if (recent_page == 1)
		return;

	recent_page --;
	show_movies();
}


void movies_page::on_btn_firstpage_clicked()
{
	if (recent_page == 1)
		return;

	recent_page = 1;
	show_movies();
}


void movies_page::on_btn_lastpage_clicked()
{
	if (recent_page == last_page)
		return;

	recent_page = last_page;
	show_movies();
}


void movies_page::on_btn_edit_clicked()
{
	if (!access)
	{
		QMessageBox::warning(this, "No Access", "You Are Not Addmin!");
		return;
	}

	int result = what_box();

	int number_movie = (recent_page - 1) * 3;
	if (result == QMessageBox::Close)
		number_movie += 0;
	else if (result == QMessageBox::No)
	{
		number_movie += 1;
		if (number_movie >= line_information.size())
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}
	}
	else if (result == QMessageBox::Yes)
	{
		number_movie += 2;
		if (number_movie >= line_information.size())
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}
	}
	else if (result == QMessageBox::Cancel)
		return;

	if (search)
	{
		int s = line_information.size();
		if (number_movie >= s)
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}

		for (int i = 0; i < s; i++)
		{
			if (line_information_search[number_movie] == line_information[i])
				number_movie = i;
		}
	}

	addnewmovie * edit = new addnewmovie(number_movie);
	edit->show();
	this->close();
}


void movies_page::on_btn_delete_clicked()
{
	if (!access)
	{
		QMessageBox::warning(this, "No Access", "You Are Not Addmin!");
		return;
	}

	int result = what_box();

	int number_movie = (recent_page - 1) * 3;
	if (result == QMessageBox::Close)
		number_movie += 0;
	else if (result == QMessageBox::No)
	{
		number_movie += 1;
		if (number_movie >= line_information.size())
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}
	}
	else if (result == QMessageBox::Yes)
	{
		number_movie += 2;
		if (number_movie >= line_information.size())
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}
	}
	else if (result == QMessageBox::Cancel)
		return;

	if (search)
	{
		int s = line_information.size();
		if (number_movie >= s)
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}

		for (int i = 0; i < s; i++)
		{
			if (line_information_search[number_movie] == line_information[i])
				number_movie = i;
		}
	}

	QString deleted_name_movie = line_information[number_movie].split(" ")[0];
	QString deleted_sans_movie = line_information[number_movie].split(" ")[12];
	line_information.erase(line_information.begin() + number_movie);
	int size = line_information.size();

	QFile file(address2);
	QTextStream out(&file);

	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
			QMessageBox::warning(this, "File", "File Not Open!");
			return;
	}

	file.resize(file.pos());
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
			out << "\n";

		out << line_information[i];
	}
	file.close();


	QFile file2(address3);
	QTextStream inout(&file2);
	QVector<QString> reserve_inf;
	QString line;

	if (!file2.open(QFile::ReadOnly | QFile::Text))
	{
			QMessageBox::warning(this, "File", "File Not Open!");
			return;
	}

	while (!inout.atEnd())
	{
		line = inout.readLine();
		if (!(line.split(" ")[1] == deleted_name_movie && line.split(" ")[2] == deleted_sans_movie))
		{
			reserve_inf.push_back(line);
		}
	}
	file2.close();

	if (!file2.open(QFile::WriteOnly | QFile::Text))
	{
			QMessageBox::warning(this, "File", "File Not Open!");
			return;
	}

	file2.resize(file2.pos());

	int size2 = reserve_inf.size();

	for (int i = 0; i < size2; i++)
	{
		if (i) inout << "\n";
		inout << reserve_inf[i];
	}
	file2.close();


	show_movies();

	if (search)
		on_btn_search_clicked();

	if (recent_page > last_page)
		on_btn_perviouspage_clicked();
}


void movies_page::on_btn_reserve_clicked()
{
	int result = what_box();

	int number_movie = (recent_page - 1) * 3;
	if (result == QMessageBox::Close)
		number_movie += 0;
	else if (result == QMessageBox::No)
	{
		number_movie += 1;
		if (number_movie >= line_information.size())
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}
	}
	else if (result == QMessageBox::Yes)
	{
		number_movie += 2;
		if (number_movie >= line_information.size())
		{
			QMessageBox::warning(this, "Box Empty!", "This Box Is Empty");
			return;
		}
	}
	else if (result == QMessageBox::Cancel)
		return;

	QString line1 = line_information[number_movie];
	QString line2 = "";

	for (int i = 0; i < 13; i++)
	{
		if (i == 11)
		{
			int tickets = line1.split(" ")[i].toInt();
			if (tickets == 0)
			{
				QMessageBox::warning(this, "Tickets", "Tickets Not Exist For This Movie!");
				return;
			}
			tickets--;
			line2.append(QString::number(tickets) + " ");
		}
		else
		{
			line2.append(line1.split(" ")[i] + " ");
		}
	}

	line_information[number_movie] = line2;
	int size = line_information.size();

	QFile file(address2);
	QTextStream out(&file);

	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	file.resize(file.pos());
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
			out << "\n";

		out << line_information[i];
	}
	file.close();


	QFile file2(address3);
	QTextStream inout(&file2);

	if (!file2.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	QString movieName = line_information[number_movie].split(" ")[0];
	QString sans = line_information[number_movie].split(" ")[12];
	bool reserved = false;
	while (!inout.atEnd())
	{
		int current_pos = inout.pos();
		line1 = inout.readLine();
		if (line1.split(" ")[0] == userName && line1.split(" ")[1] == movieName &&
			line1.split(" ")[2] == sans)
		{
			int tickets = line1.split(" ")[3].toInt();
			tickets++;
			inout.seek(current_pos);
			inout << userName << " " << movieName << " " << sans << " " << QString::number(tickets);
			reserved = true;
			break;
		}
	}

	if (!reserved)
	{
		inout << "\n" << userName << " " << movieName << " " << sans << " 1";
	}

	file2.close();

	show_movies();
}


void movies_page::on_btn_search_clicked()
{
	if (ui->searchbox->text().isEmpty())
	{
		QMessageBox::warning(this, "Empty", "Search Box Is Empty!");
		return;
	}

	line_information_search.clear();
	search = true;
	int size = line_information.size();
	QString line1, line2, box;

	for (int i = 0; i < size; i++)
	{
		line1 = line_information[i];
		line2 = line1.toUpper().replace("_", " ");
		box = ui->searchbox->text().toUpper();
		if (line2.contains(box))
		{
			line_information_search.push_back(line1);
		}
	}
	recent_page = 1;
	show_movies();
}


void movies_page::on_btn_cancel_search_clicked()
{
	if (search)
		search = false;

	ui->searchbox->clear();
	line_information_search.clear();

	show_movies();
}


void movies_page::on_btn_profile_clicked()
{
	profile * prof = new profile(userName);
	prof->show();
	this->close();
}


void movies_page::on_btn_control_clicked()
{
	if (access)
	{
		control * co = new control();
		co->show();
		this->close();
	}
	else
	{
		QMessageBox::warning(this, "No Access", "You Are Not Addmin!");
		return;
	}
}
