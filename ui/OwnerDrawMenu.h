#pragma once

#define OWNER_MENU_HIGH_LIGHT				RGB(0, 139, 160)
#define OWNER_MENU_BK_COLOR					RGB(240, 240, 240)
#define OWNER_MENU_TEXT_COLOR				RGB(33, 33, 33)
#define OWNER_MENU_HH_COLOR					RGB(250, 250, 250)

class COwnerDrawMenu : public CMenu
{
public:
	COwnerDrawMenu();
	~COwnerDrawMenu();

	// Overridables (must override draw and measure for owner-draw menu items)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	// 更改为自绘属性
	inline void COwnerDrawMenu::ModifyDrawStyle(CMenu* pMenu)
	{
		VERIFY(pMenu);
		for (int i = 0; i < pMenu->GetMenuItemCount(); i++)
		{
			UINT id = pMenu->GetMenuItemID(i);
			CString str;
			pMenu->GetMenuString(i, str, MF_BYPOSITION);
			BOOL bModi = pMenu->ModifyMenu(id, MF_BYCOMMAND | MF_OWNERDRAW, id, str);
			VERIFY(bModi);
		}
	}
};

