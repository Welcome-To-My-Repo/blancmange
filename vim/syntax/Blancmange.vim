" Alchemist Syntax File
" Maintainer: o_o
if exists("b:current_syntax")
    finish
endif

syntax match C "\v~"

syn match pc "\<|\>|\^|v"
hi link pc Include

hi link C Comment

hi link P Operator

syn match Goto "\v\@"
hi link Goto Tag

syn match Reg "[\x]"
hi link Reg Identifier

let b:current_syntax = "Alchemist"
