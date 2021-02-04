import copy


class CircularShift:
    input = ""
    output = ""

    def insert(self, user_input):
        self.input = user_input

    def gen_circular_shift(self):
        user_input = self.input.split('\n')
        words = [line.split(' ') for line in user_input]
        cs_lines = []

        for index, line in enumerate(words):
            for word in line:
                temp_list = copy.deepcopy(line)
                cs_lines.append(' '.join(temp_list))
                first_word = line.pop(0)
                line.append(first_word)

        self.output = cs_lines

    def get_lines(self):
        return self.output

class Alpha:
    cs_lines = ""
    alpha_lines = ""

    def get_cs_lines(self, lines):
        self.cs_lines = lines

    def alphabetize(self):
        self.alpha_lines = self.alphabetizer(self.cs_lines)

    # Accepts a list of strings
    # Doesn't return anything simply modifies the array passed
    def alphabetizer(self, data):
        if len(data) > 1:
            mid = len(data) // 2
            L = data[:mid]
            R = data[mid:]

            self.alphabetizer(L)
            self.alphabetizer(R)

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

        return data

    def get_alpha_lines(self):
        return self.alpha_lines
