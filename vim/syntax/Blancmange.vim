" Blancmange Syntax File
" Maintainer: o_o
if exists("b:current_syntax")
    finish
endif

syn match C "\~.*\~"
syn match C "\."
hi link C Comment

syn match S "[{|}|;]"
hi link S PreProc

syn match PC "[>|<|\^|v|'|,|@|#|Q]"
hi link PC Type

syn match Reg "[0-9|A-F]"
hi link Reg Function

syn match RI "[i|d|s|S|f|r|R|\"|!|P]"
hi link RI Constant

syn match Math "[p|c|u|&|\||!|+|-|_|\*|\/|%]"
hi link Math Statement

syn match Cmp "[g|l|=|\?|x|y|z]"
hi link Cmp Identifier

syn match IO "[\[|\]|\(|\)|I|O|m|M]"
hi link IO Operator

syn match Byte "\\\x\x"
hi link Byte Error

syn match Sys "Y"
syn match Sys "Q"
hi link Sys Special

let b:current_syntax = "Blancmange"
