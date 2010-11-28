/********************************************************************
����ʱ��:	12:11:2010   16:29
����:		����
����:		���ƶ�����
*********************************************************************/
#pragma once


#include "ID.h"
#include <egf/IBuiltinModelImpl.h>
#include <egf/BuiltinModelHelper.h>

// ͨ�� ��� ����� flat model ֵ ȷ�� PropertyID ֵ 
static const egf::PropertyID kPropertyID_prop1_MoveVelocity = 3475307868;
static const egf::PropertyID kPropertyID_prop2_MoveAccel    = 3075443446;
static const egf::PropertyID kPropertyID_prop3_RotationAxis = 3391897551;
static const egf::PropertyID kPropertyID_prop4_AngularSpeed = 1367195968;


class MovableObject :
	public egf::IBuiltinModelImpl
{
	EE_DECLARE_CLASS1(MovableObject, game::CLASS_ID_MovableObject, egf::IBuiltinModelImpl);
	EE_DECLARE_CONCRETE_REFCOUNT;


	     //������ EE_BUILTINMODELPROPERTY ��ʵ�ֵ�����
	     //�����󶨳�Ա����������model �����ԡ�
	    EE_DECLARE_BUILTINMODEL_PROPERTIES

		//��������ֱ�Ӱ����������� m_prop1_MoveDirection �ĵ�ַ:
		//��Get/Set �洢������

		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		MovableObject, 
		kPropertyID_prop1_MoveVelocity, 
		efd::Point3, 
		MovableObject, 
		GetVelocity,
		SetVelocity
		)

		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		MovableObject, 
		kPropertyID_prop2_MoveAccel, 
		efd::Point3, 
		MovableObject, 
		GetAccel,
		SetAccel
		)


		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		MovableObject, 
		kPropertyID_prop3_RotationAxis, 
		efd::Point3,
		MovableObject,
		GetRotationAxis, 
		SetRotationAxis)


		EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
		MovableObject, 
		kPropertyID_prop4_AngularSpeed, 
		efd::Float32, 
		MovableObject, 
		GetAngularSpeed,
		SetAngularSpeed
		)
		EE_END_BUILTINMODEL_PROPERTIES


		
public:

	//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
	void ChangeVelocityTo(efd::Float32 fDelayTime,efd::Point3 TargetVelocity);

	//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
	void ChangeAngleTo(efd::Float32 fDelayTime,efd::Float32 fAngular);

	//�ƶ�����ĸ��º���
	void Update(efd::TimeType timeDelta);

	// ���������model ��ʵ�壬��ʼ��������ɺ󣬵�һ�����þ������
	void  OnAdded();

	//������ ���model ��ʵ�壬��ɾ����ʱ������������
	void OnRemoved();

	MovableObject(void);
	~MovableObject(void);

	//������MovableObject �Ĵ�����������������������built in Model ʵ��
	static egf::IBuiltinModel* MovableObject::Factory()
	{
		return EE_NEW MovableObject();
	}


	// Ӧ�ó��� getter
	const efd::Point3& GetVelocity() const
	{

		return m_prop1_MoveVelocity;
	}
	void SetVelocity(const efd::Point3& MoveVelocity)
	{
		m_prop1_MoveVelocity = MoveVelocity;
	}



	
	// Ӧ�ó��� getter
	const efd::Point3& GetAccel() const
	{

		return m_prop2_Accel;
	}

	void SetAccel(const efd::Point3& Accel)
	{
		m_prop2_Accel = Accel;
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

	//ϵͨ���������
	const efd::ServiceManager* m_pServiceManager;
	//��ǰ�ٶ�
	efd::Point3 m_prop1_MoveVelocity;
	//���ٶ�
	efd::Point3 m_prop2_Accel;
	//ת����
	efd::Point3 m_prop3_RotationAxis;
	//���ٶ�,�����һ����/�� Ϊ��λ��
	efd::Float32 m_prop4_AngularSpeed;
	//Ŀ���ٶ�
	efd::Point3 m_TargetVelocity;
	//Ŀ��Ƕ�
	efd::Float32 m_TargetAngular;
	//��Ŀ���ٶȹ��ɵ�ʣ��ʱ��
	efd::Float32 m_LeftTimeForTransitionVelocity;
	//��Ŀ��Ƕȹ��ɵ�ʣ��ʱ��
	efd::Float32 m_LeftTimeForTransitionAngular;

};
typedef efd::SmartPointer<MovableObject> MovableObjectPtr;
