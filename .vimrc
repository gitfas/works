" .vimrc Author:Arakawa
" Last Change:2009/09/13 20:00:04.

" -- VIM Enviroment
" --++ Set
" 辞書ファイルを使用する設定に変更
set complete+=k
" ステータスラインに入力中のコマンドを表示する
set showcmd
" 行数を表示
set number
" C言語のインデントに従ってインデントを付ける
set cindent
" バッファを切り替えてもundoが効くようする
set hidden
" バックアップの有効
set backup
set backupdir=>~/.vimbuk
" 編集中でも別画面へ移動できる
set hid
" ステータスラインの表示行数
set laststatus=2
" ステータスラインに文字コードと改行文字を表示する
set statusline=%<%f\ %m%r%h%w%{'['.(&fenc!=''?&fenc:&enc).']['.&ff.']'}%=%l,%c%V%8P
" タブ文字を表示
set list
" タブ文字の表示設定
set listchars=tab:>-,trail:-,extends:<,eol:<
" タブ文字の数
set tabstop=4
" タブキー押した時のカーソル移動幅
set softtabstop=4
" インデント幅
set shiftwidth=4
" 折り返しの有効
set wrap
" 補完候補をステータスラインに表示
set wildmenu

" --++ Syntax
" syntax を有効
syntax on
" --+- Conky Syntax "
au BufNewFile,BufRead *conkyrc set filetype=conkyrc

"  ポップアップメニューの色変更
	hi Pmenu ctermbg=8
	hi PmenuSel ctermbg=1
	hi PmenuSbar ctermbg=0
" --++ Map
" 入力補完候補をShift＋Tabで表示
"imap <silent> <S-Tab> <C-P> 
" makeをF4で実行
map <silent> <F4> :make<CR>
" 行単位で移動
nnoremap j gj
nnoremap k gk
nnoremap <UP> gk
nnoremap <DOWN> gj

map <silent> <S-Tab> :tabn<CR> 
" -- Dictionar Switch of Filetypes
" php.version
autocmd FileType php :set dictionary+=~/.vim/dict/php_functions.dict

" -- Plugin
" --++ mswin.vim ウィンドウズ風キーマップ
" source $VIMRUNTIME/mswin.vim

" --++ SearchComplete.vim 検索ワードをタブキーで補完
source ~/.vim/plugin/SearchComplete.vim

" --++ autodate.vim 最終更新を自動記録（書式：Last Change:．）
source ~/.vim/plugin/autodate.vim

" --++ buffferlist.vim バッファリストを表示
source ~/.vim/plugin/bufferlist.vim
map <silent> <C-Tab> :call BufferList()<CR>

" --++ vimtwitter.vim twitterプラグイン
" source ~/.vim/plugin/vimtwitter.vim
let vimtwitter_login="boleophthalmus_pectinirostris@hotmail.com:00043380"

" --++ project.vim project管理
source ~/.vim/plugin/project.vim
" --++ gtags
source ~/.vim/plugin/gtags.vim

" --++ winresize.vim ウィンドウのサイズ変更
source ~/.vim/plugin/winresize.vim

" --++ mru.vim  ファイルの読み込み履歴 :MRU
source ~/.vim/plugin/mru.vim
"let MRU_File=~/.vim_mru_files
let MRU_Max_Entries = 20
let MRU_Exclude_Files = '^/tmp/.*\|^/var/tmp/.*'  " For Unix
"let MRU_Exclude_Files = '^c:\\temp\\.*'           " For MS-Windows 
let MRU_Window_Height = 15

" --++ recognize_charcode.vim 日本語エンコード
source ~/.vim/plugin/recognize_charcode.vim

" --++ yankring.vim
source ~/.vim/plugin/yankring.vim

" -- Program Suport
" --++ PHP
source ~/.vim/syntax/php.vim
autocmd FileType php :let php_sql_query = 1
autocmd FileType php :let php_htmlInStrings = 1
autocmd FileType php :let php_special_vars = 1
autocmd FileType php :let php_folding = 1
" PHPの構文チェック
autocmd FileType php :set makeprg=php\ -l\ %
autocmd FileType php :set errorformat=%m\ in\ %f\ on\ line\ %l
" *.php保存と同時に構文チェックをかける
autocmd BufWritePost *.php :make

" --++ JavaScript
source ~/.vim/syntax/javascript.vim

" --++ Java
autocmd FileType java :let java_highlight_all = 1
autocmd FileType java :let java_highlight_debug = 1
autocmd FileType java :let java_space_error = 1
" Javaのコンパイル
autocmd FileType java :set makeprg=javac\ %
" バイナリの実行は:!java %
" autocmd FileType java :map <F5> :!javac %<CR>

autocmd FileType java :map <F6> :!java %<<CR>
