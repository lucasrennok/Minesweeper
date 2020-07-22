import PySimpleGUI as sg

class menuScreen:
    def __init__(self):
        #theme
        #sg.theme("Dark Brown")
        #layout
        layout = [
            [sg.Button("Singleplayer", key="single"), sg.Button("Multiplayer", key="multi")],
            [sg.Radio("Easy", "dif", key="easy", default=True), sg.Radio("Intermediate", "dif", key="intermediate"), sg.Radio("Expert", "dif", key="expert")]
        ]
        #window
        self.window = sg.Window("Menu - Game").layout(layout)
        
    def getData(self):
        #data
        button, self.data = self.window.Read()
        difEasy = self.data['easy']
        difIntermediate = self.data['intermediate']
        difExpert = self.data['expert']
        if(difEasy==True):
            dif = 'easy'
        elif(difIntermediate==True):
            dif = 'intermediate'
        elif(difExpert==True):
            dif = 'expert'
        else:
            dif = 'close'
        return [button, dif]

    def close(self):
        self.window.close()

    