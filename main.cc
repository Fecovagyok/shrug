#include <windows.h>

#include <cwchar>
#include <iostream>

#define SHRUG L"¯\\_(ツ)_/¯"

int main() {
  HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, sizeof(SHRUG));
  if (hMem == NULL) {
    std::cerr << "Bad GlobalAlloc" << std::endl;
    return 1;
  }
  wchar_t* buffer = (wchar_t*)GlobalLock(hMem);
  wcscpy_s(buffer, sizeof(SHRUG) / sizeof(wchar_t), SHRUG);
  GlobalUnlock(hMem);

  BOOL ret = OpenClipboard(NULL);
  if (!ret) {
    std::cerr << "Could not open clipboard" << std::endl;
    return 1;
  }

  if (!EmptyClipboard()) {
    std::cerr << "Emptying clipboard failed" << std::endl;
    return 1;
  }

  if (!SetClipboardData(CF_UNICODETEXT, hMem)) {
    std::cerr << "Setting clipboard data failed" << std::endl;
    return 1;
  }

  CloseClipboard();

  return 0;
}
