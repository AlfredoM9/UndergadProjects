import json
import sys
import os
from circularshift import CircularShift, Alpha
from sql_functions import *


# Generate dummy json object
def get_json(param):
    json_data = [
    {
        "input": "https://www.wikipedia.org$the lion king\nhttps://www.utdallas.edu$UTD",
        "mode": 0
    },
    {
        "input": "https://www.nytimes.com/$The New York Times",
        "mode": 1
    },
    {
        "input": "",
        "mode": 2
    }]

    return json.dumps(json_data[param])


# Parse json object
def parse_json(json_object):
    # Convert json to python
    data = json.loads(json_object)

    # If multiple urls and keywords are given then split on newline characters
    input = data['input'].splitlines()

    # For each entry (url$keyword) split on the $ to form url and keywords
    input = [line.split("$") for line in input if line]

    # Just to make sure there are no empty or wrong formatted data
    input = [user_input for user_input in input if len(user_input) == 2]

    # Get the mode
    mode = data["mode"]

    # Create classes
    circularShift = CircularShift()
    alpha = Alpha()

    # For each entry (url & keywords)
    for index, user_input in enumerate(input):
        # CS on the keywords
        circularShift.insert(user_input[1])
        circularShift.gen_circular_shift()
        cs_lines = circularShift.get_lines()

        # Alphabetize on cs lines
        alpha.get_cs_lines(cs_lines)
        alpha.alphabetize()

        # Update the keywords with a list of CS lines
        input[index][1] = alpha.get_alpha_lines()

    # Return input and mode
    # Input is now [[url, [list of cs lines]], [url2, [list of cs lines]]...]
    return input, mode


def execute_db(input, mode):
    # If the mode is zero or "build mode" then delete the database to start from fresh
    if mode == 0 and os.path.exists("kwic.db"):
        os.remove("kwic.db")

    # Create
    db_name = "kwic.db"
    db_conn = create_connection(db_name)

    keys_db_name = "kwic_keys.db"
    keys_tb_name = keys_db_name[:-3]
    keys_db_conn = create_connection(keys_db_name)

    urls_db_name = "kwic_urls.db"
    urls_tb_name = urls_db_name[:-3]
    urls_db_conn = create_connection(urls_db_name)

    if keys_db_conn is None or urls_db_conn is None:
        print("Error! Cannot create the database connection for urls.")
        sys.exit(-1)

    keys_table_query = "CREATE TABLE IF NOT EXISTS " + str(keys_tb_name) + "(id integer PRIMARY KEY, keyword text NOT " \
                                                                            "NULL, shift text NOT NULL, " \
                                                                            "urlkey integer NOT NULL) "
    urls_table_query = "CREATE TABLE IF NOT EXISTS " + str(urls_tb_name) + "(id integer PRIMARY KEY, url text NOT " \
                                                                            "NULL, tier integer NOT NULL) "

    create_table(keys_db_conn, keys_table_query)
    create_table(urls_db_conn, urls_table_query)

    NOISE_WORDS = ['the', 'a', 'an', 'and', 'of']

    for entry in input:
        url_key = create_urls_entry(db_connection=urls_db_conn, tb_data=[entry[0], 0], table_name=urls_tb_name)
        for cs_line in entry[1]:
            words = cs_line.lower().split()
            if words[0] in NOISE_WORDS:
                continue
            else:
                data_row = [words[0], cs_line.lower(), url_key]
                create_keys_entry(keys_db_conn, data_row, keys_tb_name)

    urls_data = get_db_data(urls_db_conn, urls_tb_name)
    keys_data = get_db_data(keys_db_conn, keys_tb_name)

    keys_db_conn.close()
    urls_db_conn.close()

    return urls_data, keys_data


def kwic(json_object):
    # Parse the json object
    input, mode = parse_json(json_object)

    # Execute the database commands and return the tables
    return execute_db(input, mode)


if __name__ == '__main__':
    # Generates dummy json object
    json_input = get_json(0)

    # Calls the kwic system based on the json object
    # Always returns the tables
    urls_table, keys_table = kwic(json_input)

    # Print tables
    print(urls_table)
    print(keys_table)