// ���ڻ�ͼ��GDI+��ķ�װ

#pragma once

#define PALY_GAME_USER_NUM			4

// GDI+ͷ�ļ�

#ifdef _WIN64
#define ULONG_PTR unsigned __int64
#else
#define ULONG_PTR ULONG
#endif

#include <gdiplus.h>
using namespace Gdiplus;
// ����GDI+��
#pragma comment(lib, "gdiplus.lib")


// �����Ʊ�ѡ��ʱ��ƫ������
#define HOVER_MOVE_PIXEL_VER			10

// GDIʹ������
extern GdiplusStartupInput gdiplusStartupInputUi;
extern ULONG_PTR gdiplusTokenUi;

// ���ƴ���������
void DrawWindowRectUi(HDC & hdc, CRect rt);

class CGdiPlusMakeUi
{
public:
	CGdiPlusMakeUi();
	~CGdiPlusMakeUi();

	// GDI+��ʼ��
	static void CGdiPlusMakeUiInit();
};

