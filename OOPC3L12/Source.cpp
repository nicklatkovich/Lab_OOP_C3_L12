#include <afxwin.h>
#define RANDOM_COLOR RGB(rand() % 256, rand() % 256, rand() % 256)

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
		RECT clientRect;
		this->GetClientRect(&clientRect);

		int penWidth = rand() % 3 + 1;
		COLORREF penColor = RANDOM_COLOR;
		CPen pen(PS_SOLID, penWidth, penColor);
		m_memDC.SelectObject(pen);

		CBrush brush;
		COLORREF brushColor = RANDOM_COLOR;
		brush.CreateSolidBrush(brushColor);
		m_memDC.SelectObject(brush);

		switch (ch) {
		case '1': // Circle
		case '4': // Square
		{
			int radius = rand() % 50 + 50;
			int x = rand() % (clientRect.right + 2 * radius) - radius;
			int y = rand() % (clientRect.bottom + 2 * radius) - radius;
			if (ch == '1') {
				m_memDC.Ellipse(x - radius, y - radius, x + radius, y + radius);
			}
			else {
				m_memDC.Rectangle(x - radius, y - radius, x + radius, y + radius);
			}
			break;
		}
		case '2': // Ellipse
		case '3': // Rectangle
		{
			int width = rand() % 150 + 50;
			int height = rand() % 150 + 50;
			int x = rand() % (clientRect.right + 2 * width) - width;
			int y = rand() % (clientRect.bottom + 2 * height) - height;
			if (ch == '2') {
				m_memDC.Ellipse(x - width, y - height, x + width, y + height);
			}
			else {
				m_memDC.Rectangle(x - width, y - height, x + width, y + height);
			}
			break;
		}
		}
		this->InvalidateRect(0, FALSE);
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
