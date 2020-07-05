# CS2701 Project
The project README!!

## Setup
First, make sure you have Python >= 3.6 installed. Next, just run the following command:

```
pip install -r requirements.txt
```
> I recommend first using a `virtualenv` before running the above `pip install` command.

## Usage
First, you need to preprocess your data.
```
python preprocess.py
```

This will create `data_2000.csv` and `data_2016.csv`. Next, you can either create the visualizations or the the analyzes. These instructions will first go over visualization.
```
python generate_visualizations.py 2000
python generate_visualizations.py 2016
```

This will output two html files which will be served by the server later.

Finally, we'll run the actual analysis.
```
python analyze.py 2000
python analyze.py 2016
```

## Server
To view the visualizations through a server, just run the following command and then navigate to http://localhost:8080.
```
python server.py
```
