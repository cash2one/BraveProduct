// ======================================================================================
// File         : GameWorldService.h
// Author       : Zhang yuzhong 
// Last Change  : 11/30/2010
// Description  : ����block �� entity �ӿ�
//				  
// ======================================================================================

#include "game_pch.h"
#include "GameWorldService.h"

#include <egf/EntityLoaderService.h>
#include <egf/EntityFactoryResponse.h>
#include <efd/Foundation.h>
#include <efd/AssetLoadResponse.h>

EE_IMPLEMENT_CONCRETE_CLASS_INFO(GameWorldService);

EE_HANDLER(GameWorldService, HandleEntityLoadResult, egf::EntityLoadResult);
EE_HANDLER(GameWorldService, HandleEntityFactoryResponse, egf::EntityFactoryResponse);



GameWorldService::GameWorldService(void):
 		m_blockCat(efd::Category(
 		   efd::UniversalID::ECU_Point2Point,
 		   efd::kNetID_Any,
 		   GameWorldService::CLASS_ID)),
 		m_entityCat(efd::Category(
 		   efd::UniversalID::ECU_Point2Point,
 		   efd::kNetID_Any,
 		   GameWorldService::CLASS_ID))
{
}

GameWorldService::~GameWorldService(void)
{
}

const char * GameWorldService::GetDisplayName() const
{
	return "GameWorldService";
}

// ����OnInit��������ķ��� 
efd::SyncResult GameWorldService::OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar)
{
	pDependencyRegistrar->AddDependency<egf::EntityLoaderService>();
	pDependencyRegistrar->AddDependency<egf::EntityManager>();
	pDependencyRegistrar->AddDependency<efd::MessageService>();

	return efd::SyncResult_Success;
}

// 
efd::AsyncResult GameWorldService::OnInit()
{
	efd::MessageService* pMessageService = m_pServiceManager->GetSystemServiceAs<efd::MessageService>();	
	if (!pMessageService)
	{
		EE_ASSERT(pMessageService);		
		return efd::AsyncResult_Failure;
	}
	pMessageService->Subscribe(this, efd::kCAT_LocalMessage);
	pMessageService->Subscribe(this, m_blockCat);
	pMessageService->Subscribe(this, m_entityCat);
	return efd::AsyncResult_Complete;
}

// 
efd::AsyncResult GameWorldService::OnShutdown()
{
	efd::MessageService* pMessageService = m_pServiceManager->GetSystemServiceAs<efd::MessageService>();	
	if (!pMessageService)
	{
		EE_ASSERT(pMessageService);		
		return efd::AsyncResult_Failure;
	}

	pMessageService->Unsubscribe(this, efd::kCAT_LocalMessage);
	pMessageService->Unsubscribe(this, m_blockCat);
	pMessageService->Unsubscribe(this, m_entityCat);
	return efd::AsyncResult_Complete; 
}


// ����block����
void GameWorldService::LoadBlock(const efd::utf8string& blockUrn, bool autoEnter)
{
	egf::EntityLoaderService* pEntityLoaderService = m_pServiceManager->GetSystemServiceAs<egf::EntityLoaderService>();
	EE_ASSERT(pEntityLoaderService);
	if (pEntityLoaderService)
	{
		egf::BlockLoadParameters blp(m_blockCat);		
		blp.SetAutoEnterWorld(autoEnter);
		pEntityLoaderService->RequestEntitySetLoad(blockUrn, &blp);
	}

}
// ж��
void GameWorldService::UnLoadBlock(const efd::utf8string& blockUrn)
{
	egf::EntityLoaderService* pEntityLoaderService = m_pServiceManager->GetSystemServiceAs<egf::EntityLoaderService>();
	EE_ASSERT(pEntityLoaderService);
	if (pEntityLoaderService)
	{
		pEntityLoaderService->RequestEntitySetUnload(blockUrn);
	}
}

// ����entity
egf::EntityID GameWorldService::SpawnEntity(const efd::utf8string& modelUrn)
{
	egf::EntityManager* pEntityManager = m_pServiceManager->GetSystemServiceAs<egf::EntityManager>();
	EE_ASSERT(pEntityManager);
	if (pEntityManager)
	{
		return pEntityManager->CreateEntity(modelUrn, m_entityCat);
	}
	return egf::kENTITY_INVALID;
}
// ɾ��entity
void GameWorldService::DeleteEntity(const egf::EntityID &entityId)
{
	egf::EntityManager* pEntityManager = m_pServiceManager->GetSystemServiceAs<egf::EntityManager>();
	EE_ASSERT(pEntityManager);
	if (pEntityManager)
	{
		pEntityManager->DestroyEntity(entityId);
	}
}

void GameWorldService::HandleEntityLoadResult(
	const egf::EntityLoadResult* pWorldMessage,
	efd::Category targetChannel)
{
	
	if (m_blockCat == targetChannel)// block����
	{
		switch (pWorldMessage->m_result)
		{
		case egf::EntityLoadResult::elr_Loaded:
			break;
		case egf::EntityLoadResult::elr_EntityCreationCompleted:
			break;
		case egf::EntityLoadResult::elr_EntityDestructionCompleted:
			break;
		}
	}
	else if(m_entityCat == targetChannel)// entity������
	{

	}

	notifyObserver(Event::BlockLoad, (void*)pWorldMessage);

}

void GameWorldService::HandleEntityFactoryResponse(
	const egf::EntityFactoryResponse* pResponse,
	efd::Category targetCategory)
{
	if(m_entityCat == targetCategory)// entity������
	{
		if (pResponse->GetResult() == efd::AssetLoadResponse::ALR_Success)
		{
			egf::Entity* pNewEntity = pResponse->GetEntity();

			// do something with the newly created entity...
		}
		else
		{
			// The failure occured after all data was loaded, most likely a built-in model could not
			// be allocated or intitialized. Failure at this stage is rare.
		}
	}
}