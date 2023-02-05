-- Set lualine as statusline
-- See `:help lualine.txt`
require('lualine').setup {
  options = {
    path = 1,
    icons_enabled = true,
    theme = 'onedark',
    component_separators = '|',
    section_separators = '',
  },
}
