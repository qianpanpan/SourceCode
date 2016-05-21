// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 13:38:45
// ������  :    ����̬�߳��б�
//                    �漰���̴߳ӻ̬������̬��Ƶ��ת��������ɾ���ڵ�Ч�ʸߣ��ʲ�ȡlist�ṹ
// ===============================================================================
#include "BusyThreadList.h"
#include "CriticalLock.h"
#include "IThread.h"

namespace thead_pool
{
	CBusyThreadList::CBusyThreadList(void)
	{
		m_pLock = new CCriticalLock();
	}


	CBusyThreadList::~CBusyThreadList(void)
	{
		delete m_pLock;
		m_pLock = NULL;
	}

	void CBusyThreadList::AddBusyThread(IThread* pThread)
	{
		m_pLock->Lock();
		m_busyThreadList.push_back(pThread);
		m_pLock->UnLock();
	}

	void CBusyThreadList::DeleteBusyThread(IThread* pThread)
	{
		if (!m_busyThreadList.empty())
		{
			m_pLock->Lock();
			m_busyThreadList.remove(pThread);
			m_pLock->UnLock();
		}
	}

	void CBusyThreadList::CleanAllBusyThreads()
	{
		// ���е���һ�������������߳���ӽ�����Ϊ�վͲ�������
		if (!m_busyThreadList.empty())
		{
			m_pLock->Lock();
			list<IThread*>::iterator first = m_busyThreadList.begin();
			list<IThread*>::iterator last = m_busyThreadList.end();
			for(;first!=last;++first)
			{
				// ֪ͨ�߳��˳����ɣ����߳���������������
				(*first)->NotifyThreadExit();
			}
			m_busyThreadList.clear();
			m_pLock->UnLock();
		}
	}
}
