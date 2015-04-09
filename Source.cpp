#pragma comment(lib,"winmm")
#pragma comment (lib, "msimg32.lib")
#include <windows.h>
#include <math.h>
#define XMAX 1080
#define YMAX 810

//構造体
class jouhou{
public:
	int ID;
	int type;
	int layer;
	jouhou();
};

jouhou::jouhou() {
	type = 0;
	ID = 0;
	layer = 0;
}

//エディタ情報
struct edit{
	int point;
	int size;
};

//アイテム情報
struct item{
	int ID;
	int size;
	int condition;
	int edi_number;
	edit edit_info[10];
	LPCTSTR write_text;
	HBITMAP image;
};

//エディタ名前保管庫
struct edi_name{
	HWND edi[100];
}e_name;

//諸座標情報
int control_b_x = 80;
int control_b_y = 60;
int control_l_x = 128;
int control_l_y = 32;
int control_s_x = 158;
int control_s_y = 52;
int control_n_x = 512;
int control_n_y = 128;

int terms_b_x = 80;
int terms_b_y = 320;
int terms_l_x = 64;
int terms_l_y = 32;
int terms_s_x = 110;
int terms_s_y = 52;
int terms_n_x = 256;
int terms_n_y = 128;


//画面のサイズから相対サイズを求める
int tyousetu(RECT Rt, int xy, int point){
	int ans;
	if (xy)ans = lround(1.0*point*(Rt.right - Rt.left) / (1.0*XMAX));
	else ans = lround(1.0*point*(Rt.bottom - Rt.top) / (1.0*YMAX));

	return ans;
}

//サイズ変更の上限を設ける
int okisamax(int ans,int max){
	int squere_max;
	if (ans>max)squere_max = max;
	else squere_max = ans;
	return squere_max;
}

//tyousetu,okisamax組み合わせ
int tyousetu2(RECT Rt, int xy, int point){
	return okisamax(tyousetu(Rt, xy, point), point);
}

//円を作る
void hutuu_en(HDC hdc, int b_x, int b_y, int l_x, int l_y, int color){
	HPEN hpen;
	hpen = CreatePen(PS_SOLID, 0, color);
	SelectObject(hdc, hpen);

	SelectObject(hdc, CreateSolidBrush(color));
	Ellipse(hdc, b_x, b_y, b_x + l_x, b_y + l_y);
	DeleteObject(hpen);
}

//四角を作る
void hutuu(HDC hdc, int b_x, int b_y, int l_x, int l_y, int color){
	HPEN hpen;
	hpen = CreatePen(PS_SOLID, 0, color);
	SelectObject(hdc, hpen);

	SelectObject(hdc, CreateSolidBrush(color));
	Rectangle(hdc, b_x, b_y, b_x + l_x, b_y + l_y);
	DeleteObject(hpen);
}

//中抜きの四角を作る
void nakanuki(HDC hdc, int b_x, int b_y, int l_x, int l_y, int color){
	HPEN hpen;
	hpen = CreatePen(PS_SOLID, 2, color);
	SelectObject(hdc, hpen);
	MoveToEx(hdc, b_x+1, b_y+1, NULL);
	LineTo(hdc, b_x+2, b_y + l_y-1);
	LineTo(hdc, b_x + l_x-1, b_y + l_y-1);
	LineTo(hdc, b_x + l_x-1, b_y+1);
	LineTo(hdc, b_x+1, b_y+1);

	DeleteObject(hpen);

}

//縁付きの四角を作る
void hutituki(HDC hdc, int b_x, int b_y, int l_x, int l_y, int color, int color2){
	HPEN hpen;
	hpen = CreatePen(PS_SOLID, 2, color);
	SelectObject(hdc, hpen);

	SelectObject(hdc, CreateSolidBrush(color2));
	Rectangle(hdc, b_x, b_y, b_x + l_x, b_y + l_y);
	DeleteObject(hpen);

}

//透明黒四角
void toumei_b(HDC hdc, int b_x, int b_y, int l_x, int l_y, int alpha, HDC hBuffer, HBITMAP hBitmap){
	BLENDFUNCTION blendFunction;

	SelectObject(hBuffer, hBitmap);
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.AlphaFormat = 0;
	blendFunction.SourceConstantAlpha = alpha;
	AlphaBlend(hdc, b_x, b_y, l_x, l_y, hBuffer, 0, 0, 10, 10, blendFunction);
}

//フォント色サイズ可変テキスト
void tvdke(HDC hdc, int b_x, int b_y, int l_x, LPCTSTR tempst,int color){
	HFONT hFont;

	hFont = CreateFont(
		l_x, 0, 0, 100, FW_BOLD, FALSE, FALSE, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		VARIABLE_PITCH | FF_ROMAN, TEXT("Mgen+ 1pp regular")
		);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	SelectObject(hdc, hFont);
	TextOut(hdc, b_x, b_y, tempst, lstrlen(tempst));
	SelectObject(hdc, GetStockObject(SYSTEM_FONT));
	DeleteObject(hFont);

}

//フォント色サイズ可変テキスト、特殊文字処理付き
void tvdke2(HDC hdc, int b_x, int b_y, int l_x, LPCTSTR tempst, int color){
	static LPCTSTR temp_char[20];
	static CHAR re_Ch[100];
	int i = 0;

	tvdke(hdc, b_x, b_y, l_x, tempst, color);

	temp_char[0] = tempst;

	for (int i = 0; strstr(temp_char[i] + 2, TEXT("~c")) != NULL; i++){
		temp_char[i + 1] = strstr(temp_char[i] + 2, TEXT("~c"));

	}
}

//組み立ててるプログラムの表示
void proram_hyouji(HDC hdc, int *built_programing, item *Control_item_info, item *Terms_item_info){
	HDC hBuffer;
	for (int j = 0; j < 100; j++){

		
	}
}

//配列の書き換え
void kakikae(int mouse_x, int mouse_y, int mouse_have, jouhou *program){
	int b_x = 446, b_y = 35;
	if (b_x <= mouse_x&&b_y <= 35){
		(*(program + (int)((mouse_y - 3) / 32.0))).ID = mouse_have;
	}
}

//登録されてるアイテム作成
void terms_item_create(HWND hwnd, HINSTANCE t_ins, item *item_info){
	int b_x = 80, b_y = 320;
	int l_x = 64, l_y = 24;
	int s_x = 110, s_y = 52;

	for (int i = 0; i < 20; i++){
		for (int j = 0; j < ((item_info + i)->edi_number); j++){
			e_name.edi[i * 10 + j] = CreateWindow(
				TEXT("EDIT"),NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
				b_x + (item_info + i)->edit_info[j].point + s_x*(i % 3), b_y +5+ (i / 3)*s_y, (item_info + i)->edit_info[j].size, l_y, hwnd, (HMENU)1,
				t_ins, NULL
				);
		}
	}
}

//非表示アイテムの影表示
void hihkage(HDC hdc, HDC hBuffer, HBITMAP hBitmap, item *item_info){
	int b_x = 67, b_y = 236;
	for (int i = 0; i <20; i++){
		if (!((item_info + i)->condition)){
			if (i == 0){
				toumei_b(hdc, 67, 52, 352, 32, 160, hBuffer, hBitmap);
				toumei_b(hdc, 67, 84, 20, 32, 160, hBuffer, hBitmap);
				toumei_b(hdc, 67, 116, 142, 32, 160, hBuffer, hBitmap);
			}
			else if (i == 1){
				toumei_b(hdc, 67, 152, 352, 32, 160, hBuffer, hBitmap);
				toumei_b(hdc, 67, 184, 20, 32, 160, hBuffer, hBitmap);
				toumei_b(hdc, 67, 216, 142, 32, 160, hBuffer, hBitmap);
			}
			else{
				for (int j = 0; j < ((item_info + i)->edi_number); j++){
					ShowWindow(e_name.edi[i * 10 + j], SW_HIDE);
				}

				toumei_b(hdc, b_x, b_y + 32 *i, (item_info + i)->size, 26, 160, hBuffer, hBitmap);

			}
		}
		else{
			for (int j = 0; j < ((item_info + i)->edi_number); j++){
				ShowWindow(e_name.edi[i * 10 + j], SW_SHOW);
			}
		}
	}
}

//アイテムの選択
int sentaku(int mouse_x, int mouse_y, item *Control_item_info, item *Terms_item_info){
	int ans = 0;

	int b_x, b_y;
	int l_x, l_y;
	int s_x, s_y;

	b_x = control_b_x;
	b_y = control_b_y;
	l_x = control_l_x;
	l_y = control_l_y;
	s_x = control_s_x;
	s_y = control_s_y;
	if (b_x <= mouse_x&&mouse_x <= b_x + s_x + l_x&&b_y <= mouse_y&&mouse_y <= b_y + s_y * 2 + l_y){
		if (b_x <= mouse_x&&mouse_x <= b_x + l_x){
			for (int i = 0; i<5; i++){
				if (b_y + s_y*i <= mouse_y&&mouse_y <= b_y + s_y*i + l_y)ans = (Control_item_info+ i * 2)->ID;
			}
		}
		else if (b_x + s_x <= mouse_x&&mouse_x <= b_x + l_x + s_x){
			for (int i = 0; i < 5; i++){
				if (b_y + s_y*i <= mouse_y&&mouse_y <= b_y + s_y*i + l_y)ans = (Control_item_info + 1 + i * 2)->ID;
			}
		}
	}
	else{
		b_x = terms_b_x;
		b_y = terms_b_y;
		l_x = terms_l_x;
		l_y = terms_l_y;
		s_x = terms_s_x;
		s_y = terms_s_y;
		if (b_x <= mouse_x&&mouse_x <= b_x + s_x * 2 + l_x&&b_y <= mouse_y&&mouse_y <= b_y + s_y * 5 + l_y){
			if (b_x <= mouse_x&&mouse_x <= b_x + l_x){
				for (int i = 0; i<5; i++){
					if (b_y + s_y*i <= mouse_y&&mouse_y <= b_y + s_y*i + l_y)ans = (Terms_item_info + i * 2)->ID;
				}
			}
			else if (b_x + s_x <= mouse_x&&mouse_x <= b_x + l_x + s_x){
				for (int i = 0; i < 5; i++){
					if (b_y + s_y*i <= mouse_y&&mouse_y <= b_y + s_y*i + l_y)ans = (Terms_item_info + 1 + i * 2)->ID;
				}
			}
			else if (b_x + s_x * 2 <= mouse_x&&mouse_x <= b_x + l_x + s_x * 2){
				for (int i = 0; i < 5; i++){
					if (b_y + s_y*i <= mouse_y&&mouse_y <= b_y + s_y*i + l_y)ans = (Terms_item_info + 2 + i * 2)->ID;
				}
			}
		}
	}


	return ans;
}

//制御アイテム表示
void control_hyouji(HDC hdc, item *Control_item_info){
	HDC hBuffer;
	hBuffer = CreateCompatibleDC(hdc);
	for (int i = 0; ((Control_item_info + i)->condition)!=128; i++){
		SelectObject(hBuffer, (Control_item_info+i)->image);
		StretchBlt(hdc, control_b_x + control_s_x*(i % 2), control_b_y + (i / 2)*control_s_y, control_l_x, control_l_y, hBuffer, 0, 0, control_n_x, control_n_y, SRCCOPY);
	}
	DeleteDC(hBuffer);
};

//条件アイテム表示
void terms_hyouji(HDC hdc, item *Terms_item_info){
	HDC hBuffer;
	hBuffer = CreateCompatibleDC(hdc);
	for (int i = 0; ((Terms_item_info + i)->condition) != 128; i++){
		SelectObject(hBuffer, (Terms_item_info + i)->image);
		StretchBlt(hdc, terms_b_x + terms_s_x*(i % 3), terms_b_y + (i / 3)*terms_s_y, terms_l_x, terms_l_y, hBuffer, 0, 0, terms_n_x, terms_n_y, SRCCOPY);
	}
	DeleteDC(hBuffer);
}

//持っているアイテム表示
void have_hyouji(HDC hdc,int mouse_have,int mouse_x,int mouse_y, item *Terms_item_info, item *Control_item_info){
	HDC hBuffer;
	BLENDFUNCTION blendFunction;

	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.AlphaFormat = 0;
	blendFunction.SourceConstantAlpha = 128;

	hBuffer = CreateCompatibleDC(hdc);

	for (int i = 0; ((Terms_item_info + i)->condition) != 128; i++){
		if (((Terms_item_info + i)->ID) == mouse_have){
			SelectObject(hBuffer, (Terms_item_info + i)->image);
			AlphaBlend(hdc, mouse_x, mouse_y, terms_l_x, terms_l_y, hBuffer, 0, 0, terms_n_x, terms_n_y, blendFunction);
		}
	}

	for (int i = 0; ((Control_item_info + i)->condition) != 128; i++){
		if (((Control_item_info + i)->ID) == mouse_have){
			SelectObject(hBuffer, (Control_item_info + i)->image);
			AlphaBlend(hdc, mouse_x, mouse_y, control_l_x, control_l_y, hBuffer, 0, 0, control_n_x, control_n_y, blendFunction);
		}
	}
	DeleteDC(hBuffer);
}

//プログラム書き換え
void put_having_programing(int mouse_have, int mouse_x, int mouse_y, int *built_programing){
	int b_x = 420, b_y = 10;
	int l_x = 100, l_y = 32;
	if (b_x < mouse_x&&b_y < mouse_y){
		*(built_programing + (mouse_y - b_y) / l_y) = mouse_have;
	}

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc, hBuffer;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap[10];
	static HBITMAP control_Bitmap[10];
	static RECT Rt, Redraw;
	static int mouse_have = 0;
	static int mouse_x, mouse_y;
	static int built_programing[100];
	static jouhou program[101];
	static item item_info[101];
	static item Control_item_info[10];
	static item Terms_item_info[30];
	static HINSTANCE t_ins;
	CHAR chStr[1000];
	BLENDFUNCTION blendFunction;
	HRGN hrgn;

	switch (msg) {
	case WM_DESTROY:
		DeleteObject(hBitmap[0]);
		DeleteObject(hBitmap[1]);
		DeleteObject(hBitmap[2]);

		DeleteObject(Control_item_info[0].image);
		DeleteObject(Control_item_info[1].image);
		DeleteObject(Control_item_info[2].image);
		DeleteObject(Control_item_info[3].image);
		DeleteObject(Control_item_info[4].image);

		DeleteObject(Terms_item_info[0].image);
		DeleteObject(Terms_item_info[1].image);
		PostQuitMessage(0);
		return 0;


	case WM_CREATE:
		//if情報
		Control_item_info[0].ID = 2;
		Control_item_info[0].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("IF"));
		Control_item_info[0].write_text = TEXT("");
		Control_item_info[0].edi_number = 0;
		//not if情報
		Control_item_info[1].ID = 3;
		Control_item_info[1].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("NOT_IF"));
		Control_item_info[1].write_text = TEXT("");
		Control_item_info[1].edi_number = 0;
		//while情報
		Control_item_info[2].ID = 4;
		Control_item_info[2].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("WHILE"));
		Control_item_info[2].write_text = TEXT("");
		Control_item_info[2].edi_number = 0;
		//not_while情報
		Control_item_info[3].ID = 5;
		Control_item_info[3].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("NOT_WHILE"));
		Control_item_info[3].write_text = TEXT("");
		Control_item_info[3].edi_number = 0;
		//END情報
		Control_item_info[4].ID = 6;
		Control_item_info[4].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("END"));
		Control_item_info[4].write_text = TEXT("");
		Control_item_info[4].edi_number = 0;
		//終了
		Control_item_info[5].condition = 128;

		//ラインセンサ反応情報
		Terms_item_info[0].ID = 102;
		Terms_item_info[0].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("LINE"));
		Terms_item_info[0].write_text = TEXT("");
		Terms_item_info[0].edi_number = 0;
		//ソッキョセンサ反応情報
		Terms_item_info[1].ID = 103;
		Terms_item_info[1].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("LINE"));
		Terms_item_info[1].write_text = TEXT("");
		Terms_item_info[1].edi_number = 0;
		//タイマー情報
		Terms_item_info[2].ID = 104;
		Terms_item_info[2].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("TIMER"));
		Terms_item_info[2].write_text = TEXT("");
		Terms_item_info[2].edi_number = 1;
		Terms_item_info[2].edit_info[0].point = 17;
		Terms_item_info[2].edit_info[0].size = 28;
		//タイマー情報
		Terms_item_info[3].ID = 105;
		Terms_item_info[3].image = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("TIMER"));
		Terms_item_info[3].write_text = TEXT("");
		Terms_item_info[3].edi_number = 1;
		Terms_item_info[3].edit_info[0].point = 17;
		Terms_item_info[3].edit_info[0].size = 28;
		//終了
		Terms_item_info[4].condition = 128;

		t_ins = ((LPCREATESTRUCT)(lp))->hInstance;
		terms_item_create(hwnd, t_ins, Terms_item_info);
		GetClientRect(hwnd, (LPRECT)&Rt);
		program[0].ID = 1;

		hBitmap[0] = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance,TEXT("BG"));
		hBitmap[1] = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("SQUARE"));
		hBitmap[2] = LoadBitmap(((LPCREATESTRUCT)lp)->hInstance, TEXT("SQUARE_B"));

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetStretchBltMode(hdc, HALFTONE);
		hBuffer = CreateCompatibleDC(hdc);

		//BG
		SelectObject(hBuffer, hBitmap[0]);
		StretchBlt(hdc, 0, 0, tyousetu(Rt, 1, XMAX), tyousetu(Rt, 0, YMAX), hBuffer, 0, 0, 1280, 960, SRCCOPY);

		//組み立て枠
		SelectObject(hBuffer, hBitmap[1]);
		blendFunction.BlendOp = AC_SRC_OVER;
		blendFunction.BlendFlags = 0;
		blendFunction.AlphaFormat = 0;
		blendFunction.SourceConstantAlpha = 68;
		AlphaBlend(hdc, 0, 0, 420,tyousetu(Rt,0, YMAX), hBuffer, 0, 0, 10, 10, blendFunction);
		
		//メニュー枠
		SelectObject(hBuffer, hBitmap[1]);
		StretchBlt(hdc, 0, 0, 60, tyousetu(Rt, 0, YMAX), hBuffer, 0, 0, 10, 10, SRCCOPY);

		//nakanuki(hdc, 65, 0, 355, 50, RGB(255, 255, 255));
		//tvdke(hdc, 190,  2, 47, TEXT("制御"), RGB(255, 255, 255));

		//nakanuki(hdc, 65, 250, 355, 50, RGB(255, 255, 255));
		//tvdke(hdc, 190, 252, 47, TEXT("条件"), RGB(255, 255, 255));


		//プログラム表示
		//proram_hyouji(hdc,built_programing, Terms_item_info, Control_item_info);

		//制御のアイテム表示
		control_hyouji(hdc, Control_item_info);

		//条件のアイテム表示
		terms_hyouji(hdc, Terms_item_info);

		//持ってるのアイテム表示
		have_hyouji(hdc, mouse_have, mouse_x, mouse_y, Control_item_info, Terms_item_info);


		wsprintf(chStr, "%d,%d,%d,%d,%d,%d", mouse_have, built_programing[0], built_programing[1], built_programing[2], built_programing[3], built_programing[4]);
		TextOut(hdc, 100, 700, chStr, lstrlen(chStr));

		DeleteDC(hBuffer);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_SIZE:
		GetClientRect(hwnd, (LPRECT)&Rt);
		return 0;

	case WM_MOUSEMOVE:
		mouse_x = LOWORD(lp);
		mouse_y = HIWORD(lp);
		Redraw.left = mouse_x-100;
		Redraw.top = mouse_y - 100;
		Redraw.right = mouse_x+250;
		Redraw.bottom = mouse_y + 100;
		if (mouse_have)InvalidateRect(hwnd, &Redraw, FALSE);
		return 0;

	case WM_LBUTTONDOWN:
		mouse_have = sentaku(mouse_x, mouse_y, Control_item_info, Terms_item_info);
		return 0;

	case WM_LBUTTONUP:

		//プログラミングの書き換え
		put_having_programing(mouse_have, mouse_x, mouse_y, built_programing);
		mouse_have = 0;
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = TEXT("KITTY");

	if (!RegisterClass(&winc)) return -1;

	hwnd = CreateWindow(
		TEXT("KITTY"), TEXT("KIRIRIN"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		XMAX, YMAX,
		NULL, NULL,
		hInstance, NULL
		);

	if (hwnd == NULL) return -1;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}