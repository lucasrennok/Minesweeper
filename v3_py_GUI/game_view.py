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
        print("Matrix: ",self.game.x,"x",self.game.y)
        #layout
        layout = [
            [sg.Text("Game Minesweeper: "+difficulty)]
        ]
        matrix_game = []
        line = []
        string_but = 0
        for i in range(self.game.x):
            for j in range(self.game.y):
                string_but = 1
                line+= [sg.Button("", key=str(string_but), size=(3,0), pad=(0,0))]
                string_but += 1
            matrix_game+=[line]
            line = []
        layout+=matrix_game
        #window
        self.window = sg.Window("Minesweeper - Game").layout(layout)
        #data
        self.button, self.data = self.window.Read()

    def close(self):
        self.window.close()
