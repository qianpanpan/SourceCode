// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 14:52:27
// ������  :������У������Ƚ��ȳ��Ķ�����Ϊ��������    
// ===============================================================================
#pragma once
#include <queue>
#include <objbase.h>
using namespace std;

namespace thead_pool
{
	interface ILock;
	interface IThreadTask;

	class CTaskQueue
	{
	public:
		CTaskQueue(void);
		~CTaskQueue(void);
		void AddThreadTask(IThreadTask *pThreadTask);
		IThreadTask* GetThreadTask();
		BOOL IsTaskAllComplete();
		void CleanAllTask();
	private:
		ILock *m_pLock;
		queue<IThreadTask*>m_threadTaskQueue;
	};
}

