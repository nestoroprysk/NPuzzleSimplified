import os

for i in range(100):
    print ('[' + str(400 + i + 1) + '/700]')
    os.system('python generator.py -u 4 > test.txt')
    os.system('../Build/Run -f ../GeneratorTestsRunner/test.txt -v result -o result.txt')
