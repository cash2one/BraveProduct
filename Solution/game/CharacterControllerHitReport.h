/********************************************************************
	����ʱ��: 12:12:2010   13:13
	����:	  ����
	����:	character ����������ײ�ص���
*********************************************************************/
#pragma once
#include <nxcontroller.h>

class CharacterControllerHitReport :
	public NxUserControllerHitReport
{
public:
	CharacterControllerHitReport(void);
	virtual ~CharacterControllerHitReport(void);

	//����ײ�¼������� charcter ��һ������ѧPhysX actor ֮�䷢����ʱ������������
	//hit ��������Shape ������ֵ�Ƿ���ִ�е���Ϊ�������ƻ��߲���
	virtual NxControllerAction onShapeHit(const NxControllerShapeHit& hit);

	//�����������charcter ������character ��ײ��ʱ������������
	// hit ��������character
	//����ֵ�Ƿ���ִ�е���Ϊ�������ƻ��߲���
	virtual NxControllerAction onControllerHit(const NxControllersHit& hit);

	/// �����������PhysX character controller
	void SetOwner(NxController* pController) { m_pOwner = pController; }
	/// ��������ϵ��
	void SetPushMultiplier(efd::Float32 multiplier) { m_pushMultiplier = multiplier; }

private:
	//��������˿�����
	NxController* m_pOwner;
	//���������ϵ��
	float m_pushMultiplier;

};
