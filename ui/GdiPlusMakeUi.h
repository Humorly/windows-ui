// 用于绘图的GDI+类的封装

#pragma once

#define PALY_GAME_USER_NUM			4

// GDI+头文件
#define ULONG_PTR ULONG 
#include <gdiplus.h>
using namespace Gdiplus;
// 链接GDI+库
#pragma comment(lib, "gdiplus.lib")


// 定义牌被选中时的偏移像素
#define HOVER_MOVE_PIXEL_VER			10

// GDI使用声明
extern GdiplusStartupInput gdiplusStartupInputUi;
extern ULONG_PTR gdiplusTokenUi;

// 绘制窗体外层矩形
void DrawWindowRectUi(HDC & hdc, CRect rt);


class CGdiPlusMakeUi
{
public:
	CGdiPlusMakeUi();
	~CGdiPlusMakeUi();

	// GDI+初始化
	static void CGdiPlusMakeUiInit();
};

