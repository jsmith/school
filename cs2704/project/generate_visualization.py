from bokeh.plotting import figure, output_file, show, ColumnDataSource
from bokeh.models.tools import HoverTool
from bokeh.models.formatters import NumeralTickFormatter
import sys
import pandas as pd
import random

if len(sys.argv) != 2:
    print("Usage: generate_visualization.py YEAR")
    sys.exit(1)

input_year = sys.argv[1]


def rgb2hex(r, g, b):
    return "#{:02x}{:02x}{:02x}".format(r, g, b)


def gen_pastel_color(mix):
    red = round(random.random() * 256)
    green = round(random.random() * 256)
    blue = round(random.random() * 256)

    # mix the color
    if mix:
        red = (red + mix[0]) / 2
        green = (green + mix[1]) / 2
        blue = (blue + mix[2]) / 2

    return rgb2hex(round(red), round(green), round(blue))


df = pd.read_csv(f"data_{input_year}.csv")
# Creating a size column using the log of the GDP columns
df["size"] = df["GDP_PC"]  # np.log(df["GDP_PC"])
df["color"] = [gen_pastel_color((200, 200, 200)) for _ in range(len(df))]

# Changing the range of this column to a new value
max_gdp = df["size"].max()
df["size"] = df["size"] / max_gdp * 15 + 5
print(df["size"].to_list())

source = ColumnDataSource(df)

p = figure()
p.circle(x='GDP_PC', y='INT',
         source=source,
         size="size", color='color')

p.title.text = f'Internet Usage Across Nations In {input_year}'
p.xaxis.axis_label = 'GDP Per Capita (2011 International Dollars)'
p.yaxis.axis_label = 'Individuals Using The Internet (%)'
p.xaxis[0].formatter = NumeralTickFormatter(format="$0")

hover = HoverTool()
hover.tooltips=[
    ('Country', '@Entity'),
    ('GDP Per Capita', '@GDP_PC'),
    ('Internet Usage (%)', '@INT'),
]

p.add_tools(hover)

# output to static HTML file
output_file(f"output_{input_year}.html")

# show the results
show(p)
