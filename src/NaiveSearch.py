# Initilize if needed with pip install iv2py

import iv2py as iv
import time

def naive_search(text, pattern):
    positions = []
    m, n = len(pattern), len(text)

    for i in range(n - m + 1):
        if text[i] == pattern[0] and text[i:i + m] == pattern:
            positions.append(i)

    return positions

fasta_file_path = 'hg38_partial.fasta'
reference = "".join(str(record.seq) for record in iv.fasta.reader(file=fasta_file_path))

num_iterations = 100
illumina_files = [
    'illumina_reads_40.fasta',
    'illumina_reads_60.fasta',
    'illumina_reads_80.fasta',
    'illumina_reads_100.fasta'
]

total_time_per_file = {file: 0 for file in illumina_files}

chunk_sizes = [1000]

for chunk_size in chunk_sizes:
    for illumina_file in illumina_files:
        illumina_file_path = '' + illumina_file
        for _ in range(num_iterations):
            for record in iv.fasta.reader(file=illumina_file_path):
                query_string = record.seq[:chunk_size]
                start_time = time.time()

                # Optimized Naive substring search
                match_positions = naive_search(reference, query_string)

                end_time = time.time()
                total_time_per_file[illumina_file] += end_time - start_time

average_time_per_file = {file: total_time / num_iterations for file, total_time in total_time_per_file.items()}

for file, average_time in average_time_per_file.items():
    print(f"Average time for {num_iterations} iterations in {file}: {average_time:.6f} seconds")