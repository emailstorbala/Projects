require('packer-setup')
require('lspconfig').lua_ls.setup {
  settings = {
    Lua = {
      diagnostics = {
        -- Get the language server to recognize the `vim` global
        globals = {'vim'},
      },
    },
  },
}

vim.opt.number = true
vim.opt.cursorcolumn = true
vim.opt.cursorline = true
vim.opt.clipboard = "unnamedplus"
vim.opt.shiftwidth = 4
vim.opt.tabstop = 4
vim.opt.softtabstop = 4
vim.opt.expandtab = true
vim.opt.shiftround = true

-- Case insensitive searching UNLESS /C or capital in search
vim.opt.ignorecase = true

-- Set completeopt to have a better completion experience
vim.opt.completeopt = 'menuone,noselect'
