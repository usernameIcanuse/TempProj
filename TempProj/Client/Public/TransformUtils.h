#pragma once
#include "Client_Defines.h"
#include <stdarg.h>


BEGIN(Engine)

class CTransform;

END


BEGIN(Client)


class CTransformUtils
{
public:
	/*
	*	�Ѱ��� ����� ���� �����ϴ� �Լ�
		����1. ����� ����.
		����2. �ѱ� ��ĵ�
	*/
	static _matrix Mul_Matrix(_int imatCount, _fmatrix mat ...);

};

END
