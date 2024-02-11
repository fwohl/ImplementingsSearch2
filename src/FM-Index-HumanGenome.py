# FM - Index Human Genome Search

# Please remember to adjust the file path in the configuration 
# to match the location of your data on your local computer.

import iv2py as iv
import os
import time

# Create FM-Index
fmindex_path = "file.fmindex"

if os.path.exists(fmindex_path):
    # Load FM index from disk
    index = iv.fmindex(path=fmindex_path)
else:
    # Load FASTA file - normalize sequences (e.g., make everything uppercase, check for invalid characters)
    reference = [iv.normalize(rec.seq) for rec in iv.fasta.reader('hg38_partial.fasta')]

    # Build FM index
    index = iv.fmindex(reference=reference, samplingRate=16)
    index.save(fmindex_path)

# Number of iterations
num_iterations = 100

# List the Human Genome files
genome_files = [
    'GCA_000001405.15_GRCh38_genomic.fna',
    'GCF_000001405.26_GRCh38_genomic.fna'
]

# Dictionary to store total time per file
total_time_per_file = {file: 0 for file in genome_files}

# Function to calculate average time and print results
def calculate_and_print_results(file, reference_text_chunk_size):
    for _ in range(num_iterations):
        # Load Genome file
        genome_file_path = '' + file
        for record in iv.fasta.reader(file=genome_file_path):
            # Consider the specified number of characters in the current sequence
            reference_text_chunk = record.seq[:reference_text_chunk_size]

            # Measure the time for searching in the FM-Index
            start_time = time.time()
            res = index.search(reference_text_chunk)
            end_time = time.time()

            # Accumulate the total time per file
            total_time_per_file[file] += end_time - start_time

    # Calculate the average time per file
    average_time = total_time_per_file[file] / num_iterations
    print(f"Average time for {num_iterations} iterations in {file} ({reference_text_chunk_size} characters): {average_time:.6f} seconds")


# Iterate over different chunk sizes
chunk_sizes = [1000, 10000, 100000, 1000000]

for chunk_size in chunk_sizes:
    for genome_file in genome_files:
        calculate_and_print_results(genome_file, chunk_size)