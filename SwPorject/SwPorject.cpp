// SwPorject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SwClient.h"
#include "MyUsbMgr.h"
#include "unitl.h"
#include <thread>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址

SwClient *sc = NULL;
const int ClientCount = 2;

LRESULT CALLBACK KeyHookFunc(int nCode, WPARAM wParam, LPARAM lParam)
{
	int aa = 1;
	if (nCode >= 0)
	{
		int vkCode = 0;
		if (wParam == WM_KEYDOWN)
		{
			vkCode = *(int *)lParam;
			if (vkCode == VK_F12)
			{
				LOG_MSG(DINFO, "Pause");
				for (int i = 0; i < ClientCount; i++)
				{
					//sc[i].Pause();
				}
			}
		}
		if (wParam == WM_KEYUP)
		{
			vkCode = *(int *)lParam;
			
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
void StartKeyBoardHookThread()
{
	
}

int main()
{
	MyUsbMgr::GetInstance()->Init();
	if (MyUsbMgr::GetInstance()->Start() == 0)
	{
		Sleep(100);
		HANDLE handle;
		sc = new SwClient[ClientCount];
		std::thread client[ClientCount];
		
		/*std::thread  hookThread = std::thread([] {
			HHOOK hhook = 0;
			hhook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyHookFunc, 0, 0);
			MSG msg;
			while (GetMessage(&msg, NULL, NULL, NULL))
			{

			}
			UnhookWindowsHookEx(hhook);
		});*/

		client[0] = std::thread([] {
			SwClient *sc = new SwClient();
			sc->Init();
			/*for (int i = 0; i < 10; i++)
			{
				sc->KeyBtnClickWithCtrl('A');
				Sleep(60);
				sc->KeyBtnClickWithCtrl('C');
				Sleep(60);
				sc->KeyBtnClickWithCtrl('V');
				Sleep(60);
			}*/
			sc->Start(0, 0, 4095, 4095);
			sc->Test();
		});
		/*client[1] = std::thread([] {
			SwClient *sc = new SwClient();
			sc->Init();
			sc->Start(900, 0, 1000, 700);
			sc->Test();
		});*/
		Sleep(232322223);
	}
	else
	{
		LOG_MSG(DERROR, "Usb Error.");
	}
	return 0;
}
