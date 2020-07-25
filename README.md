# Minesweeper
Minesweeper with a GUI and without a GUI

## About the game
In the game the player have to choose coordinates that he think don't have mines, so he could continue playing and solving the matrix.
The player have a possibility to put a flag at any coordinate to save the place of a bomb.
After cleaning all the matrix without selecting a mine you win.

## The ouput of the Matrix
The coordinates have a number that represents how many bombs there are near that point

'*' represent places that have mines(if you loose you can see them)

'B' represent flags placed by the player

## V1_without_GUI
It's the version made in C. This version is singleplayer and is played in terminal or cmd.

How to use: Open a terminal, type *gcc main.c -o executable* and *./executable*

## V2_with_GUI
It's the version made in C++. This version is singleplayer and is played at a GUI(have to use QTCreator to execute).

How to use: Install QtCreator(I used 5.9.9) to use, and run it with the run button at the program.

## V3_py_GUI
It's the version made in Python. This version is singleplayer and multiplayer and is played at a GUI(made with PySimpleGUI).

How to use: Install Python and install PySimpleGUI: *pip install PySimpleGUI*, after that *python main.py*

**Good game for you, and don't be sad for loosing, minesweeper is hard sometimes(when you find a decision problem)**
**Good luck**