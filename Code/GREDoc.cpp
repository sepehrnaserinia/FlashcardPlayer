// GREDoc.cpp : implementation of the GREDoc class
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

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// GREDoc

IMPLEMENT_DYNCREATE(GREDoc, CDocument)

BEGIN_MESSAGE_MAP(GREDoc, CDocument)
	ON_COMMAND(ID_PLAYBACK_MODE, &GREDoc::OnPlaybackMode)
	ON_COMMAND(ID_PLAYBACK_NEXT, &GREDoc::OnPlaybackNext)
	ON_COMMAND(ID_PLAYBACK_PREVIOUS, &GREDoc::OnPlaybackPrevious)
	ON_COMMAND(ID_PLAYBACK_SHOWBACK, &GREDoc::OnPlaybackShowback)

	ON_COMMAND(ID_SETTINGS_ALWAYSONTOP, &GREDoc::OnSettingsAlwaysOnTop)
	ON_COMMAND(ID_SETTINGS_AUDIO, &GREDoc::OnSettingsAudio)
	ON_COMMAND(ID_SETTINGS_SHUFFLE, &GREDoc::OnSettingsShuffle)
	ON_COMMAND(ID_FRONTSPEED_5SEC, &GREDoc::OnFrontSpeed5sec)
	ON_COMMAND(ID_FRONTSPEED_10SEC, &GREDoc::OnFrontSpeed10sec)
	ON_COMMAND(ID_FRONTSPEED_INC2, &GREDoc::OnFrontSpeedInc2)
	ON_COMMAND(ID_FRONTSPEED_DEC2, &GREDoc::OnFrontSpeedDec2)
	ON_COMMAND(ID_BACKSPEED_5SEC, &GREDoc::OnBackSpeed5sec)
	ON_COMMAND(ID_BACKSPEED_10SEC, &GREDoc::OnBackSpeed10sec)
	ON_COMMAND(ID_BACKSPEED_15SEC, &GREDoc::OnBackSpeed15sec)
	ON_COMMAND(ID_BACKSPEED_30SEC, &GREDoc::OnBackSpeed30sec)
	ON_COMMAND(ID_BACKSPEED_INC5, &GREDoc::OnBackSpeedInc5)
	ON_COMMAND(ID_BACKSPEED_DEC5, &GREDoc::OnBackSpeedDec5)
	ON_COMMAND(ID_BACKFONT_INC, &GREDoc::OnBackFontInc)
	ON_COMMAND(ID_BACKFONT_DEC, &GREDoc::OnBackFontDec)
	ON_COMMAND(ID_RESIZEWINDOW_INC, &GREDoc::OnResizeWindowInc)
	ON_COMMAND(ID_RESIZEWINDOW_DEC, &GREDoc::OnResizeWindowDec)
	ON_COMMAND(ID_SETTINGS_RESET, &GREDoc::OnSettingsReset)

	ON_COMMAND(ID_CARDS_ALL, &GREDoc::OnCardsAll)
	ON_COMMAND(ID_COMMON_ALL, &GREDoc::OnCommonAll)
	ON_COMMAND(ID_BASIC_ALL, &GREDoc::OnBasicAll)
	ON_COMMAND(ID_ADVANCED_ALL, &GREDoc::OnAdvancedAll)
	ON_COMMAND(ID_COMMON_COMMONI, &GREDoc::OnCommonI)
	ON_COMMAND(ID_COMMON_COMMONII, &GREDoc::OnCommonII)
	ON_COMMAND(ID_COMMON_COMMONIII, &GREDoc::OnCommonIII)
	ON_COMMAND(ID_COMMON_COMMONIV, &GREDoc::OnCommonIV)
	ON_COMMAND(ID_COMMON_COMMONV, &GREDoc::OnCommonV)
	ON_COMMAND(ID_COMMON_COMMONVI, &GREDoc::OnCommonVI)
	ON_COMMAND(ID_BASIC_BASICI, &GREDoc::OnBasicI)
	ON_COMMAND(ID_BASIC_BASICII, &GREDoc::OnBasicII)
	ON_COMMAND(ID_BASIC_BASICIII, &GREDoc::OnBasicIII)
	ON_COMMAND(ID_BASIC_BASICIV, &GREDoc::OnBasicIV)
	ON_COMMAND(ID_BASIC_BASICV, &GREDoc::OnBasicV)
	ON_COMMAND(ID_BASIC_BASICVI, &GREDoc::OnBasicVI)
	ON_COMMAND(ID_BASIC_BASICVII, &GREDoc::OnBasicVII)
	ON_COMMAND(ID_ADVANCED_ADVANCEDI, &GREDoc::OnAdvancedI)
	ON_COMMAND(ID_ADVANCED_ADVANCEDII, &GREDoc::OnAdvancedII)
	ON_COMMAND(ID_ADVANCED_ADVANCEDIII, &GREDoc::OnAdvancedIII)
	ON_COMMAND(ID_ADVANCED_ADVANCEDIV, &GREDoc::OnAdvancedIV)
	ON_COMMAND(ID_ADVANCED_ADVANCEDV, &GREDoc::OnAdvancedV)
	ON_COMMAND(ID_ADVANCED_ADVANCEDVI, &GREDoc::OnAdvancedVI)
	ON_COMMAND(ID_ADVANCED_ADVANCEDVII, &GREDoc::OnAdvancedVII)
END_MESSAGE_MAP()


// GREDoc construction/destruction

GREDoc::GREDoc() noexcept
{
	db = new Database(this);
	set_title();
}

GREDoc::~GREDoc()
{
	db->~Database();
	delete db;
	thread_run = false;
	audioTrd.detach();
}

BOOL GREDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


// GREDoc serialization

void GREDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void GREDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void GREDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void GREDoc::SetSearchContent(const CString& value)
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

// GREDoc diagnostics

#ifdef _DEBUG
void GREDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void GREDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void audio_trd_process(void* param)
{
	GREDoc* pDoc = (GREDoc*)param;
	int count_1sec = 0;
	bool pause_1sec = false;
	while (pDoc->thread_run)
	{
		if (pDoc->pulse)
		{
			count_1sec = 0;
			pause_1sec = true;
			pDoc->pulse = false;
		}
		if (pause_1sec)
		{
			if (count_1sec >= 10)
				pause_1sec = false;
			count_1sec++;
		}
		if (pDoc->thread_play_audio && !pause_1sec && pDoc->play_cards && pDoc->audio)
		{
			pDoc->db->play_sound();
			pDoc->thread_play_audio = false;
		}
		Sleep(100);
	}
}

// GREDoc commands

void GREDoc::init_timer()
{
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	if (play_cards)
		set_time_front();
	pView->show_front();
}	 
void GREDoc::set_title()
{
	CString cstr(db->get_str_type().c_str());
	cstr.Append(L" (");
	cstr.Append(std::to_wstring(time_front).c_str());
	cstr.Append(L",");
	cstr.Append(std::to_wstring(time_back).c_str());
	cstr.Append(L")");
	SetTitle(cstr);
}
void GREDoc::set_time_front()
{
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	KillTimer(pView->m_hWnd, IDT_TIMER2);
	TimerId = SetTimer(pView->m_hWnd, IDT_TIMER1, time_front * 1000, NULL);
}
void GREDoc::set_time_back()
{
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	KillTimer(pView->m_hWnd, IDT_TIMER1);
	TimerId = SetTimer(pView->m_hWnd, IDT_TIMER2, time_back * 1000, NULL);
}

void GREDoc::OnPlaybackMode()
{
	play_cards = !play_cards;
	if (play_cards)
		init_timer();
	else
	{
		POSITION pos = GetFirstViewPosition();
		GREView* pView = (GREView*)GetNextView(pos);
		KillTimer(pView->m_hWnd, IDT_TIMER1);
		KillTimer(pView->m_hWnd, IDT_TIMER2);
	}
}
void GREDoc::OnPlaybackNext()
{
	db->next_index();
	init_timer();
	pulse = true;
}
void GREDoc::OnPlaybackPrevious()
{
	db->previous_index();
	init_timer();
	pulse = true;
}
void GREDoc::OnPlaybackShowback()
{
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	if (TimerId == IDT_TIMER1)
	{
		set_time_back();
		pView->show_back();
	}
	else if (TimerId == IDT_TIMER2)
	{
		db->next_index();
		init_timer();
	}
}

void GREDoc::OnSettingsAlwaysOnTop()
{
	always_on_top = !always_on_top;
	if (always_on_top)
		::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
	else
		::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
}
void GREDoc::OnSettingsAudio()
{
	audio = !audio;
}
void GREDoc::OnSettingsShuffle()
{
	shuffle = !shuffle;
	db->init_indexes();
	init_timer();
}
void GREDoc::OnFrontSpeed5sec()
{
	time_front = 5;
	set_title();
	init_timer();
}
void GREDoc::OnFrontSpeed10sec()
{
	time_front = 10;
	set_title();
	init_timer();
}
void GREDoc::OnFrontSpeedInc2()
{
	time_front += 2;
	set_title();
	init_timer();
	pulse = true;
}
void GREDoc::OnFrontSpeedDec2()
{
	time_front -= 2;
	if (time_front < TIMEFRONT_MIN)
		time_front = TIMEFRONT_MIN;
	set_title();
	init_timer();
	pulse = true;
}
void GREDoc::OnBackSpeed5sec()
{
	time_back = 5;
	set_title();
	init_timer();
}
void GREDoc::OnBackSpeed10sec()
{
	time_back = 10;
	set_title();
	init_timer();
}
void GREDoc::OnBackSpeed15sec()
{
	time_back = 15;
	set_title();
	init_timer();
}
void GREDoc::OnBackSpeed30sec()
{
	time_back = 30;
	set_title();
	init_timer();
}
void GREDoc::OnBackSpeedInc5()
{
	time_back += 5;
	set_title();
	init_timer();
	pulse = true;
}
void GREDoc::OnBackSpeedDec5()
{
	time_back -= 5;
	if (time_back < TIMEBACK_MIN)
		time_back = TIMEBACK_MIN;
	set_title();
	init_timer();
	pulse = true;
}
void GREDoc::OnBackFontInc()
{
	font_size += 5;
	if (font_size > FONTSIZE_MAX)
		font_size = FONTSIZE_MAX;
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	pView->adjust_font_size();
}
void GREDoc::OnBackFontDec()
{
	font_size -= 5;
	if (font_size < FONTSIZE_MIN)
		font_size = FONTSIZE_MIN;
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	pView->adjust_font_size();
}
void GREDoc::OnResizeWindowInc()
{
	horizontal_size++;
	if (horizontal_size > HSIZE_MAX)
		horizontal_size = HSIZE_MAX;
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	pView->adjust_window_size();
}
void GREDoc::OnResizeWindowDec()
{
	horizontal_size--;
	if (horizontal_size < HSIZE_MIN)
		horizontal_size = HSIZE_MIN;
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	pView->adjust_window_size();
}
void GREDoc::OnSettingsReset()
{
	audio = true;
	shuffle = true;
	always_on_top = true;
	time_front = 5;
	time_back = 10;
	font_size = 110;
	horizontal_size = 0;

	set_title();
	db->init_indexes();
	POSITION pos = GetFirstViewPosition();
	GREView* pView = (GREView*)GetNextView(pos);
	pView->adjust_font_size();
	pView->adjust_window_size();	
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
	init_timer();
}

void GREDoc::OnCardsAll()
{
	db->dif = DIF::ALL;
	db->load_database();
	set_title();
	init_timer();
}
void GREDoc::OnCommonAll()
{
	db->dif = DIF::COMMON;
	db->group = DIFG::ALL;
	db->load_database();
	set_title();
	init_timer();
}
void GREDoc::OnBasicAll()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::ALL;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedAll()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::ALL;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnCommonI()
{
	db->dif = DIF::COMMON;
	db->group = DIFG::I;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnCommonII()
{
	db->dif = DIF::COMMON;
	db->group = DIFG::II;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnCommonIII()
{
	db->dif = DIF::COMMON;
	db->group = DIFG::III;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnCommonIV()
{
	db->dif = DIF::COMMON;
	db->group = DIFG::IV;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnCommonV()
{
	db->dif = DIF::COMMON;
	db->group = DIFG::V;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnCommonVI()
{
	db->dif = DIF::COMMON;
	db->group = DIFG::VI;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnBasicI()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::I;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnBasicII()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::II;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnBasicIII()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::III;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnBasicIV()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::IV;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnBasicV()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::V;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnBasicVI()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::VI;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnBasicVII()
{
	db->dif = DIF::BASIC;
	db->group = DIFG::VII;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedI()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::I;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedII()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::II;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedIII()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::III;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedIV()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::IV;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedV()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::V;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedVI()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::VI;
	db->load_database();	
	set_title();
	init_timer();
}
void GREDoc::OnAdvancedVII()
{
	db->dif = DIF::ADVANCED;
	db->group = DIFG::VII;
	db->load_database();	
	set_title();
	init_timer();
}
