
// GAME_PROJECTDoc.h : CGAME_PROJECTDoc Ŭ������ �������̽�
//


#pragma once


class CGAME_PROJECTDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGAME_PROJECTDoc();
	DECLARE_DYNCREATE(CGAME_PROJECTDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CGAME_PROJECTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};