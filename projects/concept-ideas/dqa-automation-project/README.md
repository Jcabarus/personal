## Description
The current repair ticket workflow has many manual steps including sending notifications, updating attributes, calculating repair estimate cost, etc. that can be automated. We plan to also evaluate permissions and restrict the application to certified repair technicians. The repair ticket also includes a laptop assignment for a loaner laptop. This can make it difficult of technicians to find where the ticket is for laptops being checked out as well as having two different forms for the same process.

Evaluate the Device Quality Assurance (DQA) process and workflow. In 2025 student workers completed 2,844 DQA tickets with 475 hours logged. Determine if anything in the process can be sped up or automated such as scripting diagnostic tests, bulk creating tickets, etc.

## Restriction
- Must be a standalone, any dependecies should not be needed 

## Developement Log
- There a main two ways that this can be implemented. Python or powershell scripting. I think that it's a lot easier if it were to be implemented in powershell since it's already built-in.

- Another way is Python, however due to restriction, it must be compile into Windows EXE format. Which I will be using since it's simple.
    - The libraries will be used are:
        - PyInstaller, which compiles all necessary libraries and creates into an exe in Windows Environment

- DQA Process:
    - Test charging port
    - Test touchscreen functionality
    - Test Keyboard functionality
    - Test Mouse/Trackpad functionality
    - Test Network Adapter, making sure an IP address is available
    - Test Video Port functionality
    - Test Audio Ouput functionality
    - Test Microphone functionality
    - Test Camera functionality
    - Test USB Port functionality

- What can be automated:
    - Test Camera functionality - By automatically open the Camera app
    - Test Network Adapter, making sure an IP address is available - By having an ethernet plugged, run ipconfig
    - Test Audio Ouput functionality - By playing out a sound

- What can be semi-automated:
    - Test Keyboard functionality - By opening an website that listens for keyboard ouput
    - Test Microphone functionalit - By opening microphone indicator in Settings

- What can't be automated
    - Test charging port - Must be manually done
    - Test touchscreen functionality - Must be physically touching the screen
    - Test USB Port functionality -  Must be physically inserting a USB
    - Test Video Port functionality - Must be physically plugging in an HDMI cable
    - Test Mouse/Trackpad functionality - By moving the mouse cursor around

## Goal
- Implement automated scripting
- Implement automated DQA ticket generation
    
## How to Build
