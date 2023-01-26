vim.opt.number = true
vim.opt.cursorcolumn = true
vim.opt.cursorline = true
vim.opt.cursorbind = true
vim.opt.clipboard = "unnamedplus"
vim.opt.shiftwidth = 4
vim.opt.tabstop = 4
vim.opt.softtabstop = 4
vim.opt.expandtab = true
vim.opt.autoindent = true
vim.opt.smartindent = true
vim.opt.shiftround = true

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
