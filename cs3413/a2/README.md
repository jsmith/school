# A2
The A2 README :)

## Assumptions
- For Q1, the max line length of each line is 1000 characters
- For Q1, if a user inputs an empty line the program terminates

## Implementation Details
### Q1
- Create an array file descriptors of n + 1 * 2 where n is # of ciphers
- Create n threads which read, transform, and then write
- In the main thread, read a line of text, write to the first FD and then read from the last
- Print out the results
- If an empty line is read in, terminate the program!

### Q2
- Basi