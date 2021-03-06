#include <afxwin.h>
#define RANDOM_COLOR RGB(rand() % 256, rand() % 256, rand() % 256)
#define PI 3.14159265
#define BACK_COLOR RGB(255, 255, 255)

double doubleRand(double max, unsigned precision = 8) {
	unsigned random = rand() % precision;
	return max / precision * random;
}

class CMainWnd : public CFrameWnd {
public:
	CMainWnd();
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT, UINT, UINT);
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnRButtonDown(UINT, CPoint);
	CDC m_memDC;
	CBitmap m_bmp;
	CBrush m_bkbrush;
	void ClearWindow(COLORREF color = BACK_COLOR);
private:
	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CMainWnd::ClearWindow(COLORREF color) {
	RECT clientRect;
	this->GetClientRect(&clientRect);

	CPen pen(PS_NULL, 0, RGB(0, 0, 0));
	m_memDC.SelectObject(pen);

	CBrush brush;
	brush.CreateSolidBrush(color);
	m_memDC.SelectObject(brush);
	m_memDC.Rectangle(0, 0, clientRect.right, clientRect.bottom);
	this->InvalidateRect(0, FALSE);
}

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
	ClearWindow();
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
		case '5': // Sector
		case '6': // Segment
		{
			int radius = rand() % 50 + 50;
			int x = rand() % (clientRect.right + 2 * radius) - radius;
			int y = rand() % (clientRect.bottom + 2 * radius) - radius;
			int x1 = x - radius;
			int y1 = y - radius;
			int x2 = x + radius;
			int y2 = y + radius;
			if (ch == '1') {
				m_memDC.Ellipse(x1, y1, x2, y2);
			}
			else if (ch == '4') {
				m_memDC.Rectangle(x1, y1, x2, y2);
			}
			else {
				double a = doubleRand(2 * PI);
				double b = a + PI / 2 + doubleRand(PI);
				int x3 = x + (int)round(sin(a) * radius);
				int y3 = y + (int)round(cos(a) * radius);
				int x4 = x + (int)round(sin(b) * radius);
				int y4 = y + (int)round(cos(b) * radius);
				if (ch == '5') {
					m_memDC.Pie(x1, y1, x2, y2, x3, y3, x4, y4);
				}
				else {
					m_memDC.Chord(x1, y1, x2, y2, x3, y3, x4, y4);
				}
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
			int x1 = x - width;
			int y1 = y - height;
			int x2 = x + width;
			int y2 = y + height;
			if (ch == '2') {
				m_memDC.Ellipse(x1, y1, x2, y2);
			}
			else {
				m_memDC.Rectangle(x1, y1, x2, y2);
			}
			break;
		}
		}
		this->InvalidateRect(0, FALSE);
	}
}

void CMainWnd::OnLButtonDown(UINT, CPoint) {
	ClearWindow();
}

void CMainWnd::OnRButtonDown(UINT, CPoint) {
	RECT clientRect;
	this->GetClientRect(&clientRect);

	int steps = 6;
	int xStep = 4;
	int yStep = 4;
	int x = clientRect.right / 2 - steps * xStep;
	int y = clientRect.bottom / 2 - steps * yStep;
	double red = rand() % 256;
	double green = rand() % 256;
	double blue = rand() % 256;
	double redStep = (double)red / steps;
	double greenStep = (double)green / steps;
	double blueStep = (double)blue / steps;
	red = green = blue = 0;
	for (int i = 0; i < steps; i++) {
		m_memDC.SetTextColor(RGB(red, green, blue));
		red += redStep;
		green += greenStep;
		blue += blueStep;
		m_memDC.SetBkMode(TRANSPARENT);
		m_memDC.SelectObject(CreateFont(96, 32, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, NULL));
		RECT position;

		//// �������, ����� ����� ������ ��� � ����������� (x,y)
		//position.left = x - 200;
		//position.top = y - 200;
		//position.right = x + 200;
		//position.bottom = y + 200;

		// ����� ���������� �����, �� ������� �������
		position.left = -max(x, clientRect.right - x);
		position.right = 2 * x - position.left;
		position.top = -max(y, clientRect.bottom - y);
		position.bottom = 2 * y - position.top;

		m_memDC.DrawText(L"OOP Lab12", &position, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		x += xStep;
		y += yStep;
	}
	this->InvalidateRect(0, FALSE);
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
