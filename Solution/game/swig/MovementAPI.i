%feature("compactdefaultargs");
%include <windows.i>
%include <typemaps.i>

//�������������¶���ű����Ե����ֿռ䡣
%module MovementAPI

//������"%{....%}" ���ڵĴ����Ǳ�ֱ��д�������ļ��еģ�һ����������������ڽ�API ������
//����ͷ�ļ�
%{
#include "../ID.h"
#include "egfLua/bapiLua.h"
#include "../MovementAPI.h" 
%}



// egf/BehaviorAPI.i  Ϊд���Լ����ڽ�APIs �����˺ܶ��и������ԡ��Ƽ��������뵽���������ڽ�API ģ����
// ͨ��ʹ��'%import' ������'%include' ������û�и����κ�һ�����ĺ����Ͱ�BehaviorAPI�Ĺ����������� 

//%import "egf/BehaviorAPI.i" 

// ���ͱ����� �����ṩ֧�ַǳ���Ĺ��ܺ���Ϸ����������͡���ҲΪ��Ϊ������������룬����������������
//��  maps and lists and ���������͡�
%include "egfLua/bapiLuaTypeMaps.i"

// ����Ҫ��¶�ĺ������ķ����� include һ�� ������������ �� �ڽ� API ���� �� c++ ͷ�ļ�
%include "MovementAPI.h" 

