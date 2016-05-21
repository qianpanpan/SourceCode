// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 13:23:08
// ������  :    �����̶߳���
//					  ���ݾֲ���ԭ������������߳�֮�ڴ���������У��ʲ�ȡջ�ṹ��ſ����߳�
// ===============================================================================
#include "IdleThreadStack.h"
#include "CriticalLock.h"
#include "IThread.h"

namespace thead_pool
{
	CIdleThreadStack::CIdleThreadStack(void)
	{
		m_pLock = new CCriticalLock();
	}


	CIdleThreadStack::~CIdleThreadStack(void)
	{
		delete m_pLock;
		m_pLock = NULL;
	}

	void CIdleThreadStack::AddIdleThread(IThread *pThread)
	{
		m_pLock->Lock();
		m_idleThreads.push(pThread);
		m_pLock->UnLock();
	}

	IThread* CIdleThreadStack::PopIdleThread()
	{
		IThread *pThread = NULL;
		if (!m_idleThreads.empty())
		{
			m_pLock->Lock();
			pThread = m_idleThreads.top();
			m_idleThreads.pop();
			m_pLock->UnLock();
		}
		return pThread;
	}

	void CIdleThreadStack::CleanAllIdleThreads()
	{
		// ���е���һ�������������߳���ӽ�����Ϊ�վͲ�������
		if (!m_idleThreads.empty())
		{
			m_pLock->Lock();

			IThread *pThread = m_idleThreads.top();

			// ֪ͨ�߳��˳����ɣ����߳���������������
			pThread->NotifyThreadExit();
			m_idleThreads.pop();
			m_pLock->UnLock();
		}
	}
}

