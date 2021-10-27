// MainFrm.cpp : implementation of the MainFrame class
//

#include "pch.h"
#include "framework.h"
#include "GRE.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// MainFrame construction/destruction

MainFrame::MainFrame() noexcept
{
	// TODO: add member initialization code here
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_SYSMENU;
	
	int width = 400;
	int height = 372;
	int xpos = 10;
	int ypos = GetSystemMetrics(SM_CYFULLSCREEN) - height;
	cs.x = xpos;
	cs.y = ypos;
	cs.cx = width;
	cs.cy = height;

	return TRUE;
}

// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// MainFrame message handlers
