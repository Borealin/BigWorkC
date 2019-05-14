//
// Created by Borealin on 2019/5/14.
//
#include <stdlib.h>
#include <stdio.h>
#include <shlobj.h>
#include <windows.h>

void SaveGame(){
    TCHAR szPathName[MAX_PATH];
    BROWSEINFO bInfo = { 0 };
    bInfo.hwndOwner = GetForegroundWindow();//父窗口
    bInfo.lpszTitle = TEXT("浏览文件夹");
    bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    LPITEMIDLIST lpDlist;
    //lpDlist = SHBrowseForFolder(&bInfo);
    //if (lpDlist != NULL)
    if(SHBrowseForFolder(&bInfo))
    {
        SHGetPathFromIDList(lpDlist, szPathName);
        MessageBox(NULL, szPathName, L"Dir Name", MB_OK);

    }
}
void RecoverGame(){
}
