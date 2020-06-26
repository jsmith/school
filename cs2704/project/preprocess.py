import pandas as pd

# https://data.worldbank.org/indicator/NY.GDP.MKTP.CD
# https://ourworldindata.org/land-use#total-agricultural-land-use
# https://ourworldindata.org/internet#internet-access

gdp_across_time = pd.read_csv("gdp-across-countries.csv")
total_ag_area = pd.read_csv("total-agricultural-area-over-the-long-term.csv")
total_ag_area_2016 = total_ag_area.query('Year == 2016')

# total_ag_area.query("Year == '2016'")['Entity'].to_list()
# print(gdp_across_time)

gdp_2016 = gdp_across_time['2016']
countries = gdp_across_time['Data Source']

print(countries.to_list())

set().intersection()
