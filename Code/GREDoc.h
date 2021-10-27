// GREDoc.h : interface of the GREDoc class
//

#pragma once
#include <thread>
#include "Database.h"


#define IDT_TIMER1	5551
#define IDT_TIMER2	5552

class GREDoc : public CDocument
{
protected: // create from serialization only
	GREDoc() noexcept;
	DECLARE_DYNCREATE(GREDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~GREDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	Database* db;
	bool audio = true;
	bool shuffle = true;
	bool always_on_top = true;
	int time_front = 5;
	int time_back = 10;
	int font_size = 110;
	int horizontal_size = 0;
	
	std::thread audioTrd;
	bool pulse = false;
	bool thread_run = true;
	bool thread_play_audio = false;

	UINT TimerId = 0;
	bool play_cards = true;
	bool show_front = true;
	void init_timer();
	void set_title();
	void set_time_front();
	void set_time_back();

	afx_msg void OnPlaybackMode();
	afx_msg void OnPlaybackNext();
	afx_msg void OnPlaybackPrevious();
	afx_msg void OnPlaybackShowback();

	afx_msg void OnSettingsAlwaysOnTop();
	afx_msg void OnSettingsAudio();
	afx_msg void OnSettingsShuffle();
	afx_msg void OnFrontSpeed5sec();
	afx_msg void OnFrontSpeed10sec();
	afx_msg void OnFrontSpeedInc2();
	afx_msg void OnFrontSpeedDec2();
	afx_msg void OnBackSpeed5sec();
	afx_msg void OnBackSpeed10sec();
	afx_msg void OnBackSpeed15sec();
	afx_msg void OnBackSpeed30sec();
	afx_msg void OnBackSpeedInc5();
	afx_msg void OnBackSpeedDec5();
	afx_msg void OnBackFontInc();
	afx_msg void OnBackFontDec();
	afx_msg void OnResizeWindowInc();
	afx_msg void OnResizeWindowDec();
	afx_msg void OnSettingsReset();

	afx_msg void OnCardsAll();
	afx_msg void OnCommonAll();
	afx_msg void OnBasicAll();
	afx_msg void OnAdvancedAll();
	afx_msg void OnCommonI();
	afx_msg void OnCommonII();
	afx_msg void OnCommonIII();
	afx_msg void OnCommonIV();
	afx_msg void OnCommonV();
	afx_msg void OnCommonVI();
	afx_msg void OnBasicI();
	afx_msg void OnBasicII();
	afx_msg void OnBasicIII();
	afx_msg void OnBasicIV();
	afx_msg void OnBasicV();
	afx_msg void OnBasicVI();
	afx_msg void OnBasicVII();
	afx_msg void OnAdvancedI();
	afx_msg void OnAdvancedII();
	afx_msg void OnAdvancedIII();
	afx_msg void OnAdvancedIV();
	afx_msg void OnAdvancedV();
	afx_msg void OnAdvancedVI();
	afx_msg void OnAdvancedVII();
};

void audio_trd_process(void* param);
