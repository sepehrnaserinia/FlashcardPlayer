// GREView.h : interface of the GREView class
//

#pragma once
#include <thread>
#include <string>

class GREView : public CFormView
{
protected: // create from serialization only
	GREView() noexcept;
	DECLARE_DYNCREATE(GREView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_GRE_FORM };
#endif

// Attributes
public:
	GREDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~GREView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	RECT rc;
	CFont frontFont, backFont;
	void show_front();
	void show_back();
	void show_msg(int nID, std::string msg);
	void adjust_font_size();
	void adjust_window_size();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdatePlaybackMode(CCmdUI* pCmdUI);

	afx_msg void OnUpdateSettingsAudio(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSettingsShuffle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSettingsAlwaysOnTop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrontSpeed5sec(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrontSpeed10sec(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBackSpeed5sec(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBackSpeed10sec(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBackSpeed15sec(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBackSpeed30sec(CCmdUI* pCmdUI);

	afx_msg void OnUpdateCardsAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommonAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommonI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommonII(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommonIII(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommonIV(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommonV(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommonVI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicII(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicIII(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicIV(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicV(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicVI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasicVII(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedII(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedIII(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedIV(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedV(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedVI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvancedVII(CCmdUI* pCmdUI);
};


#ifndef _DEBUG  // debug version in GREView.cpp
inline GREDoc* GREView::GetDocument() const
   { return reinterpret_cast<GREDoc*>(m_pDocument); }
#endif
