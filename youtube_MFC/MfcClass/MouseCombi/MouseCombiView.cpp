
// MouseCombiView.cpp : CMouseCombiView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MouseCombi.h"
#endif

#include "MouseCombiDoc.h"
#include "MouseCombiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseCombiView

IMPLEMENT_DYNCREATE(CMouseCombiView, CView)

BEGIN_MESSAGE_MAP(CMouseCombiView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMouseCombiView 생성/소멸

CMouseCombiView::CMouseCombiView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_ptItemText = CPoint(10, 30);
	m_bDragFlag = false;
}

CMouseCombiView::~CMouseCombiView()
{
}

BOOL CMouseCombiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMouseCombiView 그리기

void CMouseCombiView::OnDraw(CDC* /*pDC*/)
{
	CMouseCombiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMouseCombiView 인쇄

BOOL CMouseCombiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMouseCombiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMouseCombiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMouseCombiView 진단

#ifdef _DEBUG
void CMouseCombiView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseCombiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseCombiDoc* CMouseCombiView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseCombiDoc)));
	return (CMouseCombiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseCombiView 메시지 처리기


void CMouseCombiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x >= m_ptItemText.x - 32 && point.x <= m_ptItemText.x + 32 &&
		point.y >= m_ptItemText.y - 32 && point.y <= m_ptItemText.y + 32)
	{
		m_bDragFlag = true;
		RedrawWindow();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMouseCombiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDragFlag)
	{
		m_bDragFlag = false;
		m_ptItemText = point;
		RedrawWindow();
		ReleaseCapture(); // 화면 밖으로도 드래그 가능하도록 함
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMouseCombiView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDblClk(nFlags, point);
}


void CMouseCombiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	if (m_bDragFlag)
		dc.TextOut(10, 10, _T("DRAG"));
	else
		dc.TextOut(10, 10, _T("----"));

	dc.TextOut(m_ptItemText.x, m_ptItemText.y, _T("내 컴퓨터"));
}


void CMouseCombiView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragFlag)
	{
		if (point.x >= 0 && point.y >= 0)
		{
			m_ptItemText = point;
			RedrawWindow();
		}
		else
			m_bDragFlag = false;
	}

	CView::OnMouseMove(nFlags, point);
}


int CMouseCombiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndTrack.Create(_T("STATIC"), _T("TRACK TEST"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | SS_NOTIFY,
					CRect(100, 10, 250, 160), this, 1234);

	return 0;
}
