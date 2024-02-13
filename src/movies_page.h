#ifndef MOVIES_PAGE_H
#define MOVIES_PAGE_H

#include "ui_movies_page.h"

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>

#define address "/home/mohammad/Documents/University/Projects/booking_cinema_ticket/Booking-Cinema-Ticket/src/names_passwords.txt"
#define address2 "/home/mohammad/Documents/University/Projects/booking_cinema_ticket/Booking-Cinema-Ticket/src/movies_information.txt"
#define address3 "/home/mohammad/Documents/University/Projects/booking_cinema_ticket/Booking-Cinema-Ticket/src/reserved_information.txt"

#define addminName  "Mohammad"
#define addminPassword  "1234"

namespace Ui {
class movies_page;
}

class movies_page : public QWidget
{
	Q_OBJECT

public:
	explicit movies_page(QString username = "", bool addmin = true, QWidget *parent = nullptr);
	~movies_page();
	void show_movies();
	void add_infmovies_to_vector();
	int what_box();

private slots:
	void on_btn_addnew_clicked();

	void on_btn_nextpage_clicked();

	void on_btn_perviouspage_clicked();

	void on_btn_firstpage_clicked();

	void on_btn_lastpage_clicked();

	void on_btn_edit_clicked();

	void on_btn_delete_clicked();

	void on_btn_reserve_clicked();

	void on_btn_search_clicked();

	void on_btn_cancel_search_clicked();

	void on_btn_profile_clicked();

	void on_btn_control_clicked();

private:
	Ui::movies_page *ui;
	bool access = 0;
	bool search = 0;
	QVector<QString> line_information;
	QVector<QString> line_information_search;
	int recent_page = 1;
	int last_page;
	QString userName;
};

#endif // MOVIES_PAGE_H
