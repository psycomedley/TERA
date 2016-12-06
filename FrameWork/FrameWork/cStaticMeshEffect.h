#pragma once
class cStaticMeshEffect
{
private:

public:
	cStaticMeshEffect();
	~cStaticMeshEffect();

	HRESULT Setup();
	void Update();
	void Render();
};

