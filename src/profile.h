#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
class profile;
}

class profile : public QWidget
{
	Q_OBJECT

public:
	explicit profile(QString username, QWidget *parent = nullptr);
	~profile();
	void show_information();
	void show_changes();

private slots:
	void on_btn_logout_clicked();

	void on_btn_back_clicked();

	void on_btn_unreseved_clicked();

	void on_btn_unresevedall_clicked();

private:
	Ui::profile *ui;
	QString userName;
	QVector<QString> reserved_inf;
	QVector<int> index_user_movies;
};

#endif // PROFILE_H
