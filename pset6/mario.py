from cs50 import get_int

# Main function


def main():
    i = get_height()
    make_pyramid(i, i)

# Get height from 1 to 8 inclusive


def get_height():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n

# Print the pyramid, first parameter is the height and the n is the recursive counter


def make_pyramid(h, n):
    if n == 0:
        return
    # Implementation of recursion
    make_pyramid(h, n - 1)
    # Print necessary spaces
    print(" "*(h - n), end="")
    # Print left side
    for i in range(n):
        print("#", end="")
    # Print gap
    print("  ", end="")
    # Print right side
    for i in range(n):
        print("#", end="")
    # Print new line
    print()


# Call main function
main()