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

require('base-setup')
require('packer-setup')

-- Automatically source and re-compile packer whenever you save this init.lua
local packer_group = vim.api.nvim_create_augroup('Packer', { clear = true })
vim.api.nvim_create_autocmd('BufWritePost', {
  command = 'source <afile> | silent! LspStop | silent! LspStart | PackerCompile',
  group = packer_group,
  pattern = vim.fn.expand '$MYVIMRC',
})

require('other-setup')
require('treesitter-setup')

-- Setup neovim lua configuration
require('neodev').setup()
require('my_mason')

-- Turn on lsp status information
require('fidget').setup()

require('cmp-setup')
require('color')
require('keymap-setup')

-- The line beneath this is called `modeline`. See `:help modeline`
-- vim: ts=2 sts=2 sw=2 et
