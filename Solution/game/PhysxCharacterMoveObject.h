/********************************************************************
	����ʱ��:	6:12:2010   11:05
	����:		����
	����:	  ������ƵĽ�ɫ����
*********************************************************************/
#pragma once
#include "ID.h"
#include <egf/IBuiltinModelImpl.h>
#include <egf/BuiltinModelHelper.h>
#include <NxController.h> 


// ͨ�� ��� ����� flat model ֵ ȷ�� PropertyID ֵ 
static const egf::PropertyID kPropertyID_MoveVelocity = 3475307868;
static const egf::PropertyID kPropertyID_MoveAccel    = 3075443446;
static const egf::PropertyID kPropertyID_RotationAxis = 3391897551;
static const egf::PropertyID kPropertyID_AngularSpeed = 1367195968;

class PhysxCharacterMoveObject :
	public  egf::IBuiltinModelImpl
{
	EE_DECLARE_CLASS1(PhysxCharacterMoveObject, game::CLASS_ID_PhysCharacterMoveObject, egf::IBuiltinModelImpl);
	EE_DECLARE_CONCRETE_REFCOUNT;


	//������ EE_BUILTINMODELPROPERTY ��ʵ�ֵ�����
	//�����󶨳�Ա����������model �����ԡ�
	EE_DECLARE_BUILTINMODEL_PROPERTIES

		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		PhysxCharacterMoveObject, 
		game::PROPRTY_ID_Dimension, 
		efd::Point3, 
		PhysxCharacterMoveObject, 
		GetDimension,
		SetDimension
		)

		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		PhysxCharacterMoveObject, 
		game::PROPRTY_ID_SceneName, 
		efd::utf8string, 
		PhysxCharacterMoveObject, 
		GetSceneName,
		SetSceneName
		)


		EE_BUILTINMODELPROPERTY_ACCESSOR
		(
		PhysxCharacterMoveObject, 
		game::PROPRTY_ID_CollisionGroup, 
		efd::UInt32,
		PhysxCharacterMoveObject,
		GetCollisionGroup, 
		SetCollisionGroup
		)

		


		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		PhysxCharacterMoveObject, 
		kPropertyID_RotationAxis, 
		efd::Point3,
		PhysxCharacterMoveObject,
		GetRotationAxis, 
		SetRotationAxis)


		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		PhysxCharacterMoveObject, 
		kPropertyID_AngularSpeed, 
		efd::Float32, 
		PhysxCharacterMoveObject, 
		GetAngularSpeed,
		SetAngularSpeed
		)

		EE_END_BUILTINMODEL_PROPERTIES

public:

	PhysxCharacterMoveObject(void);
	virtual ~PhysxCharacterMoveObject(void);

	//������PhysxCharacterMoveObject �Ĵ�����������������������built in Model ʵ��
	static egf::IBuiltinModel* Factory()
	{
		return EE_NEW PhysxCharacterMoveObject();
	}


	

	//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
	void ChangeHorizontalVelocityTo(efd::Float32 fDelayTime,efd::Point2 TargetVelocity);

	//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
	void ChangeAngleTo(efd::Float32 fDelayTime,efd::Float32 TargetfAngular);

	
	// ���������model ��ʵ�壬��ʼ��������ɺ󣬵�һ�����þ������
	void  OnAdded();

	//������ ���model ��ʵ�壬��ɾ����ʱ������������
	void OnRemoved();


	//���º�������Ҫ�Ƕ�λ�õĸ��£�����NxController
	void Update(efd::TimeType timeDelta);


	

	//ȡ�İ�Χ�гߴ�
	const efd::Point3& GetDimension() const
	{
		return m_Dimension;
	}
	//���ð�Χ�гߴ�
	void SetDimension(const efd::Point3& Dim)
	{
		m_Dimension = Dim;

	}

	//ȡ�ó�������
	const efd::utf8string& GetSceneName() const 
	{
		return m_sceneName;

	}
	void SetSceneName(const efd::utf8string& sceneName)
	{
		m_sceneName = sceneName;

	}
	
	//ȡ����ײ��
	efd::UInt32 GetCollisionGroup() const
	{
		return m_CollisionGroupID;

	}
	//������ײ��
	void SetCollisionGroup(const efd::UInt32& CollisionGroupID)
	{
		m_CollisionGroupID = CollisionGroupID;

	}

	


	//���ú�ȡ��ת����
	const efd::Point3& GetRotationAxis() const
	{

		return m_prop3_RotationAxis;
	}
	void SetRotationAxis(const efd::Point3& kRotationAxis)
	{

		m_prop3_RotationAxis = kRotationAxis;
		//��ͨ��Entity::SetPropertyValue �������ԣ�dirty λ�Զ����á�
		//���Ӧ�ó���ֱ�ӵ���SetRotationAxis  �޸ĳ�Ա�����������Dirty�Լ�
	}

	//ȡ�ý��ٶ�
	const efd::Float32& GetAngularSpeed() const
	{

		return m_prop4_AngularSpeed;
	}

	//���ý��ٶ�
	void SetAngularSpeed(const efd::Float32& AngularSpeed)
	{
		m_prop4_AngularSpeed = AngularSpeed;

	}

	
	

protected:
	//ȡ��PhysxController ��λ��
	const NxExtendedVec3& GetPhysxControllerPos();

	//�ƶ���ɫdispVector �� ����Ҫ�ƶ���ƫ����
	NxU32  MoveCharacter(const NxVec3& dispVector, efd::UInt32 collisionGroups);

	//���ý�ɫ��λ�á�������õ��Ǿ��Ե�λ��
	efd::UInt32 SetCharacterPos(const NxVec3& pos);

	//�ߴ�
	efd::Point3 m_Dimension;
	//��������
	efd::utf8string m_sceneName;
	//��ײ����
	efd::UInt32 m_CollisionGroupID;

	//����ǿ���Physx �� NxController
	NxController* m_pPhysxController;

	//ϵͨ���������
	const efd::ServiceManager* m_pServiceManager;
	
	
	//��ֱ���ٶ�
	efd::Float32 m_AccelOfGravity;
	//��ֱ�ٶ�
	efd::Float32 m_VelOfVertical;


	//��ǰˮƽ�ٶ�
	efd::Point2 m_MoveVelocityOfHorizontal;
	//ˮƽ���ٶ�
	efd::Point2 m_AccelOfHorizontal;
	//ˮƽĿ���ٶ�
	efd::Point2 m_TargetVelocityOfHorizontal;
	//��ˮƽĿ���ٶȹ��ɵ�ʣ��ʱ��
	efd::Float32 m_LeftTimeForTransitionofHorizontalVelocity;
	
	
	//��Ŀ��Ƕȹ��ɵ�ʣ��ʱ��
	efd::Float32 m_LeftTimeForTransitionOfAngular;
	//ת����
	efd::Point3 m_prop3_RotationAxis;
	//Ŀ��Ƕ�
	efd::Float32 m_TargetAngular;
	//���ٶ�,�����һ����/�� Ϊ��λ��
	efd::Float32 m_prop4_AngularSpeed;


	

};
typedef efd::SmartPointer<PhysxCharacterMoveObject> PhysCharacterMoveObjectPtr;
