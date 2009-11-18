// calcPlus.js -------------
// テキスト電卓＋
var WshShell = new ActiveXObject("WScript.Shell");
var outStr="" , calStr="" , preStr="" , postStr="";
var re = /(abs|acos|asin|atan|atan2|ceil|cos|exp|floor|log|max|min|pow|random|round|sin|s
qrt|tan)/g;
var selStr = Editor.GetSelectedString(0);   // 選択文字列を取得
Editor.MoveHistSet();   // 現在位置を移動履歴に登録
if(selStr == ""){   // 選択範囲がないなら以下を行なう
    Editor.BeginSelect();   // 範囲選択開始
    Editor.GoLineTop(1);    // 行頭に移動(折り返し単位)
    selStr = Editor.GetSelectedString(0);   // 選択文字列を取得
    selStr.match(/^(.*?)([ %&(-/0-9<>M^a-il-uwx|~゜゜°]+)( *?=? *?)$/);
    preStr = RegExp.$1;     // 計算式の前
    calStr = RegExp.$2;     // 計算式部分
    postStr = RegExp.$3;    // 計算式の後
    if(calStr != ""){       // 計算式と思われるものがあるなら
        selStr = calStr;    // selStr は作業用エリアとして利用コピー退避
    } else {                // 計算式が見つからないとき(マッチしてない)
        preStr = selStr;    // 行が消えないようにすべてを残す
    }
} else {                    // 明示的に選択範囲により計算式の指定がある
    calStr = selStr;        // ので、そのまま計算式とする。
}
if(calStr.match(/Math\./) == null)          // Math. が使われてないなら
    calStr = calStr.replace(re, "Math\.$&");  // 算術関数名にMath.付け
calStr = calStr.replace(/(°|゜|゜)/g, "*3.141592653589793238/180");  // Deg→Rad
try {
    outStr = eval(calStr);                  // 式を結果で置き換えて
    if(postStr != "") outStr = selStr + postStr + outStr;
    if(preStr != "") outStr = preStr + outStr;
    Editor.InsText(outStr);             // 選択範囲部分に貼り付ける
    try {   // 計算式の表示、まさにトライ
        var tryStr = "calcPopup.vbs \"" + selStr + "\""
        eval("WshShell.run(tryStr);");
    } catch (error) {
    // エラーでもスルーする
    }
} catch (error) {  // eval のエラーをトラップ？
    WshShell.Popup(calStr+"\n"+error ,0,"計算式に間違い",0);
    Editor.CancelMode();    // 各種モードの取り消し
    Editor.MoveHistPrev();  // 移動履歴:前へ
}
