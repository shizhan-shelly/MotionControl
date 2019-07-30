#By zhanshi

import xlwt
from xml.dom.minidom import parse
import xml.dom.minidom

work_book = xlwt.Workbook()
cutchart_sheet = work_book.add_sheet('Cut Chart')
attribute_sheet = work_book.add_sheet('Attribute')
configure_sheet = work_book.add_sheet('Configure')

# 使用minidom解析器打开 XML 文档
DOMTree = xml.dom.minidom.parse("XPR.xml")
collection = DOMTree.documentElement

# 在集合中获取属性majorRevision、englishMinorRevision、metricMinorRevision
majorRevision = collection.getAttribute("majorRevision")
englishMinorRevision = collection.getAttribute("englishMinorRevision")
metricMinorRevision = collection.getAttribute("metricMinorRevision")
print(majorRevision)
print(englishMinorRevision)
print(metricMinorRevision)

base_value = {"HtRecordID" : "",
              "EnglishUnits" : "",
              "MaterialType" : "",
              "ProcessCurrent" : "",
              "Gas" : "",
              "Thickness" : "",
              "Class" : "",
              "Underwater" : "",
              "WaterInjection" : "",
              "EdgeStart" : "",
              "ArgonAssist" : "",
              "Electrode" : "",
              "SwirlRing" : "",
              "Nozzle" : "",
              "Shield" : "",
              "NozzleRetainingCap" : "",
              "ShieldRetainingCap" : "",
              "WaterTube" : ""}

value = {"XprProcessID" : "",
         "PierceHeight" : "",
         "TransferHeight" : "",
         "CutHeight" : "",
         "ArcVoltage" : "",
         "Kerf" : "",
         "CutSpeed" : "",
         "Current" : "",
         "PierceDelay" : ""}

# 解析子节点
def ParseNodeValue(node, tag):
  node_value = node.getElementsByTagName("%s" % tag)[0]
  return node_value.childNodes[0].data

def ParseCurrent(class_str):
  return class_str.strip().partition("Amp")[0]

def ParseGas(class_str):
  return class_str.strip().split(" ")[1]

# 初始化
def InitCutChart():
  cutchart_sheet.write(0, 0, "HtRecordID")
  cutchart_sheet.write(0, 1, "MaterialType")
  cutchart_sheet.write(0, 2, "SpecialMaterial")
  cutchart_sheet.write(0, 3, "ProcessCurrent")
  cutchart_sheet.write(0, 4, "Gas")
  cutchart_sheet.write(0, 5, "Thickness")
  cutchart_sheet.write(0, 6, "Underwater")
  cutchart_sheet.write(0, 7, "WaterInjection")
  cutchart_sheet.write(0, 8, "EdgeStart")
  cutchart_sheet.write(0, 9, "ArgonAssist")
  cutchart_sheet.write(0, 10, "EnglishUnits")
  cutchart_sheet.write(0, 11, "Electrode")
  cutchart_sheet.write(0, 12, "SwirlRing")
  cutchart_sheet.write(0, 13, "Nozzle")
  cutchart_sheet.write(0, 14, "Shield")
  cutchart_sheet.write(0, 15, "NozzleRetainingCap")
  cutchart_sheet.write(0, 16, "ShieldRetainingCap")
  cutchart_sheet.write(0, 17, "WaterTube")
  cutchart_sheet.write(0, 18, "XprProcessID")
  cutchart_sheet.write(0, 19, "PierceHeight")
  cutchart_sheet.write(0, 20, "TransferHeight")
  cutchart_sheet.write(0, 21, "CutHeight")
  cutchart_sheet.write(0, 22, "ArcVoltage")
  cutchart_sheet.write(0, 23, "Kerf")
  cutchart_sheet.write(0, 24, "CutSpeed")
  cutchart_sheet.write(0, 25, "Current")
  cutchart_sheet.write(0, 26, "PierceDelay")

def Record(row, special_material):
  cutchart_sheet.write(row, 0, base_value["HtRecordID"])
  cutchart_sheet.write(row, 1, base_value["MaterialType"])
  cutchart_sheet.write(row, 2, "%s" % special_material)
  cutchart_sheet.write(row, 3, base_value["ProcessCurrent"])
  cutchart_sheet.write(row, 4, base_value["Gas"])
  cutchart_sheet.write(row, 5, base_value["Thickness"])
  cutchart_sheet.write(row, 6, base_value["Underwater"])
  cutchart_sheet.write(row, 7, base_value["WaterInjection"])
  cutchart_sheet.write(row, 8, base_value["EdgeStart"])
  cutchart_sheet.write(row, 9, base_value["ArgonAssist"])
  cutchart_sheet.write(row, 10, base_value["EnglishUnits"])
  cutchart_sheet.write(row, 11, base_value["Electrode"])
  cutchart_sheet.write(row, 12, base_value["SwirlRing"])
  cutchart_sheet.write(row, 13, base_value["Nozzle"])
  cutchart_sheet.write(row, 14, base_value["Shield"])
  cutchart_sheet.write(row, 15, base_value["NozzleRetainingCap"])
  cutchart_sheet.write(row, 16, base_value["ShieldRetainingCap"])
  cutchart_sheet.write(row, 17, base_value["WaterTube"])
  cutchart_sheet.write(row, 18, value["XprProcessID"])
  cutchart_sheet.write(row, 19, value["PierceHeight"])
  cutchart_sheet.write(row, 20, value["TransferHeight"])
  cutchart_sheet.write(row, 21, value["CutHeight"])
  cutchart_sheet.write(row, 22, value["ArcVoltage"])
  cutchart_sheet.write(row, 23, value["Kerf"])
  cutchart_sheet.write(row, 24, value["CutSpeed"])
  cutchart_sheet.write(row, 25, value["Current"])
  cutchart_sheet.write(row, 26, value["PierceDelay"])

# 解析Document
InitCutChart()
row = 1
records = collection.getElementsByTagName("records")
for record in records:
  base_value["HtRecordID"] = ParseNodeValue(record, "HtRecordID")
  base_value["MaterialType"] = ParseNodeValue(record, "MaterialType")
  base_value["Thickness"] = ParseNodeValue(record, "Thickness")
  base_value["Class"] = ParseNodeValue(record, "Class")
  base_value["Underwater"] = ParseNodeValue(record, "Underwater")
  base_value["WaterInjection"] = ParseNodeValue(record, "WaterInjection")
  base_value["EdgeStart"] = ParseNodeValue(record, "EdgeStart")
  base_value["ArgonAssist"] = ParseNodeValue(record, "ArgonAssist")
  base_value["EnglishUnits"] = ParseNodeValue(record, "EnglishUnits")
  base_value["Electrode"] = ParseNodeValue(record, "Electrode")
  base_value["SwirlRing"] = ParseNodeValue(record, "SwirlRing")
  base_value["Nozzle"] = ParseNodeValue(record, "Nozzle")
  base_value["Shield"] = ParseNodeValue(record, "Shield")
  base_value["NozzleRetainingCap"] = ParseNodeValue(record, "NozzleRetainingCap")
  base_value["ShieldRetainingCap"] = ParseNodeValue(record, "ShieldRetainingCap")
  base_value["WaterTube"] = "420368"
  base_value["ProcessCurrent"] = ParseCurrent(base_value.get("Class"))
  base_value["Gas"] = ParseGas(base_value.get("Class"))

  Cut = record.getElementsByTagName('Cut')[0]
  value["XprProcessID"] = ParseNodeValue(Cut, "XprProcessID")
  value["PierceHeight"] = ParseNodeValue(Cut, "PierceHeight")
  value["TransferHeight"] = ParseNodeValue(Cut, "TransferHeight")
  value["CutHeight"] = ParseNodeValue(Cut, "CutHeight")
  value["ArcVoltage"] = ParseNodeValue(Cut, "ArcVoltage")
  value["Kerf"] = ParseNodeValue(Cut, "Kerf")
  value["CutSpeed"] = ParseNodeValue(Cut, "CutSpeed")
  value["Current"] = ParseNodeValue(Cut, "Current")
  value["PierceDelay"] = ParseNodeValue(Cut, "PierceDelay")
  Record(row, "Cut")
  row = row + 1

  TrueHole = record.getElementsByTagName('TrueHole')[0]
  value["XprProcessID"] = ParseNodeValue(TrueHole, "XprProcessID")
  value["PierceHeight"] = ParseNodeValue(TrueHole, "PierceHeight")
  value["TransferHeight"] = ParseNodeValue(TrueHole, "TransferHeight")
  value["CutHeight"] = ParseNodeValue(TrueHole, "CutHeight")
  value["ArcVoltage"] = ParseNodeValue(TrueHole, "ArcVoltage")
  value["Kerf"] = ParseNodeValue(TrueHole, "Kerf")
  value["CutSpeed"] = ParseNodeValue(TrueHole, "CutSpeed")
  value["Current"] = ParseNodeValue(TrueHole, "Current")
  value["PierceDelay"] = ParseNodeValue(TrueHole, "PierceDelay")
  Record(row, "TrueHole")
  row = row + 1

  ArMarking = record.getElementsByTagName('ArMarking')[0]
  value["XprProcessID"] = ParseNodeValue(ArMarking, "XprProcessID")
  value["PierceHeight"] = ParseNodeValue(ArMarking, "PierceHeight")
  value["TransferHeight"] = ParseNodeValue(ArMarking, "TransferHeight")
  value["CutHeight"] = ParseNodeValue(ArMarking, "CutHeight")
  value["ArcVoltage"] = ParseNodeValue(ArMarking, "ArcVoltage")
  value["Kerf"] = ParseNodeValue(ArMarking, "Kerf")
  value["CutSpeed"] = ParseNodeValue(ArMarking, "CutSpeed")
  value["Current"] = ParseNodeValue(ArMarking, "Current")
  value["PierceDelay"] = ParseNodeValue(ArMarking, "PierceDelay")
  Record(row, "ArMarking")
  row = row + 1

  N2Marking = record.getElementsByTagName('N2Marking')[0]
  value["XprProcessID"] = ParseNodeValue(N2Marking, "XprProcessID")
  value["PierceHeight"] = ParseNodeValue(N2Marking, "PierceHeight")
  value["TransferHeight"] = ParseNodeValue(N2Marking, "TransferHeight")
  value["CutHeight"] = ParseNodeValue(N2Marking, "CutHeight")
  value["ArcVoltage"] = ParseNodeValue(N2Marking, "ArcVoltage")
  value["Kerf"] = ParseNodeValue(N2Marking, "Kerf")
  value["CutSpeed"] = ParseNodeValue(N2Marking, "CutSpeed")
  value["Current"] = ParseNodeValue(N2Marking, "Current")
  value["PierceDelay"] = ParseNodeValue(N2Marking, "PierceDelay")
  Record(row, "N2Marking")
  row = row + 1

work_book.save('Hypertherm-XPR.xls')
