#pragma once

class cEffect;
class cStaticMeshEffect;
class cEffectMgr : public cSingleton<cEffectMgr>
{
private:
	map<string, list<cEffect*>>	m_mapEffect;
	list<cEffect*>				m_listEffect;
	vector<cStaticMeshEffect*>	m_vecStaticMeshEffect;

	
public:
	void AddEffect(string sKey, cEffect* pEffect);
	cEffect* AddList(string sKey, D3DXVECTOR3 vPosition, D3DXMATRIXA16& matRotation);
	void RemoveList(string sKey, cEffect* pEffect);
	list<cEffect*>* GetEffectInList(string sKey);
	list<cEffect*>* GetEffectInMap(string sKey);

	void AddStaticMeshEffect(char* szFolder, char* szFilename, D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle);
	void RemoveStaticMeshEffect();


public:
	void Update();
	void Render();
	void Release();
	void StaticMeshEffectRender();

public:
	cEffectMgr();
	~cEffectMgr();
};

