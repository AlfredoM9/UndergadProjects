# Author: Alfredo Mejia
# Descrp: This file consists of functions that is going to help with the database management

# Imports
from sqlite3 import Error
import sqlite3
import sys


# Descr: Creates a db file and establishes the connection to it. The connection is then returned
def create_connection(db_name):
    # Try to establish a connection to the db. Otherwise exit the program and display error message
    try:
        conn = sqlite3.connect(db_name)
    except Error as e:
        sys.exit(e)

    # Return connection
    return conn


# Descr: Executes a create table query to a specific db file
def create_table(db_connection, create_table_query):
    # Try to execute the query to create a table.
    try:
        connection_cursor = db_connection.cursor()
        connection_cursor.execute(create_table_query)

    # Otherwise, display error message and quit program
    except Error as e:
        sys.exit(e)


# Descr: Inserts a list as entries in a table specified in a specific db file
def create_keys_entry(db_connection, tb_data, table_name):
    # Get rid of duplicates that are already in the db
    get_rid_duplicates_keys(db_connection, tb_data, table_name)

    if len(tb_data) < 3:
        return

    # Create a query
    sql = "INSERT INTO " + str(table_name) + "(keyword, shift, urlkey) VALUES(?, ?, ?)"

    # Execute query
    cur = db_connection.cursor()
    cur.execute(sql, tb_data)
    db_connection.commit()


# Descr: Inserts a list as entries in a table specified in a specific db file
def get_rid_duplicates_url(db_connection, tb_data, tb_name):
    # Get the db data
    results = get_db_data(db_connection, tb_name)

    id = 0

    # If the db data is in the list, then remove it because it doesn't need to be added
    for id, url, tier in results:
        if url in tb_data:
            tb_data.remove(url)
            return id

    return 1 if id == 0 else id + 1


def create_urls_entry(db_connection, tb_data, table_name):
    # Get rid of duplicates that are already in the db
    urlkey = get_rid_duplicates_url(db_connection, tb_data, table_name)

    # Create a query
    sql = "INSERT INTO " + str(table_name) + "(url, tier) VALUES(?, ?)"

    if len(tb_data) != 2:
        return urlkey

    cur = db_connection.cursor()
    cur.execute(sql, tb_data)
    db_connection.commit()

    return urlkey

# Descr: Modifies the list passed (tb_data) and removes any data already in the table. This ensures the insertion of
#        of new data isn't a duplicate
def get_rid_duplicates_keys(db_connection, tb_data, tb_name):
    # Get the db data
    results = get_db_data(db_connection, tb_name)

    # If the db data is in the list, then remove it because it doesn't need to be added
    for id, keyword, shift, urlkey in results:
        if keyword in tb_data and shift in tb_data and urlkey in tb_data:
            tb_data.remove(keyword)
            tb_data.remove(shift)
            tb_data.remove(urlkey)


# Descr: Returns all the data from a specific table in a db file
def get_db_data(db_conn, tb_name):
    # Get all the data given a db from the table
    cur = db_conn.cursor()
    query = "SELECT * FROM " + str(tb_name)
    results = cur.execute(query).fetchall()

    # Return results
    return results
