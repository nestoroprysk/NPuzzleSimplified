import os

for i in range(100):
    print ('[' + str(600 + i + 1) + '/700]')
    os.system('python generator.py -u 6 > test.txt')
    os.system('../Build/Run -f ../GeneratorTestsRunner/test.txt -v result -o result.txt')
