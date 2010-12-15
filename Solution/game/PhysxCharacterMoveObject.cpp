#include "game_pch.h"
#include "PhysxCharacterMoveObject.h"
#include <NxBoxController.h>
#include "PhysxCharacterMovementService.h"
#include "egf/Entity.h"
#include "MathHelpers.h"
#include "CharacterControllerHitReport.h"

EE_IMPLEMENT_CONCRETE_CLASS_INFO(PhysxCharacterMoveObject);

EE_IMPLEMENT_BUILTINMODEL_PROPERTIES(PhysxCharacterMoveObject);
PhysxCharacterMoveObject::PhysxCharacterMoveObject()
:m_prop4_AngularSpeed(0.0f),
m_TargetVelocityOfHorizontal(0.0f,0.0f),
m_TargetAngular(0.0f),
m_LeftTimeForTransitionofHorizontalVelocity(0.0f),
m_LeftTimeForTransitionOfAngular(0.0f),
m_AccelOfGravity(-9.8f),
m_VelOfVertical(0.0f)

{
	
}

PhysxCharacterMoveObject::~PhysxCharacterMoveObject(void)
{
}

//�ƶ���ɫdispVector �� ����Ҫ�ƶ���ƫ����,���ص��ƶ���ʱ����ײ������
NxU32 PhysxCharacterMoveObject::MoveCharacter(const NxVec3& dispVector, efd::UInt32 collisionGroups)
{
	NxU32 collisionFlags = 0;


	EE_ASSERT(m_pPhysxController);

	//m_pPhysxController->setInteraction(NXIF_INTERACTION_USE_FILTER);
	m_pPhysxController->move(dispVector, collisionGroups, 0.001f, collisionFlags);

	return collisionFlags;

}
//���ý�ɫ��λ�á�������õ��Ǿ��Ե�λ��
efd::UInt32 PhysxCharacterMoveObject::SetCharacterPos(const NxVec3& pos)
{
	return m_pPhysxController->setPosition(NxExtendedVec3(pos.x, pos.y, pos.z));
}
// ���������model ��ʵ�壬��ʼ��������ɺ󣬵�һ�����þ������
void  PhysxCharacterMoveObject::OnAdded()
{
	egf::IBuiltinModelImpl::OnAdded();

	// ȡ��service ������
	m_pServiceManager = GetServiceManager();

	
	//�����趨������Controller �Ĳ���
	NxBoxControllerDesc BoxControllerDesc;
	BoxControllerDesc.extents = MathHelpers::ToNxVec3(m_Dimension);
	BoxControllerDesc.stepOffset = 10;
	BoxControllerDesc.upDirection = NX_Z;
	BoxControllerDesc.skinWidth = 0.1f;
	BoxControllerDesc.slopeLimit = cosf(NxMath::degToRad(45.0f));
	efd::Point3 currentPosition = efd::Point3::ZERO;
	m_pOwningEntity->GetPropertyValue(game::PROPRTY_ID_Position,currentPosition);
	BoxControllerDesc.position.x = currentPosition.x;
	BoxControllerDesc.position.y = currentPosition.y;
	BoxControllerDesc.position.z = currentPosition.z;
	BoxControllerDesc.position.z += BoxControllerDesc.stepOffset;
	
	CharacterControllerHitReport * HitReport =  new CharacterControllerHitReport();

	BoxControllerDesc.callback = HitReport;
	

	// ע�ᵽ MovementService
	PhysxCharacterMovementService * PhysxMovementService = m_pServiceManager->GetSystemServiceAs<PhysxCharacterMovementService>();


	PhysxMovementService->RegisterMovableObject(m_pOwningEntity->GetEntityID(), this,BoxControllerDesc,&m_pPhysxController);
	HitReport->SetOwner(m_pPhysxController);

	
	
}


//������ ���model ��ʵ�壬��ɾ����ʱ������������
void PhysxCharacterMoveObject::OnRemoved()
{
	//ɾ����MovementService ע����ƶ�����
	EE_ASSERT(m_pOwningEntity);
	PhysxCharacterMovementService* pMovementService = m_pServiceManager->GetSystemServiceAs<PhysxCharacterMovementService>();
	pMovementService->UnregisterMovableObject(m_pOwningEntity->GetEntityID());
	egf::IBuiltinModelImpl::OnRemoved();

}

//����ĳ��ʵ���ˮƽ�ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
void PhysxCharacterMoveObject::ChangeHorizontalVelocityTo(efd::Float32 fDelayTime,efd::Point2 TargetVelocity)
{

	//������ڹ涨ʱ��仯��Ŀ���ٶȣ�����Ҫ�ļ��ٶ�
	m_AccelOfHorizontal = ((TargetVelocity - m_MoveVelocityOfHorizontal)/fDelayTime);
	m_LeftTimeForTransitionofHorizontalVelocity = fDelayTime;
	m_TargetVelocityOfHorizontal = TargetVelocity;
	EE_LOG(efd::kApp, 1, (
		"MovableObject::ChangeVelocityTo: �ٶȱ仯Ϊ x= %f,y = %f",
		TargetVelocity.x,TargetVelocity.y));


}

//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
void PhysxCharacterMoveObject::ChangeAngleTo(efd::Float32 fDelayTime,efd::Float32 TargetfAngular)
{
	//������ڹ涨ʱ���ڽǶȱ仯��Ŀ��Ƕ�����Ҫ�Ľ��ٶ�

	//ȡ�ĵ�ǰ�ķ���
	efd::Point3 currentEulerAngle = efd::Point3::ZERO;
	m_pOwningEntity->GetPropertyValue(
		game::PROPRTY_ID_Rotation,
		currentEulerAngle);

	efd::Float32 CurAngular = currentEulerAngle.z;
	efd::Float32 ChangeAngular = TargetfAngular - CurAngular;

	if (ChangeAngular > 180.0f)
	{
		//˵����������180 ��Ҫ������ת������ͻ�С��180
		ChangeAngular -= 360.0f;


	}
	//���С��-180 ��Ҫ������������С��180
	if (ChangeAngular < -180.0f )
	{
		ChangeAngular += 360;

	}

	m_TargetAngular = TargetfAngular;
	SetAngularSpeed (ChangeAngular / fDelayTime);
	//��λת���ǵ�ʱ��
	m_LeftTimeForTransitionOfAngular = fDelayTime;
}

//ȡ��PhysxController ��λ��
const NxExtendedVec3& PhysxCharacterMoveObject::GetPhysxControllerPos()
{
	return m_pPhysxController->getPosition();



}

//���º�������Ҫ�Ƕ�λ�õĸ��£�����NxController
void PhysxCharacterMoveObject::Update(efd::TimeType timeDelta)
{
	float timeDeltaSquare =  timeDelta * timeDelta;
	efd::Point3 currentPosition = efd::Point3::ZERO;
	m_pOwningEntity->GetPropertyValue(game::PROPRTY_ID_Position,currentPosition);
	efd::Point2 OffsetPositionOfHorizontal  = efd::Point2::ZERO;

	if (m_LeftTimeForTransitionofHorizontalVelocity != 0.0f)
	{

		float fLastLeftTime = m_LeftTimeForTransitionofHorizontalVelocity;
		m_LeftTimeForTransitionofHorizontalVelocity -= timeDelta;


		//ִ�й����ٶȲ���
		if(m_LeftTimeForTransitionofHorizontalVelocity > 0.0f)
		{
			OffsetPositionOfHorizontal =   m_MoveVelocityOfHorizontal  * timeDelta +0.5f * m_AccelOfHorizontal * timeDeltaSquare;
			m_MoveVelocityOfHorizontal = m_MoveVelocityOfHorizontal  +  m_AccelOfHorizontal  * timeDelta;


		}
		else
		{
			efd::Float32 AccelTime = fLastLeftTime;
			//�����ڼ��λ��
			OffsetPositionOfHorizontal =   m_MoveVelocityOfHorizontal  * AccelTime +0.5f * m_AccelOfHorizontal * AccelTime * AccelTime;
			//�ټ��������ڼ��λ��
			OffsetPositionOfHorizontal +=  m_TargetVelocityOfHorizontal * (timeDelta - AccelTime);

			//���ʱ�������ˣ�˵������ʱ���Ѿ������ˣ�ֱ�Ӱ�Ŀ���ٶ�������ȥ
			m_MoveVelocityOfHorizontal = m_TargetVelocityOfHorizontal;
			m_LeftTimeForTransitionofHorizontalVelocity = 0.0f;
			//���ٶȸ�λ
			m_AccelOfHorizontal = efd::Point2::ZERO;

		}

	}
	else
	{
		OffsetPositionOfHorizontal = m_MoveVelocityOfHorizontal * timeDelta;



	}

	//������㴹ֱ�����λ��
	
	float OffsetPositionOnVertical = m_VelOfVertical * timeDelta + 0.5f * m_AccelOfGravity * timeDeltaSquare;
	m_VelOfVertical += m_AccelOfGravity * timeDelta;

	efd::Point3 OffsetPosition(OffsetPositionOfHorizontal.x,OffsetPositionOfHorizontal.y,OffsetPositionOnVertical);
	
	if(OffsetPosition.Length() > 0.0f)
	{
		//���ݵ�ǰ��Ҫ�ƶ���ƫ����,��m_pPhysxController ����ʵ�峡�����ƶ�
		NxU32 ContactInfo = MoveCharacter( MathHelpers::ToNxVec3(OffsetPosition),0xffff);
		const NxExtendedVec3& ExtendedVec3 = GetPhysxControllerPos();
		if (ContactInfo & NXCC_COLLISION_DOWN)
		{
			//����˵�����������ˣ������ٶ�Ҫ��Ϊ��
			m_VelOfVertical = 0.0f;



		}
		
		
		m_pOwningEntity->SetPropertyValue(game::PROPRTY_ID_Position,MathHelpers::ToPoint3(ExtendedVec3));
	}





	if (m_LeftTimeForTransitionOfAngular > 0.0f)
	{

		m_LeftTimeForTransitionOfAngular -= timeDelta;
		//ִ�й��ɽǶȲ���


		efd::Point3 currentEulerAngle = efd::Point3::ZERO;
		m_pOwningEntity->GetPropertyValue
			(
			game::PROPRTY_ID_Rotation,
			currentEulerAngle
			);

		if (m_LeftTimeForTransitionOfAngular <= 0.0f)
		{
			m_LeftTimeForTransitionOfAngular = 0.0f;
			SetAngularSpeed(0.0f);
			currentEulerAngle.z = m_TargetAngular;


		}
		else
		{
			currentEulerAngle.z += m_prop4_AngularSpeed * timeDelta;


		}
		m_pOwningEntity->SetPropertyValue(game::PROPRTY_ID_Rotation,currentEulerAngle);
	}

}





