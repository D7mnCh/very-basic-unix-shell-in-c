# very-basic-unix-shell-in-c
tried to impl basic unix shell in c for learning purposes

# what i have learned
## about Unix-shell process
- in C, to convert an int to char in the terminal, get the keycode(numeric value) for that key (e.g 60 ), and let c format it into an a char using %c format spicifier (that 60 becomes "<" char)
- `^[` == `Esc`keycode
## about c
- you can't compare strings in c, if so you are comparing addresses, use `strcmp` to compare the content
- break from nested loop by using turned that block into a function and do early return if wanna break, rathen then using `goto`
# Resources
- [keycode table cheatsheet](https://www.toptal.com/developers/keycode/table)
- [Escape-codes cheatsheet](https://web.archive.org/web/20121225024852/http://www.climagic.org/mirrors/VT100_Escape_Codes.html) E.g \033[2J to clean the term screen

# read/search
- `REPL`?
- [Streams meaning](https://stackoverflow.com/questions/38652953/what-does-stream-mean-in-c) 
