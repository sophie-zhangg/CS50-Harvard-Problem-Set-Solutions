# TODO
import csv
import sys
from cs50 import SQL


# Import the SQL database
db = SQL("sqlite:///students.db")


# Check command-line arguments
if len(sys.argv) != 2:
    print("missing command-line argument")
    exit(1)
data = list(csv.reader(open(sys.argv[1])))
# Clear whichever rows are currently in the table
db.execute("DELETE FROM students")
# Iterate through rows of data
for row in range(1, len(data)):
    # Extract data
    x = data[row]
    full_name = x[0].split()
    first = full_name[0]
    if len(full_name) == 3:
        middle = full_name[1]
        last = full_name[2]
    else:
        middle = None
        last = full_name[1]
    house = x[1]
    birth = x[2]
    # Insert relevant data from variables
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)