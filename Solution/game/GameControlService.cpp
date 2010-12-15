#include "game_pch.h"
#include "GameControlService.h"

#include <efd/MessageService.h>
#include <ecrInput/InputService.h>

#include "GameWorldService.h"

EE_IMPLEMENT_CONCRETE_CLASS_INFO(GameControlService);

EE_HANDLER(
		   GameControlService,
		   HandleInputActionMessage,
		   ecrInput::InputActionMessage);

GameControlService::GameControlService(void)
{


}

const char* GameControlService::GetDisplayName() const
{
	return "GameControlService";
}


efd::SyncResult GameControlService::OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar)
{// ���Ʒ�������Ҫ����ľ����������Ϣ��Ӱ�� ����������Ҫ�ķ�����

	pDependencyRegistrar->AddDependency<efd::MessageService>();
	pDependencyRegistrar->AddDependency<ecrInput::InputService>();

	return efd::SyncResult_Success;
}


efd::AsyncResult GameControlService::OnInit()
{
	efd::MessageService* pMessageService =
		m_pServiceManager->GetSystemServiceAs<efd::MessageService>();	
	EE_ASSERT(pMessageService);

	ecrInput::InputService* pInputService = 
		m_pServiceManager->GetSystemServiceAs<ecrInput::InputService>();	
	EE_ASSERT(pInputService);

	// ��������Ӱ���ļ�
	EE_VERIFY(pInputService->LoadAllActionMaps("urn:demoActionMap"));

	// ����ע����Ҫ�������¼�
	m_inputCategory = pMessageService->GetGloballyUniqueCategory();
	pMessageService->Subscribe(this, m_inputCategory);

	pInputService->ListenForInputActionEvent("Test", m_inputCategory);
	pInputService->ListenForInputActionEvent("TestComBo", m_inputCategory);
	pInputService->ListenForInputActionEvent("MoveForward", m_inputCategory);

	return efd::AsyncResult_Complete;
}


efd::AsyncResult GameControlService::OnShutdown()
{
	// ��ע��
	efd::MessageService* pMessageService =
		m_pServiceManager->GetSystemServiceAs<efd::MessageService>();	
	if (!pMessageService)
	{
		EE_ASSERT(pMessageService);
		return efd::AsyncResult_Failure;
	}

	pMessageService->Unsubscribe(this, m_inputCategory);
	return efd::AsyncResult_Complete;
}

void GameControlService::HandleInputActionMessage(
	const ecrInput::InputActionMessage* pMessage, 
	efd::Category category)
{
	// ���������¼�	
	if ("Test" == pMessage->GetEventName())
	{
		EE_LOG(efd::kApp, 1, (
			"GameControlService::HandleInputActionMessage: Test"));

		GameWorldService* pWorldService = m_pServiceManager->GetSystemServiceAs<GameWorldService>();
		EE_ASSERT(pWorldService);
		if (pWorldService)
		{
			egf::EntityID entityId= pWorldService->SpawnEntity("Player");
			if (egf::kENTITY_INVALID == entityId)
			{
				int a  =0;
			}
		}
	}	
	else if ("TestComBo" == pMessage->GetEventName())
	{
		EE_LOG(efd::kApp, 1, (
			"GameControlService::HandleInputActionMessage: TestComBo"));
	}
}


