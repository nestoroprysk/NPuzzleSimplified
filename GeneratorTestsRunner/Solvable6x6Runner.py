import os

for i in range(100):
    print ('[' + str(300 + i) + '/800]')
    os.system('python generator.py -s 6 > test.txt')
    os.system('../Build/Run -f ../GeneratorTestsRunner/test.txt -v result -o result.txt -gc 0')
