import ca.jacob.jml.Algorithm;
import ca.jacob.jml.Dataset;
import ca.jacob.jml.KFold;
import ca.jacob.jml.bayes.NaiveBayes;
import ca.jacob.jml.ensemble.AdaBoost;
import ca.jacob.jml.math.Tuple;
import ca.jacob.jml.math.distance.Euclidean;
import ca.jacob.jml.math.distance.Hamming;
import ca.jacob.jml.math.distribution.Gaussian;
import ca.jacob.jml.tree.ID3;
import ca.jacob.jml.ensemble.RandomForest;
import ca.jacob.jml.neighbors.KNN;
import ca.jacob.jml.Report;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import static ca.jacob.cs6735.DataUtil.*;

public class Assignment {
    private static int NUMBER_OF_K_FOLD_ITERATIONS = 10;
    private static final KFold K_FOLD = new KFold(5, false);
    private static boolean MULTITHREADED = false;

    public static void main(String[] args) throws Throwable {
        // Parsing the optional arguments
        for(String arg : args) {
            if(arg.equals("verbose")) {
                K_FOLD.setVerbose(true);
                continue;
            }

            if(arg.equals("multithreaded")) {
                MULTITHREADED = true;
                continue;
            }

            try {
                NUMBER_OF_K_FOLD_ITERATIONS = Integer.parseInt(arg);
            } catch (Exception e) {
                // Do nothing
            }
        }

        // init
        List<Tuple<Dataset, List<Algorithm>>> datasetsAndAlgorithms  = new ArrayList<>();
        List<Algorithm> algorithms;

        // Breast Cancer Data
        algorithms = new ArrayList<>();
        algorithms.add(new ID3(ID3.MAX_LEVEL_NONE, 1));
        algorithms.add(new NaiveBayes());
        algorithms.add(new AdaBoost(new ID3(1), 100, 0.5));
        algorithms.add(new AdaBoost(new NaiveBayes(), 100, 0.1));
        algorithms.add(new RandomForest(new ID3(), 120, 0.7));
        algorithms.add(new KNN(1, new Hamming()));
        datasetsAndAlgorithms.add(new Tuple<>(loadBreastCancerData(Assignment.class), algorithms));

        // Car Data
        algorithms = new ArrayList<>();
        algorithms.add(new ID3(ID3.MAX_LEVEL_NONE, 1));
        algorithms.add(new NaiveBayes());
        algorithms.add(new AdaBoost(new ID3(4), 200, 0.3));
        algorithms.add(new AdaBoost(new NaiveBayes(), 100, 0.4));
        algorithms.add(new RandomForest(new ID3(), 200, 0.6));
        algorithms.add(new KNN(1, new Hamming()));
        datasetsAndAlgorithms.add(new Tuple<>(loadCarData(Assignment.class), algorithms));

        // E Coli. Data
        algorithms = new ArrayList<>();
        algorithms.add(new ID3(ID3.MAX_LEVEL_NONE, 2));
        algorithms.add(new NaiveBayes(new Gaussian()));
        algorithms.add(new AdaBoost(new ID3(3), 200, 0.2));
        algorithms.add(new AdaBoost(new NaiveBayes(new Gaussian()), 250, 0.10));
        algorithms.add(new RandomForest(new ID3(), 250, 0.6));
        algorithms.add(new KNN(1, new Euclidean()));
        datasetsAndAlgorithms.add(new Tuple<>(loadEColiData(Assignment.class), algorithms));

        // Mushroom Data (takes some time to run ensemble algorithms)
        algorithms = new ArrayList<>();
        algorithms.add(new ID3(ID3.MAX_LEVEL_NONE, 1));
        algorithms.add(new NaiveBayes());
        algorithms.add(new AdaBoost(new ID3(3), 10, 0.3));
        algorithms.add(new AdaBoost(new NaiveBayes(), 10, 0.5));
        algorithms.add(new RandomForest(new ID3(), 10, 0.5));
        algorithms.add(new KNN(1, new Hamming()));
        datasetsAndAlgorithms.add(new Tuple<>(loadMushroomData(Assignment.class), algorithms));

        // Letter Data (takes some time to run ensemble algorithms)
        algorithms = new ArrayList<>();
        algorithms.add(new ID3(ID3.MAX_LEVEL_NONE, 1));
        algorithms.add(new NaiveBayes(new Gaussian()));
        algorithms.add(new AdaBoost(new ID3(8), 300, 0.25));
        algorithms.add(new AdaBoost(new NaiveBayes(new Gaussian()), 10, 0.3));
        algorithms.add(new RandomForest(new ID3(), 100, 0.6));
        algorithms.add(new KNN(1, new Hamming()));
        datasetsAndAlgorithms.add(new Tuple<>(loadLetterData(Assignment.class), algorithms));

        for(Tuple<Dataset, List<Algorithm>> datasetAndAlgorithm : datasetsAndAlgorithms) {
            algorithms = datasetAndAlgorithm.last();
            if(algorithms.size() == 0) {
                continue;
            }

            Dataset d = datasetAndAlgorithm.first();
            System.out.println(d);
            System.out.println("==========================");

            for(Algorithm a : algorithms) {
                Report report = new Report();

                if(MULTITHREADED) {
                    final ExecutorService service;
                    final List<Future<Report>> tasks = new ArrayList<>();
                    service = Executors.newFixedThreadPool(NUMBER_OF_K_FOLD_ITERATIONS);
                    K_FOLD.init(a, d);
                    for (int i = 0; i < NUMBER_OF_K_FOLD_ITERATIONS; i++) {
                        System.out.print(i + 1);
                        tasks.add(service.submit(K_FOLD));
                    }

                    for (int i = 0; i < NUMBER_OF_K_FOLD_ITERATIONS; i++) {
                        try {
                            Report r = tasks.get(i).get();
                            report.combine(r);
                        } catch (InterruptedException | ExecutionException e) {
                            e.printStackTrace();
                        }
                    }
                } else {
                    for (int i = 0; i < NUMBER_OF_K_FOLD_ITERATIONS; i++) {
                        System.out.print(i + 1);
                        Report r = K_FOLD.generateReport(a, d);
                        report.combine(r);
                    }
                }
                System.out.println();
                System.out.println(a);
                System.out.println(report);
                System.out.println();
              }
        }
    }
}
