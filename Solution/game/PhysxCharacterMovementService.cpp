#include "game_pch.h"
#include "PhysxCharacterMovementService.h"
#include <egfPhysX/SceneService.h>
#include <ecrPhysX\PropService.h>
#include <ecrPhysX\NiPhysXSceneAdded.h>
#include "PhysxCharacterMoveObject.h"
#include "PhysXSceneHandle.h"


EE_IMPLEMENT_CONCRETE_CLASS_INFO(PhysxCharacterMovementService);

//PhysX ������ӵ���Ϣ,�����Ϣ������PropService
EE_HANDLER(PhysxCharacterMovementService, HandlePhysXSceneAddedMessage, ecrPhysX::NiPhysXSceneAdded);

//�����Ϣ������SceneService
EE_HANDLER_WRAP(
				PhysxCharacterMovementService,
				HandlePhysXSceneRemovedMessage,
				egfPhysX::SceneMessage,
				efd::kMSGID_PhysXSceneRemoved);


PhysxCharacterMovementService::PhysxCharacterMovementService(efdPhysX::PhysXAllocator* pAllocator)
:m_pAllocator(pAllocator),
m_pNxScene(NULL),
m_spPhysXScene(NULL)
{
	
}

PhysxCharacterMovementService::~PhysxCharacterMovementService(void)
{


}

efd::SyncResult  PhysxCharacterMovementService::OnPreInit ( efd::IDependencyRegistrar* pDependencyRegistrar )
{
	pDependencyRegistrar->AddDependency<efd::MessageService>();
	pDependencyRegistrar->AddDependency<egfPhysX::SceneService>();
	pDependencyRegistrar->AddDependency<ecrPhysX::PropService>();

	//ͨ��builtinModelID  ��FlatModelManager �а�Factory �� toolbench �е�modle ��������
	const egf::FlatModelID builtinModelID = 201573187;

	egf::FlatModelManager* pFlatModelManager =
		m_pServiceManager->GetSystemServiceAs<egf::FlatModelManager>();
	EE_ASSERT(pFlatModelManager);

	//ע��PhysxCharacterMoveObject �Ĵ�������
	pFlatModelManager->RegisterBuiltinModelFactory(
		"PhysxCharacterMoveObject",
		builtinModelID,
		PhysxCharacterMoveObject::Factory);

	return efd::SyncResult_Success;


}
//��ʼ���������
efd::AsyncResult PhysxCharacterMovementService::OnInit()
{
	efd::MessageService* pMessageService =
		m_pServiceManager->GetSystemServiceAs<efd::MessageService>();

	EE_ASSERT(pMessageService);
//Ҫ����PhysX ��Ϣ
	pMessageService->Subscribe(this, egfPhysX::kCAT_egfPhysXMessage);

	EE_ASSERT(efdPhysX::PhysXSDKManager::GetManager());

	EE_ASSERT(m_pAllocator);
	m_pkNxControllerManager = NxCreateControllerManager(m_pAllocator);

	EE_ASSERT(m_pkNxControllerManager);
	return efd::AsyncResult_Complete;

}
//����� Update 
efd::AsyncResult PhysxCharacterMovementService::OnTick()
{
	efd::TimeType gameTime = m_pServiceManager->GetTime(efd::kCLASSID_GameTimeClock);
	efd::TimeType timeDelta = gameTime - m_LastUpdate;


	m_LastUpdate = gameTime;
	efd::map<egf::EntityID, PhysCharacterMoveObjectPtr>::iterator iter = m_CharacterMoveObjectMap.begin();
	while (iter != m_CharacterMoveObjectMap.end())
	{
		PhysxCharacterMoveObject * pHandler = iter->second;
		pHandler->Update(timeDelta);
		iter++;
	}

	//���¿�����
	m_pkNxControllerManager->updateControllers();
	//����  Tick 
	return efd::AsyncResult_Pending ;

}
//����Ĺر�
efd::AsyncResult PhysxCharacterMovementService::OnShutdown()
{
	NxReleaseControllerManager(m_pkNxControllerManager);
	return efd::AsyncResult_Complete;

}

//ע����ƶ�������
void PhysxCharacterMovementService::RegisterMovableObject(const egf::EntityID& entityID, PhysxCharacterMoveObject * pObject, NxControllerDesc& desc, NxController ** ppResultPhysxController)
{
	if (m_CharacterMoveObjectMap.find(entityID) != m_CharacterMoveObjectMap.end())
	{
		//����Ѿ��������Object�Ļ�������ɾ����
		m_CharacterMoveObjectMap.erase(entityID);
	}

	if(m_pNxScene)
	{
		

		desc.position.x *= m_spPhysXScene->GetScaleFactor();
		desc.position.y *= m_spPhysXScene->GetScaleFactor();
		desc.position.z *= m_spPhysXScene->GetScaleFactor();
		desc.stepOffset *=(1.0f / m_spPhysXScene->GetScaleFactor());
		* ppResultPhysxController = m_pkNxControllerManager->createController(m_pNxScene,desc);
		m_NxControllerMap[entityID] = * ppResultPhysxController;

		m_CharacterMoveObjectMap[entityID] = pObject;
	}

}

//ɾ��ĳ���ƶ�����
void PhysxCharacterMovementService::UnregisterMovableObject(const egf::EntityID& entityID)
{
	   
	m_pkNxControllerManager->releaseController(*m_NxControllerMap[entityID]);
	m_CharacterMoveObjectMap.erase(entityID);
	m_NxControllerMap.erase(entityID);


}

//�������������Ҫ��ʾ������
const char* PhysxCharacterMovementService::GetDisplayName() const
{
	 return "PhysxCharacterMovementService";
}


//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
void PhysxCharacterMovementService::ChangeHorizontalVelocityTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Point2 TargetVelocity)
{
	PhysCharacterMoveObjectPtr pkMovableObject = NULL;
	if (m_CharacterMoveObjectMap.find(entityID,pkMovableObject))
	{
		pkMovableObject->ChangeHorizontalVelocityTo(fDelayTime,TargetVelocity);
	}
}

//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
void PhysxCharacterMovementService::ChangeAngleTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Float32 fAngular)
{
	PhysCharacterMoveObjectPtr pkMovableObject = NULL;
	if (m_CharacterMoveObjectMap.find(entityID,pkMovableObject))
	{
		pkMovableObject->ChangeAngleTo(fDelayTime,fAngular);

	}
}

//�����������ʱ��Ҫ������¼�
void PhysxCharacterMovementService::HandlePhysXSceneAddedMessage
(
 const ecrPhysX::NiPhysXSceneAdded* pMessage,
 efd::Category targetChannel
 )
{
	
	//ͨ����Ϣ��ȡ��Ҫ��ӵĳ���������
	const efd::utf8string& sceneName = pMessage->GetSceneName();

	ecrPhysX::PropService* pPropService =
		m_pServiceManager->GetSystemServiceAs<ecrPhysX::PropService>();
	EE_ASSERT(pPropService);
    //��Ϊ�����Ϣ�Ǵ�PropService �����ģ�����PropService �Ѿ������������
	NiPhysXScene* pScene = pPropService->GetScene(sceneName);
	
	if (pScene)
	{
		PhysXSceneHandlePtr spSceneHandle = NULL;
		
		spSceneHandle = EE_NEW PhysXSceneHandle(pScene);
	}

	m_CurrentSceneName = sceneName;

	m_spPhysXScene = pScene;
	m_pNxScene = pScene->GetPhysXScene();
	//SetupNxScene(sceneName);
}

//ɾ����������ʱ��Ҫ������¼�
void PhysxCharacterMovementService::HandlePhysXSceneRemovedMessage
(
 const egfPhysX::SceneMessage* pMessage,
 efd::Category targetChannel
 )
{
	//��Ϊ�����Ѿ���ɾ���ˣ��������еĿ�������Ҫ��ɾ����
	//�����ɾ�����п�����
	// The Character controllers exist in the PhysX Scenes, so clean them up.
	//DestroyControllers();


	if (m_CurrentSceneName == pMessage->GetSceneName())
	{
		m_CurrentSceneName = efd::utf8string::NullString();
	}

	if (pMessage->GetScene() == m_pNxScene)
	{
		m_spPhysXScene = NULL;
		m_pNxScene = NULL;
	}

}
