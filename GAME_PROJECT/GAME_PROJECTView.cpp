
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
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_32771, &CGAME_PROJECTView::On32771)
	ON_COMMAND(ID_32772, &CGAME_PROJECTView::On32772)
	ON_COMMAND(ID_32773, &CGAME_PROJECTView::On32773)
END_MESSAGE_MAP()

// CGAME_PROJECTView 생성/소멸


CGAME_PROJECTView::CGAME_PROJECTView()
	: mx(0)
	, my(0)
	, spd(10)
	, dx(5)
	, dy(5)
	, isRight(false)
	, motion(false)
	, stageNum(0)
	, gameType(8)
	, player(NULL)
	, isClear(false)
	, remainTime(10)
	, playTime(10)
	, isNextStage(false)
	, isPause(false)
	, isFirstStage(true)
	, isEnd(false)
	, moveTime(2500)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));

	player = new Player(480, 450, spd);

	int rx[14];
	int ry[14];

	for (int i = 0; i < 4; i++) {
		rx[i] = rand() % 500;
		ry[i] = rand() % 300 + 300;
	}

	for (int i = 4; i < 8; i++) {
		rx[i] = rand() % 500 + 450;
		ry[i] = rand() % 300 + 300;
	}

	for (int i = 8; i < 14; i++) {
		rx[i] = rand() % 500 + 200;
		ry[i] = rand() % 300 + 300;
	}

	//왼편
	enemy[0] = new Player(20, 300, 4);
	enemy[1] = new Player(220, 380, 4);
	enemy[2] = new Player(20, 460, 4);
	enemy[3] = new Player(220, 540, 4);

	//오른편
	enemy[4] = new Player(700, 600, 4);
	enemy[5] = new Player(900, 300, 4);
	enemy[6] = new Player(700, 380, 4);
	enemy[7] = new Player(900, 460, 4);


	//중간
	enemy[8] = new Player(250, 380, 4);
	enemy[9] = new Player(250, 460, 4);
	enemy[10] = new Player(610, 380, 4);
	enemy[11] = new Player(610, 460, 4);
	enemy[12] = new Player(610, 300, 4);
	enemy[13] = new Player(250, 300, 4);


	for (int i = 0; i < gameType; i++) {
		enemy[i]->SeePlayer();
		enemy[i]->SetDestination(rx[i], ry[i]);
	}

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
	
	//스테이지 비트맵 이미지 저장
	int stageBit[12] = {
		IDB_MAIN,
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
		IDB_END,
	};

	//적 비트맵 이미지 저장
	int enemyBit[10] = {
		IDB_enemy1,
		IDB_enemy2,
		IDB_enemy3,
		IDB_enemy4,
		IDB_enemy5,
		IDB_enemy6,
		IDB_enemy7,
		IDB_enemy8,
		IDB_enemy9,
		IDB_Player1,
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

	CFont Font, *oldFont;

	//스테이지 출력
	if (isFirstStage || isEnd)
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 1000, 800, SRCCOPY);
	else 
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 320, 160, SRCCOPY);

	memDC.SelectObject(pOld);
	bitmap.DeleteObject();

	if (isFirstStage || isEnd) return;

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

		bitmap.LoadBitmapW(enemyBit[stageNum-1]);
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


	//충돌 체크
	for (int i = 0; i < gameType; i++) {
		CRect rcPlayer(player->current_x+8, player->current_y+2, player->current_x + 40, player->current_y + 35);
		CRect rcEnemy(enemy[i]->current_x+8, enemy[i]->current_y+2, enemy[i]->current_x + 40, enemy[i]->current_y + 35);
		CRect isHit;

		if (isHit.IntersectRect(&rcPlayer, &rcEnemy)) {
			KillTimer(100);
			KillTimer(101);
			KillTimer(200);
			KillTimer(201);
			KillTimer(300);
			KillTimer(400);

			Sleep(500);

			Font.CreateFont(30, 30, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Fixedsys");

			oldFont = pDC->SelectObject(&Font);

			wchar_t strGameOver[20];
			wsprintf(strGameOver, L"Game Over");
			pDC->TextOut(380, 400, strGameOver);

			pDC->SelectObject(oldFont);
			Font.DeleteObject();

			break;
		}
	}

	//시간표시
	Font.CreateFont(30,30,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Fixedsys");

	SetBkMode(*pDC, TRANSPARENT);
	SetTextColor(*pDC, RGB(255, 255, 255));
	oldFont = pDC->SelectObject(&Font);

	wchar_t strRemain[32];
	wsprintf(strRemain, L"스테이지: %02d 남은 시간 %02d", stageNum, remainTime);
	pDC->TextOut(20, 20, strRemain);

	pDC->SelectObject(oldFont);
	Font.DeleteObject();

	//스테이지 클리어
	if (isNextStage) {

		Font.CreateFont(30,30,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Fixedsys");


		oldFont = pDC->SelectObject(&Font);

		wchar_t strStage[10];
		wsprintf(strStage, L"Stage %d", stageNum);
		pDC->TextOut(400, 400, strStage);

		pDC->SelectObject(oldFont);
		Font.DeleteObject();

		Sleep(3000);

		Font.CreateFont(30, 30, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Fixedsys");

		oldFont = pDC->SelectObject(&Font);

		wchar_t strStart[10];
		wsprintf(strStart, L"Start!!");
		pDC->TextOut(400, 450, strStart);

		pDC->SelectObject(oldFont);
		Font.DeleteObject();

		isClear = FALSE;

		Sleep(1000);

		mx = 450;
		my = 450;
		player->SetDestination(mx, my);

		isNextStage = FALSE;

		Sleep(1000);

		isPause = FALSE;
	}

	if (isClear == TRUE) {

		stageNum++;
		if(stageNum == 11) isEnd = true;

		Font.CreateFont(30, 30, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Fixedsys");

		oldFont = pDC->SelectObject(&Font);

		wchar_t strClear[20];
		wsprintf(strClear, L"Clear!!");
		pDC->TextOut(400, 400, strClear);

		pDC->SelectObject(oldFont);
		Font.DeleteObject();

		for (int i = 0; i < gameType; i++) {
			enemy[i]->spd += 1;
		}
		player->spd += 1;

		if (stageNum >= 5 && gameType < 14) {
			gameType++;
			playTime += 5;
		}

		moveTime -= 200;

		InitPoint();

		Sleep(3000);

		isNextStage = TRUE;

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

	if (isPause == FALSE && isClear == FALSE && isNextStage == FALSE) {

		if (((rect.Height() - 100) / 2) > point.y) {
			mx = point.x - 32;
			player->des_x = mx;
		}

		else {
			mx = point.x - 32;
			my = point.y - 48;
			player->SetDestination(mx, my);
		}

		SetTimer(100, 70, NULL);
		SetTimer(101, 70, NULL);

	}

	else {
		mx = 450;
		my = 450;
		player->SetDestination(mx, my);
		Invalidate(FALSE);
	}

	Invalidate(FALSE);
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

	case 200: //적 움직임

		for (int i = 0; i < gameType; i++) {
			enemy[i]->Move();
		}
		break;

	case 201: // 적 이동모션
		for (int i = 0; i < gameType; i++) {
			if (enemy[i]->isArrive()) {}
			else enemy[i]->Motion();
		}
		break;

	case 300: // 적 목적지 설정
		int rx[14];
		int ry[14];
		int ran_tracking;

		for (int i = 0; i < 4; i++) {
			rx[i] = rand() % 500;
			ry[i] = rand() % 300 + 300;
		}

		for (int i = 4; i < 8; i++) {
			rx[i] = rand() % 500 + 450;
			ry[i] = rand() % 300 + 300;
		}

		for (int i = 8; i < 14; i++) {
			rx[i] = rand() % 500 + 200;
			ry[i] = rand() % 300 + 300;
		}


		for (int i = 0; i < gameType; i++) {
			if(enemy[i]->current_x == enemy[i]->des_x && enemy[i]->current_y == enemy[i]->des_y)
				enemy[i]->SetDestination(rx[i], ry[i]);
		}

		ran_tracking = rand() % 14;
		enemy[ran_tracking]->SetDestination(player->current_x, player->current_y);


		break;

	case 400: // 스테이지 이동
		if (stageNum == 11) {
			KillTimer(200);
			KillTimer(201);
			KillTimer(300);
			KillTimer(400);
			
		}
		else {

			if (remainTime <= 0) {

				remainTime = playTime;

				isClear = TRUE;
				isPause = TRUE;
				player->SetDestination(450, 450);

			}
			else remainTime--;
		}
		break;
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
		SetTimer(300, moveTime, NULL);
		SetTimer(400, 1000, NULL);
		isPause = FALSE;
		if (isFirstStage) {
			isNextStage = TRUE;
			stageNum++;
			isFirstStage = FALSE;
		}
		break;
	}

	Invalidate(FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CGAME_PROJECTView::GetRandomNum(int range)
{
	return rand() % range;
}


void CGAME_PROJECTView::InitPoint()
{
	//캐릭터 위치 초기화

	enemy[0]->SetCurrentPoint(20, 300);
	enemy[1]->SetCurrentPoint(220, 380);
	enemy[2]->SetCurrentPoint(20, 460);
	enemy[3]->SetCurrentPoint(220, 540);

	enemy[4]->SetCurrentPoint(900, 300);
	enemy[5]->SetCurrentPoint(700, 380);
	enemy[6]->SetCurrentPoint(900, 460);
	enemy[7]->SetCurrentPoint(700, 540);
	
	enemy[8]->SetCurrentPoint(250, 380);
	enemy[9]->SetCurrentPoint(250, 460);
	enemy[10]->SetCurrentPoint(610, 380);
	enemy[11]->SetCurrentPoint(610, 460);
	enemy[12]->SetCurrentPoint(250, 600);
	enemy[13]->SetCurrentPoint(900, 600);

	player->SetCurrentPoint(480, 450);
}


BOOL CGAME_PROJECTView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	return TRUE;
}


void CGAME_PROJECTView::On32771()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 새게임

	KillTimer(200);
	KillTimer(201);
	KillTimer(300);
	KillTimer(400);

	for (int i = 0; i < 14; i++) {
		enemy[i]->spd = 4;
	}

	player->spd = spd;

	InitPoint();
	player->current_x = 450;
	player->current_y = 450;

	remainTime = playTime;
	stageNum = 0;
	gameType = 8;
	isPause = TRUE;
	isFirstStage = true;
	isEnd = false;
	
	Invalidate(FALSE);
}


void CGAME_PROJECTView::On32772()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 일시정지

	KillTimer(200);
	KillTimer(201);
	KillTimer(300);
	KillTimer(400);

	isPause = TRUE;

	Invalidate(FALSE);

}


void CGAME_PROJECTView::On32773()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 계속하기

	SetTimer(200, 70, NULL);
	SetTimer(201, 200, NULL);
	SetTimer(300, moveTime, NULL);
	SetTimer(400, 1000, NULL);

	isPause = FALSE;

	Invalidate(FALSE);
}
