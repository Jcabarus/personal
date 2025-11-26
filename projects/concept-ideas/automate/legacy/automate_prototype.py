import pyautogui
import sys

def screen_ratio_validation(screen_pixel_size_x: int, screen_pixel_size_y: int):
    if(screen_pixel_size_x == 2560 and screen_pixel_size_y == 1600):
        return True
    else:
        return False

def new_window():
    execution_step = [
        lambda: pyautogui.click(2350, 20),
        lambda: pyautogui.hotkey('ctrl', 'n'),
        lambda: pyautogui.click(79, 75),
        lambda: pyautogui.typewrite("SMEN"),
        lambda: pyautogui.hotkey('enter')
    ]

    for execute in execution_step:
        execute()
        pyautogui.PAUSE = 1

def equipment_situational_display(argument_list: list):
    print("Equipment Status Display:")

    target_x, target_y = pyautogui.locateCenterOnScreen('src/images/equip_sit.PNG', confidence = 0.9)
    print(target_x, target_y)

    execution_step = [
        # lambda: new_window(),
        lambda: pyautogui.doubleClick(322, 259),
        # lambda: pyautogui.click(420, 304),
        # lambda: pyautogui.typewrite("WPTUAA"),
        # lambda: pyautogui.click(41, 180)
    ]

    for execute in execution_step:
        execute()
        pyautogui.PAUSE = 0.8

def iw38(argument_list: list):
    print("IW 38: ")

    execution_step = [
        lambda: new_window(),
        lambda: pyautogui.doubleClick(83, 313),
        lambda: pyautogui.click(480, 646),
        lambda: pyautogui.typewrite("WPTUAA"),
        lambda: pyautogui.click(477, 709),
        lambda: pyautogui.hotkey('ctrl', 'a'),
        lambda: pyautogui.hotkey('del'),
        lambda: pyautogui.click(41, 180)
    ]

    for execute in execution_step:
        execute()
        pyautogui.PAUSE = 0.8

def mat_sit(argument_list: list):
    print("Material Situation Display:")

    execution_step = [

    ]

def t_code(argument_list: list): # T-codes implementation
    if(len(argument_list) == 0): # Manual Selection
        print("T-Code:")
        print("     [equip_sit]: Initialize instance of Equipment Status Report")
        print("     [mat_sit]: Initialize instance of Materials Status Report")
        print("     [iw38]: Initialize instance of IW38")
        print()

        print("                  >>: ", end = "")
        argument_list.append(input())

    if(argument_list[0] == "equip_sit"):
        # pyautogui.hotkey('alt', 'tab'),
        equipment_situational_display(argument_list)
    elif(argument_list[0] == "iw38"):
        pyautogui.hotkey('alt', 'tab'),
        iw38(argument_list)
    elif(argument_list[0] == "mat_sit"):
        pyautogui.hotkey('alt', 'tab'),
        mat_sit(argument_list)
    elif(argument_list[0] == "start"):
        pyautogui.hotkey('alt', 'tab'),
        equipment_situational_display(argument_list)
        iw38(argument_list)
    else:
        print("Error: no valid T-Code selected, supported T-Codes: ")
        print("       equip_sit, matsit, iw38", end = "\n\n")

def main():
    screen_x, screen_y = pyautogui.size()
    arguments = []

    if(len(sys.argv) == 1): # Command line arguement
        ...
    else:
        for i in range(1, len(sys.argv)):
            arguments.append(sys.argv[i])

    if(screen_ratio_validation(screen_x, screen_y)): # Screen resolution check
        t_code(arguments)
    else:
        print("Error: screen_ratio_validation = false, supported display resoution:")
        print("       2560 x 1600", end = "\n\n")

main()