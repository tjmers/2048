
#include <iostream>

#include <UIAutomation.h>

void ExtractWebpageText(HWND hwnd) {
    CoInitialize(NULL); // Initialize COM

    IUIAutomation* automation = nullptr;
    CoCreateInstance(CLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER, IID_IUIAutomation, (void**)&automation);

    IUIAutomationElement* rootElement = nullptr;
    automation->ElementFromHandle(hwnd, &rootElement);

    if (rootElement) {
        IUIAutomationTextPattern* textPattern = nullptr;
        rootElement->GetCurrentPattern(UIA_TextPatternId, (IUnknown**)&textPattern);

        if (textPattern) {
            IUIAutomationTextRange* textRange;
            textPattern->get_DocumentRange(&textRange);

            BSTR text;
            textRange->GetText(-1, &text);

            std::wcout << L"Extracted Text: " << text << std::endl;
            SysFreeString(text);
            textRange->Release();
            textPattern->Release();
        }
        rootElement->Release();
    }
    automation->Release();
    CoUninitialize(); // Uninitialize COM
}

int main() {
    HWND hwnd = FindWindowA(NULL, "2048 Game - Play 2048 Game Online - Google Chrome"); // Find the browser window
    if (hwnd) {
        ExtractWebpageText(hwnd);
    } else {
        std::cout << "Browser window not found!" << std::endl;
    }
    return 0;
}