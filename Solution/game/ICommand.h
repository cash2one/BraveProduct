// ======================================================================================
// File         : ICommand.h
// Author       : Zhang yuzhong 
// Last Change  : 12/6/2010
// Description  : ����ģʽ�ӿ� ����̳�ʵ�־�������
//				  
// ======================================================================================

#pragma once

#include <NiTArray.h>
#include <NiString.h>

class ICommand : public NiMemObject
{
public:
	ICommand(void);
	virtual ~ICommand(void);

	 virtual void SetParams( NiTObjectArray<NiString>& Argv) = 0;
	 virtual bool Execute() = 0;
};
