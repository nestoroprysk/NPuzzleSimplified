f = open("result.txt", "r")

correct = 0
read = 0

while True:
    line = f.readline()
    if not line:
        break
    read += 1
    if line.find('[ok]') != -1:
        correct += 1

print '[' + str(correct) + '/' + str(read) + ']'
