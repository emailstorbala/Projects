# If you come from bash you might have to change your $PATH.
# export PATH=$HOME/bin:/usr/local/bin:$PATH

# Path to your oh-my-zsh installation.
export ZSH="${HOME}/.oh-my-zsh"

# See https://github.com/ohmyzsh/ohmyzsh/wiki/Themes
ZSH_THEME="mysorin"
plugins=(git fzf)

source "${ZSH}/oh-my-zsh.sh"
set -o vi

. "$HOME/.zsh_aliases"
. "$HOME/.cargo/env"
