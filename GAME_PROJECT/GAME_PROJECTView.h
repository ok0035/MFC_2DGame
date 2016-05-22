
// GAME_PROJECTView.h : CGAME_PROJECTView Ŭ������ �������̽�
//

#pragma once

class CGAME_PROJECTView : public CView
{
protected: // serialization������ ��������ϴ�.
	CGAME_PROJECTView();
	DECLARE_DYNCREATE(CGAME_PROJECTView)

// Ư���Դϴ�.
public:
	CGAME_PROJECTDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGAME_PROJECTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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
	// ȭ�� ������Ʈ
	void Update();
	int stageNum;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int gameType;
	Player *player;
	Player *enemy[10];
	int GetRandomNum(int range);
};

#ifndef _DEBUG  // GAME_PROJECTView.cpp�� ����� ����
inline CGAME_PROJECTDoc* CGAME_PROJECTView::GetDocument() const
   { return reinterpret_cast<CGAME_PROJECTDoc*>(m_pDocument); }
#endif

