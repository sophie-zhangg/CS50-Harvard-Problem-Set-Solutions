# TODO
import csv
import sys
from cs50 import SQL


# Import the SQL database
db = SQL("sqlite:///students.db")


# Begin by checking the command-line arguments
if len(sys.argv) != 2:
    print("missing command-line argument")
    exit(1)
house = sys.argv[1]
# Select students from correct house
table = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ?", house)
# Sort the students by last and then first name
table.sort(key=lambda x: (x['last'], x['first']))
# Iterate through list of dictionaries
for row in range(len(table)):
    temp_dict = table[row]
    # Check if students have middle names or not
    if temp_dict["middle"] == None:
        print(f"{temp_dict['first']} {temp_dict['last']}, born {temp_dict['birth']}")
    else:
        print(f"{temp_dict['first']} {temp_dict['middle']} {temp_dict['last']}, born {temp_dict['birth']}")