#By zhanshi

import sys, sqlite3, xlrd

database_name = sys.argv[1]
connect = sqlite3.connect(database_name)
cursor = connect.cursor()

cursor.execute('''
    CREATE TABLE IF NOT EXISTS Vendor(
        ID    INTEGER  PRIMARY KEY AUTOINCREMENT,
        NAME  TEXT             NOT NULL
    )
    ''')

cursor.execute('''
    CREATE TABLE IF NOT EXISTS SystemConfig(
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
    CREATE TABLE IF NOT EXISTS PlasmaPower(
        ID        INTEGER  PRIMARY KEY AUTOINCREMENT,
        MODEL     TEXT             NOT NULL,
        VENDOR_ID INT              NOT NULL,       -- foreign key

        FOREIGN KEY (VENDOR_ID) REFERENCES Vendor(ID)
    )
    ''')

cursor.execute('''
    CREATE TABLE IF NOT EXISTS KjellbergCutChart(
        ID                    INT    NOT NULL,  --切割数据的ID号，可重复
        RECORD_NUMBER         INT    NOT NULL,  --没有具体的数据含义，只是excel中切割数据编号
        MATERIAL              TEXT,             --切割材料
        THICKNESS             REAL,             --钢板厚度，单位为mm
        CUTTING_CURRENT       REAL,             --切割电流，单位为A
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
        IGNITION_GAS_KPA      REAL,             --点火气体压强，单位为kpa
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
    CREATE TABLE IF NOT EXISTS KjellbergAttribute(
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


cursor.execute('''
    CREATE TABLE IF NOT EXISTS HyperthermCutChart(
        ID                     INT  NOT NULL, --切割表ID号，可重复
        TORCH_TYPE             TEXT,          --割枪类型
        MATERIAL_TYPE          TEXT,          --材料类型
        SPECIFIC_MATERIAL      TEXT,          --专用材料
        PROCESS_CURRENT        REAL,          --工艺电流
        PLASMA_SHIELD_GAS      TEXT,          --等离子/保护气体
        CUTTING_SURFACE        INT,           --切割表面
        THICKNESS              REAL,          --板厚
        CUTTING_SPEED          REAL,          --切割速度
        KERF                   REAL,          --割缝
        CREEP_TIME             REAL,          --爬行时间
        CUTTING_VOLTAGE        REAL,          --设置弧压
        PIERCE_TIME            REAL,          --穿孔时间
        PIERCE_HEIGHT          REAL,          --穿孔高度
        CUTTING_HEIGHT         REAL,          --切割高度
        IGNITION_HEIGHT        REAL,          --引弧高度
        CUT_HEIGHT_DELAY       REAL,          --切割高度延时
        PLASMA_MANUAL_PREFLOW  REAL,          --等离子气体手动预流
        SHIELD_MANUAL_PREFLOW  REAL,          --保护气体手动预流
        PLASMA_MANUAL_CUTFLOW  REAL,          --等离子气体手动切割流
        SHIELD_MANUAL_CUTFLOW  REAL,          --保护气体手动切割流
        PLASMA_AUTO_PREFLOW    REAL,          --等离子气体自动预流
        SHIELD_AUTO_PREFLOW    REAL,          --保护气体自动预流
        PLASMA_AUTO_CUTFLOW    REAL,          --等离子气体自动切割流
        SHIELD_AUTO_CUTFLOW    REAL,          --保护气体自动切割流
        MIXED_GAS1             REAL,          --混合气体1
        MIXED_GAS2             REAL,          --混合气体2
        SHIELD_CAP             TEXT,          --外固定帽
        SHIELD                 TEXT,          --保护帽
        NOZZLE_RETAINING_CAP   TEXT,          --内固定帽
        NOZZLE                 TEXT,          --喷嘴
        SWIRL_RING             TEXT,          --涡流环
        ELECTRODE              TEXT,          --电机
        WATER_TUBE             TEXT           --水管

    )
    ''')

def GetVendorID(vendor_name):
  cursor.execute("SELECT ID FROM Vendor WHERE NAME=:name", {"name" : vendor_name})
  return cursor.fetchone()[0]

def GetLastCuttingChartID():
  cursor.execute("SELECT MAX(CUTTING_CHART_ID) FROM SystemConfig")
  list = cursor.fetchone()[0]
  if list == None:
    return 0
  else :
    return list

def AppendVendorInfor(vendor_name):
  cursor.execute("SELECT ID FROM Vendor WHERE NAME=:name", {"name" : vendor_name})
  if cursor.fetchone() == None:
    cursor.execute("INSERT INTO Vendor (NAME) VALUES (:name)", {"name" : vendor_name})

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

xls_file_name = sys.argv[2]
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

    AppendVendorInfor(vendor_name)
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
    ignition_gas_pressure = cut_chart_sheet.cell_value(row, collumn_dis['ignition gas pressure']) * scale_dis['ignition gas pressure'] + offset_dis['ignition gas pressure']
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

    query = "INSERT INTO KjellbergCutChart VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
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
                   ignition_gas_pressure,
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

def HyperthermCuttingChart(cutting_chart_id):
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
    torch_type = cut_chart_sheet.cell_value(row, collumn_dis['torch type'])
    material = cut_chart_sheet.cell_value(row, collumn_dis['material'])
    specific_material = cut_chart_sheet.cell_value(row, collumn_dis['specific material'])
    current = cut_chart_sheet.cell_value(row, collumn_dis['current']) * scale_dis['current'] + offset_dis['current']
    plasma_shield_gas = cut_chart_sheet.cell_value(row, collumn_dis['plasma/shield gas'])
    cutting_surface = cut_chart_sheet.cell_value(row, collumn_dis['cutting surface'])
    thickness = cut_chart_sheet.cell_value(row, collumn_dis['thickness']) * scale_dis['thickness'] + offset_dis['thickness']
    cutting_speed = cut_chart_sheet.cell_value(row, collumn_dis['cutting speed']) * scale_dis['cutting speed'] + offset_dis['cutting speed']
    kerf = cut_chart_sheet.cell_value(row, collumn_dis['kerf']) * scale_dis['kerf'] + offset_dis['kerf']
    creep_time = cut_chart_sheet.cell_value(row, collumn_dis['creep time']) * scale_dis['creep time'] + offset_dis['creep time']
    cutting_voltage = cut_chart_sheet.cell_value(row, collumn_dis['cutting voltage']) * scale_dis['cutting voltage'] + offset_dis['cutting voltage']
    pierce_time = cut_chart_sheet.cell_value(row, collumn_dis['pierce time']) * scale_dis['pierce time'] + offset_dis['pierce time']
    pierce_height = cut_chart_sheet.cell_value(row, collumn_dis['pierce height']) * scale_dis['pierce height'] + offset_dis['pierce height']
    cutting_height = cut_chart_sheet.cell_value(row, collumn_dis['cutting height']) * scale_dis['cutting height'] + offset_dis['cutting height']
    ignition_height = cut_chart_sheet.cell_value(row, collumn_dis['ignition height']) * scale_dis['ignition height'] + offset_dis['ignition height']
    cut_height_delay = cut_chart_sheet.cell_value(row, collumn_dis['cut height delay']) * scale_dis['cut height delay'] + offset_dis['cut height delay']
    plasma_manual_preflow = cut_chart_sheet.cell_value(row, collumn_dis['plasma manual preflow']) * scale_dis['plasma manual preflow'] + offset_dis['plasma manual preflow']
    shield_manual_preflow = cut_chart_sheet.cell_value(row, collumn_dis['shield manual preflow']) * scale_dis['shield manual preflow'] + offset_dis['shield manual preflow']
    plasma_manual_cutflow = cut_chart_sheet.cell_value(row, collumn_dis['plasma manual cutflow']) * scale_dis['plasma manual cutflow'] + offset_dis['plasma manual cutflow']
    shield_manual_cutflow = cut_chart_sheet.cell_value(row, collumn_dis['shield manual cutflow']) * scale_dis['shield manual cutflow'] + offset_dis['shield manual cutflow']
    plasma_auto_preflow = cut_chart_sheet.cell_value(row, collumn_dis['plasma auto preflow']) * scale_dis['plasma auto preflow'] + offset_dis['plasma auto preflow']
    shield_auto_preflow = cut_chart_sheet.cell_value(row, collumn_dis['shield auto preflow']) * scale_dis['shield auto preflow'] + offset_dis['shield auto preflow']
    plasma_auto_cutflow = cut_chart_sheet.cell_value(row, collumn_dis['plasma auto cutflow']) * scale_dis['plasma auto cutflow'] + offset_dis['plasma auto cutflow']
    shield_auto_cutflow = cut_chart_sheet.cell_value(row, collumn_dis['shield auto cutflow']) * scale_dis['shield auto cutflow'] + offset_dis['shield auto cutflow']
    mixed_gas1 = cut_chart_sheet.cell_value(row, collumn_dis['mixed gas1']) * scale_dis['mixed gas1'] + offset_dis['mixed gas1']
    mixed_gas2 = cut_chart_sheet.cell_value(row, collumn_dis['mixed gas2']) * scale_dis['mixed gas2'] + offset_dis['mixed gas2']
    shield_cap = cut_chart_sheet.cell_value(row, collumn_dis['shield cap'])
    shield = cut_chart_sheet.cell_value(row, collumn_dis['shield'])
    nozzle_retaining_cap = cut_chart_sheet.cell_value(row, collumn_dis['nozzle retaining cap'])
    nozzle = cut_chart_sheet.cell_value(row, collumn_dis['nozzle'])
    swirl_ring = cut_chart_sheet.cell_value(row, collumn_dis['swirl ring'])
    electrode = cut_chart_sheet.cell_value(row, collumn_dis['electrode'])
    water_tube = cut_chart_sheet.cell_value(row, collumn_dis['water tube'])

    query = "INSERT INTO HyperthermCutChart VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    cursor.execute(query, (cutting_chart_id,
                   torch_type,
                   material,
                   specific_material,
                   current,
                   plasma_shield_gas,
                   cutting_surface,
                   thickness,
                   cutting_speed,
                   kerf,
                   creep_time,
                   cutting_voltage,
                   pierce_time,
                   pierce_height,
                   cutting_height,
                   ignition_height,
                   cut_height_delay,
                   plasma_manual_preflow,
                   shield_manual_preflow,
                   plasma_manual_cutflow,
                   shield_manual_cutflow,
                   plasma_auto_preflow,
                   shield_auto_preflow,
                   plasma_auto_cutflow,
                   shield_auto_cutflow,
                   mixed_gas1,
                   mixed_gas2,
                   shield_cap,
                   shield,
                   nozzle_retaining_cap,
                   nozzle,
                   swirl_ring,
                   electrode,
                   water_tube))


id = GetLastCuttingChartID() + 1
SystemConfig(id)
Attribute()
KjellbergCuttingChart(id)

connect.commit()
connect.close()
