// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 12:36:06
// ������  :    �̳߳ؽӿ�
// ===============================================================================
#pragma once
namespace thead_pool
{
	interface IThreadTask;
	interface IThread;
		
	interface IThreadPool
	{
		// ��ʼ���̳߳أ���ָ���̳߳����̸߳���
		virtual void InitThreadPool(int nThreadCounts) = 0;

		// �����̳߳أ�ע�������֪ͨ�߳��˳������߳��˳��������̶߳�����ȥ�ͷ���δ��ɵ��������
		virtual void DestoryThreadPool() = 0;

		// �̳߳��Ƿ��Ѿ����٣���ʱ���������̳߳�Ͷ������
		virtual BOOL IsThreadPoolDestoryed() = 0;

		// ���̳߳���Ͷ���������֮ǰ��ѯ�̳߳��Ƿ��ѱ����٣����ѱ����ٷ���FALSE,��������Ҫ��������
		virtual BOOL AddTask(IThreadTask *pTask) = 0;

		// ȡ�������������һ������
		virtual IThreadTask* GetNextTask() = 0;

		// ����������л�ȡ��һ����������̣߳�������Ϊ�ջ���ֻ��������̣߳���ô���̷߳�����ж���
		virtual void AssignNextTask(BOOL bJustChangeState ,IThread *pThread) = 0;
	};
}