#ifndef REUSE
#define REUSE

#include <string>
#include <sstream>
#include <iostream>
#include "DDSEntityManager.h"
#include "vortex_os.h"
#include "ccpp_code.h"//�ǵ�ʹ���Լ���ccpp
//#include "D:\DDS\HDE\x86_64.win64\examples\include\example_main.h"
#include "example_main.h"//�˴��ǵý�OSPL��example_main.h�ļ���������ǰ��Ŀ��

using namespace DDS;
using namespace CodeData;//�˴�Ҳ��ʹ�ø����Լ������IDL���ɵ������ռ�

class reusePub
{
	DDSEntityManager mgr;
public:
	//�������ӣ�ֻ�ڵ�һ�η���ʱ������֮��ÿ�η��Ͳ��ٴ���
	void createConnection(const char* partition, char *topic);//����1��������������2��������

															  //���з���
	void pubMsg(int coderID, const char* fileName, const char* uploadTime, const char* codeContent);

	//ɾ�����ӣ�ֻ�����˳���������ʱ��ɾ��������������ȵ�
	void endDelete();
	~reusePub();
};

class reuseSub
{
public:
	DDSEntityManager mgr;
	//�������ӣ�ֻ�ڵ�һ�η���ʱ������֮��ÿ�η��Ͳ��ٴ���
	void createConnection(const char* partition, char *topic);//����1��������������2��������

															  //���н��գ�����ʱ��ѭ���������1500�Σ�ÿ�μ��2ms
	void subMsg();

	//ɾ�����ӣ�ֻ�����˳���������ʱ��ɾ��������������ȵ�
	void endDelete();
	~reuseSub();
};
#endif