' OpenIncludeFile.vbs
' 
' 現在行にある #include <file.h>、#include "file.h" のfile.hを開く。
' 検索対象は環境変数の INCLUDE と現在開いているファイルのフォルダ内

Call Main

' メイン処理
Sub Main()
    Dim objShell
    Dim sDistFileName, sCurDirName
    Dim i, pos

    Set objShell = CreateObject("Wscript.Shell")
    sIncPath = objShell.ExpandEnvironmentStrings("%INCLUDE%")

    sDistFileName = getIncludeFileName(Editor.GetLineStr(0))
    sCurDirName = getCurrentFolderName()

    If openFile(sCurDirName & sDistFileName) Then Exit Sub

    i = 1
    Do While True
        pos = InStr(i, sIncPath, ";")
        If IsNull(pos) Then Exit Do
        If pos = 0 Then
            If openFile(Mid(sIncPath, i)) Then Exit Sub
            Exit Do
        End If
        If openFile(Mid(sIncPath, i, pos - i)) Then Exit Sub
        i = pos + 1
    Loop
End Sub

' インクルードファイル名取得
Function getIncludeFileName(sLine)
    Dim pos, endpos
 
    getIncludeFileName = ""
    pos = InStr(1, sLine, "<")
    If pos = 0 Then
        pos = InStr(1, sLine, """")
        endpos = InStr(pos + 1, sLine, """")
    Else
        endpos = InStr(pos + 1, sLine, ">")
    End If

    If pos = 0 Or endpos = 0 Then Exit Function
    pos = pos + 1
    getIncludeFileName = Mid(sLine, pos, endpos - pos)
 
End Function

' 現在のフォルダ名取得
Function getCurrentFolderName()
    Dim pos
    Dim sCurFileName
 
    getCurrentFolderName = ""
 
    sCurFileName = GetFileName()
    pos = InStrRev(sCurFileName, "\")
    If pos = 0 Then Exit Function
    getCurrentFolderName = Mid(sCurFileName, 1, pos)
End Function

' ファイルが存在していたら開く
Function openFile(sPath)
    Dim fso
    Set fso = CreateObject("Scripting.FileSystemObject")
 
    openFile = False
    If (fso.FileExists(sPath)) Then
        Editor.FileOpen (sPath)
        openFile = True
    End If
 
End Function
