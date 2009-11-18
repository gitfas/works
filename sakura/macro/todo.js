// �I��͈͂��Ȃ���΍s�I��
if(Editor.IsTextSelected() == 0)
{
    Editor.GoLineTop(0);
    Editor.Down_Sel(0);
}

// �ʏ�̑I��͈͂����݂���ꍇ�̂ݏ��� (��`�I���̂Ƃ��͉������Ȃ�)
if(Editor.IsTextSelected() == 1)
{
    var beginLine = Editor.GetSelectLineFrom();    // �I���J�n�s�ԍ�
    var endLine = Editor.GetSelectLineTo();        // �I���I���s�ԍ�
    var lineCount = endLine - beginLine;        // �I������Ă���s��
    
    // 1 �s�ȏ゠��ꍇ
    if(0 < lineCount)
    {
        var result = "";    // ���ʊi�[�p
        for(var i = 0; i < lineCount; i++)
        {
            // �s�̓��e���擾
            var lineContent = Editor.GetLineStr(beginLine + i);
            
            if(lineContent.match(/^\[ \]/))
            {
                // [ ] �� [+]
                lineContent = "[+] " + lineContent.substr(4);
            }
            else if(lineContent.match(/^\[\+\]/))
            {
                // [+] �� [ ]
                lineContent = "[ ] " + lineContent.substr(4);
            }
            else
            {
                // �V�K�� [ ]
                lineContent = "[ ] " + lineContent;
            }
            
            result += lineContent;
        }
        
        // ���ʂ����
        Editor.InsText(result);
    }
}
