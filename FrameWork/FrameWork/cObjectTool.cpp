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
	m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("����");
	m_vScaling = m_BodyStuff->GetScale();
	ResetVariable();
	//SaveInfoStuff();


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
	if (KEYBOARD->IsOnceKeyDown(DIK_F2))
	{
		LoadInfoStuff();
	}
	
	
}
void cObjectTool::Render()
{
	m_BodyStuff->Render(); // �ٵ� ������Ʈ�� ����
	
	m_BodyStuff->Bounding_Render();
	if (KEYBOARD->IsOnceKeyDown(DIK_5))
	{

		m_BodyStuff->GetpMesh()->SetupBounding(D3DXVECTOR3(-100, -200, -150), D3DXVECTOR3(100, 200, 150));

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
		m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("�ٸ�����Ʈ_1");
		ResetVariable(); // ������, ȸ�� ���� �� 0���� �ʱ�ȭ
	}

}
void cObjectTool::ChangeScaleAndAngle()
{
	// ȸ���� �� ����
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD1))
	{
		m_RotDirection = 1; //x��
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD2))
	{
		m_RotDirection = 2; //y��
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD3))
	{
		m_RotDirection = 3; // z��
	}

	// ������
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

	//ȸ��
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
		// Ŭ�п�����Ʈ ��������
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
	// �����̸�, �����̸� , ������, ������, ȸ��x,ȸ��y, ȸ��z
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

	sprintf_s(str, "\n%s %s %f %f %f %f %f %f %f %f %f %d %d"
		,foldername,filename, Px, Py, Pz,Sx,Sy,Sz,rx,ry,rz,SubsetNum,isCull);
	fprintf(fp, "%s", str);

	fclose(fp);
}
void cObjectTool::LoadInfoStuff()
{
	FILE* fp = NULL;
	char str[1024] = { NULL, };
	char foldername[120] = { NULL ,};
	char filename[120] = { NULL, };
	float Px = 0, Py=0, Pz=0;
	float Sx =0, Sy=0, Sz=0;
	float Rx=0, Ry=0, Rz=0;
	DWORD SubsetNum = 0;
	int  isCull = false;
	fopen_s(&fp, "object/StuffInfo.text", "r");
	while (1)
	{
		if (feof(fp)) break;
		fgets(&str[0],1024,fp);
		if (str[0] == '\n')
			continue;

		sscanf_s(str, "%s%s%f%f%f%f%f%f%f%f%f%d%d"
			,foldername,120,filename,120, &Px, &Py, &Pz, &Sx, &Sy, &Sz
			, &Rx, &Ry, &Rz, &SubsetNum, &isCull);

		//����� ������Ʈ �����ϱ�
		cStuff* cloneStuff = new cStuff(foldername, filename);
		cloneStuff->SetPosition(D3DXVECTOR3(Px,Py,Pz));
		cloneStuff->SetScale(D3DXVECTOR3(Sx, Sy, Sz));
		cloneStuff->SetfRotX(Rx);
		cloneStuff->SetfRotY(Ry);
		cloneStuff->SetfRotZ(Rz);
		cloneStuff->SetSubSetNum(SubsetNum);
		cloneStuff->SetIsCullMode(isCull);
		GETSINGLE(cObjMgr)->AddCloneStuff(cloneStuff);
	}
	fclose(fp);
	

}