#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	bool check_name(QString);
	bool check_password(QString);

private slots:
	void on_btn_signup_clicked();

	void on_btn_login_clicked();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
