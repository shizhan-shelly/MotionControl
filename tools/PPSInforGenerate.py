#By zhanshi

import codecs, sys, xlrd
from xml.dom.minidom import Document

xls_file_name = sys.argv[1]
sheet_name = sys.argv[2]
work_book = xlrd.open_workbook(xls_file_name)
work_sheet = work_book.sheet_by_name(sheet_name)


col_name = []
data = {}
for col in range(0, work_sheet.ncols):
  col_name.append(work_sheet.cell_value(0, col))
  col_value = []
  for row in range(1, work_sheet.nrows):
    col_value.append(work_sheet.cell_value(row, col))
  data[col_name[col]] = col_value

# create document
doc = Document()
# create root element
Chart = doc.createElement(sheet_name)
doc.appendChild(Chart)

# create record element
for row in range (1, work_sheet.nrows):
  record = doc.createElement("record")
  Chart.appendChild(record)
  for name in col_name:
    record.setAttribute(name, "%s" % data[name][row - 1])


xml_file = codecs.open(sys.argv[3], 'w','utf-8')
doc.writexml(xml_file, indent = '', newl = '\r\n', addindent = '  ',encoding='utf-8')
xml_file.close()
