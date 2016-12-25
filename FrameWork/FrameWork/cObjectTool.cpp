#include "stdafx.h"
#include "cObjectTool.h"
#include "cPlayer.h"
#include "cStuff.h"

cObjectTool::cObjectTool()
	:m_RotDirection(0)
	, m_PrevPlayerPos(0,0,0)
{
}


cObjectTool::~cObjectTool()
{
	
}
void cObjectTool::Setup()
{
	m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("나무");
	m_vScaling = m_BodyStuff->GetScale();
	ResetVariable();
	//SaveInfoStuff();


}
void cObjectTool::Update()
{

	/*cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	playerPos.z += 2.0f;
	m_BodyStuff->SetPosition(playerPos);*/
	
	ChangeBodyStuff();
	ChangeScaleAndAngle();
	AddClone();
	

	//충돌처리
	CollisionObjWithPlayerAndMonster();
	
	
}
void cObjectTool::Render()
{
	m_BodyStuff->Render(); // 바디 오브젝트만 렌더
	
	m_BodyStuff->Bounding_Render();
	if (KEYBOARD->IsOnceKeyDown(DIK_5))
	{

		m_BodyStuff->GetpMesh()->Bounding_Render(
			m_BodyStuff->GetPosition(), D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0, &m_BodyStuff->GetWorldTM());

	}
	if (KEYBOARD->IsOnceKeyDown(DIK_F2))
	{
		LoadInfoStuff();
	}
	
}
void cObjectTool::ResetVariable()
{
	m_fRx, m_fRy, m_fRz = 0;
	m_vScaling = m_BodyStuff->GetScale();
}
void cObjectTool::ChangeBodyStuff()
{
	if (KEYBOARD->IsOnceKeyDown(DIK_1))
	{
		m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("바리게이트_1");
		ResetVariable(); // 스케일, 회전 변수 다 0으로 초기화
	}

}
void cObjectTool::ChangeScaleAndAngle()
{
	// 회전할 축 선택
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD1))
	{
		m_RotDirection = 1; //x축
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD2))
	{
		m_RotDirection = 2; //y축
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD3))
	{
		m_RotDirection = 3; // z축
	}

	// 스케일
	if (KEYBOARD->IsStayKeyDown(DIK_UP))
	{
		m_vScaling.x += 0.001f; m_vScaling.y += 0.001f; m_vScaling.z += 0.001f;
		m_BodyStuff->SetScale(m_vScaling);
	}
	if (KEYBOARD->IsStayKeyDown(DIK_DOWN))
	{
		m_vScaling.x -= 0.001f; m_vScaling.y -= 0.001f; m_vScaling.z -= 0.001f;
		m_BodyStuff->SetScale(m_vScaling);
	}

	//회전
	switch (m_RotDirection)
	{
	case 1:
		if (KEYBOARD->IsStayKeyDown(DIK_RIGHT))
		{
			m_fRx += 0.03f;
			m_BodyStuff->SetfRotX(m_fRx);
		}
		if (KEYBOARD->IsStayKeyDown(DIK_LEFT))
		{
			m_fRx -= 0.03f;
			m_BodyStuff->SetfRotX(m_fRx);
		}
		break;
	case 2:
		if (KEYBOARD->IsStayKeyDown(DIK_RIGHT))
		{
			m_fRy += 0.03f;
			m_BodyStuff->SetfRotY(m_fRy);
		}
		if (KEYBOARD->IsStayKeyDown(DIK_LEFT))
		{
			m_fRy -= 0.03f;
			m_BodyStuff->SetfRotY(m_fRy);
		}
		break;
	case 3:
		if (KEYBOARD->IsStayKeyDown(DIK_RIGHT))
		{
			m_fRz += 0.03f;
			m_BodyStuff->SetfRotZ(m_fRz);
		}
		if (KEYBOARD->IsStayKeyDown(DIK_LEFT))
		{
			m_fRz -= 0.03f;
			m_BodyStuff->SetfRotZ(m_fRz);
		}
		break;
	default:
		break;
	}
}
void cObjectTool::AddClone()
{
	if (KEYBOARD->IsOnceKeyDown(DIK_SPACE))
	{
		char* folderName = ((cStuff*)m_BodyStuff)->GetFoldername();
		char* fileName = ((cStuff*)m_BodyStuff)->GetFilename();
		
		cStuff* pcloneStuff = new cStuff(folderName, fileName);
		pcloneStuff = CopyInfoToClone(m_BodyStuff, pcloneStuff);
		// 클론오브젝트 정보저장
		SaveInfoStuff(pcloneStuff);
		GETSINGLE(cObjMgr)->AddCloneStuff(pcloneStuff);
	}
	
}
cStuff* cObjectTool::CopyInfoToClone(cStaticObj* BodyStuff, cStuff* CloneStuff)
{
	cStuff* cloneStuff = CloneStuff;
	cloneStuff->SetPosition(BodyStuff->GetPosition());
	cloneStuff->SetScale(BodyStuff->GetScale());
	cloneStuff->SetfRotX(BodyStuff->GetfRotX());
	cloneStuff->SetfRotY(BodyStuff->GetfRotY());
	cloneStuff->SetfRotZ(BodyStuff->GetfRotZ());
	cloneStuff->SetFoldername(((cStuff*)BodyStuff)->GetFoldername());
	cloneStuff->SetFilename(((cStuff*)BodyStuff)->GetFilename());
	cloneStuff->SetIsCullMode(((cStuff*)BodyStuff)->GetIsCullMode());
	cloneStuff->SetSubSetNum(((cStuff*)BodyStuff)->GetSubSetNum());
	return cloneStuff;
}
void cObjectTool::SaveInfoStuff(cStuff* CloneStuff)
{

	//ofstream a("object / StuffInfo.text");
	FILE* fp = NULL;
	char str[1024] = { NULL, };
	fopen_s(&fp, "object/StuffInfo.text", "a");
	// 폴더이름, 파일이름 , 포지션, 스케일, 회전x,회전y, 회전z
	char* foldername = CloneStuff->GetFoldername();
	char* filename = CloneStuff->GetFilename();
	float Px = CloneStuff->GetPosition().x;
	float Py = CloneStuff->GetPosition().y;
	float Pz = CloneStuff->GetPosition().z; 
	float Sx = CloneStuff->GetScale().x;
	float Sy = CloneStuff->GetScale().y;
	float Sz = CloneStuff->GetScale().z;
	float rx = CloneStuff->GetfRotX();
	float ry = CloneStuff->GetfRotY();
	float rz = CloneStuff->GetfRotZ();
	DWORD SubsetNum = CloneStuff->GetSubSetNum();
	bool  isCull = CloneStuff->GetIsCullMode();
	float MaxX = CloneStuff->GetpMesh()->GetvMax().x;
	float MaxY = CloneStuff->GetpMesh()->GetvMax().y;
	float MaxZ = CloneStuff->GetpMesh()->GetvMax().z;
	float MinX = CloneStuff->GetpMesh()->GetvMin().x;
	float MinY = CloneStuff->GetpMesh()->GetvMin().y;
	float MinZ = CloneStuff->GetpMesh()->GetvMin().z;

	sprintf_s(str, "\n%s %s %f %f %f %f %f %f %f %f %f %d %d %f %f %f %f %f %f"
		,foldername,filename, Px, Py, Pz,Sx,Sy,Sz,rx,ry,rz,SubsetNum,isCull
		, MinX, MinY, MinZ, MaxX, MaxY, MaxZ);
	fprintf(fp, "%s", str);

	fclose(fp);
}
void cObjectTool::LoadInfoStuff()
{
	FILE* fp = NULL;
	char str[2048] = { NULL, };
	char foldername[120] = { NULL ,};
	char filename[120] = { NULL, };
	float Px = 0, Py=0, Pz=0;
	float Sx =0, Sy=0, Sz=0;
	float Rx=0, Ry=0, Rz=0;
	float MinX = 0, MinY = 0, MinZ = 0;
	float MaxX = 0, MaxY = 0, MaxZ = 0;
	DWORD SubsetNum = 0;
	int  isCull = false;
	int a = 0;

	fopen_s(&fp, "object/StuffInfo.text", "r");
	
	while (1)
	{
		if (feof(fp)) break;
		fgets(&str[0],2048,fp);
		if (str[0] == '\n')
			continue;

		sscanf_s(str, "%s%s%f%f%f%f%f%f%f%f%f%d%d%f%f%f%f%f%f"
			, foldername, 120, filename, 120, &Px, &Py, &Pz, &Sx, &Sy, &Sz
			, &Rx, &Ry, &Rz, &SubsetNum, &isCull
			, &MinX, &MinY, &MinZ, &MaxX, &MaxY, &MaxZ);

		//저장된 오브젝트 생성하기
		cStuff* cloneStuff = new cStuff(foldername, filename);
		cloneStuff->SetPosition(D3DXVECTOR3(Px,Py,Pz));
		cloneStuff->SetScale(D3DXVECTOR3(Sx, Sy, Sz));
		cloneStuff->SetfRotX(Rx);
		cloneStuff->SetfRotY(Ry);
		cloneStuff->SetfRotZ(Rz);
		cloneStuff->SetSubSetNum(SubsetNum);
		cloneStuff->SetIsCullMode(isCull);
		cloneStuff->SetFoldername(&foldername[0]);
		cloneStuff->SetFilename(&filename[0]);
		D3DXVECTOR3 vMIN(MinX*0.05f, MinY*0.85f, MinZ*0.05f);
		D3DXVECTOR3 vMAX(MaxX*0.05f, MaxY*0.85f, MaxZ*0.05f);
		cloneStuff->GetpMesh()->GetpBox()->SetvMax(vMAX);
		cloneStuff->GetpMesh()->GetpBox()->SetvMin(vMIN);
		cloneStuff->SetRevisionScale(D3DXVECTOR3(0.05f, 0.85f, 0.05f));
		GETSINGLE(cObjMgr)->AddCloneStuff(cloneStuff);
	}
	fclose(fp);
	

}
void cObjectTool::CollisionObjWithPlayerAndMonster()
{
	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	vector<cDynamicObj*> pVecAllMonster = GETSINGLE(cObjMgr)->GetALLMonsterList();

	vector<cStaticObj*> vecCloneStuff = *(GETSINGLE(cObjMgr)->GetAllCloneStuff());
	cBoundingBox* playerBox = &(pPlayer->GetBox());
	//cBoundingBox* MostersBox = 
	
	for (size_t i = 0; i < vecCloneStuff.size(); ++i)
	{
		// 캐릭터와 오브젝트 충돌
		cBoundingBox* stuffBox = &(vecCloneStuff[i]->GetBox());
		if (GETSINGLE(cCollision)->Collision(playerBox, stuffBox))
		{
			pPlayer->SetPosition(m_PrevPlayerPos);
			D3DXVECTOR3 afterPos = GETSINGLE(cObjMgr)->GetPlayer()->GetPosition();
			int a = 0;
		}
		else
		{
			m_PrevPlayerPos = GETSINGLE(cObjMgr)->GetPlayer()->GetPosition();
		}

		//몬스터와 오브젝트 충돌
		for (size_t j = 0; j < pVecAllMonster.size(); ++j)
		{
			if (pVecAllMonster[j]->GetInfo().sName =="Globe") continue;
			cBoundingBox* MosterBox = &(pVecAllMonster[j]->GetBox());
			
			if (GETSINGLE(cCollision)->Collision(MosterBox, stuffBox))
			{
				pVecAllMonster[j]->SetPosition(pVecAllMonster[j]->GetPrevPosition());
			}
			{
				pVecAllMonster[j]->SetPrevPosition(pVecAllMonster[j]->GetPosition());
			}
		}

	}

	
		
}