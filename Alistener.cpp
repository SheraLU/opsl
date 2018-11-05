#include "Alistener.h"
#include "CheckStatus.h"
#include <sstream>
#include<fstream>
#include"data.h"

using namespace DDS;
using namespace CodeData;

void getAllFiles(string path, vector<string>& files)
{
	// 文件句柄
	long long hFile = 0;
	// 文件信息
	struct _finddata_t fileinfo;

	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*.txt").c_str(), &fileinfo)) != -1) {
		while (1) {
			// 保存文件的全路径
			files.push_back(p.assign(fileinfo.name));
			if (_findnext(hFile, &fileinfo))
				break;
		} //寻找下一个，成功返回0，否则-1

		_findclose(hFile);
	}
}

void Alistener::on_data_available(DDS::DataReader_ptr reader)
THROW_ORB_EXCEPTIONS
{
	DDS::ReturnCode_t status;
	CodeSeq msgList;
	SampleInfoSeq infoSeq;
	auto i = Luxijun::getInstance();
	status = m_MsgReader->read(msgList, infoSeq, LENGTH_UNLIMITED,
		ANY_SAMPLE_STATE, NEW_VIEW_STATE, ANY_INSTANCE_STATE);
	checkStatus(status, "MsgDataReader::read");
	printf("=== [ListenerDataListener::on_data_available] - msgList.length : %d\n", msgList.length());
	for (DDS::ULong j = 0; j < msgList.length(); j++)
	{
		string time = msgList[j].uploadTime;
		if (time.compare("-1") == 0)//收到请求【设定时间为-1的消息为请求】
		{
			reusePub ASendCode;
			if (msgList[j].coderID < 2)
				cout << "当前节点" << endl;
			else 
			{
				if (msgList[j].coderID <3 )//默认当前节点为1，后续根据用户更改
					ASendCode.createConnection("AB", "msgab");
				else if (msgList[j].coderID <4)
					ASendCode.createConnection("AC", "msgac");
				else if (msgList[j].coderID <5)
					ASendCode.createConnection("AD", "msgad");
				else if (msgList[j].coderID <6)
					ASendCode.createConnection("AE", "msgae");
				vector<string> fs;
				getAllFiles("D:\\materials\\TISHE\\HDE\\x86_64.win64\\opslTest\\CodeManagerTest\\CodeManager\\code", fs);
				char str[100];
				int size = fs.size();
				for (int i = 0; i < size; i++)
				{
					string word;
					fstream filein;
					filein.open(".\\code\\" + fs[i], ios::in);
					filein >> word;
					ASendCode.pubMsg(1,fs[i].data(), "time", word.data());//发送本地代码

					//os_nanoSleep({ 0, 2000000000 });
				}
				ASendCode.endDelete();
			}
		}
		else//收到代码
		{
			int id = msgList[j].coderID;
			if(msgList[j].coderID < 2)
				cout << "当前节点" << endl;
			else  if (id < 3)
				i->msgListB.push_back(msgList[j]); 
			else if (id < 4)
				i->msgListC.push_back(msgList[j]);
			else if (id < 5)
				i->msgListD.push_back(msgList[j]);
			else if (id < 6)
				i->msgListE.push_back(msgList[j]);
			else
				cout << "Wrong Puber" << endl;
			string filen= msgList[j].fileName;
			string cont = msgList[j].codeContent;
			printf("\n    --- message received ---\n");
			printf("\n    userID  : %d\n", msgList[j].coderID);
			printf("\n    fileName  : %d\n", filen);
			cout << "   Message :" << cont << endl;
		}
	}
	//status = m_MsgReader->return_loan(msgList, infoSeq);
	//checkStatus(status, "MsgDataReader::return_loan");
	// unblock the waitset in Subscriber main loop
	m_guardCond->set_trigger_value(true);
};

void Alistener::on_requested_deadline_missed(DDS::DataReader_ptr
	reader, const DDS::RequestedDeadlineMissedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_requested_deadline_missed] : triggered\n");
	printf("\n=== [ListenerDataListener::on_requested_deadline_missed] : stopping\n");
	m_closed = true;
	// unblock the waitset in Subscriber main loop
	m_guardCond->set_trigger_value(true);
};

void Alistener::on_requested_incompatible_qos(DDS::DataReader_ptr
	reader, const DDS::RequestedIncompatibleQosStatus &status)
	THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_requested_incompatible_qos] : triggered\n");
};

void Alistener::on_sample_rejected(DDS::DataReader_ptr reader, const
	DDS::SampleRejectedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_sample_rejected] : triggered\n");
};

void Alistener::on_liveliness_changed(DDS::DataReader_ptr reader,
	const DDS::LivelinessChangedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_liveliness_changed] : triggered\n");
};

void Alistener::on_subscription_matched(DDS::DataReader_ptr reader,
	const DDS::SubscriptionMatchedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_subscription_matched] : triggered\n");
};

void Alistener::on_sample_lost(DDS::DataReader_ptr reader, const DDS
	::SampleLostStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_sample_lost] : triggered\n");
};

