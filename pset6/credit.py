from cs50 import get_int

# Main function


def main():
    # Ask for input of card number
    card_num = get_int("Number: ")
    num_of_digits = get_card(card_num)
    sum = check_sum(card_num, num_of_digits)
    first_two = get_digit(card_num, num_of_digits) * 10 + get_digit(card_num, num_of_digits - 1)
    if sum % 10 == 0:
        if (first_two == 34 or first_two == 37) and num_of_digits == 15:
            print("AMEX")
            exit(0)
        elif (first_two > 50 and first_two < 56) and num_of_digits == 16:
            print("MASTERCARD")
            exit(0)
        elif int(first_two / 10) == 4 and (num_of_digits == 13 or num_of_digits == 16):
            print("VISA")
            exit(0)
        else:
            print("INVALID")
            exit(2)
    else:
        print("INVALID")
        exit(3)


# Return the num of digits in the card number
def get_card(card_num):
    if card_num >= 1000000000000 and card_num < 10000000000000:
        return 13
    elif card_num >= 100000000000000 and card_num < 1000000000000000:
        return 15
    elif card_num >= 1000000000000000 and card_num < 10000000000000000:
        return 16
    else:
        print("INVALID")
        exit(1)


# check sum function
def check_sum(card, num_of_digits):
    sum = 0
    counter = 1
    while True:
        current = get_digit(card, counter)
        if counter % 2 == 0:
            current *= 2
            if current > 9:
                current = get_digit(current, 1) + get_digit(current, 2)
        sum += current
        counter += 1
        if counter >= (num_of_digits + 1):
            break
    return sum


# function to get a digit from a number
def get_digit(num, n):
    if (n == 1):
        return num % 10
    return int(num / 10 ** (n - 1) % 10)


# Call main function
main()