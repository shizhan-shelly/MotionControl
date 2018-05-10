#By zhanshi

import sys, sqlite3, xlrd

database_name = "test.db"
connect = sqlite3.connect(database_name)
cursor = connect.cursor()

cursor.execute('''
    CREATE TABLE Vendor(
        ID    INT  PRIMARY KEY NOT NULL,
        NAME  TEXT             NOT NULL
    )
    ''')

cursor.execute('''
    CREATE TABLE SystemConfig(
        CUTTING_CHART_ID   INT     NOT NULL,  --对应一张切割表的ID，不唯一
        VENDOR_ID          INT     NOT NULL,  --等离子电源厂商ID
        PLASMA_POWER_MODEL TEXT    NOT NULL,  --等离子电源型号
        GAS_BOX_MODEL      TEXT,              --气体箱型号
        TORCH_MODEL        TEXT,              --割枪型号
        VERSION            TEXT    NOT NULL,  --版本号
        SELECTED_RECORD    INT,               --被选择记录

        FOREIGN KEY (VENDOR_ID) REFERENCES Vendor(ID)
    )
    ''')

cursor.execute('''
    CREATE TABLE PlasmaPower(
        ID        INTEGER  PRIMARY KEY AUTOINCREMENT,
        MODEL     TEXT             NOT NULL,
        VENDOR_ID INT              NOT NULL,       -- foreign key

        FOREIGN KEY (VENDOR_ID) REFERENCES Vendor(ID)
    )
    ''')

cursor.execute('''
    CREATE TABLE KjellbergCuttingData(
        ID                    INT    NOT NULL,  --切割数据的ID号，可重复
        RECORD_NUMBER         INT    NOT NULL,  --没有具体的数据含义，只是excel中切割数据编号
        MATERIAL              TEXT,             --切割材料
        THICKNESS             REAL,             --钢板厚度，单位为mm
        CUTTING_CURRENT       REAL,             --切Attribute割电流，单位为A
        TECHNOLOGY            TEXT,             --切割技术
        CATHODE               TEXT,             --电极
        GAS_GUIDE             TEXT,             --涡流环
        NOZZLE                TEXT,             --喷嘴
        NOZZLE_CAP            TEXT,             --喷嘴帽
        SWIRL_GAS_CAP         TEXT,             --涡流器帽
        PROTECTION_CAP        TEXT,             --保护帽
        COOLING_TUBE          TEXT,             --冷却水管
        SWIRL_GAS_NOZZLE      TEXT,             --涡流器喷嘴
        SPECIAL_PART          TEXT,             --特殊零件
        PLASMA_GAS1           TEXT,             --等离子气体1
        PLASMA_GAS2           TEXT,             --等离子气体2
        PLASMA_GAS3           TEXT,             --等离子气体3
        SWIRL_GAS1            TEXT,             --涡流器气体1
        SWIRL_GAS2            TEXT,             --涡流器气体2
        IGNITION_GAS          TEXT,             --点火气体
        PLASMA_GAS1_KPA       REAL,             --等离子气体1压强，单位为kpa
        PLASMA_GAS2_KPA       REAL,             --等离子气体2压强，单位为kpa
        PLASMA_GAS3_KPA       REAL,             --等离子气体3压强，单位为kpa
        SWIRL_GAS1_KPA        REAL,             --涡流器气体1压强，单位为kpa
        SWIRL_GAS2_KPA        REAL,             --涡流器气体2压强，单位为kpa
        CUTTING_PRESSURE      REAL,             --切割压强，单位为kpa
        IGNITION_HEIGHT       REAL,             --引弧高度，单位为mm
        CUTTING_HEIGHT        REAL,             --切割高度，单位为mm
        PIERCE_HEIGHT         REAL,             --穿孔高度，单位为mm
        PIERCE_TIME           REAL,             --穿孔时间，单位为s
        CUTTING_VOLTAGE       REAL,             --设置弧压，单位为V
        PLASMA_OFF_TIME       REAL,             --等离子提前关弧时间，单位为s
        ADDITIONAL_HEIGHT     REAL,             --附加高度，单位为mm
        UP_SLOPE              REAL,             --上升沿时间，单位为s
        DOWN_SLOPE            REAL,             --下降沿时间，单位为s
        CUTTING_SPEED_SPEED   REAL,             --切割速度速度，mm/min
        CUTTING_SPEED_MAX     REAL,             --最大切割速度，mm/min
        CUTTING_SPEED_HOLE    REAL,             --切割速度（hole），mm/min
        CUTTING_SPEED_QUALITY REAL,             --切割速度（quality），mm/min
        KERF_QUALITY          REAL,             --割缝（hole），单位为mm
        KERF_HOLE             REAL,             --割缝（quality），单位为mm
        GAS_CODE_DECIMAL      INT,              --气体代码
        SPECIAL_CODE_DECIMAL  INT,              --特殊代码
        MARKING_RECORD        INT,              --打标记录
        TECHNOLOGY_RANGE      INT               --切割技术等级

    )
    ''')

cursor.execute('''
    CREATE TABLE KjellbergAttribute(
        NAME                 TEXT    NOT NULL,
        KEYWORD_FLAG         INT     NOT NULL,
        DATA_TYPE            TEXT    NOT NULL,
        NAME_NUMBER          INT,
        UNIT_NUMBER          INT,
        MIN                  NUMERIC,
        MAX                  NUMERIC,
        DEFAULT_VALUE        NUMERIC,
        DISPLAY_FORMAT       TEXT,
        WR                   INT,
        ALIAS_INDEX          INT,
        PICTURE              BLOB,
        DISPLAY_GROUP        INT,
        SCALE                REAL,
        OFFSET               REAL

    )
    ''')

def VendorInitial():
  "Init Vendor table."
  query = "INSERT INTO Vendor VALUES (?, ?)"
  vendor = [(1, 'Kjellberg'),
            (2, 'Hypertherm'),
            (3, 'LiuHe'),
            ]
  cursor.executemany(query, vendor)

def GetVendorID(vendor_name):
  cursor.execute("SELECT ID FROM Vendor WHERE NAME=:value",
                 {"value" : vendor_name})

  return cursor.fetchone()[0]

def LastCuttingChartID():
  cursor.execute("SELECT CUTTING_CHART_ID FROM SystemConfig ORDER BY CUTTING_CHART_ID")
  list = cursor.fetchone()
  if list == None:
    return 0
  else :
    return max(list)

def AppendPlasmaPowerInfor(plasma_power_model, vendor_id):
  cursor.execute("SELECT ID FROM PlasmaPower \
                  WHERE MODEL=:model \
                  AND VENDOR_ID=:vendor_id",
                 {"model" : plasma_power_model,
                  "vendor_id" : vendor_id})
  if cursor.fetchone() == None:
    query = "INSERT INTO PlasmaPower (MODEL, VENDOR_ID) VALUES (?, ?)"
    cursor.execute(query, (plasma_power_model, vendor_id))

def AppendSystemConfigInfor(cutting_chart_id, vendor_id, plasma_power_model, gas_box_model, torch_model, version):
  cursor.execute("SELECT CUTTING_CHART_ID FROM SystemConfig \
                  WHERE VENDOR_ID=:vendor_id \
                  AND PLASMA_POWER_MODEL=:plasma_power_model \
                  AND GAS_BOX_MODEL=:gas_box_model \
                  AND TORCH_MODEL=:torch_model \
                  AND VERSION=:version",
                 {"vendor_id" : vendor_id,
                  "plasma_power_model" : plasma_power_model,
                  "gas_box_model" : gas_box_model,
                  "torch_model" : torch_model,
                  "version" : version})
  if cursor.fetchone() == None:
    cursor.execute("INSERT INTO SystemConfig VALUES (?, ?, ?, ?, ?, ?, ?)",
                   (cutting_chart_id, vendor_id, plasma_power_model, gas_box_model, torch_model, version, 0))

xls_file_name = sys.argv[1]
work_book = xlrd.open_workbook(xls_file_name)
config_sheet = work_book.sheet_by_name('Configuration')
attribute_sheet = work_book.sheet_by_name('Attribute')
cut_chart_sheet = work_book.sheet_by_name('Cut Chart')

def SystemConfig(cutting_chart_id):
  "Insert system config information into SystemConfig table."
  titles = {}
  title_row = int(config_sheet.cell_value(0, 0))
  for col in range(0, config_sheet.ncols):
    titles[config_sheet.cell_value(title_row - 1, col)] = col

  for row in range(title_row, config_sheet.nrows):
    vendor_name = config_sheet.cell_value(row, titles['Manufacturer'])
    plasma_power_model = config_sheet.cell_value(row, titles['Plasma Model'])
    gas_box_model = config_sheet.cell_value(row, titles['Gas Model'])
    torch_model = config_sheet.cell_value(row, titles['Torch Type'])
    version = config_sheet.cell_value(row, titles['Version'])

    vendor_id = GetVendorID(vendor_name)
    AppendPlasmaPowerInfor(plasma_power_model, vendor_id)
    AppendSystemConfigInfor(cutting_chart_id, vendor_id, plasma_power_model, gas_box_model, torch_model, version)


def Attribute():
  "Insert attribute information into Attribute table."
  titles = {}
  title_row = int(attribute_sheet.cell_value(0, 0))
  for col in range(0, attribute_sheet.ncols):
    titles[attribute_sheet.cell_value(title_row - 1, col)] = col

  for row in range(title_row, attribute_sheet.nrows):
    cursor.execute("INSERT INTO KjellbergAttribute VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
                   (attribute_sheet.cell_value(row, titles['Name']),
                    attribute_sheet.cell_value(row, titles['Keyword']),
                    attribute_sheet.cell_value(row, titles['Data Type']),
                    attribute_sheet.cell_value(row, titles['Name Number']),
                    attribute_sheet.cell_value(row, titles['Unit Number']),
                    attribute_sheet.cell_value(row, titles['Min']),
                    attribute_sheet.cell_value(row, titles['Max']),
                    attribute_sheet.cell_value(row, titles['Default']),
                    attribute_sheet.cell_value(row, titles['Display Format']),
                    attribute_sheet.cell_value(row, titles['WR']),
                    attribute_sheet.cell_value(row, titles['Alias Table']),
                    attribute_sheet.cell_value(row, titles['Picture']),
                    attribute_sheet.cell_value(row, titles['Group']),
                    attribute_sheet.cell_value(row, titles['Scale']),
                    attribute_sheet.cell_value(row, titles['Offset'])))

def KjellbergCuttingChart(cutting_chart_id):
  "Insert cutting data into CuttingData table. This Cutting chart id will be defined with cutting_chart_id"
  titles = {}
  title_row = int(attribute_sheet.cell_value(0, 0))
  for col in range(0, attribute_sheet.ncols):
    titles[attribute_sheet.cell_value(title_row - 1, col)] = col

  collumn_dis = {}
  scale_dis = {}
  offset_dis = {}
  for row in range(title_row, attribute_sheet.nrows):
    collumn_dis[attribute_sheet.cell_value(row, titles['Name'])] = int(attribute_sheet.cell_value(row, titles['Column'])) -1
    scale_dis[attribute_sheet.cell_value(row, titles['Name'])] = attribute_sheet.cell_value(row, titles['Scale'])
    offset_dis[attribute_sheet.cell_value(row, titles['Name'])] = attribute_sheet.cell_value(row, titles['Offset'])

  start_row = int(attribute_sheet.cell_value(0, 1))
  for row in range(start_row - 1, cut_chart_sheet.nrows):
    material = cut_chart_sheet.cell_value(row, collumn_dis['material'])
    thickness = cut_chart_sheet.cell_value(row, collumn_dis['thickness']) * scale_dis['thickness'] + offset_dis['thickness']
    current = cut_chart_sheet.cell_value(row, collumn_dis['current']) * scale_dis['thickness'] + offset_dis['thickness']
    technology = cut_chart_sheet.cell_value(row, collumn_dis['technology'])
    ignition_height = cut_chart_sheet.cell_value(row, collumn_dis['ignition height']) * scale_dis['ignition height'] + offset_dis['ignition height']
    cutting_height = cut_chart_sheet.cell_value(row, collumn_dis['cutting height']) * scale_dis['cutting height'] + offset_dis['cutting height']
    pierce_height = cut_chart_sheet.cell_value(row, collumn_dis['pierce height']) * scale_dis['pierce height'] + offset_dis['pierce height']
    pierce_time = cut_chart_sheet.cell_value(row, collumn_dis['pierce time']) * scale_dis['pierce time'] + offset_dis['pierce time']
    cutting_voltage = cut_chart_sheet.cell_value(row, collumn_dis['cutting voltage']) * scale_dis['cutting voltage'] + offset_dis['cutting voltage']
    plasma_off_time = cut_chart_sheet.cell_value(row, collumn_dis['plasma off time']) * scale_dis['plasma off time'] + offset_dis['plasma off time']
    cooling_tube = cut_chart_sheet.cell_value(row, collumn_dis['cooling tube'])
    cathode = cut_chart_sheet.cell_value(row, collumn_dis['cathode'])
    gas_guide = cut_chart_sheet.cell_value(row, collumn_dis['gas guide'])
    nozzle = cut_chart_sheet.cell_value(row, collumn_dis['nozzle'])
    nozzle_cap = cut_chart_sheet.cell_value(row, collumn_dis['nozzle cap'])
    swirl_gas_cap = cut_chart_sheet.cell_value(row, collumn_dis['swirl gas cap'])
    protection_cap = cut_chart_sheet.cell_value(row, collumn_dis['protection cap'])
    swirl_gas_nozzle = cut_chart_sheet.cell_value(row, collumn_dis['swirl gas nozzle'])
    special_part = ''
    plasma_gas_1 = cut_chart_sheet.cell_value(row, collumn_dis['plasma gas 1'])
    plasma_gas_2 = cut_chart_sheet.cell_value(row, collumn_dis['plasma gas 2'])
    plasma_gas_3 = cut_chart_sheet.cell_value(row, collumn_dis['plasma gas 3'])
    swirl_gas_1 = cut_chart_sheet.cell_value(row, collumn_dis['swirl gas 1'])
    swirl_gas_2 = cut_chart_sheet.cell_value(row, collumn_dis['swirl gas 2'])
    ignition_gas = cut_chart_sheet.cell_value(row, collumn_dis['ignition gas'])
    gas_code = cut_chart_sheet.cell_value(row, collumn_dis['gas code'])
    special_code = cut_chart_sheet.cell_value(row, collumn_dis['special code'])
    plasma_gas_1_pressure = cut_chart_sheet.cell_value(row, collumn_dis['plasma gas 1 pressure']) * scale_dis['plasma gas 1 pressure'] + offset_dis['plasma gas 1 pressure']
    plasma_gas_2_pressure = cut_chart_sheet.cell_value(row, collumn_dis['plasma gas 2 pressure']) * scale_dis['plasma gas 2 pressure'] + offset_dis['plasma gas 2 pressure']
    plasma_gas_3_pressure = cut_chart_sheet.cell_value(row, collumn_dis['plasma gas 3 pressure']) * scale_dis['plasma gas 3 pressure'] + offset_dis['plasma gas 3 pressure']
    swirl_gas_1_pressure = cut_chart_sheet.cell_value(row, collumn_dis['swirl gas 1 pressure']) * scale_dis['swirl gas 1 pressure'] + offset_dis['swirl gas 1 pressure']
    swirl_gas_2_pressure = cut_chart_sheet.cell_value(row, collumn_dis['swirl gas 2 pressure']) * scale_dis['swirl gas 2 pressure'] + offset_dis['swirl gas 2 pressure']
    cutting_pressure = cut_chart_sheet.cell_value(row, collumn_dis['cutting pressure']) * scale_dis['cutting pressure'] + offset_dis['cutting pressure']
    additional_height = cut_chart_sheet.cell_value(row, collumn_dis['additional height']) * scale_dis['additional height'] + offset_dis['additional height']
    up_slope =cut_chart_sheet.cell_value(row, collumn_dis['up slope']) * scale_dis['up slope'] + offset_dis['up slope']
    down_slope = cut_chart_sheet.cell_value(row, collumn_dis['down slope']) * scale_dis['down slope'] + offset_dis['down slope']
    cutting_speed_speed = 0.0
    cutting_speed_max = 0.0
    cutting_speed_hole = cut_chart_sheet.cell_value(row, collumn_dis['cutting speed hole']) * scale_dis['cutting speed hole'] + offset_dis['cutting speed hole']
    cutting_speed_quality = cut_chart_sheet.cell_value(row, collumn_dis['cutting speed']) * scale_dis['cutting speed'] + offset_dis['cutting speed']
    kerf_hole = cut_chart_sheet.cell_value(row, collumn_dis['kerf hole']) * scale_dis['kerf hole'] + offset_dis['kerf hole']
    kerf_quality = cut_chart_sheet.cell_value(row, collumn_dis['kerf']) * scale_dis['kerf'] + offset_dis['kerf']
    record_number = cut_chart_sheet.cell_value(row, collumn_dis['record number'])
    technology_range = cut_chart_sheet.cell_value(row, collumn_dis['technology range'])
    marking_record = cut_chart_sheet.cell_value(row, collumn_dis['marking record'])

    query = "INSERT INTO KjellbergCuttingData VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    cursor.execute(query, (cutting_chart_id,
                   record_number,
                   material,
                   thickness,
                   current,
                   technology,
                   cathode,
                   gas_guide,
                   nozzle,
                   nozzle_cap,
                   swirl_gas_cap,
                   protection_cap,
                   cooling_tube,
                   swirl_gas_nozzle,
                   special_part,
                   plasma_gas_1,
                   plasma_gas_2,
                   plasma_gas_3,
                   swirl_gas_1,
                   swirl_gas_2,
                   ignition_gas,
                   plasma_gas_1_pressure,
                   plasma_gas_2_pressure,
                   plasma_gas_3_pressure,
                   swirl_gas_1_pressure,
                   swirl_gas_2_pressure,
                   cutting_pressure,
                   ignition_height,
                   cutting_height,
                   pierce_height,
                   pierce_time,
                   cutting_voltage,
                   plasma_off_time,
                   additional_height,
                   up_slope,
                   down_slope,
                   cutting_speed_speed,
                   cutting_speed_max,
                   cutting_speed_hole,
                   cutting_speed_quality,
                   kerf_hole,
                   kerf_quality,
                   gas_code,
                   special_code,
                   marking_record,
                   technology_range))

VendorInitial()
id = LastCuttingChartID() + 1
SystemConfig(id)
Attribute()
KjellbergCuttingChart(id)

connect.commit()
connect.close()
