//
// Created by Kalle on 16.07.2026.
//

#include "file_dialog.h"

#include <ObjectArray.h>
#include <shobjidl_core.h>
std::wstring FileDialoger::OpenFileDialog() {
  HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

  IFileOpenDialog* dialog = nullptr;
  hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr,
                        CLSCTX_ALL, IID_PPV_ARGS(&dialog));

  if (SUCCEEDED(hr)) {
    COMDLG_FILTERSPEC filters[] =
    {
      {L"Fichiers JSON", L"*.json"}
    };

    dialog->SetFileTypes(1, filters);
    dialog->SetFileTypeIndex(1);
    hr = dialog->Show(nullptr);

    if (SUCCEEDED(hr)) {
      IShellItem* item = nullptr;
      hr = dialog->GetResult(&item);

      if (SUCCEEDED(hr)) {
        PWSTR path = nullptr;
        item->GetDisplayName(SIGDN_FILESYSPATH, &path);

        std::wstring result(path);

        CoTaskMemFree(path);
        item->Release();
        dialog->Release();
        CoUninitialize();

        return result;
      }
    }

    dialog->Release();
  }

  CoUninitialize();
  return L"";

}