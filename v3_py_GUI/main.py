from menu_view import menuScreen
from game_view import gameScreen

def main():
    menu_window = menuScreen()
    option = menu_window.getData()
    menu_window.close()
    del menu_window

    if(option[0]=="single"):
        game_window = gameScreen(option[1])
        game_window.close()
        del game_window
    elif(option[0]=="multi"):
        pass#game_window = gameScreen(option[0], option[1])
    else:
        return None


#starts here
main()