/********************************************************************
	����ʱ��:	7:12:2010   11:27
	����:		����
	����:	  �Ƕ�PhysxCharacter �������Ĺ������
*********************************************************************/
#pragma once
#include <NxControllerManager.h>
#include "PhysxCharacterMoveObject.h"
#include "efdPhysX\PhysXAllocator.h"
#include <ecrPhysX\NiPhysXSceneAdded.h>
#include <egfPhysX\SceneMessage.h>
#include <NiPhysXScene.h>

class PhysxCharacterMovementService
	:public efd::ISystemService
{

	/// @cond EMERGENT_INTERNAL
	EE_DECLARE_CLASS1(
		PhysxCharacterMovementService,
		game::SERVICE_ID_PhysxCharacterMovementService,
		efd::ISystemService);
	EE_DECLARE_CONCRETE_REFCOUNT
public:
	PhysxCharacterMovementService(efdPhysX::PhysXAllocator* pAllocator);
	virtual ~PhysxCharacterMovementService(void);

	virtual efd::SyncResult  OnPreInit ( efd::IDependencyRegistrar* pDependencyRegistrar );
	//��ʼ���������
	virtual efd::AsyncResult OnInit();
	//����� Update 
	virtual efd::AsyncResult OnTick();
	//����Ĺر�
	virtual efd::AsyncResult OnShutdown();

	//ע����ƶ�������
	void RegisterMovableObject(const egf::EntityID& entityID, PhysxCharacterMoveObject * pObject, NxControllerDesc& desc, NxController ** ppResultPhysxController);

	//ɾ��ĳ���ƶ�����
	void UnregisterMovableObject(const egf::EntityID& entityID);

	//�������������Ҫ��ʾ������
	const char* GetDisplayName() const;


	//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
	void ChangeHorizontalVelocityTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Point2 TargetVelocity);

	//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
	void ChangeAngleTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Float32 fAngular);

	//�����������ʱ��Ҫ������¼�
	void HandlePhysXSceneAddedMessage
		(
		const ecrPhysX::NiPhysXSceneAdded* pMessage,
		efd::Category targetChannel
		);
	

	//ɾ����������ʱ��Ҫ������¼�
	void HandlePhysXSceneRemovedMessage
		(
		const egfPhysX::SceneMessage* pMessage,
		efd::Category targetChannel
		);
	

protected:

	//Physx ������������
	NxControllerManager* m_pkNxControllerManager;

	// ���� ���Զ�����ı�
	efd::map<egf::EntityID, PhysCharacterMoveObjectPtr> m_CharacterMoveObjectMap;
	//���еĿ�����
	efd::map<egf::EntityID, NxController * > m_NxControllerMap;




	// ��һ�ε��õ�ʱ�䣬�������� delta time �õ�
	efd::TimeType m_LastUpdate;

	//����ȷ������ģ����ͬ�������첽ִ��
	bool m_runSynchronously;

	//�ڴ����������������CharacterController 
	efdPhysX::PhysXAllocator* m_pAllocator;

	//��ǰ������������
	efd::utf8string m_CurrentSceneName;

	//��ǰ��������
	NiPhysXScene* m_spPhysXScene;

	//����������������
	NxScene* m_pNxScene;



};
