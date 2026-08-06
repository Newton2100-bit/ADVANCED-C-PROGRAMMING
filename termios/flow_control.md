# IXON
## User side flow control
> User → Terminal → Program
>       (user's Ctrl+S affects program's input)
- you user can press C^S or C^Q
- C^S pauses the input to the program
- C^Q resumes input

# IXOFF
> Program → Terminal → User
>       (program's Ctrl+S affects user's output)# program side flow control
- program can send C^S and manipulate.
- program can send C^q to resume terminal outputs
