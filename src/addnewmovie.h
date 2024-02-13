#ifndef ADDNEWMOVIE_H
#define ADDNEWMOVIE_H

#include <QWidget>

namespace Ui {
class addnewmovie;
}

class addnewmovie : public QWidget
{
	Q_OBJECT

public:
	explicit addnewmovie(int number_movie = -1, QWidget *parent = nullptr);
	~addnewmovie();
	void show_inf_movie();
	bool check_name(QString name);

private slots:
	void on_btn_cancel_clicked();

	void on_btn_apply_clicked();

private:
	Ui::addnewmovie *ui;
	int number;
	bool editing = false;
	QVector<QString> lines;
	QString name_movie, sans_movie;
};

#endif // ADDNEWMOVIE_H
