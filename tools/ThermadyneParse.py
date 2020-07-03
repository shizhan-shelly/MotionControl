#By zhanshi

import sys, xlwt, xlrd
from xml.dom.minidom import parse
import xml.dom.minidom

work_book = xlwt.Workbook()
cutchart_sheet = work_book.add_sheet('Cut Chart')
attribute_sheet = work_book.add_sheet('Attribute')
configure_sheet = work_book.add_sheet('Configure')


# 解析xml节点值
def ParseNodeValue(node, tag):
  node_value = node.getElementsByTagName("%s" % tag)[0]
  return node_value.childNodes[0].data


def ParseXMD(xmd_file):
  ATTR_DOMTree = xml.dom.minidom.parse(xmd_file)
  collection = ATTR_DOMTree.documentElement
  attr_Revision = collection.getAttribute("FileRev")
  config_items = ["Caption", "Comment", "Typ", "Min", "Max", "Default", "TextNo", "P_Field",
                  "Format", "Factor", " Level", " ImportFactor", "ImportOffset", "ImportColumn",
                  "ImportColumn2", "TableNo", "ReferenceRow", "PictureIndex", "ViewIndex"]

  config_values = []
  for row in range(191):
    record = collection.getElementsByTagName("Col%s" % row)[0]
    config_value = {}
    for config_item in config_items:
      config_value[config_item] = record.getAttribute(config_item)
      attribute_sheet.write(row, config_items.index(config_item), config_value[config_item])
    config_values.append(config_value)
  return config_values

def ParseXML(xml_file, config_values):
  CUT_CHART_DOMTree = xml.dom.minidom.parse(xml_file)
  collection = CUT_CHART_DOMTree.documentElement
  version = collection.getAttribute("FileRev")
  process = collection.getAttribute("Technology")
  records = collection.getElementsByTagName("Tabelle1")

  for col in range(len(config_values)):
    cutchart_sheet.write(0, col, config_values[col]["Caption"])
    for row in range(1, records.length):
      if config_values[col]["TableNo"] == '0':
        cutchart_sheet.write(row, col, records[row].parentNode.attributes[config_values[col]["Caption"]].nodeValue)


# 解析Document
config_values = ParseXMD("Plasma_Thermadyne.xmd")
ParseXML("Plasma_Thermadyne_Example.xml", config_values)
work_book.save('Thermadyne_Example.xls')
