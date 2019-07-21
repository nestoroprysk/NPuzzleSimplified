import os

for i in range(100):
    print ('[' + (500 + str(i)) + '/800]', end = '')
    os.system('python generator.py -u 4 > test.txt')
    os.system('../Build/Run -f ../GeneratorTestsRunner/test.txt -v result -o result.txt')
