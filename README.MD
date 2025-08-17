# Check in Journal
---
## A very simple CLI Check in Journal Project in C++

This project is a very simple project that can track down what you do on every day basis. Inspired by bullet journal, you can jot down an entry from the CLI with a simple command. The personal puprose of this project is to just start creating programming project once again with a stupidly simple CRUD project that I can do in one or two sit. I believe everyone can also replicate this project, regardless the skill level.

### How to build
In this case I'm using `g++` compiler to compile it. Please adjust if you're using another compiler

```
g++ main.cpp -o journal
```

### How to use
The project used the parameter of `main()` function, which is `argc` and `argv`. Which mean you can directly use the command on the Command line terminal.
#### Commands
Use this command to see every command in the CLI

```
./journal HELP 
```

What this program can do with **commands**:
- Add entry to the list
- Save entries as `.txt` file
- Search for a single keyword in every entry
- Show entries that can also be queried by time
- Undo the latest entry
- Reset the save file

To use commands shown in the `HELP` menu, use

```
./journal {command}
```

### Known issues
Because of how simple the project is, there's a huge limitation when it comes to what the program can do. Like how it can't handle different order of the commands, how the search function can only search entry with only one single keyword, or the fact there's no update command.

---
### End of Readme
It's a fun little project that get me back on track of making projects! If you found a bug or have a feedback, you can absolutely tell me about it!