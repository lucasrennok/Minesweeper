from menu_view import menuScreen
from game_view import gameScreen
from game_view import resultScreen

def main():
    menu_window = menuScreen()
    option = menu_window.getData()
    menu_window.close()
    del menu_window

    if(option[0]=="single"):
        game_window = gameScreen(option[1])
        result = game_window.play()
    elif(option[0]=="multi"):
        return 1 #game_window = gameScreen(option[0], option[1])
    else:
        print("closing...")
        return None
    game_window.close()
    del game_window

    result_window = resultScreen(result)
    result_window.close()
    del result_window


#starts here
main()