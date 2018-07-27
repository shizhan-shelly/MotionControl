#By zhanshi

import sys, xlrd
from xml.dom.minidom import Document

xls_file_name = "Hypertherm-HPR.xlsx"
work_book = xlrd.open_workbook(xls_file_name)
config_sheet = work_book.sheet_by_name('Configuration')
attribute_sheet = work_book.sheet_by_name('Attribute')
cut_chart_sheet = work_book.sheet_by_name('Cut Chart')

vendor_name = "Hypertherm"
cut_chart_version = "1.0"


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

# 创建DOM文档对象
doc = Document()
# 创建根节点
CutChart = doc.createElement('CutChart')
CutChart.setAttribute('Vendor', vendor_name)
CutChart.setAttribute('Version', cut_chart_version)
doc.appendChild(CutChart)

#创建属性子节点
CutChartAttr = doc.createElement('CutChartAttr')
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

#创建数据子节点
CutChartData = doc.createElement('CutChartData')
CutChart.appendChild(CutChartData)
for row in range (data_start_row - 1, cut_chart_sheet.nrows):
  record = doc.createElement("Record")
  CutChartData.appendChild(record)
  for xx in field_name:
    if data_type[xx] == "TEXT":
      record.setAttribute(xx, "%s" % cut_chart_sheet.cell_value(row, column[xx]))
    elif data_type[xx] == "FLOAT":
      record.setAttribute(xx, "%.2f" % (cut_chart_sheet.cell_value(row, column[xx]) * scale[xx] + offset[xx]))
    elif data_type[xx] == "INT":
      record.setAttribute(xx, "%d" % (cut_chart_sheet.cell_value(row, column[xx]) * scale[xx] + offset[xx]))


xml_file = open('HPR.xml','w')
doc.writexml(xml_file, indent = '',newl = '\n', addindent = '  ',encoding='utf-8')
xml_file.close()
