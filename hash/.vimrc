set nocompatible              " be iMproved, required
filetype off                  " required

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'

let g:ycm_warning_symbol = '>'
let g:ycm_max_num_candidates = 15
let g:ycm_add_preview_to_completeopt = 0
set completeopt-=preview


call vundle#end()            " required
filetype plugin indent on    " required
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ

set ls=2
set statusline=%F\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %=\ [%L]\ [ASCII=\%03.3b]\ [HEX=\%02.2B]
set number relativenumber
set ignorecase
set autoindent
set showcmd
set incsearch
set path+=**
set wildmenu


au BufWinLeave * mkview
au BufWinEnter * silent loadview

map <silent> <F9> :set ls=1<Enter>
map <silent> <F10> :set ls=2<Enter>
nmap <Tab> <C-W>w
map <F2> :w<Enter>
map <F3> :q<Enter>
map <F5> :vsplit<Space>
map <F6> :setlocal spell! spelllang=en_us<CR>
map <S-Tab> :tabn<Enter>
map <F7> :tabe<Space>
imap jj  <Esc>
:nnoremap k gk
:nnoremap j gj

if has("autocmd")
  au VimEnter,InsertLeave * silent execute '!echo -ne "\e[2 q"' | redraw!
  au InsertEnter,InsertChange *
    \ if v:insertmode == 'i' | 
    \   silent execute '!echo -ne "\e[6 q"' | redraw! |
    \ elseif v:insertmode == 'r' |
    \   silent execute '!echo -ne "\e[4 q"' | redraw! |
    \ endif
  au VimLeave * silent execute '!echo -ne "\e[ q"' | redraw!
endif

syntax on
:color jellybeans
