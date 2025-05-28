## Repository Workflow
```
Prerequisites:
    1. ssh-keygen
    2: cat .ssh/id_rsa.pub and copy the generate key
    3: Goto SSH settings"
    4: Paste the generated key

Empty Directory:
    1. git init
    2. git clone

Making Changes:
    1. git add
    2. git commit
    3. git push

Reverting Changes:
    1. git restore <file | dir/ | .>
    1. git rm --cached <file | dir/>

Branch Management:
    1. git branch -a
    2. git branch <branch_name>
        a. git push -u origin <branch_name> 
    3. git checkout <branch_name> or git switch <branch_nname>
    4. git branch -d <branch_name> 
        a. git push origin --delete <branch_name> 
    5. git merge
    6. git pull

Repository Management:
    Local:
        1. git status
        2. git log
    Remote:
        1. git remote -v
        2. git remote set-url origin <url>
        3. git push --all origin
        4. git push --tags origin

Troubleshooting:
    1. Repository Management
```
<br>

## Guideline
```
Commit template:
       Added: git commit -m "[+][reason]"
     Deleted: git commit -m "[-][reason]"
    Modified: git commit -m "[*][reason]"
     Nesting: git commit -m "[+-*][reason]"
```
<br>

## Setup Configuration
**Username configuration**
```
git config --global user.name <name>
```
<br>

**Email configuration**
```
git config --global user.email <email address>
```
<br>

**Command line output colorization accessbility**
```
git config --global color.ui auto
```
<br>

## Branches
**Displays all the local branches including remote branches. with `*` is pointing to what branch you are in**
```
git branch -a 
```
<br>

**Initializes `<branch_name>` in a local repository, followed by `git push -u origin <branch_name>` to push `<branch_name>` to remote repository**
```
git branch <branch_name>
```
<br>

**Switches branch to `<branch_name>`. To verify what branch you are in `git status`**
```
git checkout <branch_name> 
```
<br>

**Merge `<branch_name>` history to current branch**
```
git merge <branch_name> 
```
<br>

**Deletes `<branch_name>` in a local repository, followed by `git push origin --delete <branch_name>` to delete `<branch_name>` to the remote repository**
```
git branch -d <branch_name> 
```
<br>

## Applying Changes
**Displays version history for the current branch** 
```
git log 
```
<br>

**Displays history of `<file>`** 
```
git log --follow <file> 
```
<br>

**Displays the difference between `<branch_a>` `<brach_b>`**
```
git diff <branch_a> <branch_b>  
```
<br>

**Displays metadata and changes of `<commit>`**
```
git show <commit> 
```
<br>

**Prepares the `<file | dir/ | .>` for staging**
```
git add <file | dir/ | .> 
```
<br>

**Stages the commit for `git push`**
```
git commit -m <messsage> 
```
<br>

## Synchronizing Changes
**Fetches the history from the remote branch**
```
git fetch 
```
<br>

**Merges branche's history into the current branch. This is usually part of the Git operation**
```
git merge <branch>
```
<br>

**Pushes the changes from local repository to the remote repository**
```
git push 
```
<br>

**Updates the local branch's commits from the remote branch**
```
git pull 
```
<br>

## Repository Initialization
**Initializes local directory a local repository. `.gitignore` is create upon command execution**
```
git init 
```
<br>

**Downloads remote reposity**
```
git clone <url> 
```
<br>

## Redo Commits
**Undo all commits after `commits`, and preserving changes locally**
```
git reset <commit> 
```
<br>

**Undo all commits after `commits`, and no change preservation**
```
git reset --hard <commit> 
```