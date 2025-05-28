## Naming Directories
**Acceptable**
- Generally, you want to make the name descriptive and have a sense of purpose.
- The use of `-` is high encouraged for readabily.

Example:
```
- directory
- directory-to-a-file
```

**Not acceptable** <br>
- Generally, don't want to use capitalizations because those are reserved for file naming. 
- Whitespaces are not allowed due to compatibility issues, use `-` instead.
- Not using separation to a directory name is highly discouraged due to unreadable as well was organization

Example:
```
- directorytoafile
- directory to a file
- DirectoryToaFile
```
<br>

## Naming Files
**Acceptable**
- Generally, you want to make the name descriptive and have a sense of purpose.
- The use of `_` is high encouraged for readabily.
- The use of capitalization is allowed and optional.

Example:
```
- file
- File
- file_name
- File_Name
```

**Not acceptable** <br>
- Whitespaces are not allowed due to compatibility issues, use `_` instead.
- Not using separation to a file name is not recommended due to unreadable as well was organization.

Example:
```
- File
- File Name
- FileName
```
<br>

## Projects Directories
- Always have two reserved directories: `src/` and `test/` as well as a `README.md` file. Your in root of the `project/` you can have the final executable, if applicable.
    - `src/` should generally have: source codes, header files
    - `test` should generally have: test files

Example:
```
    example-project/
    |---> README.md
    |---> documentation/
    |---> |-> project.md
    |---> executable
    |---> src/
    |     |---> source_code.cpp
    |     |---> source_code.h
    |---> test/
          |---> test_program1.cpp
          |---> test_program2.cpp
          |---> test_program3.cpp
```