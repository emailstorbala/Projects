vim.opt.cursorcolumn = true
vim.opt.clipboard = "unnamedplus"

-- Set colorscheme
vim.cmd [[colorscheme onedark]]

-- Enable highlight search
vim.o.hlsearch = true

-- Enable mouse mode
vim.o.mouse = 'a'

-- Case insensitive searching UNLESS /C or capital in search
vim.o.ignorecase = true
vim.o.smartcase = true

-- Set completeopt to have a better completion experience
vim.o.completeopt = 'menuone,noselect'
