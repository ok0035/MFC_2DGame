
// GAME_PROJECTView.cpp : CGAME_PROJECTView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GAME_PROJECT.h"
#endif

#include "GAME_PROJECTDoc.h"
#include "GAME_PROJECTView.h"
#include<Windows.h>
#include<random>
#include<ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGAME_PROJECTView

IMPLEMENT_DYNCREATE(CGAME_PROJECTView, CView)

BEGIN_MESSAGE_MAP(CGAME_PROJECTView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGAME_PROJECTView 생성/소멸


CGAME_PROJECTView::CGAME_PROJECTView()
	: mx(0)
	, my(0)
	, spd(10)
	, dx(10)
	, dy(10)
	, isRight(false)
	, motion(false)
	, stageNum(0)
	, gameType(10)
	, player(NULL)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));

	player = new Player(450, 350, spd);

	int rx[10];
	int ry[10];

	for (int i = 0; i < 10; i++) {
		rx[i] = rand() % 1000;
		ry[i] = rand() % 300 + 300;
	}

	for (int i = 0; i < 10; i++) {
		enemy[i] = new Player(rx[i], ry[i], 5);
	}

	/*


	enemy[0] = new Player(10, 0, 5);
	enemy[1] = new Player(50, 0, 5);
	enemy[2] = new Player(70, 0, 5);
	enemy[3] = new Player(90, 0, 5);
	enemy[4] = new Player(300, 0, 5);
	enemy[5] = new Player(400, 0, 5);
	enemy[6] = new Player(600, 0, 5);
	enemy[7] = new Player(700, 0, 5);
	enemy[8] = new Player(800, 0, 5);
	enemy[9] = new Player(900, 0, 5);
	*/
	
	/*
	for (int i = 0; i < 10; i++) {
		enemy[i]->SetRandomCurrentX();
		enemy[i]->SetRandomCurrentY();
		enemy[i]->SetRandomDesX();
		enemy[i]->SetRandomDesY();
	}
	*/


}

CGAME_PROJECTView::~CGAME_PROJECTView()
{
}

BOOL CGAME_PROJECTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGAME_PROJECTView 그리기

void CGAME_PROJECTView::OnDraw(CDC* pDC)
{
	CGAME_PROJECTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	int stageBit[10] = {
		IDB_Stage1,
		IDB_Stage2,
		IDB_Stage3,
		IDB_Stage4,
		IDB_Stage5,
		IDB_Stage6,
		IDB_Stage7,
		IDB_Stage8,
		IDB_Stage9,
		IDB_Stage10,
	};

	int enemyBit[9] = {
		IDB_enemy1,
		IDB_enemy2,
		IDB_enemy3,
		IDB_enemy4,
		IDB_enemy5,
		IDB_enemy6,
		IDB_enemy7,
		IDB_enemy8,
		IDB_enemy9,
	};
	
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.LoadBitmapW(stageBit[stageNum]); // 스테이지 읽어옴

	BITMAP bmpInfo;
	bitmap.GetBitmap(&bmpInfo);

	CBitmap *pOld = memDC.SelectObject(&bitmap);

	CRect rect;
	GetClientRect(&rect);

	//스테이지 출력
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 320, 160, SRCCOPY);

	memDC.SelectObject(pOld);
	bitmap.DeleteObject();

	// 플레이어 읽어옴
	bitmap.LoadBitmapW(IDB_Player1); 
	bitmap.GetBitmap(&bmpInfo);

	pOld = memDC.SelectObject(&bitmap);

	//플레이어 출력 & 플레이어 좌우 방향 및 걷는 모션
	if (player->isRight == TRUE) {
		if (player->isMotion == TRUE)
			pDC->TransparentBlt(player->current_x, player->current_y, 70, 70, &memDC, 0, 48 * 2, 48, 48, RGB(247, 0, 255));
		else
			pDC->TransparentBlt(player->current_x, player->current_y, 70, 70, &memDC, 48, 48 * 2, 48, 48, RGB(247, 0, 255));
	}

	else {
		if (player->isMotion == TRUE)
			pDC->TransparentBlt(player->current_x, player->current_y, 70, 70, &memDC, 0, 48, 48, 48, RGB(247, 0, 255));
		else
			pDC->TransparentBlt(player->current_x, player->current_y, 70, 70, &memDC, 48, 48, 48, 48, RGB(247, 0, 255));
	}

	memDC.SelectObject(pOld);
	bitmap.DeleteObject();

	//적 읽어옴

	for (int i = 0; i < gameType; i++) {

		bitmap.LoadBitmapW(enemyBit[stageNum]);
		bitmap.GetBitmap(&bmpInfo);

		pOld = memDC.SelectObject(&bitmap);

		if (enemy[i]->isRight == TRUE) {
			if (enemy[i]->isMotion == TRUE) {
				pDC->TransparentBlt(enemy[i]->current_x, enemy[i]->current_y, 70, 70, &memDC, 0, 48 * 2, 48, 48, RGB(247, 0, 255));
			}
			else {
				pDC->TransparentBlt(enemy[i]->current_x, enemy[i]->current_y, 70, 70, &memDC, 48, 48 * 2, 48, 48, RGB(247, 0, 255));
			}
		}

		else {
			if (enemy[i]->isMotion == TRUE) {
				pDC->TransparentBlt(enemy[i]->current_x, enemy[i]->current_y, 70, 70, &memDC, 0, 48, 48, 48, RGB(247, 0, 255));
			}
			else {
				pDC->TransparentBlt(enemy[i]->current_x, enemy[i]->current_y, 70, 70, &memDC, 48, 48, 48, 48, RGB(247, 0, 255));
			}
		}
		memDC.SelectObject(pOld);
		bitmap.DeleteObject();
	}
}


// CGAME_PROJECTView 인쇄

BOOL CGAME_PROJECTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGAME_PROJECTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGAME_PROJECTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGAME_PROJECTView 진단

#ifdef _DEBUG
void CGAME_PROJECTView::AssertValid() const
{
	CView::AssertValid();
}

void CGAME_PROJECTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGAME_PROJECTDoc* CGAME_PROJECTView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGAME_PROJECTDoc)));
	return (CGAME_PROJECTDoc*)m_pDocument;
}
#endif //_DEBUG


// CGAME_PROJECTView 메시지 처리기


void CGAME_PROJECTView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);

	if (((rect.Height() - 100) / 2) > point.y) return;

	mx = point.x - 32;
	my = point.y - 48;

	player->SetDestination(mx, my);

	SetTimer(100, 70, NULL);
	SetTimer(101, 70, NULL);

	CView::OnRButtonDown(nFlags, point);
}


void CGAME_PROJECTView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nIDEvent) {

	case 100: //주인공 캐릭터 움직임
		player->Move();
		if (player->isArrive()) {
			KillTimer(100);
		}
		break;

	case 101: //player 걷는 모션

		if (player->isArrive()) {
			KillTimer(101);
		}

		player->Motion();

		break;

	case 200:
		
		for (int i = 0; i < gameType; i++) {

			enemy[i]->Move();
			//if (enemy[i]->isArrive())
				//KillTimer(200);
		}
		break;

	case 201:
		for (int i = 0; i < gameType; i++) {
			if (enemy[i]->isArrive()) {}
			else enemy[i]->Motion();
		}
		break;

	case 300:
		int rx[10];
		int ry[10];

		for (int i = 0; i < 10; i++) {
			rx[i] = rand() % 1000;
			ry[i] = rand() % 300 + 300;
		}

		for (int i = 0; i < 10; i++) {
			enemy[i]->SetDestination(rx[i], ry[i]);
			Invalidate(FALSE);
		}

		
		break;

	case 400:
		if (stageNum == 9) KillTimer(400);
		else {
			stageNum++;
			for (int i = 0; i < 10; i++) {
				enemy[i]->spd + 5;
			}
		}
	}




	Invalidate(FALSE); // FASLE로 설정해야 바뀐 부분만 업데이트되어 깜빡임이 방지됨

	CView::OnTimer(nIDEvent);
}

// 화면 업데이트
void CGAME_PROJECTView::Update()
{

}



void CGAME_PROJECTView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);
}


void CGAME_PROJECTView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nChar) {

	case VK_RETURN:
		SetTimer(200, 70, NULL);
		SetTimer(201, 200, NULL);
		SetTimer(300, 2500, NULL);
		SetTimer(400, 10000, NULL);
		break;
	}

	Invalidate(FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CGAME_PROJECTView::GetRandomNum(int range)
{
	return rand() % range;
}
