// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 13:15:22
// ������  :    �ٽ�����
// ===============================================================================
#pragma once
#include "ILock.h"
namespace thead_pool
{
	class CCriticalLock:public ILock
	{
	public:
		CCriticalLock(void);
		~CCriticalLock(void);

		virtual void Lock();
		virtual void UnLock();
	private:
		CRITICAL_SECTION m_critcalSection;
	};
}

