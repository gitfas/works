// calcPlus.js -------------
// �e�L�X�g�d��{
var WshShell = new ActiveXObject("WScript.Shell");
var outStr="" , calStr="" , preStr="" , postStr="";
var re = /(abs|acos|asin|atan|atan2|ceil|cos|exp|floor|log|max|min|pow|random|round|sin|s
qrt|tan)/g;
var selStr = Editor.GetSelectedString(0);   // �I�𕶎�����擾
Editor.MoveHistSet();   // ���݈ʒu���ړ������ɓo�^
if(selStr == ""){   // �I��͈͂��Ȃ��Ȃ�ȉ����s�Ȃ�
    Editor.BeginSelect();   // �͈͑I���J�n
    Editor.GoLineTop(1);    // �s���Ɉړ�(�܂�Ԃ��P��)
    selStr = Editor.GetSelectedString(0);   // �I�𕶎�����擾
    selStr.match(/^(.*?)([ %&(-/0-9<>M^a-il-uwx|~�K�K��]+)( *?=? *?)$/);
    preStr = RegExp.$1;     // �v�Z���̑O
    calStr = RegExp.$2;     // �v�Z������
    postStr = RegExp.$3;    // �v�Z���̌�
    if(calStr != ""){       // �v�Z���Ǝv������̂�����Ȃ�
        selStr = calStr;    // selStr �͍�Ɨp�G���A�Ƃ��ė��p�R�s�[�ޔ�
    } else {                // �v�Z����������Ȃ��Ƃ�(�}�b�`���ĂȂ�)
        preStr = selStr;    // �s�������Ȃ��悤�ɂ��ׂĂ��c��
    }
} else {                    // �����I�ɑI��͈͂ɂ��v�Z���̎w�肪����
    calStr = selStr;        // �̂ŁA���̂܂܌v�Z���Ƃ���B
}
if(calStr.match(/Math\./) == null)          // Math. ���g���ĂȂ��Ȃ�
    calStr = calStr.replace(re, "Math\.$&");  // �Z�p�֐�����Math.�t��
calStr = calStr.replace(/(��|�K|�K)/g, "*3.141592653589793238/180");  // Deg��Rad
try {
    outStr = eval(calStr);                  // �������ʂŒu��������
    if(postStr != "") outStr = selStr + postStr + outStr;
    if(preStr != "") outStr = preStr + outStr;
    Editor.InsText(outStr);             // �I��͈͕����ɓ\��t����
    try {   // �v�Z���̕\���A�܂��Ƀg���C
        var tryStr = "calcPopup.vbs \"" + selStr + "\""
        eval("WshShell.run(tryStr);");
    } catch (error) {
    // �G���[�ł��X���[����
    }
} catch (error) {  // eval �̃G���[���g���b�v�H
    WshShell.Popup(calStr+"\n"+error ,0,"�v�Z���ɊԈႢ",0);
    Editor.CancelMode();    // �e�탂�[�h�̎�����
    Editor.MoveHistPrev();  // �ړ�����:�O��
}
