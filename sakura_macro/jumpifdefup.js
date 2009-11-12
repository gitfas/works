var target = false, nest = 1, y = ExpandParameter("$y"), yy = parseInt(y);
if(/^\s*#(?:if|ifdef)/.test(GetLineStr(0))) {
    GoLineEnd();
    do {
        SearchNext("^\\s*#(?:if|ifdef|else|elif|endif)",2+4+16);
        if(ExpandParameter("$y")==y) break;
        y = ExpandParameter("$y");
        if(/^\s*#(?:if|ifdef)/.test(GetLineStr(0))) nest++;
        else if(/^\s*#endif/.test(GetLineStr(0))) nest--;
    } while(nest > 0);
}
else {
    GoLineTop(1);
    do {
        SearchPrev("^\\s*#(?:if|ifdef|else|elif|endif)",2+4+16);
        if(ExpandParameter("$y")==y) break;
        y = ExpandParameter("$y");
        if(/^\s*#endif/.test(GetLineStr(0))) nest++;
        else if(nest==1 || /^\s*#(?:if|ifdef)/.test(GetLineStr(0))) nest--;
    } while(nest > 0);
}
if(nest > 0) Jump(yy,1);
CancelMode();
SearchClearMark();
CurLineCenter();
