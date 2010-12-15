// ======================================================================================
// File         : GameInitingState.h
// Author       : Zhang yuzhong 
// Last Change  : 12/3/2010
// Description  : ��Ϸ��ʼ���׶� ����һ����̨�̼߳�����Ҫ�������ļ�
//				  ��ʼ������, ������UI���߼����� �ȵ�
// ======================================================================================

#include "game_pch.h"
#include "GameInitingState.h"
#include "GameStateService.h"
#include "ScreenTextureClick.h"

#include <NiDefaultClickRenderStep.h>

EE_IMPLEMENT_CONCRETE_CLASS_INFO(GameInitingState);

GameInitingState::GameInitingState(
								   GameStateService* pMasterService, GameStateID nextID, 
								   efd::utf8string displayTexture)
	: GameState(pMasterService, GameState::InitGameStateID, nextID)
	, m_bInitFinish(true)
	, m_pstrDisplayTex(displayTexture)
{
}

GameInitingState::~GameInitingState(void)
{
}

void GameInitingState::OnInit()
{
	
}
void GameInitingState::OnTick(efd::TimeType time)
{
	if (m_bInitFinish)
	{
		m_pMasterService->ChangeState(m_nextStateID);
	}
}
void GameInitingState::OnShutdown()
{

}

efd::Bool GameInitingState::Enter()
{
	if (!m_bInitFinish)
	{
		return false;
	}
	m_bInitFinish = false;	
	StartInitDataThread();

	if (m_pstrDisplayTex.size())
	{
		NiDefaultClickRenderStep* pRenderStep = m_pMasterService->DisableMainRender();
		EE_ASSERT(pRenderStep);
		m_pRenderClick = EE_NEW ScreenTextureClick();
		EE_ASSERT(m_pRenderClick);

		m_pRenderClick->AddTexture(EE_EXTERNAL_NEW ScreenTextureClick::Element(m_pstrDisplayTex), "sign");
		pRenderStep->AppendRenderClick(m_pRenderClick);
		m_pRenderClick->SetActive(true);
	}
	

	return true;
}
efd::Bool GameInitingState::Leave()
{
	if (!m_bInitFinish)
	{
		return false;
	}
	CleanupInitDataThread();

	if (m_pstrDisplayTex.size())
	{
		NiDefaultClickRenderStep* pRenderStep = m_pMasterService->EnableMainRender();
		EE_ASSERT(pRenderStep);

		pRenderStep->RemoveRenderClick(m_pRenderClick);
	}
	return true;
}

void GameInitingState::StartInitDataThread()
{
	m_pkThreadProc = NiNew InitGameThreadProc(this);
	m_pkInitDataThread = efd::Thread::Create(m_pkThreadProc);

	NIASSERT(m_pkInitDataThread);
	NIMEMASSERT(NiVerifyAddress(m_pkInitDataThread));
	if (m_pkInitDataThread)
	{
		m_pkInitDataThread->SetPriority(efd::Thread::TIME_CRITICAL);
		m_pkInitDataThread->Resume();
	}
}

// �����̨���ݵ��߳̽������������
void GameInitingState::CleanupInitDataThread()
{
	if (m_pkThreadProc)
	{
		EE_DELETE m_pkThreadProc;
		m_pkThreadProc = NULL;
	}
	
	if (m_pkInitDataThread)
	{
		EE_DELETE m_pkInitDataThread;
		m_pkInitDataThread = NULL;
	}
	
}

InitGameThreadProc::InitGameThreadProc(GameInitingStatePtr pParams )
{
	m_pGameInit = pParams;
}

unsigned int InitGameThreadProc::ThreadProcedure(efd::Thread* pThread)
{
	// ������Ϸ���ݳ�ʼ��


	m_pGameInit->m_bInitFinish = true;
	return 0;
}
