import os

for i in range(100):
    print ('[' + (400 + str(i)) + '/800]', end = '')
    os.system('python generator.py -u 3 > test.txt')
    os.system('../Build/Run -f ../GeneratorTestsRunner/test.txt -v result -o result.txt')
