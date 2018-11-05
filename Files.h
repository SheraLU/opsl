#pragma once
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string.h>
#include <QString>
#include "fstream"
class Files
{
public:
	Files(QString name, QString owner, int linenum);
	~Files(); 
		QString name;
		QString tm;
		QString owner;
		QString words;
		QString fname;
		int linenum;
		void save();
		void get();
};

