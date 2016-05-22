
// GAME_PROJECTView.h : CGAME_PROJECTView 클래스의 인터페이스
//

#pragma once

class CGAME_PROJECTView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGAME_PROJECTView();
	DECLARE_DYNCREATE(CGAME_PROJECTView)

// 특성입니다.
public:
	CGAME_PROJECTDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGAME_PROJECTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	int mx;
	int my;
	int spd;
	int dx;
	int dy;
	bool isRight;
	bool motion;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 화면 업데이트
	void Update();
	int stageNum;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int gameType;
	Player *player;
	Player *enemy[10];
	int GetRandomNum(int range);
};

#ifndef _DEBUG  // GAME_PROJECTView.cpp의 디버그 버전
inline CGAME_PROJECTDoc* CGAME_PROJECTView::GetDocument() const
   { return reinterpret_cast<CGAME_PROJECTDoc*>(m_pDocument); }
#endif

