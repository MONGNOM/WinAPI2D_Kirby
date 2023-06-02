#pragma once
#include "CItem.h"
class CPersimmon : public CItem
{
public:
	CPersimmon();
	virtual ~CPersimmon();


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

