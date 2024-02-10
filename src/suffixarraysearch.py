#use like this: "python suffixarraysearch2.py"
#with the data being in the same folder as the python file

import iv2py as iv
import gzip
import time 

def SuffixArray(txt):
	n=len(txt)
	print(n)
	suffixes=[]
	for i in range(n):
		suffixes.append(txt[i:])
	suffixes.sort()
	suffArr = [txt.index(suffix) for suffix in suffixes]
	return suffArr



def suffixarraysearch(pattern, txt, sa):
	n=len(txt)
	m = len(pattern)
	l = 0
	r = n-1
	while l <= r:
		mid = l + (r - l)//2
		res = txt[sa[mid]:sa[mid]+m]
		if res == pattern:
			#print("Pattern of query ", ii, "found at index ", sa[mid])
			return
		if res < pattern:
			l = mid + 1
		else:
			r = mid - 1
print("start")
time_start = time.perf_counter()
for reference in iv.fasta.reader(file='../data/hg38_partial.fasta.gz'):
	sa=iv.create_suffixarray(reference.seq)
time_end = time.perf_counter()
time_duration = time_end - time_start
print(f'Took {time_duration:.3f} seconds for suffixarrayconstruction')

#print(sa)
time_start = time.perf_counter()
ii=0

with open ('runtime_python.txt', 'w') as f:
    time_end0=time.perf_counter()
    timedur=time_end0-time_start
    #f.write("start: ")
    #f.write(str(timedur))
    for query in iv.fasta.reader(file='../data/illumina_reads_100.fasta.gz'):
        if(ii>1000000):
            break
        if(ii==1000000):
            time_end = time.perf_counter()
            time_duration = time_end - time_start
            f.write("time for 1 000 000 queries: ")
            f.write(str(time_duration))
            f.write("ms\n")
            print(f'Took {time_duration:.3f} seconds for 1,000,000 queries of length 100')
        if(ii==100000):
            time_end = time.perf_counter()
            time_duration1 = time_end - time_start
            f.write("time for 100 000 queries: ")
            f.write(str(time_duration1))
            f.write("ms\n")
            print(f'Took {time_duration1:.3f} seconds for 100,000 queries of length 100')
            time_start = time.perf_counter()
        if(ii==10000):
            time_end = time.perf_counter()
            time_duration2 = time_end - time_start
            f.write("time for 10000 queries: ")
            f.write(str(time_duration2))
            f.write("ms\n")
            print(f'Took {time_duration2:.3f} seconds for 10,000 queries of length 100')
            time_start = time.perf_counter()
        if(ii==1000):
            time_end = time.perf_counter()
            time_duration3 = time_end - time_start
            f.write("time for 1000 queries: ")
            f.write(str(time_duration3))
            f.write("ms\n")
            print(f'Took {time_duration3:.3f} seconds for 1,000 queries of length 100')
            time_start = time.perf_counter()
        for reference in iv.fasta.reader(file='../data/hg38_partial.fasta.gz'):
            suffixarraysearch(query.seq,reference.seq,sa)
        ii+=1



f.close()

#print(f'Took {time_duration3:.3f} seconds for 1,000 queries of length 100')
#print(f'Took {time_duration2:.3f} seconds for 10,000 queries of length 100')
#print(f'Took {time_duration1:.3f} seconds for 100,000 queries of length 100')
#print(f'Took {time_duration:.3f} seconds for 1,000,000 queries of length 100')
