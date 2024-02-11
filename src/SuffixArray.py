# Suffix Array Implementation

# To initialize
# pip install iv2py
# Please readjust your config in the file path = ''

import iv2py as iv
import time

# Read the reference sequence from the FASTA file
fasta_file_path = 'hg38_partial.fasta'
reference = "".join(str(record.seq) for record in iv.fasta.reader(file=fasta_file_path))

# Create a suffix array from the reference sequence
sa = iv.create_suffixarray(reference)

# Number of iterations
num_iterations = 100

# List the Illumina files
illumina_files = [
    'illumina_reads_100.fasta',
    'illumina_reads_40.fasta',
    'illumina_reads_60.fasta',
    'illumina_reads_80.fasta'
]

# Dictionary to store total time per file
total_time_per_file = {file: 0 for file in illumina_files}

# Perform search for different chunk sizes
chunk_sizes = [1000, 10000, 100000, 1000000]

for chunk_size in chunk_sizes:
    for illumina_file in illumina_files:
        for _ in range(num_iterations):
            # Load Illumina file
            illumina_file_path = '' + illumina_file
            for record in iv.fasta.reader(file=illumina_file_path):
                # Consider the specified number of characters in the current sequence as the query
                query_string = record.seq[:chunk_size]

                # Perform the search in the suffix array
                start_time = time.time()

                # Simple substring search using the suffix array
                match_positions = [pos for pos in sa if record.seq[pos:].startswith(query_string)]

                end_time = time.time()

                # Accumulate the total time per file
                total_time_per_file[illumina_file] += end_time - start_time

# Calculate the average time per file
average_time_per_file = {file: total_time / num_iterations for file, total_time in total_time_per_file.items()}

# Print the results
for file, average_time in average_time_per_file.items():
    print(f"Average time for {num_iterations} iterations in {file}: {average_time:.6f} seconds")
