#include <afxwin.h>

class CMainWnd : public CFrameWnd {
public:
	CMainWnd();
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT, UINT, UINT);
	CDC m_memDC;
	CBitmap m_bmp;
	CBrush m_bkbrush;
private:
	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
	Create(NULL, L"Lab12", WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);
	int maxX = GetSystemMetrics(SM_CXSCREEN);
	int maxY = GetSystemMetrics(SM_CYSCREEN);
	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_bmp.CreateCompatibleBitmap(&dc, maxX, maxY);
	m_memDC.SelectObject(&m_bmp);
	m_bkbrush.CreateStockObject(WHITE_BRUSH);
	m_memDC.SelectObject(&m_bkbrush);
	m_memDC.PatBlt(0, 0, maxX, maxY, PATCOPY);
}

void CMainWnd::OnPaint() {
	CPaintDC paintDC(this);
	RECT clientRect;
	this->GetClientRect(&clientRect);
	paintDC.BitBlt(0, 0, clientRect.right, clientRect.bottom, &m_memDC, 0, 0, SRCCOPY);
}

void CMainWnd::OnKeyDown(UINT ch, UINT, UINT) {
	if (ch < '7' && ch > '0') {
		int penStyle;
		int random = rand();
		switch (random / (RAND_MAX / 3)) {
		case 0: penStyle = PS_SOLID; break;
		case 1: penStyle = PS_DOT;  break;
		case 2: penStyle = PS_DASH; break;
		}
		int penWidth = rand() % 3 + 1;
		COLORREF penColor = RGB(rand() % 256, rand() % 256, rand() % 256);
		CPen pen(penStyle, penWidth, penColor);
		m_memDC.SelectObject(pen);

		CBrush brush;
		COLORREF brushColor = RGB(rand() % 256, rand() % 256, rand() % 256);
		brush.CreateSolidBrush(brushColor);
		m_memDC.SelectObject(brush);

		if (ch == '1') {
			m_memDC.Ellipse(0, 0, 100, 100);
			this->InvalidateRect(0, FALSE);
		}
	}
}

class CMyApp : public CWinApp {
public:
	CMyApp();
	virtual BOOL InitInstance();
};

CMyApp::CMyApp() {}

BOOL CMyApp::InitInstance() {
	m_pMainWnd = new CMainWnd();
	ASSERT(m_pMainWnd);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMyApp theApp;
