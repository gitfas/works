start = " ";        // 行頭
separator = " : ";  // 区切り
end = "";           // 行末
zeros = "00000000"; // "0" 埋め用

// 選択範囲がなければ全選択
if(Editor.IsTextSelected() == 0)
{
    Editor.SelectAll();
}

// 通常の選択範囲が存在する場合のみ処理 (矩形選択のときは何もしない)
if(Editor.IsTextSelected() == 1)
{
    var beginLine = Editor.GetSelectLineFrom(); // 選択開始行番号
    var endLine = Editor.GetSelectLineTo();     // 選択終了行番号
    var lineCount = endLine - beginLine;        // 選択されている行数
    var len = String(lineCount).length;         // 行数の桁数
    
    var result = "";    // 結果格納用
    for(var i = 0; i < lineCount; i++)
    {
        var lineNumber = (zeros + (i + 1)).slice(-len);     // 行番号を "0" 埋めで生成
        var lineContent = Editor.GetLineStr(beginLine + i); // 行内容を取得
        
        // "行頭 + 行番号 + 区切り + 行内容 + 行末" を結果に追加
        result += start + lineNumber + separator + lineContent + end;
    }
    
    // 結果を入力
    Editor.InsText(result);
}
