import re

def convert_code(code):
    code = code.rstrip()
    code = re.sub(r'w\((\d+)\)', lambda m: f'w[{int(m.group(1))-1}]', code)
    #code = re.sub(r'(\w+)\*\*(\S+)', r'std::pow(\1, \2)', code)
    code = code.replace('&', '')
    #code = re.sub(r'$', ';', code, flags=re.MULTILINE)
    
    if code.strip() == '':
        return ''
    return code + ';\n'

cpp_file = open('Me.txt', 'w')
for line in open('Me.f').readlines():
    cpp_file.write(convert_code(line))