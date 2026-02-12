## Description

The current repair ticket workflow has many manual steps including sending notifications, updating attributes, calculating repair estimate cost, etc. that can be automated. We plan to also evaluate permissions and restrict the application to certified repair technicians. The repair ticket also includes a laptop assignment for a loaner laptop. This can make it difficult of technicians to find where the ticket is for laptops being checked out as well as having two different forms for the same process.

Evaluate the Device Quality Assurance (DQA) process and workflow. In 2025 student workers completed 2,844 DQA tickets with 475 hours logged. Determine if anything in the process can be sped up or automated such as scripting diagnostic tests, bulk creating tickets, etc.

## Restriction
- Must be a standalone, any dependecies should not be needed 

## Developement Log
Implement automated scripting
- There a main two ways that this can be implemented. Python or powershell scripting. I think that it's a lot easier if it were to be implemented in powershell since it's already built-in.
- Another way is Python, however due to restriction, it must be compile into Windows EXE format. Which I will be using since it's simple.
    - The libraries will be used are:
        - PyInstaller, which compiles all necessary libraries and creates into an exe in Windows Environment
## Goal
- Implement automated scripting
- Implement automated DQA ticket generation
    
## How to Build
