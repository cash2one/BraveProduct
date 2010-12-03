// ======================================================================================
// File         : GameInitingState.h
// Author       : Zhang yuzhong 
// Last Change  : 12/3/2010
// Description  : ��Ϸ��ʼ���׶� ����һ����̨�̼߳�����Ҫ�������ļ�
//				  
// ======================================================================================
#pragma once
#include "GameState.h"
#include <NiThreadProcedure.h>

class InitGameThreadProc;
class ScreenTextureClick;

class GameInitingState : public GameState
{
	EE_DECLARE_CLASS1(GameInitingState, game::CLASS_ID_GameInitingState, GameState);
	EE_DECLARE_CONCRETE_REFCOUNT;

	friend class InitGameThreadProc;
public:
	GameInitingState(GameStateService* pMasterService
		, GameStateID nextID
		, efd::utf8string displayTexture);
	virtual ~GameInitingState(void);

public:
	virtual void OnInit();
	virtual void OnTick(efd::TimeType time);
	virtual void OnShutdown();

	virtual efd::Bool Enter();
	virtual efd::Bool Leave();

private:
	efd::Thread*								m_pkInitDataThread;	//��ʼ����Ϸ���ݵ��̶߳���
	InitGameThreadProc*						m_pkThreadProc;			//������̴߳�����
	efd::Bool								m_bInitFinish;// ��ʼ�����
	efd::utf8string							m_pstrDisplayTex;// ��ʾ��ͼƬ
	ScreenTextureClick*						m_pRenderClick;

public:
	void StartInitDataThread();
	void CleanupInitDataThread();
};

typedef efd::SmartPointer<GameInitingState> GameInitingStatePtr;


class InitGameThreadProc : public NiThreadProcedure
{
public:
	InitGameThreadProc(GameInitingStatePtr pParams );
	virtual unsigned int ThreadProcedure(efd::Thread* pThread);
protected:
	GameInitingStatePtr	m_pGameInit;		// ���ݸ��̵߳Ĳ���
};