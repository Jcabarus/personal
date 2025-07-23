import pyautogui
import sys

def screen_ratio_validation(screen_pixel_size_x: int, screen_pixel_size_y: int):
    if(screen_pixel_size_x == 2560 and screen_pixel_size_y == 1600):
        return True
    else:
        return False
    
def equipment_situational_display(argument_list: list):
    ...

def iw38(argument_list: list):
    ...

def t_code(argument_list: list):
    if(len(argument_list) == 0):
        print("T-Code:")
        print("        [equip_sit]: Initialize instance of Equipment Status Report")
        print("          [mat_sit]: Initialize instance of Materials Status Report")
        print("             [iw38]: Initialize instance of IW38")
        print()

        print("                  >>: ", end = "")
        argument_list.append(input())

    if(argument_list[0] == "equip_sit"):
        equipment_situational_display(argument_list)
    elif(argument_list[0] == "iw38"):
        iw38(argument_list)
    else:
        print("Error: no valid T-Code selected, supported T-Codes: ")
        print("       equip_sit, matsit, iw38", end = "\n\n")

def main():
    screen_x, screen_y = pyautogui.size()
    arguments = []

    if(len(sys.argv) == 1):
        ...
    else:
        for i in range(1, len(sys.argv)):
            arguments.append(sys.argv[i])

    if(screen_ratio_validation(screen_x, screen_y)):
        t_code(arguments)
    else:
        print("Error: screen_ratio_validation = false, supported display resoution:")
        print("       2560 x 1600", end = "\n\n")

main()