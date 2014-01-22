#!/usr/bin/env python

import math
import random
import argparse
import os
import tempfile

NPOINTS  = random.randint(10,50)
NFILES   = 50

parser = argparse.ArgumentParser(description='Generate lots of files with random points')
parser.add_argument('-o', dest='outdir', action='store',
                   help='output directory')
parser.add_argument("--float", help="With float numbers",action="store_true")

args = parser.parse_args()

for fnum in xrange(NFILES):
    filename = os.path.join(args.outdir,"pcloud%s.dat"%fnum)
    with open(filename,"w") as fd:
        for i in range(NPOINTS):
            if args.float:
                x = random.random() 
                y = random.random() 
            else:
                x = random.randint(-100,100) 
                y = random.randint(-100,100) 
            fd.write("%s %s\n"%(x,y))
