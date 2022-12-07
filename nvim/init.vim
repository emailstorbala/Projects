set runtimepath^=~/.vim runtimepath+=~/.vim/after
let &packpath = &runtimepath

source ~/.vim/vimrc

lua require("lspconfig").clangd.setup {}
