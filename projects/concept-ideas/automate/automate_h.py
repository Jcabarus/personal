import pyautogui

class Automate:
    def __init__(self):
        ...

    def navigation(self, button: str):
        pyautogui.PAUSE = 1.5

        match button:
            case "green_back":
                ...
            case "yellow_back":
                ...
            case "red_cancel":
                ...
            case "save_button":
                ...
            case "green_check":
                ...
            case "execute_button":
                ...
            case _:
                print("Error: navigation(), cases exhausted") 

    def new_window(self):
        ...

    def t_code_navigation(self, t_code: str, argument_list: list): # list = equip_sit, [force element]
        match t_code:
            case "iw38":
                ...
            case "iw39":
                ...
            case "equip_sit":
                ...
            case "mat_sit":
                ...
            case _:
                print("Error: t_code_navigation(), cases exhausted")