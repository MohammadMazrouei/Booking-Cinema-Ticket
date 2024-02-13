#include "addnewmovie.h"
#include "ui_addnewmovie.h"
#include "movies_page.h"

addnewmovie::addnewmovie(int number_movie, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::addnewmovie)
{
	ui->setupUi(this);
	number = number_movie;
	if (number_movie != -1)
	{
		show_inf_movie();
		editing = true;
	}
}

addnewmovie::~addnewmovie()
{
	delete ui;
}


void addnewmovie::on_btn_cancel_clicked()
{
	movies_page * mp = new movies_page();
	mp->show();
	this->close();
}


void addnewmovie::on_btn_apply_clicked()
{
	QString moviename, director, producer, writer, cast1, cast2, cast3, musician;
	QString countries, genres, sans, releaseyear, tickets;

	// Read information on fields
	{
		moviename = ui->get_moviename->text();
		director = ui->get_director->text();
		producer = ui->get_producer->text();
		writer = ui->get_writer->text();
		cast1 = ui->get_cast1->text();
		musician = ui->get_musician->text();
		countries = ui->get_countries->text();
		genres = ui->get_genres->text();
		sans = ui->get_sans->text();
		releaseyear = ui->get_releaseyear->text();
		tickets = ui->get_tickets->text();
		if (!ui->get_cast2->text().isEmpty())
			cast2 = ui->get_cast2->text();
		else
			cast2 = "_____";
		if (!ui->get_cast3->text().isEmpty())
			cast3 = ui->get_cast3->text();
		else
			cast3 = "_____";
	}

	// Warning Empty Fields
	{
		if (moviename.isEmpty())
		{
			QMessageBox::warning(this, "Movies Name", "Movies Name Field Is Empty!");
			return;
		}
		if (director.isEmpty())
		{
			QMessageBox::warning(this, "Director", "Director Field Is Empty!");
			return;
		}
		if (producer.isEmpty())
		{
			QMessageBox::warning(this, "Producer", "Producer Field Is Empty!");
			return;
		}
		if (writer.isEmpty())
		{
			QMessageBox::warning(this, "Writer", "Writer Field Is Empty!");
			return;
		}
		if (cast1.isEmpty())
		{
			QMessageBox::warning(this, "Cast", "Cast Field Is Empty!");
			return;
		}
		if (musician.isEmpty())
		{
			QMessageBox::warning(this, "Musician", "Musician Field Is Empty!");
			return;
		}
		if (countries.isEmpty())
		{
			QMessageBox::warning(this, "Countries", "Countries Field Is Empty!");
			return;
		}
		if (releaseyear.isEmpty())
		{
			QMessageBox::warning(this, "Release Year", "Release Year Field Is Empty!");
			return;
		}
		if (genres.isEmpty())
		{
			QMessageBox::warning(this, "Genres", "Genres Field Is Empty!");
			return;
		}
		if (tickets.isEmpty())
		{
			QMessageBox::warning(this, "Tickets", "Tickets Field Is Empty!");
			return;
		}
		if (sans.isEmpty())
		{
			QMessageBox::warning(this, "Sans", "Sans Field Is Empty!");
			return;
		}
	}

	// Replace "_" for Space
	{
		moviename = moviename.replace(" ", "_");
		director = director.replace(" ", "_");
		producer = producer.replace(" ", "_");
		writer = writer.replace(" ", "_");
		cast1 = cast1.replace(" ", "_");
		cast2 = cast2.replace(" ", "_");
		cast3 = cast3.replace(" ", "_");
		musician = musician.replace(" ", "_");
		countries = countries.replace(" ", "_");
		releaseyear = releaseyear.replace(" ", "_");
		genres = genres.replace(" ", "_");
		tickets = tickets.replace(" ", "_");
		sans = sans.replace(" ", "_");
	}

	// Check Release Year
	{
		if (releaseyear.size() != 4)
		{
			QMessageBox::warning(this, "Release Year", "Release Year Is Incorrect!");
			return;
		}
		for (int i = 0; i < 4; i++)
		{
			if (releaseyear[i] < "0" || releaseyear[i] > "9")
			{
				QMessageBox::warning(this, "Release Year", "Release Year Is Incorrect!");
				return;
			}
		}
	}

	// Check Tickets
	{
		for (int i = 0; i < tickets.size(); i++)
		{
			if (tickets[i] < "0" || tickets[i] > "9")
			{
				QMessageBox::warning(this, "Tickets", "Tickets Is Incorrect!");
				return;
			}
		}
	}

	QFile file(address2);
	QTextStream out(&file);

	if (!file.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	if (editing)
	{
		QString line = "";
		line.append(moviename + " " + director + " " + producer + " " + writer + " " +
					cast1 + " " + cast2 + " " + cast3 + " " + musician + " " +
					countries + " " + genres + " " + releaseyear + " " + tickets + " " + sans);

		lines[number] = line;

		int size = lines.size();
		file.resize(file.pos());
		for (int i = 0; i < size; i++)
		{
			if (i != 0)
				out << "\n";

			out << lines[i];
		}
	}

	else
	{
		while (!out.atEnd())
			out.readLine();

		out << "\n" << moviename << " " << director << " " << producer << " " << writer << " ";
		out << cast1 << " " << cast2 << " " << cast3 << " " << musician << " " << countries;
		out << " " << genres << " " << releaseyear << " " << tickets << " " << sans;
	}

	file.close();

	if (editing)
	{
		QString edited_name_movie = ui->get_moviename->text().replace(" ", "_");
		QString edited_sans_movie = ui->get_sans->text().replace(" ", "_");

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
			if (!(line.split(" ")[1] == name_movie && line.split(" ")[2] == sans_movie))
			{
				reserve_inf.push_back(line);
			}
			else
			{
				QString line2 = "";
				line2.append(line.split(" ")[0] + " " + edited_name_movie + " " +
							 edited_sans_movie + " " + line.split(" ")[3]);

				reserve_inf.push_back(line2);
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
	}

	movies_page * mp = new movies_page();
	mp->show();
	this->close();
}


void addnewmovie::show_inf_movie()
{
	QFile file(address2);
	QTextStream in(&file);

	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "File", "File Not Open!");
		return;
	}

	QString line;

	while (!in.atEnd())
	{
		line = in.readLine();
		lines.push_back(line);
	}
	file.close();
	line = lines[number];

	name_movie = line.split(" ")[0];
	sans_movie = line.split(" ")[12];

	// Show information movies in boxs
	{
		ui->get_moviename->setText(line.split(" ")[0].replace("_", " "));
		ui->get_director->setText(line.split(" ")[1].replace("_", " "));
		ui->get_producer->setText(line.split(" ")[2].replace("_", " "));
		ui->get_writer->setText(line.split(" ")[3].replace("_", " "));
		ui->get_cast1->setText(line.split(" ")[4].replace("_", " "));
		ui->get_cast2->setText(line.split(" ")[5].replace("_", " "));
		ui->get_cast3->setText(line.split(" ")[6].replace("_", " "));
		ui->get_musician->setText(line.split(" ")[7].replace("_", " "));
		ui->get_countries->setText(line.split(" ")[8].replace("_", " "));
		ui->get_genres->setText(line.split(" ")[9].replace("_", " "));
		ui->get_releaseyear->setText(line.split(" ")[10].replace("_", " "));
		ui->get_tickets->setText(line.split(" ")[11].replace("_", " "));
		ui->get_sans->setText(line.split(" ")[12].replace("_", " "));
	}
}

