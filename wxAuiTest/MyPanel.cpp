#include "MyPanel.h"



CMyPanel::CMyPanel(wxWindow *parent,
	wxWindowID winid,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name)
	: wxPanel(parent, winid, pos, size, style, name)
{

}

CMyPanel::~CMyPanel()
{
}
