from menu_view import menuScreen
from game_view import gameScreen
from game_view import resultScreen

def main():
    play_more = True
    while(play_more==True):
        menu_window = menuScreen()
        option = menu_window.getData()
        menu_window.close()
        del menu_window

        if(option[0]=="single"):
            game_window = gameScreen(option[1])
            result = game_window.play()
            if(result==None):
                game_window.close()
                del game_window
                print("Closing...")
                return None
        elif(option[0]=="multi"):
            return 1 #game_window = gameScreen(option[0], option[1])
        else:
            print("Closing...")
            return None

        result_window = resultScreen(result)
        play_more = result_window.getData()
        result_window.close()
        del result_window
        
        game_window.close()
        del game_window


#starts here
main()