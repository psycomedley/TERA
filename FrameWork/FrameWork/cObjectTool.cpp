#include "stdafx.h"
#include "cObjectTool.h"
#include "cPlayer.h"
#include "cStuff.h"

cObjectTool::cObjectTool()
	:m_RotDirection(0)
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
	ReadInfoStuff();

}
void cObjectTool::Update()
{

	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	playerPos.z += 2.0f;
	m_BodyStuff->SetPosition(playerPos);
	
	ChangeBodyStuff();
	ChangeScaleAndAngle();
	AddClone();
}
void cObjectTool::Render()
{
	m_BodyStuff->Render(); // 바디 오브젝트만 렌더
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
	sprintf_s(str, "%s %s %f %f %f %f %f %f %f %f %f\n"
		,foldername,filename, Px, Py, Pz,Sx,Sy,Sz,rx,ry,rz, 1024);
	fprintf(fp, "%s", str);

	fclose(fp);
}
void cObjectTool::ReadInfoStuff()
{
	FILE* fp = NULL;
	char str[1024] = { NULL, };
	char foldername[120] = { NULL ,};
	char filename[120] = { NULL, };
	float Px = 0.0f;
	float Sx, Sy, Sz;
	float Rx, Ry, Rz;
	fopen_s(&fp, "object/StuffInfo.text", "r");
	while (!feof(fp))
	{
		fscanf_s(fp, "%s", str, sizeof(str));
		strcpy_s(foldername,sizeof(foldername), &str[0]);
		fscanf_s(fp, "%s", str, sizeof(str));
		strcpy_s(filename, sizeof(filename), &str[0]);
		fscanf_s(fp, "%f", Px);
	}
	fclose(fp);
	

}