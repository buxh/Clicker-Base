#include "utils.hpp"
#include "clicker.hpp"

typedef LONG NTSTATUS, * PNTSTATUS;
#define STATUS_SUCCESS (0x00000000)

typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

inline RTL_OSVERSIONINFOW utils::compatibility::GetRealOSVersion() {
	HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
	if (hMod) {
		RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
		if (fxPtr != nullptr) {
			RTL_OSVERSIONINFOW staind = { 0 };
			staind.dwOSVersionInfoSize = sizeof(staind);
			if (STATUS_SUCCESS == fxPtr(&staind)) {
				return staind;
			}
		}
	}
	RTL_OSVERSIONINFOW staind = { 0 };
	return staind;
}

inline void utils::visuals() {
	// make your own ui
	//
	SetConsoleTitleA("");
	HWND hwnd = GetConsoleWindow();
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
	system("mode 73, 20");
	utils::ShowConsoleCursor(false);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	ShowWindow(hwnd, SW_NORMAL);
}

void utils::compatibility::check() {
	auto deploy = utils::compatibility::GetRealOSVersion();
	if (deploy.dwBuildNumber == 18363) {
		utils::thread::launch::normal();
	}
	else {
		utils::thread::launch::compatibility();
	}
}

void utils::thread::launch::compatibility() {
	if (utils::debug::logs == true) { std::cout << "[+] Foreign winver found" << std::endl; }
	Sleep(250);
	if (utils::debug::logs == true) { std::cout << "[+] Deploying compatibility mode" << std::endl; }
	std::chrono::high_resolution_clock::now();
	SetThreadPriority(std::this_thread::get_id, THREAD_PRIORITY_TIME_CRITICAL);
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
}

void utils::thread::launch::normal() {
	std::chrono::high_resolution_clock::now();
	SetThreadPriority(std::this_thread::get_id, THREAD_PRIORITY_NORMAL);
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
}

void utils::ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

// credit to eternal (github.com/git-eternal)
//
void utils::selfdestruct::selfdelete()
{
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];

	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	StringCbPrintf(szCmd, 2 * MAX_PATH, 0, ("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\""), szModuleName);

	CreateProcess(NULL, szCmd,
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW,
		NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
}

void utils::init() {
	utils::visuals();
	if (utils::debug::logs == true) { std::cout << "[+] Applied Console Style" << std::endl; }
	Sleep(100);
	if (utils::debug::logs == true) { std::cout << "[+] Checking windows version" << std::endl; }
	utils::compatibility::check();
	if (utils::debug::logs == true) { std::cout << "[+] Launching clicker thread" << std::endl; }
	clicker::thread();
}