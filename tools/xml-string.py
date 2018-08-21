#By zhanshi

import glob
import os
import re
import sys

def Parse(name, str):
  pattern = re.compile(name + r'\s*=\s*"(.*?)"')
  splits = pattern.findall(str)
  raw_strings = []
  for s in splits:
    if len(s.strip()) != 0:
      raw_strings.append(s.strip())

  return raw_strings

def ParseDisplayName(str):
  pattern = re.compile(r'__DisplayName\s*=\s*"(.*?)"')
  splits = pattern.findall(str)
  raw_strings = []
  for s in splits:
    if len(s.strip()) != 0:
      raw_strings.append(s.strip())

  return raw_strings

'''
   Usage:
   argv[0]: xml-string
   argv[1]: scan path
   argv[2]: output file
'''
if __name__ == '__main__':
  if len(sys.argv) != 3:
    print('Usage example: xml-string.py ./ translate_zh.ts')
    sys.exit(1)

  scan_path = sys.argv[1]
  trans_file = sys.argv[2]

  origin = []

  ''' Read from translate_zh.ts. '''
  if (os.path.exits(trans_file)):
    origin = GetOrrigin(trans_file)

  ''' Process xml file. '''
  strings = Process()
  non_duped = set(string)

  with open(trans_file, 'w', encoding="utf-8") as out:
    out.write('''<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="zh_CN">
<context>
    <name></name>
  ''')
     for i in range(0, len(origin), 2):
      out.write('    <message>\n')
      out.write('        <source>{0}</source>\n'.format(origin[i]))
      out.write('        <translation>{0}</translation>\n'.format(origin[i + 1]))
      out.write('    </message>\n')

    for str in non_duped:
      if str not in origin:
        out.write('    <message>\n')
        out.write('        <source>{0}</source>\n'.format(str))
        out.write('        <translation type="unfinished"></translation>\n')
        out.write('    </message>\n')
      else:
        print("Exist: {0}".format(str))

    out.write('''</context>
</TS>
''')
