filetype plugin indent on
syntax on

colorscheme gruvbox
set background=dark
set backspace=indent,eol,start
set showcmd
set hlsearch
set splitbelow
set noswapfile
let NERDTreeShowHidden=1


call plug#begin('~/.vim/plugged')
Plug 'neovim/nvim-lspconfig'
Plug 'dense-analysis/ale'
Plug 'preservim/nerdtree'
Plug 'davidhalter/jedi-vim'
Plug 'Yggdroot/indentLine'
call plug#end()

"let g:airline_theme='base16'
"let g:airline_theme='base16_default'
let g:airline_theme='base16_gruvbox_dark_hard'
let g:indentLine_enabled = 1
let g:indentLine_char_list = ['|', '¦', '┆', '┊']

let g:lsp_document_highlight_enabled = 1
let g:ale_cpp_cc_options = '-std=c++2a -Wall -Wextra -Weffc++ -Wsign-conversion'

let g:netrw_banner = 0
let g:netrw_liststyle = 3
let g:netrw_browse_split = 4
let g:netrw_altv = 1
let g:netrw_winsize = 20
let NERDTreeShowHidden=1

set ruler
set laststatus=2
set t_vb=
set mouse-=a

set encoding=utf-8
set fileencodings=utf-8

let $RTP=split(&runtimepath, ',')[0]
let $RC="$HOME/.vim/vimrc"

map <C-p> :e#<CR>
map <C-n> :set number!<CR>
map <C-l> :set list!<CR>
map <S-s> :ALEToggle<CR>
map <C-t> :NERDTree<CR>
map <C-x> :NERDTreeClose<ENTER>

"This is to avoid indentation changes for yaml content
map <C-u> :setlocal indentexpr=<CR>
