:: Compiling the Java file with the proper classpath
javac -classpath ".;jml.jar" Assignment.java

:: Running the compiled file
java -classpath ".;jml.jar" Assignment

:: Run with optional parameters (verbose, multithreaded or # of iterations)
:: java -classpath ".;jml.jar" Assignment multithreaded 10
