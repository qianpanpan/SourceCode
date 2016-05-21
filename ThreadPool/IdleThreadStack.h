// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 13:23:08
// ������  :    �����̶߳���
//					  ���ݾֲ���ԭ������������߳�֮�ڴ���������У��ڴ滻ҳ�Ŀ���С��
//					  �ʲ�ȡջ�ṹ��ſ����߳�
// ===============================================================================
#pragma once
#include <stack>
#include <objbase.h>
using namespace std;

namespace thead_pool
{
	interface IThread;
	interface ILock;

	class CIdleThreadStack
	{
	public:
		CIdleThreadStack(void);
		~CIdleThreadStack(void);
		// ������߳�ջ������߳�
		void AddIdleThread(IThread *pThread);
		// �ӿ����߳�ջ��ȡ�߳�
		IThread* PopIdleThread();
		// ��������߳�
		void CleanAllIdleThreads();
	private:
		ILock *m_pLock;
		stack<IThread*>m_idleThreads;
	};
}

