#pragma once

#include <wx/wx.h>
struct SCNotification;

class CScintillaPanel : public wxPanel
{
public:
	CScintillaPanel(wxFrame* pParent);
	~CScintillaPanel();

	typedef void (*ScintillaNotify)(int code, const SCNotification* info);

	static CScintillaPanel* CreatePanel(HINSTANCE app, wxFrame* pParent);
	bool Initialise(HINSTANCE app);
	LRESULT SendEditor(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0);
	void SetAStyle(int style, COLORREF fore, COLORREF back = RGB(255, 255, 255), int size = -1, const TCHAR *face = 0);
	void AddText(const wxString& text);
	void SetModEventMask(int mask);
	int GetModEventMask();
	void SetNotificationHandler(ScintillaNotify handler);



private:

	void OnSize(wxSizeEvent& event);
	void ConfigureEditor();

	virtual bool MSWHandleMessage(WXLRESULT *result,
		WXUINT message,
		WXWPARAM wParam,
		WXLPARAM lParam);

	static HINSTANCE	m_hLibrary;
	HINSTANCE			m_app;
	HWND				m_scintilla;
	wxFrame*			m_pParent;
	ScintillaNotify		m_handler;

	// direct call to scintilla
	int(*m_fn)(void*, int, int, int);
	void * m_ptr;

};

