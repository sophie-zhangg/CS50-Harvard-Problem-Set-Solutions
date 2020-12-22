from cs50 import get_string

# Get text input
text = get_string("Text: ")
# Initialize variables
lett = sent = 0
words = 1
# For loop over every character
for i in range(len(text)):
    if text[i].isalpha():
        lett += 1
    elif text[i] in (".", "?", "!"):
        sent += 1
    elif text[i] == " ":
        words += 1
# Calculate readability w/ the Coleman-Liau formula
grade_lev = round(0.0588 * (lett / words * 100) - 0.296 * (sent / words * 100) - 15.8)
# Print grade level
if grade_lev < 1:
    print("Before Grade 1")
    exit(0)
elif grade_lev >= 16:
    print("Grade 16+")
    exit(0)
else:
    print(f"Grade {grade_lev}")
    exit(0)
exit(1)