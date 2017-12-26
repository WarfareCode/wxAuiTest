#pragma once

#include <wx/wx.h>

class CMyPanel :
	public wxPanel
{
public:

	CMyPanel(wxWindow *parent,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxPanelNameStr);

	~CMyPanel();
};

