// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 16:10:13
// ������  :    �����̳߳��࣬���������ӿڣ�1.�̳߳س�ʼ����2.�̳߳����٣�3.���̳߳�Ͷ������
// ===============================================================================
#pragma once
#include "IdleThreadStack.h"
#include "BusyThreadList.h"
#include "TaskQueue.h"
#include "IThreadPool.h"

namespace thead_pool
{
	interface IThreadPool;
	class CThreadPool:public IThreadPool
	{

	public:
		CThreadPool();
		~CThreadPool();

		virtual BOOL AddTask(IThreadTask *pTask);
		virtual void InitThreadPool(int nThreadCounts);
		virtual void DestoryThreadPool();

	protected:
		virtual BOOL IsThreadPoolDestoryed();
		virtual IThreadTask* GetNextTask();
		virtual void AssignNextTask(BOOL bJustChangeState,IThread *pThread);

	private:

		// �̳߳��Ƿ��ѱ�����
		BOOL m_bThreadPoolDestoryed;
		// �̳߳�״̬��
		ILock* m_pPoolStatusLock;

		// �����߳�ջ
		CIdleThreadStack m_idleThreadStack;
		// �����߳��б�
		CBusyThreadList  m_busyThreadList;
		// �������
		CTaskQueue m_taskQueue;

	};
}