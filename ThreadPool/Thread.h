// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 15:01:37
// ������  :    �̳߳��߳̾�����
// ===============================================================================
#pragma once
#include "IThread.h"
#include "IThreadTask.h"
namespace thead_pool
{
	interface IThreadPool;
	class CThread:public IThread
	{
	public:
		CThread(IThreadPool *pThreadPool, BOOL bAutoDelete = TRUE);
		~CThread(void);
		virtual void CreateThread();
		virtual void NotifyThreadExit();
		virtual void Run();
		virtual void AssignTask(IThreadTask *pTask);

		static unsigned int __stdcall ProcThread(void *pParam);

	private:
		// ��������֪ͨ�¼�
		void CreateTaskNotifyEvent();

		// �߳��Ƿ���������ɺ�������
		BOOL	m_bAutoDelete;
		// �߳��Ƿ�������
		BOOL m_bRunning;
		// �߳̾��
		HANDLE m_hThread;
		// �¼�֪ͨ���������ͬ������ĵ���
		HANDLE m_hEventTaskArrive;
		// �����̳߳�ָ�룬��ִ���굱ǰ����󣬻��յ�ǰ�̵߳������߳�ջ
		IThreadPool* m_pThreadPool;
		// ��ǰִ�е�����ָ��
		IThreadTask* m_pThreadTask; 
	};
}


