# A1
## Requirements
- This uses `c99`

## Running
First, build the appropriate question:
```shell
# Use one of the following commands to compile the code.
make q1
make q2
make q3
```

And then run:
```
./a.out
```

## Assumptions
1. Processes are identified by a *single* char.
2. The maximum size of a user's name is `10` characters.
3. Each input *line* does not exceed `100` characters.
4. For all three questions, a CPU *will* print out `IDLE` if it idles before all jobs are finished. Also, in Q2, if a CPU never does any work at all, it will never print `IDLE`. This is just an implementation detail which I think is fine as there are no given constraints around printing `IDLE`.
5. For Q3, if a CPU sees a job that hasn't arrived yet, it sleep until it arrives. Q3 is a bit vague IMO and left open to interpretation in some respects.

## Algorithm Explanations
1. Simply iterate through the list of jobs. Keep a `time` variable but always set the `time` to the maximum of `time` and `job->arrival`. Use a linked list of users to keep track of the end time of their last job.
2. Keep two queues of processors. One is the idle queue and the other is the running queue. The running queue is a priority queue ordered by end time. Also keep a `time` variable but this time increment it by one each loop to simulate a CPU cycle. During each cycle, check if any processors have completed their jobs and add all idle processors back to the idle queue. Finally, check for any CPUs that were previously running but are now idle and print that they are idling. Next, during the same cycle, check for jobs that have arrived. Use any idle processors to complete those jobs. Again, use a linked list of users to keep track of the end time of their last job.
3. Create `n` threads which first grab a job from the queue, sleep if the job hasn't arrived yet, print out the information about the job and then sleep for the duration of the job. Again, use a linked list of users to keep track of the end time of their last job.
