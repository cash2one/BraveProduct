/********************************************************************
	����ʱ��:	25:11:2010   9:41
	����:		����
	����:	    �ƶ��� API	,��ҪΪ�ƶ���
*********************************************************************/
#pragma once
#include "egf/EntityID.h"

namespace PhysxCharacterMovementAPI
{

	//����ĳ��ʵ����ٶ��ڹ涨��ʱ��仯��ĳ��ֵ
    efd::Bool ChangeHorizontalVelocityTo(egf::EntityID entityID,efd::Float32 fDelayTime,efd::Point2 TargetVelocity);
	//�����ڹ涨ʱ������ת��ĳ��������ת���ĳ���Ƕ�
	efd::Bool ChangeAngleTo(egf::EntityID entityID,efd::Float32 fDelayTime,efd::Float32 fAngular);


}
