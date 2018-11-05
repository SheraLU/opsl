#ifndef CODEHISTORY_H
#define CODEHISTORY_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QString>
#include<data.h>

namespace Ui {
class CodeHistory;
}

class CodeHistory : public QWidget
{
    Q_OBJECT

public:
    explicit CodeHistory(QWidget *parent = 0,QString ip="");
    QString ip;
	//void getfiles();
	void getfiles(QString i);
   // void gettimes();
    ~CodeHistory();

private slots:
    void on_uptime_itemClicked(QListWidgetItem *item);

private:
    Ui::CodeHistory *ui;
};

#endif // CODEHISTORY_H
