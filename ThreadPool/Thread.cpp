// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 15:01:37
// ������  :    �̳߳��߳̾�����
// ===============================================================================
#include "Thread.h"
#include <process.h>
#include "IThreadPool.h"


namespace thead_pool
{
	CThread::CThread(IThreadPool *pThreadPool,BOOL bAutoDelete)
		:m_hThread(NULL)
		,m_hEventTaskArrive(NULL)
		,m_pThreadPool(pThreadPool)
		,m_bRunning(FALSE)
		,m_pThreadTask(NULL)
		,m_bAutoDelete(bAutoDelete)
	{
		CreateTaskNotifyEvent();
		CreateThread();
	}


	CThread::~CThread(void)
	{
		CloseHandle(m_hThread);
		CloseHandle(m_hEventTaskArrive);
	}

	void CThread::CreateTaskNotifyEvent()
	{
		m_hEventTaskArrive = CreateEvent(NULL,TRUE,FALSE,L"");
	}

	void CThread::CreateThread()
	{
		m_bRunning = TRUE;
		m_hThread = (HANDLE)_beginthreadex(NULL,0,ProcThread,this,0,NULL);
	}

	void CThread::NotifyThreadExit()
	{
		m_bRunning = FALSE;
		SetEvent(m_hEventTaskArrive);
		WaitForSingleObject(m_hThread,INFINITE);
	}

	void CThread::Run()
	{
		while(TRUE)
		{
			//����û������������ô���̹߳��𣬲�ռ��cpu����Դ
			DWORD dwWaitResult =  WaitForSingleObject(m_hEventTaskArrive, INFINITE);
			// ����ȵ��ˣ��Ȱ���ͷ���������꣬�ٿ��Ƿ��ѱ�֪ͨ�˳�
			if (WAIT_OBJECT_0 == dwWaitResult)
			{
				// ��Ҫ�����¼����Ա��´�ʹ��
				ResetEvent(m_hEventTaskArrive);

				// �����������ôȥ��������
				if (NULL != m_pThreadTask)
				{
					m_pThreadTask->ProcessTask();
					delete m_pThreadTask;
					m_pThreadTask = NULL;
				}

				// �����ʱ�ѱ�֪ͨ�˳�����ô������Ҫ�����ˣ����ձ��̵߳������߳�ջ
				m_pThreadPool->AssignNextTask(!m_bRunning,this);	

			}
			// ��ʧ���ˣ�������ĳЩ�����
			else if (WAIT_FAILED == dwWaitResult)
			{
				// �̳߳�֪ͨ�߳��˳�
				if (!m_bRunning)
				{
					// �����ʱ�ѱ�֪ͨ�˳������ձ��̵߳������߳�ջ
					m_pThreadPool->AssignNextTask(TRUE,this);	
					break;
				}
			}

			// �߳��ѱ����յ������߳�ջ�����߳̿��԰����˳���
			if (!m_bRunning)
				break;

		}

		if(m_bAutoDelete)
		{
			delete this;
		}
	}

	// �ú������ⲿ�̶߳���ά�����⣬��������
	void CThread::AssignTask(IThreadTask *pTask)
	{
		m_pThreadTask = pTask;
		SetEvent(m_hEventTaskArrive);
	}

	unsigned int __stdcall CThread::ProcThread(void *pParam)
	{
		CThread *pThread = (CThread*)pParam;
		pThread->Run();

		return 0;
	}

}
