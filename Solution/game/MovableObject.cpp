#include "game_pch.h"
#include "MovableObject.h"
#include "MovementService.h"
#include "egf/Entity.h"
#include "efd/EEMath.h"



EE_IMPLEMENT_CONCRETE_CLASS_INFO(MovableObject);

EE_IMPLEMENT_BUILTINMODEL_PROPERTIES(MovableObject);

MovableObject::MovableObject(void)
:m_prop4_AngularSpeed(0.0f),
m_TargetVelocity(0.0f,0.0f,0.0f),
m_TargetAngular(0.0f),
m_LeftTimeForTransitionVelocity(0.0f),
m_LeftTimeForTransitionAngular(0.0f)
{

}

MovableObject::~MovableObject(void)
{

}


// ���������model ��ʵ�壬��ʼ��������ɺ󣬵�һ�����þ������
void  MovableObject::OnAdded()
{
	egf::IBuiltinModelImpl::OnAdded();



	// ȡ��service ������
	m_pServiceManager = GetServiceManager();

	// ע�ᵽ MovementService
	MovementService* pMovementService = m_pServiceManager->GetSystemServiceAs<MovementService>();
	pMovementService->RegisterMovableObject(m_pOwningEntity->GetEntityID(), this);
}

//������ ���model ��ʵ�壬��ɾ����ʱ������������
void MovableObject::OnRemoved()
{
	//ɾ����MovementService ע����ƶ�����
	EE_ASSERT(m_pOwningEntity);
	MovementService* pMovementService = m_pServiceManager->GetSystemServiceAs<MovementService>();
	pMovementService->UnregisterMovableObject(m_pOwningEntity->GetEntityID());
	egf::IBuiltinModelImpl::OnRemoved();

}

//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
void MovableObject::ChangeVelocityTo(efd::Float32 fDelayTime,efd::Point3 TargetVelocity)
{

	//������ڹ涨ʱ��仯��Ŀ���ٶȣ�����Ҫ�ļ��ٶ�
	SetAccel((TargetVelocity - m_prop1_MoveVelocity)/fDelayTime);
	m_LeftTimeForTransitionVelocity = fDelayTime;
	m_TargetVelocity = TargetVelocity;
	EE_LOG(efd::kApp, 1, (
		"MovableObject::ChangeVelocityTo: �ٶȱ仯Ϊ x= %f,y = %f, z = %f\n",
		TargetVelocity.x,TargetVelocity.y,TargetVelocity.z));
	
		





}

//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�,�������ת��������С���Ǹ�������ת
void MovableObject::ChangeAngleTo(efd::Float32 fDelayTime,efd::Float32 TargetfAngular)
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
	m_LeftTimeForTransitionAngular = fDelayTime;

	
}

//�ƶ�����ĸ��º���
void MovableObject::Update(efd::TimeType timeDelta)
{


	efd::Point3 currentPosition = efd::Point3::ZERO;
	m_pOwningEntity->GetPropertyValue(game::PROPRTY_ID_Position,currentPosition);
	efd::Point3 OffsetPosition = efd::Point3::ZERO;
	
	if (m_LeftTimeForTransitionVelocity != 0.0f)
	{

		float fLastLeftTime = m_LeftTimeForTransitionVelocity;
		m_LeftTimeForTransitionVelocity -= timeDelta;

		
		//ִ�й����ٶȲ���
		if(m_LeftTimeForTransitionVelocity > 0.0f)
		{
			OffsetPosition =   m_prop1_MoveVelocity  * timeDelta +0.5f * m_prop2_Accel * timeDelta * timeDelta;
			SetVelocity(m_prop1_MoveVelocity  +  m_prop2_Accel  * timeDelta);


		}
		else
		{
			efd::Float32 AccelTime = fLastLeftTime;
			//�����ڼ��λ��
			OffsetPosition =   m_prop1_MoveVelocity  * AccelTime +0.5f * m_prop2_Accel * AccelTime * AccelTime;
			//�ټ��������ڼ��λ��
			OffsetPosition += m_TargetVelocity * (timeDelta - AccelTime);

			//���ʱ�������ˣ�˵������ʱ���Ѿ������ˣ�ֱ�Ӱ�Ŀ���ٶ�������ȥ
			m_prop1_MoveVelocity = m_TargetVelocity;
			m_LeftTimeForTransitionVelocity = 0.0f;
			//���ٶȸ�λ
			SetAccel(efd::Point3::ZERO);

		}
		
	}
	else
	{
		OffsetPosition = m_prop1_MoveVelocity * timeDelta;



	}

	m_pOwningEntity->SetPropertyValue(game::PROPRTY_ID_Position,currentPosition + OffsetPosition);


	if (m_LeftTimeForTransitionAngular > 0.0f)
	{

		m_LeftTimeForTransitionAngular -= timeDelta;
		//ִ�й��ɽǶȲ���
		

		efd::Point3 currentEulerAngle = efd::Point3::ZERO;
		m_pOwningEntity->GetPropertyValue
				(
				game::PROPRTY_ID_Rotation,
				currentEulerAngle
				);

		if (m_LeftTimeForTransitionAngular <= 0.0f)
		{
			m_LeftTimeForTransitionAngular = 0.0f;
			SetAngularSpeed(0.0f);
			currentEulerAngle.z = m_TargetAngular;


		}
		else
		{
			currentEulerAngle.z += m_prop4_AngularSpeed * timeDelta;


		}
		m_pOwningEntity->SetPropertyValue(game::PROPRTY_ID_Rotation,currentEulerAngle);
	}

	// 	efd::Point3 currentEulerAngle = efd::Point3::ZERO;
	// 	 		m_pOwningEntity->GetPropertyValue(
	// 	 			game::PROPRTY_ID_Rotation,
	// 	 			currentEulerAngle);
	// 
	// 	//��ȡ�õ�ǰ�ĽǶ�
	// 	currentEulerAngle.z += m_prop4_AngularSpeed * timeDelta * efd::EE_RADIANS_TO_DEGREES;
	// 	m_pOwningEntity->SetPropertyValue(game::PROPRTY_ID_Rotation,currentEulerAngle);
	// 
	// 	if (m_LeftTimeForTransitionAngular)
	// 	{
	// 		currentEulerAngle.z += m_prop4_AngularSpeed * timeDelta;
	// 
	// 	}

	// 
	// 
	// 	
	// 	//����,�������µ��ٶ�
	// 	SetVelocity(m_prop1_MoveVelocity + m_prop2_Accel * timeDelta);
	// 
	// 
	// 	efd::Point3 currentPosition = efd::Point3::ZERO;
	// 	m_pOwningEntity->GetPropertyValue(
	// 		game::PROPRTY_ID_Position,
	// 		currentPosition);
	// 
	// 	currentPosition += OffsetPosition;
	// 	m_pOwningEntity->SetPropertyValue(game::PROPRTY_ID_Position,currentPosition);
	// 
	// 
	// 	if(m_prop4_AngularSpeed != 0.0f && m_prop3_RotationAxis.Length() != 0)
	// 	{
	// 		//ȡ�ĵ�ǰ�ķ���
	// 		efd::Point3 currentEulerAngle = efd::Point3::ZERO;
	// 		m_pOwningEntity->GetPropertyValue(
	// 			game::PROPRTY_ID_Rotation,
	// 			currentEulerAngle);
	// 
	// 
	// 		//efd::Matrix3 matRot;
	// 		//matRot.FromEulerAnglesXYZ(currentEulerAngle.x,currentEulerAngle.y,currentEulerAngle.z);
	// 
	// 		//EE_ASSERT(m_prop3_RotationAxis.Length() == 1);
	// 
	// 
	// 		//efd::Matrix3 matRotChange; 
	// 		//���������ת�ĽǶ�
	// 		//matRotChange.MakeRotation(m_prop4_AngularSpeed * timeDelta,m_prop3_RotationAxis);
	// 
	// 		//matRot = matRotChange * matRot  ;
	// 
	// 
	// 		//efd::Point3 EulerAngle;
	// 		//matRot.ToEulerAnglesXYZ(EulerAngle.x,EulerAngle.y,EulerAngle.z);
	// 
	// 
	// 		// �������ڰ�����������ת�����⣬������ʱ�����ã���������ת��������ʱ����
	// 		
	// 		currentEulerAngle.z += m_prop4_AngularSpeed * timeDelta * efd::EE_RADIANS_TO_DEGREES;
	// 		m_pOwningEntity->SetPropertyValue(game::PROPRTY_ID_Rotation,currentEulerAngle);


}


