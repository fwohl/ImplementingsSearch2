#use like this: "python naivesearch3.py"
#with the data being in the same folder as the python file


import iv2py as iv
import gzip
import time 
from memory_profiler import profile

def search(pat, txt):
    M = len(pat)
    N = len(txt)

    # A loop to slide pat[] one by one */
    for i in range(N - M + 1):
        j = 0

        # For current index i, check
        # for pattern match */
        while(j < M):
            if (txt[i + j] != pat[j]):
                break
            j += 1

        #if (j == M):
            #print("Pattern of query ", ii, "found at index ", i)


time_start = time.perf_counter()
ii=0
#for reference in iv.fasta.reader(file='../data/hg38_partial.fasta.gz'):
#    print("reference length:",len(reference))

for query in iv.fasta.reader(file='../data/illumina_reads_40.fasta.gz'):
    if(ii>100000):
        break
    if(ii==1000000):
        time_end = time.perf_counter()
        time_duration = time_end - time_start
        print(f'Took {time_duration:.3f} seconds for 1,000,000 queries of length 100')
    if(ii==100000):
        time_end = time.perf_counter()
        time_duration = time_end - time_start
        print(f'Took {time_duration:.3f} seconds for 100,000 queries of length 100')
    if(ii==10000):
        time_end = time.perf_counter()
        time_duration = time_end - time_start
        print(f'Took {time_duration:.3f} seconds for 10,000 queries of length 100')
    if(ii==100):
        time_end = time.perf_counter()
        time_duration = time_end - time_start
        print(f'Took {time_duration:.3f} seconds for 1,000 queries of length 100')
    for reference in iv.fasta.reader(file='../data/hg38_partial.fasta.gz'):
        search(query.seq,reference.seq)
    ii+=1



