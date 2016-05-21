// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 13:38:45
// ������  :    ����̬�߳��б�
//                    �漰���̴߳ӻ̬������̬��Ƶ��ת��������ɾ���ڵ�Ч�ʸߣ��ʲ�ȡlist�ṹ
// ===============================================================================
#pragma once
#include <list>
#include <objbase.h>
using namespace  std;

namespace thead_pool
{
	interface IThread;
	interface ILock;
	class CBusyThreadList
	{
	public:
		CBusyThreadList(void);
		~CBusyThreadList(void);
		// �������߳��б�������߳�
		void AddBusyThread(IThread* pThread);
		// �������߳��б���ɾ���߳�
		void DeleteBusyThread(IThread* pThread); 
		// ���������߳�
		void CleanAllBusyThreads();
	private:
		ILock *m_pLock;
		list<IThread*>m_busyThreadList;
	};

}

