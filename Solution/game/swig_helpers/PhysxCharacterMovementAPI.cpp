#include "game_pch.h"
#include "PhysxCharacterMovementAPI.h"
#include "../PhysxCharacterMovementService.h"
#include <egf/ScriptContext.h>
#include <egf/Scheduler.h>

//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
efd::Bool PhysxCharacterMovementAPI::ChangeHorizontalVelocityTo(egf::EntityID entityID,efd::Float32 fDelayTime,efd::Point2 TargetVelocity)
{
	PhysxCharacterMovementService* pPhysxCharacterMovementService =
		egf::g_bapiContext.GetSystemServiceAs<PhysxCharacterMovementService>();
	egf::Scheduler* pScheduler = egf::g_bapiContext.GetSystemServiceAs<egf::Scheduler>();
	EE_ASSERT(pScheduler);

	egf::Entity* pEntity = pScheduler->FindEntity(entityID);

	if (pEntity == NULL)
		return false;

	pPhysxCharacterMovementService->ChangeHorizontalVelocityTo(entityID,fDelayTime,TargetVelocity);


	return true;




}
//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
efd::Bool PhysxCharacterMovementAPI::ChangeAngleTo(egf::EntityID entityID,efd::Float32 fDelayTime,efd::Float32 fAngular)
{
	PhysxCharacterMovementService* pPhysxCharacterMovementService =
		egf::g_bapiContext.GetSystemServiceAs<PhysxCharacterMovementService>();
	egf::Scheduler* pScheduler = egf::g_bapiContext.GetSystemServiceAs<egf::Scheduler>();
	EE_ASSERT(pScheduler);

	egf::Entity* pEntity = pScheduler->FindEntity(entityID);

	if (pEntity == NULL)
		return false;

	pPhysxCharacterMovementService->ChangeAngleTo(entityID,fDelayTime,fAngular);


	return true;




}

