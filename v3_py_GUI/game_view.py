import PySimpleGUI as sg
from minesweeper import pointMatrix
from minesweeper import Minesweeper

class gameScreen:
    def __init__(self, difficulty):
        if(difficulty=='easy'):
            dif = 1
        elif(difficulty=='intermediate'):
            dif = 2
        elif(difficulty=='expert'):
            dif = 3
        self.game = Minesweeper(dif)
        #layout
        layout = [
            [sg.Button("Cancel", key="cancel")]
        ]
        #window
        self.window = sg.Window("Menu").layout(layout)
        #data
        self.button, self.data = self.window.Read()

    def close(self):
        self.window.close()
