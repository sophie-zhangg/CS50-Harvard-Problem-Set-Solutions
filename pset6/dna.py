import csv
import sys

# Main function

# Data saved in dictionary with name and tuple


def main():
    # Initialize variables
    name = ""
    strs = []
    # Take arguments
    if len(sys.argv) != 3:
        print("missing command-line argument")
        exit(1)
    # Read and load files
    data = list(csv.reader(open(sys.argv[1])))
    sequence_f = open(sys.argv[2])
    genome = sequence_f.read()
    # Search each genome for the max and ad to STR list
    for i in range(1, len(data[0])):
        longest = search(data[0][i], genome)
        strs.append(longest)
    match = False
    # Check all the people for a match
    for person in range(1, len(data)):
        for i in range(1, len(data[0])):
            if int(data[person][i]) == strs[i - 1]:
                match = True
                name = data[person][0]
            else:
                match = False
                break
        if match == True:
            print(name)
            exit(0)
    print("No match")
    exit(1)

# Search through the sequence for STR and return the max repeats


def search(STR, seq):
    # Declare and initialize local variable
    max = temp = i = 0
    # Loop through each character
    while i < (len(seq) - len(STR) - 1):
        potential = seq[i:i + len(STR)]
        if potential == STR:
            temp += 1
            i += len(STR)
        else:
            if temp > max:
                max = temp
            temp = 0
            i += 1
    return max


# Call main function
main()