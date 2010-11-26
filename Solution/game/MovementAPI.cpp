#include "game_pch.h"
#include "MovementAPI.h"
#include "MovementService.h"
#include <egf/ScriptContext.h>
#include <egf/Scheduler.h>

//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
efd::Bool MovementAPI::ChangeVelocityTo(egf::EntityID entityID,efd::Float32 fDelayTime,efd::Point3 TargetVelocity)
{
	MovementService* pMovementService =
		egf::g_bapiContext.GetSystemServiceAs<MovementService>();
	egf::Scheduler* pScheduler = egf::g_bapiContext.GetSystemServiceAs<egf::Scheduler>();
	EE_ASSERT(pScheduler);

	egf::Entity* pEntity = pScheduler->FindEntity(entityID);

	if (pEntity == NULL)
		return false;

	pMovementService->ChangeVelocityTo(entityID,fDelayTime,TargetVelocity);


	return true;




}
//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
efd::Bool MovementAPI::ChangeAngleTo(egf::EntityID entityID,efd::Float32 fDelayTime,efd::Float32 fAngular)
{
	MovementService* pMovementService =
		egf::g_bapiContext.GetSystemServiceAs<MovementService>();
	egf::Scheduler* pScheduler = egf::g_bapiContext.GetSystemServiceAs<egf::Scheduler>();
	EE_ASSERT(pScheduler);

	egf::Entity* pEntity = pScheduler->FindEntity(entityID);

	if (pEntity == NULL)
		return false;

	pMovementService->ChangeAngleTo(entityID,fDelayTime,fAngular);


	return true;




}

