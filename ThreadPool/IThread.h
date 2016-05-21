// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 12:38:23
// ������  :    
// ===============================================================================
#pragma once
#include <objbase.h>
namespace thead_pool
{
	interface IThreadTask;
	interface IThread
	{
		// �����߳�
		virtual void CreateThread() = 0;

		// ֪ͨ�߳��˳�
		virtual void NotifyThreadExit() = 0;

		// �߳�ִ��ʵ��
		virtual void Run() = 0;

		// ���̰߳�������:����ÿ���̳߳ط������񣬱�Ȼ�Ǵӿ����߳��б���ժȡ�̣߳�
		// �����б��Ᵽ�����ʴ˺������ᱻ���룬�������
		virtual void AssignTask(IThreadTask *pTask) = 0;
	};
}