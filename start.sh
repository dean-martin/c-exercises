#!/bin/bash
cd ~/work/c_programming_language
S=$(tmux new-session -ds 'c_programming' 'nvim .')
tmux splitw -hd
tmux a
