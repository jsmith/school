# CS6735 Programming Assignment
This folder contains one Java file `Assignment.java` and the `jml.jar` (Java Machine Learning) jar file.

## Running
Two accompanying files help run the assignment on either Windows or Unix based computers: `run.bat` or `run.sh`. Simply run one of these files.

## Training Time
Training on the `breast-cancer-wisconsin.data`, `car.data` and `ecoli.data` datasets takes minimal time; however, the `letter-recognition.data` and `mushroom.data` do take longer, especially for the ensemble algorithms.

## Optional Arguments
* Verbose: This will output every new k-fold iteration (default `false`)
* Multithreaded: This will run every iteration of one dataset/algorithm pair at the same time (default `false`)
* Number of iterations: This is the number of cross validation algorithms that will be implemented (default `10`)

*An example of how to use the arguments is provided in the script files.*

## Other Information
If you want to only run some algorithms, simply comment out those you do not wish to run in `Assignment.java`.
