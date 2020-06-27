import scipy.stats
import sys
import pandas as pd

if len(sys.argv) != 2:
    print("Usage: analyze.py YEAR")
    sys.exit(1)

input_year = sys.argv[1]

df = pd.read_csv(f"data_{input_year}.csv")
result = scipy.stats.pearsonr(df["GDP_PC"], df["INT"])
print(result)

