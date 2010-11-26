#include "game_pch.h"
#include "MovementService.h"
#include "egf/FlatModelManager.h"

EE_IMPLEMENT_CONCRETE_CLASS_INFO(MovementService);

MovementService::MovementService(void)
{

}

MovementService::~MovementService(void)
{

}


efd::SyncResult MovementService:: OnPreInit ( efd::IDependencyRegistrar* pDependencyRegistrar )
{

	//ͨ��builtinModelID  ��FlatModelManager �а�Factory �� toolbench �е�modle ��������
	const egf::FlatModelID builtinModelID = 264070643;

	egf::FlatModelManager* pFlatModelManager =
		m_pServiceManager->GetSystemServiceAs<egf::FlatModelManager>();
	EE_ASSERT(pFlatModelManager);

	//ע��MovableObject �Ĵ�������
	pFlatModelManager->RegisterBuiltinModelFactory(
		"MovableObject",
		builtinModelID,
		MovableObject::Factory);

	return efd::SyncResult_Success;
	



}


//ע����ƶ�������
void MovementService::RegisterMovableObject
(
 const egf::EntityID& entityID, MovableObject * pObject
 )
{
	
	if (m_MovableObjectMap.find(entityID) != m_MovableObjectMap.end())
	{
		//����Ѿ��������Object�Ļ�������ɾ����
		m_MovableObjectMap.erase(entityID);
	}
	m_MovableObjectMap[entityID] = pObject;


}
//ɾ��ĳ���ƶ�����
void MovementService::UnregisterMovableObject(const egf::EntityID& entityID)
{
	m_MovableObjectMap.erase(entityID);
}

//��ʼ���������
 efd::AsyncResult MovementService::OnInit()
{

	
	return efd::AsyncResult_Complete;


}
//����� Update 
 efd::AsyncResult MovementService::OnTick()
{
	efd::TimeType gameTime = m_pServiceManager->GetTime(efd::kCLASSID_GameTimeClock);
	efd::TimeType timeDelta = gameTime - m_lastUpdate;
	m_lastUpdate = gameTime;
	efd::map<egf::EntityID, MovableObjectPtr>::iterator iter = m_MovableObjectMap.begin();
	while (iter != m_MovableObjectMap.end())
	{
		MovableObject* pHandler = iter->second;
		pHandler->Update(timeDelta);
		iter++;
	}

	//����  Tick 
	return efd::AsyncResult_Pending ;

}
//����Ĺر�
 efd::AsyncResult MovementService::OnShutdown()
{
	return efd::AsyncResult_Complete;

}

 //�������������Ҫ��ʾ������
 const char* MovementService::GetDisplayName() const
 {
	 return "MovementService";
 }

 //����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
 void MovementService::ChangeVelocityTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Point3 TargetVelocity)
 {

	 MovableObjectPtr pkMovableObject = NULL;
	 if (m_MovableObjectMap.find(entityID,pkMovableObject))
	 {
		 pkMovableObject->ChangeVelocityTo(fDelayTime,TargetVelocity);
	   
	 }

 }

 //�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
 void MovementService::ChangeAngleTo(const egf::EntityID& entityID,efd::Float32 fDelayTime,efd::Float32 fAngular)
 {
	 MovableObjectPtr pkMovableObject = NULL;
	 if (m_MovableObjectMap.find(entityID,pkMovableObject))
	 {
		 pkMovableObject->ChangeAngleTo(fDelayTime,fAngular);

	 }





 }