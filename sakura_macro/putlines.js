start = " ";        // �s��
separator = " : ";  // ��؂�
end = "";           // �s��
zeros = "00000000"; // "0" ���ߗp

// �I��͈͂��Ȃ���ΑS�I��
if(Editor.IsTextSelected() == 0)
{
    Editor.SelectAll();
}

// �ʏ�̑I��͈͂����݂���ꍇ�̂ݏ��� (��`�I���̂Ƃ��͉������Ȃ�)
if(Editor.IsTextSelected() == 1)
{
    var beginLine = Editor.GetSelectLineFrom(); // �I���J�n�s�ԍ�
    var endLine = Editor.GetSelectLineTo();     // �I���I���s�ԍ�
    var lineCount = endLine - beginLine;        // �I������Ă���s��
    var len = String(lineCount).length;         // �s���̌���
    
    var result = "";    // ���ʊi�[�p
    for(var i = 0; i < lineCount; i++)
    {
        var lineNumber = (zeros + (i + 1)).slice(-len);     // �s�ԍ��� "0" ���߂Ő���
        var lineContent = Editor.GetLineStr(beginLine + i); // �s���e���擾
        
        // "�s�� + �s�ԍ� + ��؂� + �s���e + �s��" �����ʂɒǉ�
        result += start + lineNumber + separator + lineContent + end;
    }
    
    // ���ʂ����
    Editor.InsText(result);
}
