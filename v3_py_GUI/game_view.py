import PySimpleGUI as sg
from minesweeper import pointMatrix
from minesweeper import Minesweeper
import create_game
import connection
import time

class gameScreen:
    def __init__(self, difficulty, type_game):
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
            [sg.Text("Difficulty: "+difficulty)]
        ]
        matrix_game = []
        line = []
        string_but = 1
        for i in range(self.game.x):
            for j in range(self.game.y):
                line+= [sg.Button("", key=str(string_but), size=(3,0), pad=(0,0))]
                string_but += 1
            matrix_game+=[line]
            line = []
        layout+=matrix_game
        if(type_game=="multi"):
            layout+=[[sg.Button("Update", key="upd")]]
        #window
        self.window = sg.Window("Minesweeper - Game").layout(layout)

    def play(self,but_multiplayer):
        #data
        self.window.finalize()
        if(but_multiplayer=="upd"):
            return 0
        string_but = 1
        for i in range(self.game.x):
            for j in range(self.game.y):
                self.window[str(string_but)].bind("<Button-3>", '000')
                string_but += 1
        while(1):
            if(but_multiplayer==None):
                button, self.data = self.window.Read()
            elif(but_multiplayer!=None):
                print("TESTE: ",but_multiplayer)
                button = but_multiplayer
            if(button==None):
                return None
            b_num = int(button)
            if(b_num<1000):
                option = 1
                row = 0
                column = 0
                while(b_num>self.game.y):
                    row=row+1
                    b_num=b_num-self.game.y
                column=b_num-1
                situation = self.game.playerDecision(row, column, option)
                self.unlock_button(button,row,column,option)
                if(situation==1):
                    self.unlock_all_buttons()
                    self.window.finalize()
                    return 1
                elif(situation==2):
                    self.unlock_all_buttons()
                    self.window.finalize()
                    return 2
            elif(b_num>=1000):
                b_num=int(b_num/1000)
                cont = b_num
                row = 0
                column = 0
                while(b_num>self.game.y):
                    row=row+1
                    b_num=b_num-self.game.y
                column=b_num-1
                if(self.window.FindElement(str(cont)).GetText()=="B"):
                    self.window.FindElement(str(cont)).Update("")
                elif(self.game.matrix[row][column].unlocked==False):
                    self.window.FindElement(str(cont)).Update("B")
            if(but_multiplayer!=None):
                return 0

    def get_button(self):
        button, self.data = self.window.Read()
        return button

    def unlock_button(self, button, row, column, option):
        if(option==1):
            if(self.game.matrix[row][column].mine==False):
                if(self.game.matrix[row][column].mines_around!=-1):
                    self.window.FindElement(button).Update(str(self.game.matrix[row][column].mines_around))
                else:
                    self.window.FindElement(button).Update("0")
                    self.cleanZerosView()
                    print("*Zeros Cleaned*")
            elif(self.game.matrix[row][column].mine==True):
                self.window.FindElement(button).Update("*")
        elif(option==2):
            self.window.FindElement(button).Update("B")

    def unlock_all_buttons(self):
        cont = 1
        while(cont<=((self.game.x)*(self.game.y))):
            but_num=cont
            row = 0
            column = 0
            while(but_num>self.game.y):
                row=row+1
                but_num=but_num-self.game.y
            column=but_num-1
            if(self.game.matrix[row][column].unlocked==False):
                self.unlock_button(str(cont), row, column, 1)
            cont+=1

    def cleanZerosView(self):
        cont = 1
        while(cont<=((self.game.x)*(self.game.y))):
            but_num=cont
            row = 0
            column = 0
            while(but_num>self.game.y):
                row=row+1
                but_num=but_num-self.game.y
            column=but_num-1
            if(self.game.matrix[row][column].unlocked==True):
                if(self.game.matrix[row][column].mines_around==-1):
                    self.window.FindElement(str(cont)).Update("0")
                else:
                    self.window.FindElement(str(cont)).Update(str(self.game.matrix[row][column].mines_around))
            cont+=1

    def create_connect(self,create_the_game, ip):
        #connect here
        if(create_the_game==True):
            return create_game.create_server(self, ip)
        elif(create_game==False):
            return connection.connect_to_server(self, ip)
        return None

    def close(self):
        self.window.close()

class resultScreen:
    def __init__(self, won):
        if(won==1):
            layout = [
                [sg.Text("You WON!")],
                [sg.Quit(), sg.Button("Play Again", key="play")]
            ]
        elif(won==2):
            layout = [
                [sg.Text("You loose.")],
                [sg.Quit(), sg.Button("Play Again", key="play")]
            ]
        self.window = sg.Window("Result - Game").layout(layout)
        self.window.finalize()

    def getData(self):
        self.button, self.data = self.window.Read()
        if(self.button=="play"):
            return True
        else:
            return False

    def close(self):
        self.window.close()