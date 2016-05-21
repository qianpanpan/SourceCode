// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 14:52:27
// ������  :������У������Ƚ��ȳ��Ķ�����Ϊ��������    
// ===============================================================================
#include "TaskQueue.h"
#include "CriticalLock.h"
#include "IThreadTask.h"

namespace thead_pool
{
	CTaskQueue::CTaskQueue(void)
	{
		m_pLock = new CCriticalLock();
	}

	CTaskQueue::~CTaskQueue(void)
	{
		delete m_pLock;
		m_pLock = NULL;
	}

	void CTaskQueue::AddThreadTask(IThreadTask *pThreadTask)
	{
		m_pLock->Lock();
		m_threadTaskQueue.push(pThreadTask);
		m_pLock->UnLock();
	}

	IThreadTask* CTaskQueue::GetThreadTask()
	{
		IThreadTask *pThreadTask = NULL;
		if (!m_threadTaskQueue.empty())
		{
			m_pLock->Lock();
			pThreadTask = m_threadTaskQueue.front();
			m_threadTaskQueue.pop();
			m_pLock->UnLock();
		}
		return pThreadTask;
	}

	void CTaskQueue::CleanAllTask()
	{
		// ���е���һ������������������ӽ�����Ϊ�վͲ�������
		if (!m_threadTaskQueue.empty())
		{
			m_pLock->Lock();
			IThreadTask *pThreadTask = m_threadTaskQueue.front();
			delete pThreadTask;
			pThreadTask = NULL;
			m_threadTaskQueue.pop();
			m_pLock->UnLock();
		}
	}

	BOOL CTaskQueue::IsTaskAllComplete()
	{
		m_pLock->Lock();
		BOOL bAllComplete =  m_threadTaskQueue.empty();
		m_pLock->UnLock();
		return bAllComplete;
	}

}
