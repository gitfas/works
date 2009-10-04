;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; last updated : 2009/10/04-17:11:22
;; @author Arakawa
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Windows用シンボリックリンク作成コマンド C:\cygwin\bin\winln.exe
;; http://homepage1.nifty.com/emk/symlink.html

;; note
;; .emacs Reload
;; M-x load-file RET ~/.emacs

;; Load PATH


;; Hide tool-bar
(tool-bar-mode -1)

;; default find file path
(cd "~/")

;; Window configuration
(if window-system (progn
  (setq initial-frame-alist '((width . 100) (height . 50) (top . 0) (left .
0)))
))

;; 日本語環境設定
(set-language-environment "Japanese")

;; 表示
(setq time-stamp-start "last updated : ")
(setq time-stamp-format "%04y/%02m/%02d-%02H:%02M:%02S")
;; 行端デリミタ
(setq time-stamp-end "$")
(if (not (memq 'time-stamp write-file-hooks))
    (setq write-file-hooks
		  (cons 'time-stamp write-file-hooks)))

;; php-mode
(autoload 'php-mode "php-mode" "Major mode for editing php code." t)

;; *.php is php-mode
(setq auto-mode-alist
      (cons (cons "\\.php$" 'php-mode) auto-mode-alist))

;; Tab-Width
(setq default-tab-width 4)
;; Indent-Width
(setq tab-stop-list
	  '(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60))

;; Show Time
(display-time-mode t)

;; Show Line-No
(linum-mode t)

;; Show Column-No
(setq column-number-mode t)

;; Back-Up File
(setq make-backup-files nil)
;; Auto-Save File
(setq auto-save-default nil)

;; バッファ名の一部からバッファ選択を絞込み
(iswitchb-mode t)

;; C-f,C-b,C-n,C-pで候補を切り替え
(add-hook 'iswitchb-define-mode-map-hook
		  (lambda ()
			(define-key iswitchb-mode-map "\C-n" 'iswitchb-next-match)
			(define-key iswitchb-mode-map "\C-p" 'iswitchb-prev-match)
			(define-key iswitchb-mode-map "\C-f" 'iswitchb-next-match)
			(define-key iswitchb-mode-map "\C-b" 'iswitchb-prev-match)))

;; 対応括弧に色付け
(show-paren-mode t)

;; シェルモードで ls 出力などをカラー表示する設定
(autoload 'ansi-color-for-comint-mode-on "ansi-color"
  "Set `ansi-color-for-comint-mode' to t." t)
(add-hook 'shell-mode-hook 'ansi-color-for-comint-mode-on)


;; Auto-Indent
(global-set-key "\C-m" 'newline-and-indent)
(global-set-key "\C-j" 'newline)

;; Shell-mode : Input Password
(add-hook 'comint-output-filter-functions
              'comint-watch-for-password-prompt)

;;; ESHELL
;; Emacs起動時にEshellを起動
(add-hook 'after-init-hook (lambda() (eshell) ))

;; 補完時に大文字小文字を区別しない
(setq eshell-cmpl-ignore-case t)
;; 確認なしでヒストリ保存
(setq eshell-ask-to-save-history (quote always))
;; 補完時にサイクルする
(setq eshell-cmpl-cycle-completions t)
;; 補完候補がこの数値以下だとサイクルせずに候補表示
(setq eshell-cmpl-cycle-cutoff-length 5)
;; 履歴で重複を無視する
(setq eshell-hist-ignoredups t)
;; prompt文字列の変更
(setq eshell-prompt-function
      (lambda ()
        (concat "[fas@localhost "
                (eshell/pwd)
                (if (= (user-uid) 0) "]\n# " "]\n$ ")
                )))
;; 変更したprompt文字列に合う形でpromptの初まりを指定(C-aで"$ "の次にカーソルがくるようにする)
(setq eshell-prompt-regexp "^[^#$]*[$#] ")

;; カレントバッファのディレクトリに移動しつつeshellを起動する
(defun eshell-cd-default-directory ()
  (interactive)
  (let ((dir default-directory))
    (eshell)
    (cd dir)
    (eshell-interactive-print (concat "cd " dir "\n"))
    (eshell-emit-prompt)))

;; カーソルの色 Windowsで反転させるとカーソルが見えない
(add-to-list 'default-frame-alist '(cursor-color . "SlateBlue2"))

;; クリップボードにコピー
(global-set-key "\M-w" 'clipboard-kill-ring-save)
;; 切り取ってクリップボードへ
(global-set-key "\C-w" 'clipboard-kill-region)

;; タブ, 全角スペースを表示する
;;(defface my-face-r-1 '((t (:background "gray15"))) nil)
(defface my-face-b-1 '((t (:background "gray"))) nil)
(defface my-face-b-2 '((t (:background "gray26"))) nil)
(defface my-face-u-1 '((t (:foreground "SteelBlue" :underline t))) nil)
;;(defvar my-face-r-1 'my-face-r-1)
(defvar my-face-b-1 'my-face-b-1)
(defvar my-face-b-2 'my-face-b-2)
(defvar my-face-u-1 'my-face-u-1)

(defadvice font-lock-mode (before my-font-lock-mode ())
  (font-lock-add-keywords
   major-mode
   '(("\t" 0 my-face-b-2 append)
     ("　" 0 my-face-b-1 append)
     ("[ \t]+$" 0 my-face-u-1 append)
     ;;("[\r]*\n" 0 my-face-r-1 append)
     )))
(ad-enable-advice 'font-lock-mode 'before 'my-font-lock-mode)
(ad-activate 'font-lock-mode)
