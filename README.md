# Welcome to Chess!

## Introduction

This is a command-line chess game.

## Download

Requirements:

- The GCC C++ compiler
- Make
- Git

Here are the steps to download the game:

1. Using you terminal, navigate to the directory where you would like to download this repository
2. In your terminal, type ```git clone https://github.com/adi-joshi/Chess.git```
3. Navigate into the Chess directory, and type ```make```. This will make an executable called ```chess```.
4. Type ```./chess``` to begin the game.

How to play the game:

1. The game will prompt you whose move it is.
2. You can type in the move in UCI notation (i.e. type the square that the piece is currently on, followed by the square that you want to move it to. For example, if you want to move your Knight from the square g1 to the square f3, then you would type ```g1f3``` and press enter). If you want to promote a pawn, type the move as above, then add an '=' and then the piece name that you want to promote your pawn to (e.g. If your pawn is on g7 and you want to promote it to a Knight on g8, you would type ```g7g8=n``` or ```g7g8=N```. You can similarly type ```g7g8=b, g7g8=B, g7g8=r, g7g8=R, g7g8=q, g7g8=Q```).
3. The program will notify you if it thinks that your move is invalid, or if it can't read your move.

## To do List:
- GUI
