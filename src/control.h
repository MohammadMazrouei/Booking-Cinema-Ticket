#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>

namespace Ui {
class control;
}

class control : public QWidget
{
	Q_OBJECT

public:
	explicit control(QWidget *parent = nullptr);
	~control();
	void show_information();

private slots:
	void on_btn_back_clicked();

private:
	Ui::control *ui;
};

#endif // CONTROL_H
