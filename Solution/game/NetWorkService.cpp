#include "game_pch.h"
#include "NetWorkService.h"

EE_IMPLEMENT_CONCRETE_CLASS_INFO(NetWorkService);

NetWorkService::NetWorkService(void)
{
}

NetWorkService::~NetWorkService(void)
{
}

const char * NetWorkService::GetDisplayName() const
{
	return "NetWorkService";
}

	// ����OnInit��������ķ��� 
efd::SyncResult NetWorkService::OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar)
{
	return efd::SyncResult_Success;
}

	// 
efd::AsyncResult NetWorkService::OnInit()
{
	// ע�����������Ϣ�Ĵ���
	return efd::AsyncResult_Complete;
}

	// 
efd::AsyncResult NetWorkService::OnShutdown()
{
	return efd::AsyncResult_Complete;
}

efd::AsyncResult NetWorkService::OnTick()
{
	// ����ÿ��������Ϣ
	return efd::AsyncResult_Pending;
}
