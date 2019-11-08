import io

fn = 'bindings/_core.cpp'
line = b'\tbind_ecvl_functions(M("ecvl"));\n'

with io.open(fn, 'rb') as f:
    data = f.read()
data = data.replace(line, b'')
data = data.replace(
    b'}\n\n\n#include <map>',
    b'%s}\n\n\n#include <map>' % line
)
with io.open(fn, 'wb') as f:
    f.write(data)
