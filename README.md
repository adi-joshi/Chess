# Welcome to Chess!

## Introduction

This is a command-line chess game.

## Download

Requirements:

- The GCC C++ compiler
- Make
- Git
- SDL2

Here are the steps to download and compile the game:

1. Using you terminal, navigate to the directory where you would like to download this repository
2. In your terminal, type ```git clone https://github.com/adi-joshi/Chess.git```
3. Navigate into the Chess directory, and type ```make```. This will make an executable called ```chess```.

There are 2 command line options: for a text-based game (```-t```) or for a GUI-based game (```-g```).

How to play the text-based game:

1. Type ```./chess``` (or ```./chess -t```) to begin the game.
2. The game will prompt you whose move it is.
3. You can type in the move in UCI notation (i.e. type the square that the piece is currently on, followed by the square that you want to move it to. For example, if you want to move your Knight from the square g1 to the square f3, then you would type ```g1f3``` and press enter). If you want to promote a pawn, type the move as above, then add an '=' and then the piece name that you want to promote your pawn to (e.g. If your pawn is on g7 and you want to promote it to a Knight on g8, you would type ```g7g8=n``` or ```g7g8=N```. You can similarly type ```g7g8=b, g7g8=B, g7g8=r, g7g8=R, g7g8=q, g7g8=Q```).
4. The program will notify you if it thinks that your move is invalid, or if it can't read your move.

How to play the GUI-based game:
1. Type ```./chess -g``` to begin the game.
2. A screen will appear with the chess board and chess pieces.
3. You can move the pieces on the board using your mouse.
4. If you input a move that the program thinks cannot be played, it will return the piece to its original square, and output an error message on the terminal console.

## References
- Board image: Made by "the lila authors and pirouetti". Taken from "https://github.com/lichess-org/lila/blob/master/public/images/board/wood.jpg" under the AGPLv3+ license on June 25, 2022.
- Piece images: Made by "Colin M.L. Burnett". Taken from "https://github.com/lichess-org/lila/blob/master/public/piece/cburnett" under the GPLv2+ license on June 25, 2022.
- Fonts: The Open Sans font is used. Made by "Steve Matteson". Taken from "https://www.1001fonts.com/open-sans-font.html" under the Apache License, Version 2.0.

## To do List:
- Moves so far in GUI
