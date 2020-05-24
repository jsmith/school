# A3
The A3 README!!

> Note, I've sometimes observed behaviour where the input parses the incorrect # of words in a line. If you see this, just run it again! I've never seen it fail twice in a row.

## Assumptions
### Q1
- The assignment mentioned "each CPU is a pthread in your solution" but that seems to be a typo. I do comply with this requirement but there is only one CPU.
- If a new job arrive that has *lower* priority than the currently running job (no matter where that job is from), it does not interrupt the CPU.
- If a new job does interrupt the CPU due to priority, the current job is not modified in any way and just inserted back into its original queue.
- Name buffer size is 100.

### Q2
- Two cars *cannot* leave in the same direction at the same time unit. The second car will have to wait for the next time unit.
- Name buffer size is 100.

## Implementation Details
### Q1
- It basically just follows the algorithm described in the question.
- It takes it one "time increment" at a time. During each loop, it checks:
    1. What jobs have arrived?
    2. Is the current job still running or is there a new job that should take priority (due to preemption of queue0)?
    3. If the job is finished for now (due to any of the above conditions), get the next job and place in on the CPU.
    4. Before you run the above step, process the job that just came off the OS. Is it finished? If not, where should it be added back?

### Q2
- Using a [conditional variable](https://en.cppreference.com/w/cpp/thread/condition_variable) to implement Q2. This is built using semaphores and the implementation can be found in `cv.c`. Basically, a conditional variable is useful for notifying a set of threads that something has occurred.
- Why did I take this approach? To make the solution a lot easier, I decided to take things one time unit at a time. To do this, I needed a way to tell threads that "hey, the time has been incremented and I want you to run your logic".
- Threads (ie. cars) can be in two different states: "waiting" or "driving".
- Depending on the state they run different logic.
- If they're waiting, they check "have I arrived at the bridge yet?", "has someone already left at this time unit?", "are there cars coming the from the other direction?". If all of those checks pass, the car then becomes a "driver".
- We use a simple char variable ('N', 'S') and a counter (# of cars on the bridge) to determine the current state of the bridge. 
- A "driver" has its own logic that it runs every time unit that basically checks "am I there yet?".
- Once a driver "arrives", the thread terminates. 
- That's it! I feel like the solution is pretty intuitive :)
