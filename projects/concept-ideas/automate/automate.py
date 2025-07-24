import pyautogui

class Automate:
    def __init__(self):
        ...

    def navigation(self, button: str):
        pyautogui.PAUSE = 1

        match button:
            case "green_back":
                pyautogui.click(pyautogui.locateCenterOnScreen('src/images/green_back.PNG', confidence = 0.8))
            case "yellow_back":
                pyautogui.click(pyautogui.locateCenterOnScreen('src/images/yellow_back.PNG', confidence = 0.8))
            case "red_cancel":
                pyautogui.click(pyautogui.locateCenterOnScreen('src/images/red_cancel.PNG', confidence = 0.8))
            case "save_button":
                pyautogui.click(pyautogui.locateCenterOnScreen('src/images/save_button.PNG', confidence = 0.8))
            case "green_check":
                pyautogui.click(pyautogui.locateCenterOnScreen('src/images/green_check.PNG', confidence = 0.8))
            case "execute_button":
                pyautogui.click(pyautogui.locateCenterOnScreen('src/images/execute_button.PNG', confidence = 0.8))
            case _:
                print("Error: navigation(), cases") 

    def new_window(self):
        target_x, target_y = pyautogui.locateCenterOnScreen('src/images/address_bar.PNG', confidence = 0.8)

        execution_step = [
            lambda: pyautogui.click(target_x, target_y),
            lambda: pyautogui.hotkey('ctrl', 'n'),
            lambda: pyautogui.click(target_x, target_y),
            lambda: pyautogui.typewrite("SMEN"),
            lambda: pyautogui.hotkey('enter'),
        ]

        pyautogui.PAUSE = 1

        for execute in execution_step:
            execute()

    def t_code_navigation(self, t_code: str, argument_list: list): # list = equip_sit, [force element]
        self.argument_list = argument_list

        match t_code:
            case "equip_sit":
                if(len(argument_list) == 1):
                    argument_list.append("WPTUAA")

                target_x, target_y = pyautogui.locateCenterOnScreen('src/images/equip_sit.PNG', confidence = 0.8)

                execution_step = [
                    lambda: pyautogui.doubleClick(target_x, target_y),
                    lambda: pyautogui.click(pyautogui.locateCenterOnScreen('src/images/force_element_bar.PNG', confidence = 0.5), ),
                    lambda: pyautogui.typewrite(self.argument_list[1]),
                    lambda: self.navigation("execute_button")
                ]

                pyautogui.PAUSE = 1.0

                for execute in execution_step:
                    execute()
            case "mat_sit":
                ...
            case "iw38":
                if(len(argument_list) == 1):
                    argument_list.append("WPTUAA")

                target_x, target_y = pyautogui.locateCenterOnScreen('src/images/iw38.PNG', confidence = 0.8)

                execution_step = [
                    lambda: pyautogui.doubleClick(target_x, target_y),
                    # lambda: pyautogui.click(pyautogui.locateCenterOnScreen('src/images/period_bar.PNG', confidence = 0.5)),
                    lambda: pyautogui.hotkey('ctrl', 'a'),
                    lambda: pyautogui.hotkey('delete'),
                    # lambda: pyautogui.click(pyautogui.locateCenterOnScreen('src/images/work_center_bar.PNG', confidence = 0.5)),
                    lambda: pyautogui.typewrite(self.argument_list[1]),
                    lambda: self.navigation("execute_button")
                ]
                
                pyautogui.PAUSE = 1.0

                for execute in execution_step:
                    execute()
            case "iw39":
                ...
            case "iw47":
                ...
            case _:
                print("Error: t_code_navigation(), case exhausted")