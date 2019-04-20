# Exam
## Architectural Tactics and Patterns
- A pattern is
    - A set of design decisions that are found in practice
    - has known properties that permit use
    - describe a class of architectures

- Patterns are not invented, they are found in practice.
- There will never be a complete list of patterns as they are always being created/destroyed depending on the environment.
- Architectures are seldom found using first principles.
- Patterns package tactics. They are typically constructed of several different tactics.
- Multiple patterns can (should) be used within a complex system.

### Layered Pattern
#### Context
To develop and evolve portions of the system independently.

#### Problem
Modules can be developed independently, with little to no interaction among parts, supporting portability, modifiability, and reuse.

#### Solution
The layered patterns defines a set of layers (groupings of modules that offer a cohesive set of services) and uni-directional allowed to use layers (ie. a layer is aloud to use the next lower layer) among the layers.

The layered pattern is heavily used. For example, consider a running Java program. Program -> JVM -> OS -> Hardware.

### Broken Pattern
#### Context
Implementing systems with collaborative services: interoperation, connection, information exchange, and service availability.

#### Problem
How to structure distributed software such that modules do not need to know the nature/location of the service providers. How do we dynamically change the bindings between services?

#### Solution
The pattern defines a runtime component called the broker which mediates the communication between between an number of clients and services.

### MVC Pattern
#### Context
For interactive GUI based systems, to keep modifications to the user interface separate from the rest of the system, and support multiple or alternative views of computing results or current state of data.

#### Problem
• How can user interface functionality be kept separate from application functionality and still be responsive to user input, or changes in the underlying application’s data?
• How can multiple views of user interface be created, maintained, and coordinated when the underlying application data changes?

#### Solution

### Pipe-and-Filter Pattern
#### Context
transform streams of data items from input to output, using reusable components.

#### Problem
divide a system into reusable, loosely coupled components with simple, generic interaction mechanisms with flexible and dynamic combination of such reusable components, also support parallel executions of components

#### Solution
