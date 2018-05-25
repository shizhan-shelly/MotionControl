#By zhanshi

import sys, sqlite3, xlrd

database_file = sys.argv[1]
connect = sqlite3.connect(database_file)
cursor = connect.cursor()

alias_excel_file = sys.argv[2]
work_book = xlrd.open_workbook(alias_excel_file)
work_sheet_list = work_book.sheet_names()
for work_sheet_name in work_sheet_list:
  # If not exist, create alias table
  work_sheet = work_book.sheet_by_name(work_sheet_name)
  alias_table_name = work_sheet.cell_value(0, 1)
  cursor.execute('''
      CREATE TABLE IF NOT EXISTS %s (
          ALIAS_NAME    TEXT  PRIMARY KEY NOT NULL,
          ORIGINAL_NAME TEXT              NOT NULL

      )
      ''' % (alias_table_name))

  # insert data of alias table
  for row in range(1, work_sheet.nrows):
    alias = work_sheet.cell_value(row, 0)
    value = work_sheet.cell_value(row, 1)
    cursor.execute("INSERT INTO %s VALUES (?, ?)" % (alias_table_name),
                   (alias, value))

connect.commit()
connect.close()
