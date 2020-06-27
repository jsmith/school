from bokeh.plotting import figure, output_file, show, ColumnDataSource
from bokeh.models.tools import HoverTool
import sys
import pandas as pd

if len(sys.argv) != 3:
    print("Usage: preprocess.py INPUT OUTPUT")
    sys.exit(1)

input_csv, output_html = sys.argv[1:]

if not input_csv.endswith(".csv"):
    print("INPUT must be a csv")
    sys.exit(1)

if not output_html.endswith(".html"):
    print("OUTPUT must be a html")
    sys.exit(1)

df = pd.read_csv(input_csv)
# Creating a size column using the log of the GDP columns
df["size"] = df["GDP_PC"]  # np.log(df["GDP_PC"])

# Changing the range of this column to a new value
max_gdp = df["size"].max()
df["size"] = df["size"] / max_gdp * 15 + 5
print(df["size"].to_list())

source = ColumnDataSource(df)

p = figure()
p.circle(x='GDP_PC', y='INT',
         source=source,
         size="size", color='green')

p.title.text = 'Internet Usage Across Nations'
p.xaxis.axis_label = 'GDP Per Capita (2011 International $)'
p.yaxis.axis_label = 'Individuals Using The Internet (%)'

hover = HoverTool()
hover.tooltips=[
    ('Country', '@Entity'),
    ('GDP Per Capita', '@GDP_PC'),
    ('Internet Usage (%)', '@INT'),
]

p.add_tools(hover)

# output to static HTML file
output_file(output_html)

# show the results
show(p)
