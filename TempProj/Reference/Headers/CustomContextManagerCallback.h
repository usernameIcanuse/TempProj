#pragma once
#include "Base.h"

BEGIN(Engine)

class CCustomContextManagerCallback : public DxContextManagerCallback
{
public:
	CCustomContextManagerCallback(ID3D11Device* pDevice);

	// DxContextManagerCallback��(��) ���� ��ӵ�
	virtual void acquireContext() override;
	virtual void releaseContext() override;
	virtual ID3D11Device* getDevice() const override;
	virtual ID3D11DeviceContext* getContext() const override;
	virtual bool synchronizeResources() const override;

public:
	std::recursive_mutex mMutex;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;
	bool mSynchronizeResources = false;
};

END