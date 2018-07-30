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
        FIELD_NAME           TEXT    NOT NULL,
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
        DISPLAY_GROUP        INT

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
    cursor.execute("INSERT INTO KjellbergAttribute VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
                   (attribute_sheet.cell_value(row, titles['Name']),
                    attribute_sheet.cell_value(row, titles['Keyword']),
                    attribute_sheet.cell_value(row, titles['DataType']),
                    attribute_sheet.cell_value(row, titles['NameText']),
                    attribute_sheet.cell_value(row, titles['UnitText']),
                    attribute_sheet.cell_value(row, titles['Min']),
                    attribute_sheet.cell_value(row, titles['Max']),
                    attribute_sheet.cell_value(row, titles['Default']),
                    attribute_sheet.cell_value(row, titles['DisplayFormat']),
                    attribute_sheet.cell_value(row, titles['WR']),
                    attribute_sheet.cell_value(row, titles['AliasIndex']),
                    attribute_sheet.cell_value(row, titles['Picture']),
                    attribute_sheet.cell_value(row, titles['Group'])))

def KjellbergCutChart(cutting_chart_id):
  "Insert cutting data into CuttingData table. This Cutting chart id will be defined with cutting_chart_id"
  titles = {}
  title_row = int(attribute_sheet.cell_value(0, 0))
  for col in range(0, attribute_sheet.ncols):
    titles[attribute_sheet.cell_value(title_row - 1, col)] = col

  column_dis = {}
  scale_dis = {}
  offset_dis = {}
  for row in range(title_row, attribute_sheet.nrows):
    column_dis[attribute_sheet.cell_value(row, titles['Name'])] = int(attribute_sheet.cell_value(row, titles['Column'])) -1
    scale_dis[attribute_sheet.cell_value(row, titles['Name'])] = attribute_sheet.cell_value(row, titles['Scale'])
    offset_dis[attribute_sheet.cell_value(row, titles['Name'])] = attribute_sheet.cell_value(row, titles['Offset'])

  start_row = int(attribute_sheet.cell_value(0, 1))
  for row in range(start_row - 1, cut_chart_sheet.nrows):
    material = cut_chart_sheet.cell_value(row, column_dis['Material'])
    thickness = cut_chart_sheet.cell_value(row, column_dis['Thickness']) * scale_dis['Thickness'] + offset_dis['Thickness']
    current = cut_chart_sheet.cell_value(row, column_dis['Current']) * scale_dis['Current'] + offset_dis['Current']
    technology = cut_chart_sheet.cell_value(row, column_dis['Technology'])
    ignition_height = cut_chart_sheet.cell_value(row, column_dis['IgnitionHeight']) * scale_dis['IgnitionHeight'] + offset_dis['IgnitionHeight']
    cutting_height = cut_chart_sheet.cell_value(row, column_dis['CuttingHeight']) * scale_dis['CuttingHeight'] + offset_dis['CuttingHeight']
    pierce_height = cut_chart_sheet.cell_value(row, column_dis['PierceHeight']) * scale_dis['PierceHeight'] + offset_dis['PierceHeight']
    pierce_time = cut_chart_sheet.cell_value(row, column_dis['PierceTime']) * scale_dis['PierceTime'] + offset_dis['PierceTime']
    cutting_voltage = cut_chart_sheet.cell_value(row, column_dis['CuttingVoltage']) * scale_dis['CuttingVoltage'] + offset_dis['CuttingVoltage']
    plasma_off_time = cut_chart_sheet.cell_value(row, column_dis['PlasmaOffTime']) * scale_dis['PlasmaOffTime'] + offset_dis['PlasmaOffTime']
    cooling_tube = cut_chart_sheet.cell_value(row, column_dis['CoolingTube'])
    cathode = cut_chart_sheet.cell_value(row, column_dis['Cathode'])
    gas_guide = cut_chart_sheet.cell_value(row, column_dis['GasGuide'])
    nozzle = cut_chart_sheet.cell_value(row, column_dis['Nozzle'])
    nozzle_cap = cut_chart_sheet.cell_value(row, column_dis['NozzleCap'])
    swirl_gas_cap = cut_chart_sheet.cell_value(row, column_dis['SwirlGasCap'])
    protection_cap = cut_chart_sheet.cell_value(row, column_dis['ProtectionCap'])
    swirl_gas_nozzle = cut_chart_sheet.cell_value(row, column_dis['SwirlGasNozzle'])
    special_part = ''
    plasma_gas_1 = cut_chart_sheet.cell_value(row, column_dis['PlasmaGas1'])
    plasma_gas_2 = cut_chart_sheet.cell_value(row, column_dis['PlasmaGas2'])
    plasma_gas_3 = cut_chart_sheet.cell_value(row, column_dis['PlasmaGas3'])
    swirl_gas_1 = cut_chart_sheet.cell_value(row, column_dis['Swirlgas1'])
    swirl_gas_2 = cut_chart_sheet.cell_value(row, column_dis['SwirlGas 2'])
    ignition_gas = cut_chart_sheet.cell_value(row, column_dis['IgnitionGas'])
    gas_code = cut_chart_sheet.cell_value(row, column_dis['GasCode'])
    special_code = cut_chart_sheet.cell_value(row, column_dis['SpecialCode'])
    plasma_gas_1_pressure = cut_chart_sheet.cell_value(row, column_dis['PlasmaGas1Pressure']) * scale_dis['PlasmaGas1Pressure'] + offset_dis['PlasmaGas1Pressure']
    plasma_gas_2_pressure = cut_chart_sheet.cell_value(row, column_dis['PlasmaGas2Pressure']) * scale_dis['PlasmaGas2Pressure'] + offset_dis['PlasmaGas2Pressure']
    plasma_gas_3_pressure = cut_chart_sheet.cell_value(row, column_dis['PlasmaGas3Pressure']) * scale_dis['PlasmaGas3Pressure'] + offset_dis['PlasmaGas3Pressure']
    swirl_gas_1_pressure = cut_chart_sheet.cell_value(row, column_dis['SwirlGas1Pressure']) * scale_dis['SwirlGas1pressure'] + offset_dis['SwirlGas1pressure']
    swirl_gas_2_pressure = cut_chart_sheet.cell_value(row, column_dis['SwirlGas2pressure']) * scale_dis['SwirlGas2pressure'] + offset_dis['SwirlGas2pressure']
    ignition_gas_pressure = cut_chart_sheet.cell_value(row, column_dis['IgnitionGasPressure']) * scale_dis['IgnitionGasPressure'] + offset_dis['IgnitionGasPressure']
    cutting_pressure = cut_chart_sheet.cell_value(row, column_dis['CuttingPressure']) * scale_dis['CuttingPressure'] + offset_dis['CuttingPressure']
    additional_height = cut_chart_sheet.cell_value(row, column_dis['AdditionalHeight']) * scale_dis['AdditionalHeight'] + offset_dis['AdditionalHeight']
    up_slope =cut_chart_sheet.cell_value(row, column_dis['UpSlope']) * scale_dis['UpSlope'] + offset_dis['UpSlope']
    down_slope = cut_chart_sheet.cell_value(row, column_dis['DownSlope']) * scale_dis['DownSlope'] + offset_dis['DownSlope']
    cutting_speed_speed = 0.0
    cutting_speed_max = 0.0
    cutting_speed_hole = cut_chart_sheet.cell_value(row, column_dis['CuttingSpeedHole']) * scale_dis['CuttingSpeedHole'] + offset_dis['CuttingSpeedHole']
    cutting_speed_quality = cut_chart_sheet.cell_value(row, column_dis['CuttingSpeed']) * scale_dis['CuttingSpeed'] + offset_dis['CuttingSpeed']
    kerf_hole = cut_chart_sheet.cell_value(row, column_dis['KerfHole']) * scale_dis['KerfHole'] + offset_dis['KerfHole']
    Kerf_quality = cut_chart_sheet.cell_value(row, column_dis['Kerf']) * scale_dis['Kerf'] + offset_dis['Kerf']
    record_number = cut_chart_sheet.cell_value(row, column_dis['RecordNumber'])
    technology_range = cut_chart_sheet.cell_value(row, column_dis['TechnologyRange'])
    marking_record = cut_chart_sheet.cell_value(row, column_dis['MarkingRecord'])

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

def HyperthermCutChart(cutting_chart_id):
  titles = {}
  title_row = int(attribute_sheet.cell_value(0, 0))
  for col in range(0, attribute_sheet.ncols):
    titles[attribute_sheet.cell_value(title_row - 1, col)] = col

  column_dis = {}
  scale_dis = {}
  offset_dis = {}
  for row in range(title_row, attribute_sheet.nrows):
    column_dis[attribute_sheet.cell_value(row, titles['Name'])] = int(attribute_sheet.cell_value(row, titles['Column'])) -1
    scale_dis[attribute_sheet.cell_value(row, titles['Name'])] = attribute_sheet.cell_value(row, titles['Scale'])
    offset_dis[attribute_sheet.cell_value(row, titles['Name'])] = attribute_sheet.cell_value(row, titles['Offset'])

  start_row = int(attribute_sheet.cell_value(0, 1))
  for row in range(start_row - 1, cut_chart_sheet.nrows):
    torch_type = cut_chart_sheet.cell_value(row, column_dis['TorchType'])
    material = cut_chart_sheet.cell_value(row, column_dis['Material'])
    specific_material = cut_chart_sheet.cell_value(row, column_dis['SpecificMaterial'])
    current = cut_chart_sheet.cell_value(row, column_dis['Current']) * scale_dis['Current'] + offset_dis['Current']
    plasma_shield_gas = cut_chart_sheet.cell_value(row, column_dis['GasType'])
    cutting_surface = cut_chart_sheet.cell_value(row, column_dis['CuttingSurface'])
    thickness = cut_chart_sheet.cell_value(row, column_dis['Thickness']) * scale_dis['Thickness'] + offset_dis['Thickness']
    cutting_speed = cut_chart_sheet.cell_value(row, column_dis['CuttingSpeed']) * scale_dis['CuttingSpeed'] + offset_dis['CuttingSpeed']
    kerf = cut_chart_sheet.cell_value(row, column_dis['Kerf']) * scale_dis['Kerf'] + offset_dis['Kerf']
    creep_time = cut_chart_sheet.cell_value(row, column_dis['CreepTime']) * scale_dis['CreepTime'] + offset_dis['CreepTime']
    cutting_voltage = cut_chart_sheet.cell_value(row, column_dis['CuttingVoltage']) * scale_dis['CuttingVoltage'] + offset_dis['CuttingVoltage']
    pierce_time = cut_chart_sheet.cell_value(row, column_dis['PierceTime']) * scale_dis['PierceTime'] + offset_dis['PierceTime']
    pierce_height = cut_chart_sheet.cell_value(row, column_dis['PierceHeight']) * scale_dis['PierceHeight'] + offset_dis['PierceHeight']
    cutting_height = cut_chart_sheet.cell_value(row, column_dis['CuttingHeight']) * scale_dis['CuttingHeight'] + offset_dis['CuttingHeight']
    ignition_height = cut_chart_sheet.cell_value(row, column_dis['IgnitionHeight']) * scale_dis['IgnitionHeight'] + offset_dis['IgnitionHeight']
    cut_height_delay = cut_chart_sheet.cell_value(row, column_dis['CutHeightDelay']) * scale_dis['CutHeightDelay'] + offset_dis['CutHeightDelay']
    plasma_manual_preflow = cut_chart_sheet.cell_value(row, column_dis['PlasmaManualPreflow']) * scale_dis['PlasmaManualPreflow'] + offset_dis['PlasmaManualPreflow']
    shield_manual_preflow = cut_chart_sheet.cell_value(row, column_dis['ShieldManualPreflow']) * scale_dis['ShieldManualPreflow'] + offset_dis['ShieldManualPreflow']
    plasma_manual_cutflow = cut_chart_sheet.cell_value(row, column_dis['PlasmaManualCutflow']) * scale_dis['PlasmaManualCutflow'] + offset_dis['PlasmaManualCutflow']
    shield_manual_cutflow = cut_chart_sheet.cell_value(row, column_dis['ShieldManualCutflow']) * scale_dis['ShieldManualCutflow'] + offset_dis['ShieldManualCutflow']
    plasma_auto_preflow = cut_chart_sheet.cell_value(row, column_dis['PlasmaAutoPreflow']) * scale_dis['PlasmaAutoPreflow'] + offset_dis['PlasmaAutoPreflow']
    shield_auto_preflow = cut_chart_sheet.cell_value(row, column_dis['ShieldAutoPreflow']) * scale_dis['ShieldAutoPreflow'] + offset_dis['ShieldAutoPreflow']
    plasma_auto_cutflow = cut_chart_sheet.cell_value(row, column_dis['PlasmaAutoCutflow']) * scale_dis['PlasmaAutoCutflow'] + offset_dis['PlasmaAutoCutflow']
    shield_auto_cutflow = cut_chart_sheet.cell_value(row, column_dis['ShieldAutoCutflow']) * scale_dis['ShieldAutoCutflow'] + offset_dis['ShieldAutoCutflow']
    mixed_gas1 = cut_chart_sheet.cell_value(row, column_dis['MixedGas1']) * scale_dis['MixedGas1'] + offset_dis['MixedGas1']
    mixed_gas2 = cut_chart_sheet.cell_value(row, column_dis['MixedGas2']) * scale_dis['MixedGas2'] + offset_dis['MixedGas2']
    shield_cap = cut_chart_sheet.cell_value(row, column_dis['ShieldCap'])
    shield = cut_chart_sheet.cell_value(row, column_dis['Shield'])
    nozzle_retaining_cap = cut_chart_sheet.cell_value(row, column_dis['NozzleRetainingCap'])
    nozzle = cut_chart_sheet.cell_value(row, column_dis['Nozzle'])
    swirl_ring = cut_chart_sheet.cell_value(row, column_dis['SwirlRing'])
    electrode = cut_chart_sheet.cell_value(row, column_dis['Electrode'])
    water_tube = cut_chart_sheet.cell_value(row, column_dis['WaterTube'])

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
KjellbergCutChart(id)

connect.commit()
connect.close()
