
// MFCApplication9Doc.cpp: CMFCApplication9Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "MFCApplication9.h"
#endif

#include "MFCApplication9Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication9Doc

IMPLEMENT_DYNCREATE(CMFCApplication9Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication9Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication9Doc 생성/소멸

CMFCApplication9Doc::CMFCApplication9Doc() noexcept : mFreeLineCnt(0), mFreeDotCnt(0), mStrLineCnt(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	memset(mFreeLineNum, 0, sizeof(mFreeLineNum));
	memset(mFreeLine, 0, sizeof(mFreeLine));
	memset(mStrLine, 0, sizeof(mStrLine));
}

CMFCApplication9Doc::~CMFCApplication9Doc()
{
	for (int i = 0; i < mStrLineCnt; i++) {
		delete *(*(mStrLine + i) + 0);
		delete *(*(mStrLine + i) + 1);
	}
}

BOOL CMFCApplication9Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCApplication9Doc serialization

void CMFCApplication9Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		AfxMessageBox(L"save");
		ar << mFreeLineCnt;
		for (int i = 0; i < mFreeLineCnt; i++)
			ar << mFreeLineNum[i];
		for (int i = 0; i < mFreeLineCnt; i++)
			for (int j = 0; j < mFreeLineNum[i] ; j++) 
				ar << mFreeLine[i][j];
		
		ar << mStrLineCnt;
		for (int i = 0; i < mStrLineCnt; i++) {
			ar << *mStrLine[i][0];
			ar << *mStrLine[i][1];
		}
	}
	else
	{
		for (int i = 0; i < mStrLineCnt; i++) {
			delete* (*(mStrLine + i) + 0);
			delete* (*(mStrLine + i) + 1);
		}
		memset(mFreeLineNum, 0, sizeof(mFreeLineNum));
		memset(mFreeLine, 0, sizeof(mFreeLine));
		memset(mStrLine, 0, sizeof(mStrLine));

		ar >> mFreeLineCnt;
		for (int i = 0; i < mFreeLineCnt; i++)
			ar >> mFreeLineNum[i];
		for (int i = 0; i < mFreeLineCnt; i++)
			for (int j = 0; j < mFreeLineNum[i]; j++)
				ar >> mFreeLine[i][j];
		
		ar >> mStrLineCnt;
		for (int i = 0; i < mStrLineCnt; i++) {
			CPoint* p = new CPoint();
			CPoint* p2 = new CPoint();
			ar >> *p;
			mStrLine[i][0] = p;
			ar >> *p2;
			mStrLine[i][1] = p2;
		}
		UpdateAllViews(NULL);
		AfxMessageBox(L"load");
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplication9Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCApplication9Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication9Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication9Doc 진단

#ifdef _DEBUG
void CMFCApplication9Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication9Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication9Doc 명령
