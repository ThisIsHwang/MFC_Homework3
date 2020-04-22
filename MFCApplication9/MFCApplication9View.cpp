
// MFCApplication9View.cpp: CMFCApplication9View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication9.h"
#endif

#include "MFCApplication9Doc.h"
#include "MFCApplication9View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication9View

IMPLEMENT_DYNCREATE(CMFCApplication9View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication9View, CView)
    ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_MOUSEMOVE()
	
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_NEW, &CMFCApplication9View::OnFileNew)
END_MESSAGE_MAP()

// CMFCApplication9View 생성/소멸

CMFCApplication9View::CMFCApplication9View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApplication9View::~CMFCApplication9View()
{
}

BOOL CMFCApplication9View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication9View 그리기

void CMFCApplication9View::OnDraw(CDC* pDC)
{
	CMFCApplication9Doc* pDoc = GetDocument();


	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for (int i = 0; i < pDoc->mStrLineCnt; i++) {
		pDC->MoveTo(**(*(pDoc->mStrLine + i) + 0));
		pDC->LineTo(**(*(pDoc->mStrLine + i) + 1));
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (int i = 0; i < pDoc->mFreeLineCnt; i++)
		for (int j = 0; j <pDoc->mFreeLineNum[i] - 1 ; j++) {
			pDC->MoveTo(*(*(pDoc->mFreeLine + i) + j));
			pDC->LineTo(*(*(pDoc->mFreeLine + i) + j + 1));
		}
}


// CMFCApplication9View 진단

#ifdef _DEBUG
void CMFCApplication9View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication9View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication9Doc* CMFCApplication9View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication9Doc)));
	return (CMFCApplication9Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication9View 메시지 처리기


void CMFCApplication9View::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCApplication9Doc* pDoc = GetDocument();
	pDoc->mFreeDotCnt = 0;
	pDoc->mFreeLine[pDoc->mFreeLineCnt][pDoc->mFreeDotCnt++] = point;
    CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication9View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCApplication9Doc* pDoc = GetDocument();
	if (pDoc->mFreeLineCnt < 100) {
		pDoc->mFreeLineNum[pDoc->mFreeLineCnt] = pDoc->mFreeDotCnt;
		pDoc->mFreeLineCnt++;
	} 
	CView::OnLButtonUp(nFlags, point);
}



void CMFCApplication9View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CMFCApplication9Doc* pDoc = GetDocument();
	if (pDoc->mFreeDotCnt < 10000 && nFlags & MK_LBUTTON) {
		dc.MoveTo(pDoc->mFreeLine[pDoc->mFreeLineCnt][pDoc->mFreeDotCnt-1]);
		dc.LineTo(point);
		pDoc->mFreeLine[pDoc->mFreeLineCnt][pDoc->mFreeDotCnt++] = point;
	}
	CView::OnMouseMove(nFlags, point);
	
}





void CMFCApplication9View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCApplication9Doc* pDoc = GetDocument();
	pDoc->mStrStart = new CPoint(point);
	CView::OnRButtonDown(nFlags, point);
}


void CMFCApplication9View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCApplication9Doc* pDoc = GetDocument();
	pDoc->mStrEnd = new CPoint(point);
	CClientDC dc(this);
	dc.MoveTo(*pDoc->mStrStart);
	dc.LineTo(*pDoc->mStrEnd);
	//*(*(pDoc->mStrLine + pDoc->mStrLineCnt))= pDoc->mStrStart;
	pDoc->mStrLine[pDoc->mStrLineCnt][0] = pDoc->mStrStart;
	pDoc->mStrLine[pDoc->mStrLineCnt][1] = pDoc->mStrEnd;
	pDoc->mStrLineCnt++;
	CView::OnRButtonUp(nFlags, point);
}


void CMFCApplication9View::OnFileNew()
{
	CMFCApplication9Doc* pDoc = GetDocument();
	for (int i = 0; i < pDoc->mStrLineCnt; i++) {
		delete *(*(pDoc->mStrLine + i) + 0);
		delete *(*(pDoc->mStrLine + i) + 1);
	}

	pDoc->mFreeLineCnt = 0;
	pDoc->mFreeDotCnt = 0;
	pDoc->mStrLineCnt = 0;
	memset(pDoc->mFreeLineNum, 0, sizeof(pDoc->mFreeLineNum));
	memset(pDoc->mFreeLine, 0, sizeof(pDoc->mFreeLine));
	memset(pDoc->mStrLine, 0, sizeof(pDoc->mStrLine));
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
