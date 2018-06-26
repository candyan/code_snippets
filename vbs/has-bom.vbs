Option Explicit

Const UTF8_BOM = "﻿"
Const UTF16BE_BOM = "��"
Const UTF16LE_BOM = "��"

Const ForReading = 1
Const ForWriting = 2

Dim fso
Set fso = WScript.CreateObject("Scripting.FileSystemObject")

Dim f
f = WScript.Arguments.Item(0)

Dim t
t = fso.OpenTextFile(f, ForReading).ReadAll

If Left(t, 3) = UTF8_BOM Then
  MsgBox "UTF-8-BOM detected!"
ElseIf Left(t, 2) = UTF16BE_BOM Then
  MsgBox "UTF-16-BOM (Big Endian) detected!"
ElseIf Left(t, 2) = UTF16LE_BOM Then
  MsgBox "UTF-16-BOM (Little Endian) detected!"
Else
  MsgBox "No BOM detected!"
End If