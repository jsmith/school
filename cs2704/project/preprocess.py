import pandas as pd

# The data source URLs
# https://ourworldindata.org/internet#internet-access
# https://ourworldindata.org/grapher/gdp-per-capita-worldbank

gdp_pc_across_time = pd.read_csv("gdp-per-capita-worldbank.csv")
total_int_access = pd.read_csv("share-of-individuals-using-the-internet.csv")


def get_data_for_year(year: int) -> pd.DataFrame:
    # Filter each dataset to the year we care about
    total_int_access_specific = total_int_access.query(f'Year == {year}').set_index("Entity")
    gdp_pc_specific = gdp_pc_across_time.query(f"Year == {year}").set_index("Entity")

    # Do an inner join on the country name so that we only display data where we have both datapoints
    merged = gdp_pc_specific.merge(total_int_access_specific, left_index=True, right_index=True, how="inner")

    # Renaming since the names are super long
    # The new names aren't that descriptive but are much easier to work with
    merged = merged.rename(columns={
        "GDP per capita (int.-$) (constant 2011 international $)": "GDP_PC",
        "Individuals using the Internet (% of population) (% of population)": "INT",
    })

    # Extracting the columns I care actually about
    return merged.loc[:, ['GDP_PC', "INT"]]


data_2016 = get_data_for_year(2016)
data_2000 = get_data_for_year(2000)

data_2016.to_csv("data_2016.csv")
data_2000.to_csv("data_2000.csv")
