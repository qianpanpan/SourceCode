// ===============================================================================
// ����:    
// �汾:    v1.0.0.0
// ����           :    Qiangp
// ����ʱ��   :    2016-5-20 13:17:51
// ������  :    �ٽ�����
// ===============================================================================
#include "CriticalLock.h"

namespace thead_pool
{
	CCriticalLock::CCriticalLock(void)
	{
		InitializeCriticalSection(&m_critcalSection);
	}


	CCriticalLock::~CCriticalLock(void)
	{
		DeleteCriticalSection(&m_critcalSection);
	}

	void CCriticalLock::Lock()
	{
		EnterCriticalSection(&m_critcalSection);
	}

	void CCriticalLock::UnLock()
	{
		LeaveCriticalSection(&m_critcalSection);
	}

}
