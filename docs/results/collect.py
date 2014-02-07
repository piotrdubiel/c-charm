from glob import glob

for result in glob('mushroom/ascending/*.txt'):
    s = 0.0
    c=0
    with open(result) as f:
        for line in f:
            if 'Finding close sets...' in line:
                #print line.split('\t')[-1]
                s += float(line.split('\t')[-1][:-2])
                c += 1

        print s / c
