#include "game_pch.h"
#include "GamePlayingState.h"
#include "GameStateService.h"

EE_IMPLEMENT_CONCRETE_CLASS_INFO(GamePlayingState);

GamePlayingState::GamePlayingState(GameStateService* pMasterService)
	:GameState(pMasterService, PlayingStateID)
{
}

GamePlayingState::~GamePlayingState(void)
{
}

void GamePlayingState::OnInit()
{
	// �߼�������ݳ�ʼ��
}
void GamePlayingState::OnTick(efd::TimeType time)
{
	// ��Ϸ���߼�
}
void GamePlayingState::OnShutdown()
{
	// ����߼��������
}

efd::Bool GamePlayingState::Enter()
{
	return true;
}
efd::Bool GamePlayingState::Leave()
{
	return true;
}
