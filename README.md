# JinX
Simple compiler written in C++ to work with a declarative language called Jinx.


## Syntax of Jinx
```
begin <block_name>                          `<- mark begining of program`

    !# This will be a comment
    number a = 1                            `<- Variable Declarations`

    a = 4                                   `<- Variable ReAssignment`

    print a                                 `<- Print variable value to system standard output stream`
end <block_name>                            `<- mark end of program`
```


## Simple Program
```
begin main
    !# Declare variables
    number a = 1
    number b = 2

    !# Print them to the console
    print a
    print b

    !# Assign B to A and then print the new value of A
    !# a = b
    print a b
end main
```


## File Extension
All files for Jinx end with the extensions either `jx` or `jinx`.


## Execution Command
`make; ./bin/main ./examples/simple.jx`