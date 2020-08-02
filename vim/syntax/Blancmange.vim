" Blancmange Syntax File
" Maintainer: o_o
if exists("b:current_syntax")
    finish
endif

syn match C "\~.*\~"
hi link C Comment

syn match S "[{|}|;]"
hi link S Error

syn match PC "[>|<|\^|v|\.|@|#|Q]"
hi link PC Type

syn match Reg "[0-9|A-F]"
hi link Reg Function

syn match RI "[s|S|r|R|f|j|i|d|\"|P]"
hi link RI Constant

syn match Math "[p|c|u|&|\||!|+|-|_|\*|\/|%]"
hi link Math Statement

syn match Cmp "[g|l|=|\?|]"
hi link Cmp Identifier

syn match IO "[\[|\]|\(|\)|I|O]"
hi link IO Operator

syn match Sys "Y"
hi link Sys Special

let b:current_syntax = "Blancmange"
