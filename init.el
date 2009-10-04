;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; last updated : 2009/10/04-17:11:22
;; @author Arakawa
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Windows�p�V���{���b�N�����N�쐬�R�}���h C:\cygwin\bin\winln.exe
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

;; ���{����ݒ�
(set-language-environment "Japanese")

;; �\��
(setq time-stamp-start "last updated : ")
(setq time-stamp-format "%04y/%02m/%02d-%02H:%02M:%02S")
;; �s�[�f���~�^
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

;; �o�b�t�@���̈ꕔ����o�b�t�@�I�����i����
(iswitchb-mode t)

;; C-f,C-b,C-n,C-p�Ō���؂�ւ�
(add-hook 'iswitchb-define-mode-map-hook
		  (lambda ()
			(define-key iswitchb-mode-map "\C-n" 'iswitchb-next-match)
			(define-key iswitchb-mode-map "\C-p" 'iswitchb-prev-match)
			(define-key iswitchb-mode-map "\C-f" 'iswitchb-next-match)
			(define-key iswitchb-mode-map "\C-b" 'iswitchb-prev-match)))

;; �Ή����ʂɐF�t��
(show-paren-mode t)

;; �V�F�����[�h�� ls �o�͂Ȃǂ��J���[�\������ݒ�
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
;; Emacs�N������Eshell���N��
(add-hook 'after-init-hook (lambda() (eshell) ))

;; �⊮���ɑ啶������������ʂ��Ȃ�
(setq eshell-cmpl-ignore-case t)
;; �m�F�Ȃ��Ńq�X�g���ۑ�
(setq eshell-ask-to-save-history (quote always))
;; �⊮���ɃT�C�N������
(setq eshell-cmpl-cycle-completions t)
;; �⊮��₪���̐��l�ȉ����ƃT�C�N�������Ɍ��\��
(setq eshell-cmpl-cycle-cutoff-length 5)
;; �����ŏd���𖳎�����
(setq eshell-hist-ignoredups t)
;; prompt������̕ύX
(setq eshell-prompt-function
      (lambda ()
        (concat "[fas@localhost "
                (eshell/pwd)
                (if (= (user-uid) 0) "]\n# " "]\n$ ")
                )))
;; �ύX����prompt������ɍ����`��prompt�̏��܂���w��(C-a��"$ "�̎��ɃJ�[�\��������悤�ɂ���)
(setq eshell-prompt-regexp "^[^#$]*[$#] ")

;; �J�����g�o�b�t�@�̃f�B���N�g���Ɉړ�����eshell���N������
(defun eshell-cd-default-directory ()
  (interactive)
  (let ((dir default-directory))
    (eshell)
    (cd dir)
    (eshell-interactive-print (concat "cd " dir "\n"))
    (eshell-emit-prompt)))

;; �J�[�\���̐F Windows�Ŕ��]������ƃJ�[�\���������Ȃ�
(add-to-list 'default-frame-alist '(cursor-color . "SlateBlue2"))

;; �N���b�v�{�[�h�ɃR�s�[
(global-set-key "\M-w" 'clipboard-kill-ring-save)
;; �؂����ăN���b�v�{�[�h��
(global-set-key "\C-w" 'clipboard-kill-region)

;; �^�u, �S�p�X�y�[�X��\������
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
     ("�@" 0 my-face-b-1 append)
     ("[ \t]+$" 0 my-face-u-1 append)
     ;;("[\r]*\n" 0 my-face-r-1 append)
     )))
(ad-enable-advice 'font-lock-mode 'before 'my-font-lock-mode)
(ad-activate 'font-lock-mode)
