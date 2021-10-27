// GREView.cpp : implementation of the GREView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GRE.h"
#endif

#include "GREDoc.h"
#include "GREView.h"
	
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// GREView

IMPLEMENT_DYNCREATE(GREView, CFormView)

BEGIN_MESSAGE_MAP(GREView, CFormView)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_PLAYBACK_MODE, &GREView::OnUpdatePlaybackMode)

	ON_UPDATE_COMMAND_UI(ID_SETTINGS_ALWAYSONTOP, &GREView::OnUpdateSettingsAlwaysOnTop)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_AUDIO, &GREView::OnUpdateSettingsAudio)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_SHUFFLE, &GREView::OnUpdateSettingsShuffle)
	ON_UPDATE_COMMAND_UI(ID_FRONTSPEED_5SEC, &GREView::OnUpdateFrontSpeed5sec)
	ON_UPDATE_COMMAND_UI(ID_FRONTSPEED_10SEC, &GREView::OnUpdateFrontSpeed10sec)
	ON_UPDATE_COMMAND_UI(ID_BACKSPEED_5SEC, &GREView::OnUpdateBackSpeed5sec)
	ON_UPDATE_COMMAND_UI(ID_BACKSPEED_10SEC, &GREView::OnUpdateBackSpeed10sec)
	ON_UPDATE_COMMAND_UI(ID_BACKSPEED_15SEC, &GREView::OnUpdateBackSpeed15sec)
	ON_UPDATE_COMMAND_UI(ID_BACKSPEED_30SEC, &GREView::OnUpdateBackSpeed30sec)
	
	ON_UPDATE_COMMAND_UI(ID_CARDS_ALL, &GREView::OnUpdateCardsAll)
	ON_UPDATE_COMMAND_UI(ID_COMMON_ALL, &GREView::OnUpdateCommonAll)
	ON_UPDATE_COMMAND_UI(ID_BASIC_ALL, &GREView::OnUpdateBasicAll)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ALL, &GREView::OnUpdateAdvancedAll)
	ON_UPDATE_COMMAND_UI(ID_COMMON_COMMONI, &GREView::OnUpdateCommonI)
	ON_UPDATE_COMMAND_UI(ID_COMMON_COMMONII, &GREView::OnUpdateCommonII)
	ON_UPDATE_COMMAND_UI(ID_COMMON_COMMONIII, &GREView::OnUpdateCommonIII)
	ON_UPDATE_COMMAND_UI(ID_COMMON_COMMONIV, &GREView::OnUpdateCommonIV)
	ON_UPDATE_COMMAND_UI(ID_COMMON_COMMONV, &GREView::OnUpdateCommonV)
	ON_UPDATE_COMMAND_UI(ID_COMMON_COMMONVI, &GREView::OnUpdateCommonVI)
	ON_UPDATE_COMMAND_UI(ID_BASIC_BASICI, &GREView::OnUpdateBasicI)
	ON_UPDATE_COMMAND_UI(ID_BASIC_BASICII, &GREView::OnUpdateBasicII)
	ON_UPDATE_COMMAND_UI(ID_BASIC_BASICIII, &GREView::OnUpdateBasicIII)
	ON_UPDATE_COMMAND_UI(ID_BASIC_BASICIV, &GREView::OnUpdateBasicIV)
	ON_UPDATE_COMMAND_UI(ID_BASIC_BASICV, &GREView::OnUpdateBasicV)
	ON_UPDATE_COMMAND_UI(ID_BASIC_BASICVI, &GREView::OnUpdateBasicVI)
	ON_UPDATE_COMMAND_UI(ID_BASIC_BASICVII, &GREView::OnUpdateBasicVII)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ADVANCEDI, &GREView::OnUpdateAdvancedI)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ADVANCEDII, &GREView::OnUpdateAdvancedII)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ADVANCEDIII, &GREView::OnUpdateAdvancedIII)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ADVANCEDIV, &GREView::OnUpdateAdvancedIV)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ADVANCEDV, &GREView::OnUpdateAdvancedV)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ADVANCEDVI, &GREView::OnUpdateAdvancedVI)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ADVANCEDVII, &GREView::OnUpdateAdvancedVII)
END_MESSAGE_MAP()

// GREView construction/destruction

GREView::GREView() noexcept
	: CFormView(IDD_GRE_FORM)
{
	rc.left = rc.right = rc.top = rc.bottom = 0;
}

GREView::~GREView()
{
}

void GREView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL GREView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void GREView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	adjust_window_size();
	::SetWindowPos(
		AfxGetMainWnd()->m_hWnd,
		(GetDocument()->always_on_top) ? HWND_TOPMOST : HWND_NOTOPMOST,
		0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

	GREDoc* pDoc = GetDocument();
	frontFont.CreatePointFont(200, L"Times News Roman");
	GetDlgItem(IDC_CARD_FRONT)->SetFont(&frontFont);
	backFont.CreatePointFont(pDoc->font_size, L"Times News Roman");
	GetDlgItem(IDC_CARD_BACK)->SetFont(&backFont);

	pDoc->audioTrd = std::thread(audio_trd_process, pDoc);
	pDoc->set_title();
	pDoc->init_timer();
}


// GREView diagnostics

#ifdef _DEBUG
void GREView::AssertValid() const
{
	CFormView::AssertValid();
}

void GREView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

GREDoc* GREView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(GREDoc)));
	return (GREDoc*)m_pDocument;
}
#endif //_DEBUG


// GREView message handlers

void GREView::show_front()
{
	GREDoc* pDoc = GetDocument();
	show_msg(IDC_CARD_FRONT, pDoc->db->get_front());
	show_msg(IDC_CARD_BACK, "");
	pDoc->thread_play_audio = true;
}
void GREView::show_back()
{
	GREDoc* pDoc = GetDocument();
	show_msg(IDC_CARD_BACK, pDoc->db->get_back());
	pDoc->thread_play_audio = true;
}
void GREView::show_msg(int nID, std::string msg)
{
	std::wstring wmsg(msg.begin(), msg.end());
	GetDlgItem(nID)->SetWindowTextW(wmsg.c_str());
}
void GREView::adjust_font_size()
{
	GREDoc* pDoc = GetDocument();
	backFont.CreatePointFont(pDoc->font_size, L"Times News Roman");
	GetDlgItem(IDC_CARD_BACK)->SetFont(&backFont);
}
void GREView::adjust_window_size()
{
	int width = 400;
	GREDoc* pDoc = GetDocument();
	AfxGetMainWnd()->GetWindowRect(&rc);
	rc.right = rc.left + width + pDoc->horizontal_size * 50;
	AfxGetMainWnd()->MoveWindow(&rc);
}

void GREView::OnTimer(UINT_PTR nIDEvent)
{
	GREDoc* pDoc = GetDocument();
	if (nIDEvent == IDT_TIMER1)
	{
		show_back();
		pDoc->set_time_back();
	}
	else if (nIDEvent == IDT_TIMER2)
	{
		pDoc->db->next_index();
		show_front();
		pDoc->set_time_front();
	}
	CFormView::OnTimer(nIDEvent);
}
void GREView::OnUpdatePlaybackMode(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	if (pDoc->play_cards)
		pCmdUI->SetText(L"&Pause\tSpace");
	else
		pCmdUI->SetText(L"&Play\tSpace");
	pCmdUI->SetCheck(pDoc->play_cards);
}

void GREView::OnUpdateSettingsAudio(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->audio);
}
void GREView::OnUpdateSettingsShuffle(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->shuffle);
}
void GREView::OnUpdateSettingsAlwaysOnTop(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->always_on_top);
}
void GREView::OnUpdateFrontSpeed5sec(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->time_front == 5);
}
void GREView::OnUpdateFrontSpeed10sec(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->time_front == 10);
}
void GREView::OnUpdateBackSpeed5sec(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->time_back == 5);
}
void GREView::OnUpdateBackSpeed10sec(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->time_back == 10);
}
void GREView::OnUpdateBackSpeed15sec(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->time_back == 15);
}
void GREView::OnUpdateBackSpeed30sec(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->time_back == 30);
}

void GREView::OnUpdateCardsAll(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ALL);
}
void GREView::OnUpdateCommonAll(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::COMMON && pDoc->db->group == DIFG::ALL);
}
void GREView::OnUpdateBasicAll(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::ALL);
}
void GREView::OnUpdateAdvancedAll(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::ALL);
}
void GREView::OnUpdateCommonI(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::COMMON && pDoc->db->group == DIFG::I);
}
void GREView::OnUpdateCommonII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::COMMON && pDoc->db->group == DIFG::II);
}
void GREView::OnUpdateCommonIII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::COMMON && pDoc->db->group == DIFG::III);
}
void GREView::OnUpdateCommonIV(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::COMMON && pDoc->db->group == DIFG::IV);
}
void GREView::OnUpdateCommonV(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::COMMON && pDoc->db->group == DIFG::V);
}
void GREView::OnUpdateCommonVI(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::COMMON && pDoc->db->group == DIFG::VI);
}
void GREView::OnUpdateBasicI(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::I);
}
void GREView::OnUpdateBasicII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::II);
}
void GREView::OnUpdateBasicIII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::III);
}
void GREView::OnUpdateBasicIV(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::IV);
}
void GREView::OnUpdateBasicV(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::V);
}
void GREView::OnUpdateBasicVI(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::VI);
}
void GREView::OnUpdateBasicVII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::BASIC && pDoc->db->group == DIFG::VII);
}
void GREView::OnUpdateAdvancedI(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::I);
}
void GREView::OnUpdateAdvancedII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::II);
}
void GREView::OnUpdateAdvancedIII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::III);
}
void GREView::OnUpdateAdvancedIV(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::IV);
}
void GREView::OnUpdateAdvancedV(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::V);
}
void GREView::OnUpdateAdvancedVI(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::VI);
}
void GREView::OnUpdateAdvancedVII(CCmdUI* pCmdUI)
{
	GREDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->db->dif == DIF::ADVANCED && pDoc->db->group == DIFG::VII);
}
