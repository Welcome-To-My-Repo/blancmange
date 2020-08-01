" Alchemist Syntax File
" Maintainer: o_o
if exists("b:current_syntax")
    finish
endif

syntax match S "\["
syntax match S "\]"
syntax match S "\,"
hi link S Statement

syntax match C "\#.*\#"
hi link C Comment

syntax keyword Symbol symbol
hi link Symbol Identifier

syntax keyword F formula
hi link F Function
syntax keyword inF req aux ret var
hi link inF Keyword

syntax keyword E element
hi link E Type
syntax keyword inE surface structure quantum shadow 
hi link inE Keyword
syn keyword alsoE overlap compound
hi link alsoE Structure

syntax keyword Unit small short int num integer number ratio float ref
hi link Unit Type

syn match String "\\.*\\"
hi link String String

syn match Char "\\.\\"
hi link Char Character

syn match As "\:"
syn match As "\;"
syn match AS "\v\{"
syn match AS "\v\}"
hi link As SpecialChar

syn keyword Ab about
hi link Ab SpecialComment

syn match P "\v\+"
syn match P "\v\-"
syn match P "\v\*"
syn match P "\v\/"
syn match P "\v\%"
syn match P "\v\`"
syn match P "\v\~"
syn match P "\v\'"
syn match P "\v\""
syn match P "\v\&"
syn match P "\v\|"
syn match P "\v\!"
syn keyword P rtr rtl asl asr lsl lsr eq
syn match P "\v\<"
syn match P "\v\>"
syn match P "\v\="
syn match P "\v\?"
syn match P "\v\^"
syn match P "\v\."
hi link P Operator

syn match Goto "\v\@"
hi link Goto Tag

syn keyword S stone
hi link S Special

syn match N "[0-9]\+\|\.\{1}"
hi link N Number

syn match Binary "[0-1]\{8}"
hi link Binary Type

syn match Hex "0x[0-f]\+"
hi link Hex Identifier

let b:current_syntax = "Alchemist"
