import copy

# Accepts a list of strings
# Doesn't return anything simply modifies the array passed
def alphabetizer(data):
    if len(data) > 1:
        mid = len(data) // 2
        L = data[:mid]
        R = data[mid:]

        alphabetizer(L)
        alphabetizer(R)

        i = j = k = 0

        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                data[k] = L[i]
                i += 1
            else:
                data[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            data[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            data[k] = R[j]
            j += 1
            k += 1


def circular_shift(user_input):
    user_input = user_input.split('\n')
    words = [line.split(' ') for line in user_input]
    cs_lines = []

    for index, line in enumerate(words):
        for word in line:
            temp_list = copy.deepcopy(line)
            cs_lines.append(' '.join(temp_list))
            first_word = line.pop(0)
            line.append(first_word)

    return cs_lines

if __name__ == '__main__':
    user_input = "How Architecture Wins Technology Wars\nThe Art Of Systems Architecting"

    cs_lines = circular_shift(user_input)
    alphabetizer(cs_lines)
    for i in range(len(cs_lines)):
        print(cs_lines[i])
