# L3
L3 implementation details & observations.

## Impl Details
- From the lecture, Dr. Kent specified that we had the ability to be flexible with our implementation. Because of this, I choose to use an array buffer and count variable. When using these together, they act as a FILO (ie. stack) data structure.
- I generate the characters in the buffer using an uppercase array. For example, if the buffer size is 10, the contents of the array will always be `['A', 'B', 'C', ..., 'I', 'J']`. This helped performs observation.

## Observations
- When N == M, `A` is the only character printed out. It is consistently printed every `N` seconds. In this scenario, the amount of data produced and consumed is equal and neither thread is starved.
- When N < M, the producer is creating more data than can be consumed by the consumer. We see that the characters being printed out are increasing in size since the producer is consuming from the top of the stack. Eventually, there will be no more room in the buffer and the producer will be limited by the consumer.
- When N > M, the producer is creating less data than can be consumed by the consumer. In this situation, the only character that is being printed out is `A` as that value is immediately consumed by the consumer. We only see that the consumer is limited by the producer and will only print out a character every `N` seconds. 