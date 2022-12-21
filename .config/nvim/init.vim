set runtimepath^=~/.vim runtimepath+=~/.vim/after
let &packpath = &runtimepath
set listchars=eol:$,tab:>-,trail:~,extends:>,precedes:<
source ~/.vim/vimrc

lua require("lspconfig").clangd.setup {}
