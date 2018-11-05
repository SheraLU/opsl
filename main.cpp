#include "mainwindow.h"
#include <QApplication>
#include<qdebug.h>
#include"Alistener.h"
#include"data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	bool closed = false;
	ReturnCode_t status = -1;
	int count = 0;

	auto i = Luxijun::getInstance();
	/*根据节点号改*/
	i->BtoA.createConnection("AB", "msgab");
	i->CtoA.createConnection("AC", "msgac");
	i->DtoA.createConnection("AD", "msgad");
	i->EtoA.createConnection("AE", "msgae");
	DataReader_var Breader = i->BtoA.mgr.getReader(), Creader = i->CtoA.mgr.getReader(),
		Dreader = i->DtoA.mgr.getReader(), Ereader = i->EtoA.mgr.getReader();
	Alistener *BListener = new Alistener(), *CListener = new Alistener(),
		*DListener = new Alistener(),*EListener = new Alistener();
	BListener->m_MsgReader = CodeDataReader::_narrow(Breader.in());
	CListener->m_MsgReader = CodeDataReader::_narrow(Creader.in());
	DListener->m_MsgReader = CodeDataReader::_narrow(Dreader.in());
	EListener->m_MsgReader = CodeDataReader::_narrow(Ereader.in());
	checkHandle(BListener->m_MsgReader.in(), "MsgDataReader::_narrow");
	checkHandle(CListener->m_MsgReader.in(), "MsgDataReader::_narrow");
	checkHandle(DListener->m_MsgReader.in(), "MsgDataReader::_narrow");
	checkHandle(EListener->m_MsgReader.in(), "MsgDataReader::_narrow");

	cout << "=== [ListenerDataSubscriber] set_listener" << endl;
	DDS::StatusMask mask =
		DDS::DATA_AVAILABLE_STATUS | DDS::REQUESTED_DEADLINE_MISSED_STATUS;
	BListener->m_MsgReader->set_listener(BListener, mask);
	cout << "=== [ListenerDataSubscriber] B Ready ..." << endl;
	BListener->m_closed = false;

	CListener->m_MsgReader->set_listener(CListener, mask);
	cout << "=== [ListenerDataSubscriber] C Ready ..." << endl;
	CListener->m_closed = false;

	DListener->m_MsgReader->set_listener(DListener, mask);
	cout << "=== [ListenerDataSubscriber] D Ready ..." << endl;
	DListener->m_closed = false;

	EListener->m_MsgReader->set_listener(EListener, mask);
	cout << "=== [ListenerDataSubscriber] E Ready ..." << endl;
	EListener->m_closed = false;

	// waitset used to avoid spinning in the loop below
	DDS::WaitSet_var ws = new DDS::WaitSet();
	ws->attach_condition(BListener->m_guardCond);
	ws->attach_condition(CListener->m_guardCond);
	ws->attach_condition(DListener->m_guardCond);
	ws->attach_condition(EListener->m_guardCond);
	DDS::ConditionSeq condSeq;

	cout << "===[ListenerDataSubscriber] Market Closed" << endl;


    a.exec();
	return 0;
}
