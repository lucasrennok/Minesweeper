from menu_view import menuScreen
from game_view import gameScreen

def main():
    menu_window = menuScreen()
    option = menu_window.getData()
    menu_window.close()
    del menu_window

    if(option[0]=="single"):
        game_window = gameScreen(option[1])
    elif(option[0]=="multi"):
        pass #game_window = gameScreen(option[0], option[1])
    else:
        print("closing...")
        return None
    game_window.close()
    del game_window


#starts here
main()