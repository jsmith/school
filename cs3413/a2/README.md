# A2
The A2 README :)

## Assumptions
- For Q1, the max line length of each encryption line is 1000 characters
- For Q1, if a user inputs an empty encryption line the program terminates

## Implementation Details
### Q1
- Create an array file descriptors of n + 1 * 2 where n is # of ciphers
- Create n threads which read, transform, and then write
- In the main thread, read a line of text, write to the first FD and then read from the last
- Print out the results
- If an empty line is read in, terminate the program!

### Q2
- Keep a global "tickets left" variable that is used to determine if there are tickets left to sell
- Pass in a "Seller" struct with a "tickets_sold" attribute to the seller thread which the seller can use to keep track of their tickets sold
- Use a global "customer id" to get unique customer IDs
- Use an integer array to keep track of the # of remaining tickets per day. This uses a dynamically resizing array!