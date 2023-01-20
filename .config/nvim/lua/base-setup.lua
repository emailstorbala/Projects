vim.opt.cursorcolumn = true
vim.opt.textwidth = 100

-- Decrease update time
vim.wo.signcolumn = 'yes'
vim.opt.clipboard = "unnamedplus"

-- Set colorscheme
vim.cmd [[colorscheme onedark]]

vim.opt.listchars = {
  eol = '$',
  tab = '>-',
  extends = '>',
  precedes = '<',
  trail = '~'
}

-- [[ Setting options ]]
-- See `:help vim.o`
-- Language based indentation moved inside after/ftplugin directory
-- Set highlight on search
vim.o.hlsearch = true

-- Enable mouse mode
vim.o.mouse = 'a'

-- Case insensitive searching UNLESS /C or capital in search
vim.o.ignorecase = true
vim.o.smartcase = true
vim.o.updatetime = 250

-- Set completeopt to have a better completion experience
vim.o.completeopt = 'menuone,noselect'
