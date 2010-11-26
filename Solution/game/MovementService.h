/********************************************************************
	����ʱ��:	12:11:2010   16:27
	����:		����
	����:	   �����ƶ��ķ���
*********************************************************************/
#pragma once
#include "ID.h"
#include <efd/ISystemService.h>
#include <efd/Foundation.h>
#include "MovableObject.h"

class MovementService :
	public efd::ISystemService
{
	/// @cond EMERGENT_INTERNAL
	EE_DECLARE_CLASS1(
		MovementService,
		game::CLASS_ID_MovementService,
		efd::ISystemService);
	EE_DECLARE_CONCRETE_REFCOUNT;
public:
	MovementService(void);
	~MovementService(void);

	
	virtual efd::SyncResult  OnPreInit ( efd::IDependencyRegistrar* pDependencyRegistrar );
	//��ʼ���������
	virtual efd::AsyncResult OnInit();
	//����� Update 
	virtual efd::AsyncResult OnTick();
	//����Ĺر�
	virtual efd::AsyncResult OnShutdown();

	//ע����ƶ�������
	void RegisterMovableObject(const egf::EntityID& entityID, MovableObject * pObject);

	//ɾ��ĳ���ƶ�����
	void UnregisterMovableObject(const egf::EntityID& entityID);

	//�������������Ҫ��ʾ������
	const char* GetDisplayName() const;


	//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
	void ChangeVelocityTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Point3 TargetVelocity);

	//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
	void ChangeAngleTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Float32 fAngular);
	
		

protected:

	// ���� ���Զ�����ı�
	efd::map<egf::EntityID, MovableObjectPtr> m_MovableObjectMap;

	/// ��һ�ε��õ�ʱ�䣬�������� delta time �õ�
	efd::TimeType m_lastUpdate;




};


