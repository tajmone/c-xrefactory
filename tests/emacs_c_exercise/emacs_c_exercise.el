(find-file "cexercise/index.c")
;; Completion
(search-forward "void completion")
(c-xref-push-and-goto-definition)
(search-forward "    com")
(c-xref-completion)
(search-forward "    sp")
(c-xref-completion)
(search-forward "    fpr")
(c-xref-completion)
;; Can't use anything but the first completion, because there seems to
;; be no way to move point to other line in completion buffer when in
;; batch mode. Here's somethings that don't seem to work:
(next-line)
(forward-line)
(call-interactively 'forward-line)
(set-mark (point))
(c-xref-interactive-completion-select)
(search-forward "ptm->")
(c-xref-completion)
(c-xref-interactive-completion-select)
(search-forward "fpu")
(c-xref-completion)
(next-line)(next-line)
(c-xref-interactive-completion-select)
(save-buffer)
(search-forward "[0]).")
(c-xref-completion)
(next-line)(next-line)
(c-xref-interactive-completion-select)
(search-forward "    ass")
(c-xref-completion)
(search-forward " xx->")
(c-xref-completion)
(next-line)(next-line)
(c-xref-interactive-completion-select)
(search-forward "l=ll;")
(c-xref-completion)
(search-forward "l!=NULL;")
(c-xref-completion)
(c-xref-pop-and-return)
;; Parameters
(search-forward "void addRemoveParamete")
(c-xref-push-and-goto-definition)
(search-backward "void printNewline(")
(search-forward "printNewlin")
(c-xref-non-interactive-del-parameter (c-xref-get-identifier-on-point) 1)
(search-backward "void printint")
(search-forward "printin")
(c-xref-non-interactive-add-parameter "printint" 1 "int i" "0")
(c-xref-pop-and-return)
;; Extract function
(search-forward "void extractFunctio")
(c-xref-push-and-goto-definition)
(search-forward "region begin")
(beginning-of-line)
(set-mark-command nil)
(search-forward "region end")
(forward-line)
(setq c-xref-renaming-default-name "extracted")
(c-xref-extract-function t)
(c-xref-pop-and-return)
;; Rename
(search-forward "void renameSym")
(c-xref-push-and-goto-definition)
(search-forward "i,")
(backward-char 2)
(c-xref-non-interactive-renaming "-rfct-rename" (c-xref-get-identifier-on-point) "i2")
(search-forward "renameSymbol(")
(backward-char 2)
(c-xref-non-interactive-renaming "-rfct-rename" (c-xref-get-identifier-on-point) "newRenameSymbol")
(search-forward "j = 33;")
(backward-char 7)
(c-xref-non-interactive-renaming "-rfct-rename" (c-xref-get-identifier-on-point) "j2")
(search-forward "renameM")
(c-xref-non-interactive-renaming "-rfct-rename" (c-xref-get-identifier-on-point) "renameMeToo")
(c-xref-pop-and-return)
(save-some-buffers t)
(kill-emacs)
