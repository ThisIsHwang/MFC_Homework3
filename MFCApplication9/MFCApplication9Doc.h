
// MFCApplication9Doc.h: CMFCApplication9Doc 클래스의 인터페이스
//


#pragma once


class CMFCApplication9Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication9Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication9Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	CPoint mFreeLine[100][10000]; 
	int mFreeLineNum[100]; // 선들의 길이 저장
	int mFreeLineCnt; // 현재 선의 수 저장
	int mFreeDotCnt; // 현재 선의 길이 저장

	CPoint* mStrLine[100][2];
	CPoint* mStrStart;
	CPoint* mStrEnd;
	int mStrLineCnt;

	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCApplication9Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
