#include "Files.h"
#include <iostream>
#include <QMessageBox>
#include <io.h>
#include <string>
using namespace std;




Files::Files(QString owner, QString name, int linenum)
{
	this->name = name;
	this->owner = owner;
	this->linenum = linenum;
}

void Files::save()
{
	char tmp[64];
	time_t t = time(0);
	strftime(tmp, sizeof(tmp), "%m-%d-%H-%m", localtime(&t));
	this->tm = QString(QLatin1String(tmp));
	std::ofstream outfile;
	string filename = "code//" + this->name.toStdString() + "_" + this->tm.toStdString() + ".txt";
	//string filename = this->name.toStdString() + "_" + this->tm.toStdString() + ".txt";
	outfile.open(filename); //���������ļ�
	QMessageBox::about(NULL, "�ɹ�", QString::fromStdString(filename));
	// outfile<<this->owner.toStdString()<<endl;
	//outfile<<this->tm.toStdString()<<endl;

	outfile << words.toStdString() << endl;

	outfile.close(); //�ر��ļ�
	QMessageBox::about(NULL, "�ɹ�", "�����ϴ��ɹ�!");
	
}

void Files::get() {
	fstream in;
	in.open("code//"+this->fname.toStdString()+".txt");//���ļ�
												 //���ж�ȡ
	string str;
	string code = "";
	int i = 0;
	while (getline(in, str))
	{
		code += str;
		i++;
	}
	this->words = QString::fromStdString(code);
	linenum = i;
	in.close();//�ر��ļ�
}


Files::~Files()
{
}
