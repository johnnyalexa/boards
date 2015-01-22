# boards
Board configurations for chibiOS-RT.

This directory contains the support files for various board models. If you
want to support a new board:
- Create a new directory under ./boards, give it the name of your board.
- Copy inside the new directory the files from a similar board.
- Customize board.c, board.h and board.mk in order to correctly initialize
  your board.
  
  
# OLIMEX_STM32_P103
Default board as template.