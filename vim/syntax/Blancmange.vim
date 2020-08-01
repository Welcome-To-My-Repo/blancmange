" Blancmange Syntax File
" Maintainer: o_o
if exists("b:current_syntax")
    finish
endif

syntax match PC "\v\."
syntax match PC "\v\,"
syntax match PC "\v\^"
syntax match PC "\v\v"
syntax match PC "\v\<"
syntax match PC "\v\>"
syntax match PC "\v\@"
syntax match PC "\v\#"
hi link PC Statement

syn match rOp "\v\l"
syn match rOp "\v\L"
syn match rOp "\v\r"
syn match rOp "\v\R"
syn match rOp "\v\f"
syn match rOp "\v\j"
syn match rOp "\v\""
syn match rOp "\v\P"
hi link rOp string

syn match Op "\v\p"
syn match Op "\v\d"
syn match Op "\v\s"
syn match Op "\v\&"
syn match Op "\v\o"
syn match Op "\v\!"
syn match Op "\v\+"
syn match Op "\v\-"
syn match Op "\v\*"
syn match Op "\v\/"
syn match Op "\v\%"
hi link Op Operator

syn match Cmp "\v\g"
syn match Cmp "\v\l"
syn match Cmp "\v\="
hi link Cmp Identifier

syn match Con "\v\?"
hi link Con Type

syn match IO "\v\["
syn match IO "\v\]"
syn match IO "\v\("
syn match IO "\v\)"
hi link IO Type

syn match Syn "\v\{|\}|\;"
hi link Syn Include

hi link Error Error

let b:current_syntax = "Alchemist"
