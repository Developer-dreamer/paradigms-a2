# paradigms-a2
## Test plan
1. 1 -> abcd
2. 2 (x2) ->
3. 1 Hello world, from KSE
4. 8 -> 2 5 -> 6 ->
5. 5 -> just for see the result
6. 13 (x2) -> (Undo)
7. 14 -> (Redo)
8. 5 -> make sure everything is correct
9. *You may use here Cut, Copy, Paste here*
10. 16 -> (Check the cursor position)
11. 18 -> (This command will reset cursor position)

## Output
```
Enter a command: 1
Enter a string: abcd
String abcd
Enter a command: 2
New line has been started
Enter a command: 2
New line has been started
Enter a command: 1
Enter a string: Hello world, from KSE
String Hello world, from KSE
Enter a command: 8
Enter coordinates(fromat: (x, y) - (row, line)) : 2 5
Enter the length of the string to delete: 6
Enter a command: 5
abcd

Hello, from KSE
Enter a command: 13
Enter a command: 13
Enter a command: 5
abcd


Enter a command: 14
Enter a command: 5
abcd

Hello world, from KSE
Enter a command: 16
Cursor position: (2, 5)
Enter a command: 18
Enter a command: 0
Program has been closed successfully
```
