// 選択範囲がなければ行選択
if(Editor.IsTextSelected() == 0)
{
    Editor.GoLineTop(0);
    Editor.Down_Sel(0);
}

// 通常の選択範囲が存在する場合のみ処理 (矩形選択のときは何もしない)
if(Editor.IsTextSelected() == 1)
{
    var beginLine = Editor.GetSelectLineFrom();    // 選択開始行番号
    var endLine = Editor.GetSelectLineTo();        // 選択終了行番号
    var lineCount = endLine - beginLine;        // 選択されている行数
    
    // 1 行以上ある場合
    if(0 < lineCount)
    {
        var result = "";    // 結果格納用
        for(var i = 0; i < lineCount; i++)
        {
            // 行の内容を取得
            var lineContent = Editor.GetLineStr(beginLine + i);
            
            if(lineContent.match(/^\[ \]/))
            {
                // [ ] → [+]
                lineContent = "[+] " + lineContent.substr(4);
            }
            else if(lineContent.match(/^\[\+\]/))
            {
                // [+] → [ ]
                lineContent = "[ ] " + lineContent.substr(4);
            }
            else
            {
                // 新規に [ ]
                lineContent = "[ ] " + lineContent;
            }
            
            result += lineContent;
        }
        
        // 結果を入力
        Editor.InsText(result);
    }
}
