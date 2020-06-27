import scipy.stats
import sys
import pandas as pd

if len(sys.argv) != 2:
    print("Usage: preprocess.py INPUT")
    sys.exit(1)

input_csv = sys.argv[1]

if not input_csv.endswith(".csv"):
    print("INPUT must be a csv")
    sys.exit(1)

df = pd.read_csv(input_csv)

# print(df["GDP_PC"].to_list())
# print(df["INT"].to_list())

result = scipy.stats.pearsonr(df["GDP_PC"].to_list(), df["INT"].to_list())
print(result)

# /Users/jacob/git/school/cs2704/project/venv/bin/python /Users/jacob/git/school/cs2704/project/analyze.py data_2016.csv
# (0.7794576677679484, 3.314131098645568e-48)

# /Users/jacob/git/school/cs2704/project/venv/bin/python /Users/jacob/git/school/cs2704/project/analyze.py data_2000.csv
# (0.6869152264016811, 1.3033324290700025e-32)
