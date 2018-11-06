#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <codehistory.h>
#include <person.h>
#include <iostream>
#include <Files.h>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	CodeHistory* ch = new CodeHistory();
	~MainWindow();
	void MainWindow::setPersons();
	void MainWindow::setPerson(QString ip);
	void MainWindow::getHistory(QString ip);
	int MainWindow::geti();

	private slots:
	void on_team_clicked();

	void on_submit_clicked();

	void on_person_lw_itemClicked(QListWidgetItem *item);

	void on_update_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

