#By zhanshi

import sys, xlrd
from xml.dom.minidom import Document

xls_file_name = sys.argv[1]
work_book = xlrd.open_workbook(xls_file_name)
config_sheet = work_book.sheet_by_name('Configuration')
attribute_sheet = work_book.sheet_by_name('Attribute')
cut_chart_sheet = work_book.sheet_by_name('Cut Chart')

config_define = {"Hypertherm" : ("PlasmaPower",),
                 "Kjellberg" : ("PlasmaPower", "GasBox", "Torch"),
                 "Liuhe" : ("PlasmaPower",),
                 "Koike" : ("PlasmaPower",)}

config_start_row = int(config_sheet.cell_value(0, 0))
vendor_name = "%s" % config_sheet.cell_value(config_start_row, 0)
cut_chart_version = "%s" % config_sheet.cell_value(config_start_row, 4)

attr_title = {}
attr_start_row = int(attribute_sheet.cell_value(0, 0))
for col in range(0, attribute_sheet.ncols):
  attr_title[attribute_sheet.cell_value(attr_start_row - 1, col)] = col

data_start_row = int(attribute_sheet.cell_value(0, 1))

field_name = []
column = {}
scale = {}
offset = {}
data_type = {}
for row in range(attr_start_row, attribute_sheet.nrows):
  field_name.append(attribute_sheet.cell_value(row, attr_title['Name']))
  column[attribute_sheet.cell_value(row, attr_title['Name'])] = int(attribute_sheet.cell_value(row, attr_title['Column'])) -1
  scale[attribute_sheet.cell_value(row, attr_title['Name'])] = attribute_sheet.cell_value(row, attr_title['Scale'])
  offset[attribute_sheet.cell_value(row, attr_title['Name'])] = attribute_sheet.cell_value(row, attr_title['Offset'])
  data_type[attribute_sheet.cell_value(row, attr_title['Name'])] = attribute_sheet.cell_value(row, attr_title['DataType'])

# create document
doc = Document()
# create root element
CutChart = doc.createElement('CutChart')
CutChart.setAttribute('Vendor', vendor_name)
CutChart.setAttribute('Version', cut_chart_version)
doc.appendChild(CutChart)

# create system config information
for row in range(config_start_row, config_sheet.nrows):
  CutChartConfig = doc.createElement('CutChartConfig')
  CutChart.appendChild(CutChartConfig)
  for col in range(0, len(config_define[vendor_name])):
    CutChartConfig.setAttribute(config_define[vendor_name][col], "%s" % config_sheet.cell_value(row, col + 1))

# create current select element and attr element
CurrentSelect = doc.createElement('CurrentSelectCutChartRecord')
CutChartAttr = doc.createElement('CutChartAttr')
CutChart.appendChild(CurrentSelect)
CutChart.appendChild(CutChartAttr)
for row in range (attr_start_row, attribute_sheet.nrows):
  field_attr = doc.createElement(attribute_sheet.cell_value(row, attr_title['Name']))
  field_attr.setAttribute('IsKeyword', "%d" % attribute_sheet.cell_value(row, attr_title['Keyword']))
  field_attr.setAttribute('DataType', "%s" % attribute_sheet.cell_value(row, attr_title['DataType']))
  field_attr.setAttribute('NameText', "%s" % attribute_sheet.cell_value(row, attr_title['NameText']))
  field_attr.setAttribute('UnitText', "%s" % attribute_sheet.cell_value(row, attr_title['UnitText']))
  field_attr.setAttribute('Min', "%s" % attribute_sheet.cell_value(row, attr_title['Min']))
  field_attr.setAttribute('Max', "%s" % attribute_sheet.cell_value(row, attr_title['Max']))
  field_attr.setAttribute('Default', "%s" % attribute_sheet.cell_value(row, attr_title['Default']))
  field_attr.setAttribute('DisplayFormat', "%s" % attribute_sheet.cell_value(row, attr_title['DisplayFormat']))
  field_attr.setAttribute('WR', "%d" % attribute_sheet.cell_value(row, attr_title['WR']))
  field_attr.setAttribute('AliasIndex', "%d" % attribute_sheet.cell_value(row, attr_title['AliasIndex']))
  field_attr.setAttribute('Picture', "%d" % attribute_sheet.cell_value(row, attr_title['Picture']))
  field_attr.setAttribute('Group', "%d" % attribute_sheet.cell_value(row, attr_title['Group']))
  CutChartAttr.appendChild(field_attr)
  if field_attr.getAttribute("IsKeyword") == "1":
    CurrentSelect.setAttribute(field_attr.tagName, "")

# create data element
CutChartData = doc.createElement('CutChartData')
CutChart.appendChild(CutChartData)
for row in range (data_start_row - 1, cut_chart_sheet.nrows):
  record = doc.createElement("Record")
  CutChartData.appendChild(record)
  for name in field_name:
    cell_value = cut_chart_sheet.cell_value(row, column[name])
    if data_type[name] == "TEXT":
      record.setAttribute(name, "%s" % cell_value)
    elif data_type[name] == "FLOAT":
      record.setAttribute(name, "%.3f" % (float(cell_value) * scale[name] + offset[name]))
    elif data_type[name] == "INT":
      record.setAttribute(name, "%d" % (int(cell_value) * scale[name] + offset[name]))
    elif data_type[name] == "BOOL":
      record.setAttribute(name, "%s" % cell_value)


xml_file = open(sys.argv[2],'w')
doc.writexml(xml_file, indent = '',newl = '\n', addindent = '  ',encoding='utf-8')
xml_file.close()
