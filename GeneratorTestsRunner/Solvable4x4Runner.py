import os

for i in range(100):
    print ('[' + (100 + str(i)) + '/800]', end = '') 
    os.system('python generator.py -s 4 > test.txt')
    os.system('../Build/Run -f ../GeneratorTestsRunner/test.txt -v result -o result.txt -gc 0')
