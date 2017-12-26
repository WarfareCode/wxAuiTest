
#include <wx/wx.h>
#include "wx/aui/aui.h"
#include "wx/treectrl.h"
#include "wx/artprov.h"
#include "ScintillaPanel.h"
#include "MyPanel.h"

class CMyFrame : public wxFrame
{
public:

	CMyFrame(wxWindow *parent,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize);


	~CMyFrame();

	void Init();
	wxTextCtrl* CreateTextCtrl(const wxString& ctrl_text);
	void AddTree(wxCommandEvent& WXUNUSED(event));
	wxTreeCtrl* CreateTreeCtrl();
	wxPoint GetStartPosition();

	wxDECLARE_EVENT_TABLE();


private:

	wxAuiManager m_mgr;
	CScintillaPanel* m_pEditor;

	void OnFileOpen(wxCommandEvent& WXUNUSED(event));
	void OnExit(wxCommandEvent& WXUNUSED(event));


	enum
	{
		ID_FileOpen = wxID_HIGHEST + 1,
		ID_CreateText,
		ID_GridContent,
	};

};

class CMyApp : public wxApp
{
public:

	bool OnInit();

private:

	CMyFrame* pFrame;
};

bool CMyApp::OnInit()
{
	pFrame = new CMyFrame(NULL, wxT("Simple wxWidgets"), wxPoint(50, 50), wxSize(800, 600));
	pFrame->InitDialog();
	pFrame->Init();
	pFrame->Show();

	return true;
}

IMPLEMENT_APP(CMyApp);

//--------------------------------------------------------


CMyFrame::CMyFrame(wxWindow *parent,
	const wxString& title,
	const wxPoint& pos,
	const wxSize& size)
	: wxFrame(parent, -1, title, pos)
{
}

CMyFrame::~CMyFrame()
{
	m_mgr.UnInit();
}

void CMyFrame::Init()
{
	m_mgr.SetManagedWindow(this);

//	wxTextCtrl* pTextCtrl = CreateTextCtrl(_T("text Control 1"));

	//m_mgr.AddPane(pTextCtrl, wxAuiPaneInfo().
	//	Name(wxT("test10")).Caption(wxT("Text Pane with Hide Prompt")).
	//	Bottom().Layer(1).Position(1));

	wxTreeCtrl* pTreeCtrl = CreateTreeCtrl();

	m_mgr.AddPane(pTreeCtrl, wxAuiPaneInfo().
		Name(wxT("test8")).Caption(wxT("Tree Pane")).
		Left().Layer(1).Position(1).
		CloseButton(true).MaximizeButton(true));

	m_mgr.Update();

	CMyPanel* pPanel = new CMyPanel(this, wxID_ANY,
			wxPoint(0, 0), wxSize(160, 250),
			wxTR_DEFAULT_STYLE | wxNO_BORDER);

	m_mgr.AddPane(pPanel, wxAuiPaneInfo().
		Name(wxT("panel")).Caption(wxT("Panel")).
		Bottom().Layer(1).Position(1).
		CloseButton(true).MaximizeButton(true));


	m_pEditor = new CScintillaPanel(this, wxID_ANY,
		wxPoint(0, 0), wxSize(600, 300),
		wxTR_DEFAULT_STYLE | wxNO_BORDER);

	m_pEditor->Initialise(GetModuleHandle(NULL));

	m_mgr.AddPane(m_pEditor, wxAuiPaneInfo().
		Name(wxT("editor")).Caption(wxT("Scintilla Editor")).Center().
		CloseButton(true).MaximizeButton(true));


	m_mgr.Update();

	// create menu
	wxMenuBar* mb = new wxMenuBar;

	wxMenu* file_menu = new wxMenu;
	file_menu->Append(wxID_OPEN);
	file_menu->Append(wxID_EXIT);

	wxMenu* view_menu = new wxMenu;
	view_menu->Append(ID_CreateText, _("Create Text Control"));
	view_menu->AppendSeparator();
	view_menu->Append(ID_GridContent, _("Use a Grid for the Content Pane"));

	wxMenu* help_menu = new wxMenu;
	help_menu->Append(wxID_ABOUT);

	mb->Append(file_menu, _("&File"));
	mb->Append(view_menu, _("&View"));
	mb->Append(help_menu, _("&Help"));

	SetMenuBar(mb);


	SetPosition(wxPoint(100, 100));
	SetSize(wxSize(900, 700));



}

wxBEGIN_EVENT_TABLE(CMyFrame, wxFrame)
	EVT_MENU(wxID_OPEN, CMyFrame::OnFileOpen)
	EVT_MENU(wxID_EXIT, CMyFrame::OnExit)
wxEND_EVENT_TABLE()

wxTextCtrl* CMyFrame::CreateTextCtrl(const wxString& ctrl_text)
{
	static int n = 0;

	wxString text;
	if (!ctrl_text.empty())
		text = ctrl_text;
	else
		text.Printf(wxT("This is text box %d"), ++n);

	return new wxTextCtrl(this, wxID_ANY, text,
		wxPoint(0, 0), wxSize(150, 90),
		wxNO_BORDER | wxTE_MULTILINE);
}

void CMyFrame::AddTree(wxCommandEvent& WXUNUSED(event))
{
	m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
		Caption(wxT("Tree Control")).
		Float().FloatingPosition(GetStartPosition()).
		FloatingSize(wxSize(150, 300)));
	m_mgr.Update();
}

wxTreeCtrl* CMyFrame::CreateTreeCtrl()
{
	wxTreeCtrl* tree = new wxTreeCtrl(this, wxID_ANY,
		wxPoint(0, 0), wxSize(160, 250),
		wxTR_DEFAULT_STYLE | wxNO_BORDER);

	wxImageList* imglist = new wxImageList(16, 16, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16)));
	imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16)));
	tree->AssignImageList(imglist);

	wxTreeItemId root = tree->AddRoot(wxT("wxAUI Project"), 0);
	wxArrayTreeItemIds items;



	items.Add(tree->AppendItem(root, wxT("Item 1"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 2"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 3"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 4"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 5"), 0));


	int i, count;
	for (i = 0, count = items.Count(); i < count; ++i)
	{
		wxTreeItemId id = items.Item(i);
		tree->AppendItem(id, wxT("Subitem 1"), 1);
		tree->AppendItem(id, wxT("Subitem 2"), 1);
		tree->AppendItem(id, wxT("Subitem 3"), 1);
		tree->AppendItem(id, wxT("Subitem 4"), 1);
		tree->AppendItem(id, wxT("Subitem 5"), 1);
	}


	tree->Expand(root);

	return tree;
}

wxPoint CMyFrame::GetStartPosition()
{
	static int x = 0;
	x += 20;
	wxPoint pt = ClientToScreen(wxPoint(0, 0));
	return wxPoint(pt.x + x, pt.y + x);
}

void CMyFrame::OnFileOpen(wxCommandEvent& WXUNUSED(event))
{
	wxString s = m_pEditor->GetAllText();
}

void CMyFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}
